/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander/Ian Craggs - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "MQTTClient.h"
//#include "paho_timer.h"

static void NewMessageData(MessageData* md, MQTTString* aTopicName, MQTTMessage* aMessage) {
    md->topicName = aTopicName;
    md->message = aMessage;
}


static int getNextPacketId(MQTTClient *c) {
    return c->next_packetid = (c->next_packetid == MAX_PACKET_ID) ? 1 : c->next_packetid + 1;
}


static int sendPacket(MQTTClient* c, int length, Timer* timer)
{
    int rc = MQTT_FAILURE, 
        sent = 0;
    
    while (sent < length && !TimerIsExpired(timer))
    {
        rc = c->ipstack->mqttwrite(c->ipstack, &c->buf[sent], length, TimerLeftMS(timer));
        if (rc < 0)  // there was an error writing the data
            break;
        sent += rc;
    }
    if (sent == length)
    {
        TimerCountdown(&c->ping_timer, c->keepAliveInterval); // record the fact that we have successfully sent the packet
        rc = MQTT_SUCCESS;
    }
    else
        rc = MQTT_FAILURE;
    return rc;
}


void MQTTClientInit(MQTTClient* c, Network* network, unsigned int command_timeout_ms,
		unsigned char* sendbuf, size_t sendbuf_size, unsigned char* readbuf, size_t readbuf_size)
{
    int i;
    c->ipstack = network;
    
    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
        c->messageHandlers[i].topicFilter = 0;
    c->command_timeout_ms = command_timeout_ms;
    c->buf = sendbuf;
    c->buf_size = sendbuf_size;
    c->readbuf = readbuf;
    c->readbuf_size = readbuf_size;
    c->isconnected = 0;
	c->connAckReceived = 0;
	c->subAckReceived = 0;
	c->unsubAckReceived = 0;
	c->pubAckReceived = 0;
	c->pubCompReceived = 0;
    c->ping_outstanding = 0;
    c->defaultMessageHandler = NULL;
	c->userData = NULL;
	c->next_packetid = 1;
    TimerInit(&c->ping_timer);
	TimerInit(&c->last_received_timer);
	TimerInit(&c->ping_response_timer);
#if defined(MQTT_TASK)
	MutexInit(&c->mutex);
#endif
}


static int decodePacket(MQTTClient* c, int* value, int timeout)
{
    unsigned char i;
    int multiplier = 1;
    int len = 0;
    const int MAX_NO_OF_REMAINING_LENGTH_BYTES = 4;

    *value = 0;
    do
    {
        int rc = MQTTPACKET_READ_ERROR;

        if (++len > MAX_NO_OF_REMAINING_LENGTH_BYTES)
        {
            rc = MQTTPACKET_READ_ERROR; /* bad data */
            goto exit;
        }
        rc = c->ipstack->mqttread(c->ipstack, &i, 1, timeout);
        if (rc != 1)
            goto exit;
        *value += (i & 127) * multiplier;
        multiplier *= 128;
    } while ((i & 128) != 0);
exit:
    return len;
}


static int readPacket(MQTTClient* c, Timer* timer)
{
    int rc = MQTT_FAILURE;
    MQTTHeader header = {0};
    int len = 0;
    int rem_len = 0;

    /* 1. read the header byte.  This has the packet type in it */
    if (c->ipstack->mqttread(c->ipstack, c->readbuf, 1, TimerLeftMS(timer)) != 1)
        goto exit;

    len = 1;
    /* 2. read the remaining length.  This is variable in itself */
    decodePacket(c, &rem_len, TimerLeftMS(timer));
    len += MQTTPacket_encode(c->readbuf + 1, rem_len); /* put the original remaining length back into the buffer */

    /* 3. read the rest of the buffer using a callback to supply the rest of the data */
    if (rem_len > 0 && (c->ipstack->mqttread(c->ipstack, c->readbuf + len, rem_len, TimerLeftMS(timer)) != rem_len))
        goto exit;

    header.byte = c->readbuf[0];
    rc = header.bits.type;

	if (c->keepAliveInterval > 0) {
		TimerCountdown(&c->last_received_timer, c->keepAliveInterval); // record the fact that we have successfully received a packet
	}
exit:
    return rc;
}


// assume topic filter and name is in correct format
// # can only be at end
// + and # can only be next to separator
static char isTopicMatched(char* topicFilter, MQTTString* topicName)
{
    char* curf = topicFilter;
    char* curn = topicName->lenstring.data;
    char* curn_end = curn + topicName->lenstring.len;
    
    while (*curf && curn < curn_end)
    {
        if (*curn == '/' && *curf != '/')
            break;
        if (*curf != '+' && *curf != '#' && *curf != *curn)
            break;
        if (*curf == '+')
        {   // skip until we meet the next separator, or end of string
            char* nextpos = curn + 1;
            while (nextpos < curn_end && *nextpos != '/')
                nextpos = ++curn + 1;
        }
        else if (*curf == '#')
            curn = curn_end - 1;    // skip until end of string
        curf++;
        curn++;
    };
    
    return (curn == curn_end) && (*curf == '\0');
}


int deliverMessage(MQTTClient* c, MQTTString* topicName, MQTTMessage* message)
{
    int i;
    int rc = MQTT_FAILURE;

    // we have to find the right message handler - indexed by topic
    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
    {
        if (c->messageHandlers[i].topicFilter != 0 && (MQTTPacket_equals(topicName, (char*)c->messageHandlers[i].topicFilter) ||
                isTopicMatched((char*)c->messageHandlers[i].topicFilter, topicName)))
        {
            if (c->messageHandlers[i].fp != NULL)
            {
                MessageData md;
                NewMessageData(&md, topicName, message);
                c->messageHandlers[i].fp(&md, c->userData);
                rc = MQTT_SUCCESS;
            }
        }
    }
    
    if (rc == MQTT_FAILURE && c->defaultMessageHandler != NULL) 
    {
        MessageData md;
        NewMessageData(&md, topicName, message);
        c->defaultMessageHandler(&md, c->userData);
        rc = MQTT_SUCCESS;
    }   
    
    return rc;
}


int keepalive(MQTTClient* c)
{
    int rc = MQTT_FAILURE;

    if (c->keepAliveInterval == 0)
    {
        rc = MQTT_SUCCESS;
        goto exit;
    }

    if (TimerIsExpired(&c->ping_timer) || TimerIsExpired(&c->last_received_timer))
    {
		if (!c->ping_outstanding)
        {
			Timer timer;
            TimerInit(&timer);
            TimerCountdownMS(&timer, 1000);
            int len = MQTTSerialize_pingreq(c->buf, c->buf_size);
			if (len > 0 && (rc = sendPacket(c, len, &timer)) == MQTT_SUCCESS) // send the ping packet
			{
				TimerCountdown(&c->ping_response_timer, c->keepAliveInterval);
				c->ping_outstanding = 1;
			}
        }
		else if (TimerIsExpired(&c->ping_response_timer))
		{
			c->isconnected = 0;
		}
    }

exit:
    return rc;
}


int cycle(MQTTClient* c, Timer* timer)
{
    // read the socket, see what work is due
    unsigned short packet_type = readPacket(c, timer);
    
    int len = 0,
        rc = MQTT_SUCCESS;

    switch (packet_type)
    {
		case CONNACK_MSG:
			c->connAckReceived = 1;
			break;
		case PUBACK_MSG:
			c->pubAckReceived = 1;
			break;
		case SUBACK_MSG:
			c->subAckReceived = 1;
			break;
		case UNSUBACK_MSG:
			c->unsubAckReceived = 1;
			break;
        case PUBLISH_MSG:
        {
            MQTTString topicName;
            MQTTMessage msg;
            int intQoS;
            if (MQTTDeserialize_publish(&msg.dup, &intQoS, &msg.retained, &msg.id, &topicName,
               (unsigned char**)&msg.payload, &msg.payloadlen, c->readbuf, c->readbuf_size) != 1)
                goto exit;
            msg.qos = (enum QoS)intQoS;
            deliverMessage(c, &topicName, &msg);
            if (msg.qos != QOS0)
            {
                if (msg.qos == QOS1)
                    len = MQTTSerialize_ack(c->buf, c->buf_size, PUBACK_MSG, 0, msg.id);
                else if (msg.qos == QOS2)
                    len = MQTTSerialize_ack(c->buf, c->buf_size, PUBREC_MSG, 0, msg.id);
                if (len <= 0)
                    rc = MQTT_FAILURE;
                else
                    rc = sendPacket(c, len, timer);
                if (rc == MQTT_FAILURE)
                    goto exit; // there was a problem
            }
            break;
        }
        case PUBREC_MSG:
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = MQTT_FAILURE;
            else if ((len = MQTTSerialize_ack(c->buf, c->buf_size, PUBREL_MSG, 0, mypacketid)) <= 0)
                rc = MQTT_FAILURE;
            else if ((rc = sendPacket(c, len, timer)) != MQTT_SUCCESS) // send the PUBREL_MSG packet
                rc = MQTT_FAILURE; // there was a problem
            if (rc == MQTT_FAILURE)
                goto exit; // there was a problem
            break;
        }
        case PUBCOMP_MSG:
			c->pubCompReceived = 1;
            break;
        case PINGRESP_MSG:
            c->ping_outstanding = 0;
            break;
    }
    keepalive(c);
exit:
    if (rc == MQTT_SUCCESS)
        rc = packet_type;
    return rc;
}


int MQTTYield(MQTTClient* c, int timeout_ms)
{
    int rc = MQTT_SUCCESS;
    Timer timer;

    TimerInit(&timer);
    TimerCountdownMS(&timer, timeout_ms);

	do
    {
        if (cycle(c, &timer) == MQTT_FAILURE)
        {
            rc = MQTT_FAILURE;
            break;
        }
	} while (!TimerIsExpired(&timer));
        
    return rc;
}


void MQTTRun(void* parm)
{
	Timer timer;
	MQTTClient* c = (MQTTClient*)parm;

	TimerInit(&timer);

	while (1)
	{
#if defined(MQTT_TASK)
		MutexLock(&c->mutex);
#endif
		TimerCountdownMS(&timer, 500); /* Don't wait too long if no traffic is incoming */
		cycle(c, &timer);
#if defined(MQTT_TASK)
		MutexUnlock(&c->mutex);
#endif
	} 
}


#if defined(MQTT_TASK)
int MQTTStartTask(MQTTClient* client)
{
	return ThreadStart(&client->thread, &MQTTRun, client);
}
#endif


int waitfor(MQTTClient* c, int packet_type, Timer* timer)
{
    int rc = MQTT_FAILURE;
    
	// Use bool values to determine if a packet type has been received. This only works if waitfor is 
	// called once at a time per type. However, it can be called with a different type at the same 
	// time, for instance, while waiting for a subscription acknowledgement (SUBACK_MSG) we could 
	// publish a QoS1 message and wait for the acknowledgement (PUBACK_MSG).
	switch (packet_type)
	{
	case CONNACK_MSG:
		c->connAckReceived = 0;
		break;
	case SUBACK_MSG:
		c->subAckReceived = 0;
		break;
	case UNSUBACK_MSG:
		c->unsubAckReceived = 0;
		break;
	case PUBACK_MSG:
		c->pubAckReceived = 0;
		break;
	case PUBCOMP_MSG:
		c->pubCompReceived = 0;
		break;
	}

	do
	{
		switch (packet_type)
		{
		case CONNACK_MSG:
			if (c->connAckReceived) {
				c->connAckReceived = 0;
				return packet_type;
			}
			break;
		case SUBACK_MSG:
			if (c->subAckReceived) {
				c->subAckReceived = 0;
				return packet_type;
			}
			break;
		case UNSUBACK_MSG:
			if (c->unsubAckReceived) {
				c->unsubAckReceived = 0;
				return packet_type;
			}
			break;
		case PUBACK_MSG:
			if (c->pubAckReceived) {
				c->pubAckReceived = 0;
				return packet_type;
			}
			break;
		case PUBCOMP_MSG:
			if (c->pubCompReceived) {
				c->pubCompReceived = 0;
				return packet_type;
			}
			break;
		}
		if (TimerIsExpired(timer))
			break; // we timed out
		cycle(c, timer);
	} while (1);
    
    return rc;
}


int MQTTConnect(MQTTClient* c, MQTTPacket_connectData* options)
{
    Timer connect_timer;
    int rc = MQTT_FAILURE;
    MQTTPacket_connectData default_options = MQTTPacket_connectData_initializer;
    int len = 0;

#if defined(MQTT_TASK)
	MutexLock(&c->mutex);
#endif
	if (c->isconnected) /* don't send connect packet again if we are already connected */
		goto exit;
    
    TimerInit(&connect_timer);
    TimerCountdownMS(&connect_timer, c->command_timeout_ms);

    if (options == 0)
        options = &default_options; /* set default options if none were supplied */
    
    c->keepAliveInterval = options->keepAliveInterval;
	TimerCountdown(&c->ping_timer, c->keepAliveInterval);
    if ((len = MQTTSerialize_connect(c->buf, c->buf_size, options)) <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &connect_timer)) != MQTT_SUCCESS)  // send the connect packet
        goto exit; // there was a problem

    if (c->keepAliveInterval > 0)
    {
        TimerCountdown(&c->last_received_timer, c->keepAliveInterval);
    }

    // this will be a blocking call, wait for the connack
    if (waitfor(c, CONNACK_MSG, &connect_timer) == CONNACK_MSG)
    {
        unsigned char connack_rc = 255;
        unsigned char sessionPresent = 0;
        if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, c->readbuf, c->readbuf_size) == 1)
            rc = connack_rc;
        else
            rc = MQTT_FAILURE;
    }
    else
        rc = MQTT_FAILURE;
    
exit:
    if (rc == MQTT_SUCCESS)
        c->isconnected = 1;

#if defined(MQTT_TASK)
	MutexUnlock(&c->mutex);
#endif

    return rc;
}


int MQTTSubscribe(MQTTClient* c, const char* topicFilter, enum QoS qos, messageHandler messageHandler)
{ 
    int rc = MQTT_FAILURE;  
    Timer timer;
    int len = 0;
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicFilter;
    
#if defined(MQTT_TASK)
	MutexLock(&c->mutex);
#endif
	if (!c->isconnected)
		goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);
    
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"

// Código que genera el warning
   len = MQTTSerialize_subscribe(c->buf, c->buf_size, 0, getNextPacketId(c), 1, &topic, (int*)&qos);


#pragma GCC diagnostic pop

    if (len <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != MQTT_SUCCESS) // send the subscribe packet
        goto exit;             // there was a problem
    
    if (waitfor(c, SUBACK_MSG, &timer) == SUBACK_MSG)      // wait for suback 
    {
        int count = 0, grantedQoS = -1;
        unsigned short mypacketid;
        if (MQTTDeserialize_suback(&mypacketid, 1, &count, &grantedQoS, c->readbuf, c->readbuf_size) == 1)
            rc = grantedQoS; // 0, 1, 2 or 0x80 
        if (rc != 0x80)
        {
            int i;
            for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
            {
                if (c->messageHandlers[i].topicFilter == 0)
                {
                    c->messageHandlers[i].topicFilter = topicFilter;
                    c->messageHandlers[i].fp = messageHandler;
                    rc = 0;
                    break;
                }
            }
        }
    }
    else 
        rc = MQTT_FAILURE;
        
exit:
#if defined(MQTT_TASK)
	MutexUnlock(&c->mutex);
#endif
    return rc;
}


int MQTTUnsubscribe(MQTTClient* c, const char* topicFilter)
{   
    int rc = MQTT_FAILURE;
    Timer timer;    
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicFilter;
    int len = 0;

#if defined(MQTT_TASK)
	MutexLock(&c->mutex);
#endif
	if (!c->isconnected)
		goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);
    
    if ((len = MQTTSerialize_unsubscribe(c->buf, c->buf_size, 0, getNextPacketId(c), 1, &topic)) <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != MQTT_SUCCESS) // send the subscribe packet
        goto exit; // there was a problem
    
    if (waitfor(c, UNSUBACK_MSG, &timer) == UNSUBACK_MSG)
    {
        unsigned short mypacketid;  // should be the same as the packetid above
        if (MQTTDeserialize_unsuback(&mypacketid, c->readbuf, c->readbuf_size) == 1)
            rc = 0; 
    }
    else
        rc = MQTT_FAILURE;
    
exit:
#if defined(MQTT_TASK)
	MutexUnlock(&c->mutex);
#endif
    return rc;
}


int MQTTPublish(MQTTClient* c, const char* topicName, MQTTMessage* message)
{
    int rc = MQTT_FAILURE;
    Timer timer;   
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicName;
    int len = 0;

#if defined(MQTT_TASK)
	MutexLock(&c->mutex);
#endif
	if (!c->isconnected)
		goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

    if (message->qos == QOS1 || message->qos == QOS2)
        message->id = getNextPacketId(c);
    
    len = MQTTSerialize_publish(c->buf, c->buf_size, 0, message->qos, message->retained, message->id, 
              topic, (unsigned char*)message->payload, message->payloadlen);
    if (len <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != MQTT_SUCCESS) // send the subscribe packet
        goto exit; // there was a problem
    
    if (message->qos == QOS1)
    {
        if (waitfor(c, PUBACK_MSG, &timer) == PUBACK_MSG)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = MQTT_FAILURE;
        }
        else
            rc = MQTT_FAILURE;
    }
    else if (message->qos == QOS2)
    {
        if (waitfor(c, PUBCOMP_MSG, &timer) == PUBCOMP_MSG)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = MQTT_FAILURE;
        }
        else
            rc = MQTT_FAILURE;
    }
    
exit:
#if defined(MQTT_TASK)
	MutexUnlock(&c->mutex);
#endif
    return rc;
}


int MQTTDisconnect(MQTTClient* c)
{  
    int rc = MQTT_FAILURE;
    Timer timer;     // we might wait for incomplete incoming publishes to complete
    int len = 0;

#if defined(MQTT_TASK)
	MutexLock(&c->mutex);
#endif
    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

	len = MQTTSerialize_disconnect(c->buf, c->buf_size);
    if (len > 0)
        rc = sendPacket(c, len, &timer);            // send the disconnect packet
        
    c->isconnected = 0;
	c->ping_outstanding = 0;

#if defined(MQTT_TASK)
	MutexUnlock(&c->mutex);
#endif
    return rc;
}

