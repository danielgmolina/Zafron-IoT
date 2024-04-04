#include "giroscopio.h"

//Giroscopio

void inicializarGiro(void);
void getAxisGyro(int16_t *gyrox, int16_t *gyroy, int16_t *gyroz) ;

int16_t gyrox;
int16_t gyroy;
int16_t gyroz;

float gyrox_g;
float gyroy_g;
float gyroz_g;


void inicializarGiro(void) {

	 uint8_t addressWrite=0xd4;
	 uint8_t turnOn[]={0x11,0x10};
	 HAL_I2C_Master_Transmit(&hi2c2,addressWrite,turnOn,2,1);


}

void getAxisGyro(int16_t *gyrox, int16_t *gyroy, int16_t *gyroz) {

	uint8_t addressWrite = 0xd4;
	uint8_t addressRead = 0xd5;

	uint8_t GYRcmd[1];
	uint8_t GYRread[1];

	//ACC X
	GYRcmd[0] = 0x22;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyrox = GYRread[0];

	GYRcmd[0] = 0x23;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyrox |= ((GYRread[0]) << 8);

	//ACC Y

	GYRcmd[0] = 0x24;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyroy = GYRread[0];

	GYRcmd[0] = 0x25;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyroy |= ((GYRread[0]) << 8);

	//ACC Z

	GYRcmd[0] = 0x26;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyroz = GYRread[0];

	GYRcmd[0] = 0x27;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, GYRcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, GYRread, 1, 1);
	*gyroz |= ((GYRread[0]) << 8);

	gyrox_g = (*gyrox *2) / 16384.0;
	gyroy_g = (*gyroy *2) / 16384.0;
	gyroz_g = (*gyroz *2)/ 16384.0;

}

