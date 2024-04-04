#include "temperatura.h"

//Temperatura
float m;
float temperatura;
uint16_t T0_Calibracion_Grados;
int16_t T0_Calibracion_ADC;

void inicializarTemperatura(void);
void getTemperatura(float *temperatura);

void inicializarTemperatura(void){

	//I2C
	uint8_t direccionEscritura = 0xbe;
	uint8_t direccionLectura = 0xbf;

	// ºC
	uint8_t direccion_T0_Calibracion[] = {0x32};
	uint8_t direccion_T1_Calibracion[] = {0x33};
	uint8_t direccion_MSB_Calibracion[] = {0x35};

	//ADC
	uint8_t direccion_T0_out_low[] = {0x3c};
	uint8_t direccion_T0_out_high[] = {0x3d};
	uint8_t direccion_T1_out_low[] = {0x3e};
	uint8_t direccion_T1_out_high[] = {0x3f};

	//Output temperature (ºC)
	uint16_t T1_Calibracion_Grados;
	uint8_t MSB_Calibracion;

	//Input temperature LSB (ADC)
	int16_t T1_Calibracion_ADC;

	uint8_t recepcion[2];
	uint8_t powerOn[] = {0x20, 0x81};

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, powerOn, 2, 1); //Encender sensor

	//T0 y T1 en ºC
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T0_Calibracion, 1, 1); //Calibracion
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T0_Calibracion_Grados = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T1_Calibracion, 1, 1); //Calibracion
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T1_Calibracion_Grados = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_MSB_Calibracion, 1, 1); //Calibracion
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	MSB_Calibracion = recepcion[0];

	T0_Calibracion_Grados |= (MSB_Calibracion & 0x03) << 8;
	T1_Calibracion_Grados |= (MSB_Calibracion & 0x0C) << 6; // Ojo

	T0_Calibracion_Grados = T0_Calibracion_Grados/8;
	T1_Calibracion_Grados = T1_Calibracion_Grados/8;

	//T0 ADC
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T0_out_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T0_Calibracion_ADC = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T0_out_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T0_Calibracion_ADC |= (recepcion[0] << 8);

	//T1 ADC
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T1_out_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T1_Calibracion_ADC = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccion_T1_out_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	T1_Calibracion_ADC |= (recepcion[0] << 8);

	//Pendiente m
	m = ((float)(T1_Calibracion_Grados - T0_Calibracion_Grados) / (float)(T1_Calibracion_ADC - T0_Calibracion_ADC));
}

void getTemperatura(float *temperatura){

	//I2C
	uint8_t direccionEscritura = 0xbe;
	uint8_t direccionLectura = 0xbf;

	uint8_t direccionTemperatura_low[] = {0x2A};
	uint8_t direccionTemperatura_high[] = {0x2B};

	uint8_t recepcion[2];
	int16_t temp;

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccionTemperatura_low, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);

	temp = recepcion[0];

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, direccionTemperatura_high, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);

	temp |= (recepcion[0] << 8);

	*temperatura = (T0_Calibracion_Grados - m*T0_Calibracion_ADC) + m*temp;
}
