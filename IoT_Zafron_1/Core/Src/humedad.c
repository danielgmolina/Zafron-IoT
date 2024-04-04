#include "humedad.h"

//Humedad

void inicializarHumedad(void);
void getHumedad(float *humedad);

float mh;
float humedad;
uint8_t H0_Calibracion_RH;
int16_t H0_Calibracion_ADC;


void inicializarHumedad(void){

	//I2C
	uint8_t direccionEscritura = 0xbe;
	uint8_t direccionLectura = 0xbf;

	// RH
	uint8_t direccion_H0_Calibracion[] = {0x30};
	uint8_t direccion_H1_Calibracion[] = {0x31};

	//ADC
	uint8_t direccion_H0_out_low[] = {0x36};
	uint8_t direccion_H0_out_high[] = {0x37};
	uint8_t direccion_H1_out_low[] = {0x3a};
	uint8_t direccion_H1_out_high[] = {0x3b};

	//Output humedad (%RH)
	uint8_t H1_Calibracion_RH;

	//Input temperature LSB (ADC)
	int16_t H1_Calibracion_ADC;

	uint8_t recepcion[2];
	uint8_t powerOn[] = {0x20, 0x81};

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, powerOn, 2, 1); //Encender sensor

	//T0 y T1 en �C
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H0_Calibracion, 1, 1); //Calibracion
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H0_Calibracion_RH = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H1_Calibracion, 1, 1); //Calibracion
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H1_Calibracion_RH = recepcion[0];

	H0_Calibracion_RH = H0_Calibracion_RH/2;
	H1_Calibracion_RH = H1_Calibracion_RH/2;

	//H0 ADC
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H0_out_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H0_Calibracion_ADC = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H0_out_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H0_Calibracion_ADC |= (recepcion[0] << 8);

	//H1 ADC
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H1_out_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H1_Calibracion_ADC = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_H1_out_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	H1_Calibracion_ADC |= (recepcion[0] << 8);

	//Pendiente m
	mh = ((float)(H1_Calibracion_RH - H0_Calibracion_RH) / (float)(H1_Calibracion_ADC - H0_Calibracion_ADC));
}

void getHumedad(float *humedad){

	//I2C
	uint8_t direccionEscritura = 0xbe;
	uint8_t direccionLectura = 0xbf;

	uint8_t direccionHumedad_low[] = {0x28};
	uint8_t direccionHumedad_high[] = {0x29};

	uint8_t recepcion[2];
	int16_t hum;

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccionHumedad_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);

	hum = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccionHumedad_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);

	hum |= (recepcion[0] << 8);

	*humedad = (H0_Calibracion_RH - mh*H0_Calibracion_ADC) + mh*hum;
}


