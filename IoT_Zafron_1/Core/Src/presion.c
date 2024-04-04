#include "presion.h"

//Presion

void inicializarBarometro(void);
void getPresion(float *pressure);

float pressure;


void inicializarBarometro(void){

	uint8_t addressWrite=0xba;
	uint8_t turnOn[]={0x10,0x20};//The address of the register and the value of the register to turn on the sensor

    HAL_I2C_Master_Transmit(&hi2c2,addressWrite,turnOn,2,1);
}

void getPresion(float *pressure){

	int lsb;
	uint8_t addressWrite=0xba;
	uint8_t addressRead=0xbb;
	uint8_t pressXL[]={0x28};
	uint8_t pressL[]={0x29};
	uint8_t pressH[]={0x2a};
	uint8_t data[2];

    HAL_I2C_Master_Transmit(&hi2c2,addressWrite,pressXL,1,1);
	HAL_I2C_Master_Receive(&hi2c2,addressRead,data,2,1);
	lsb=data[0];

	HAL_I2C_Master_Transmit(&hi2c2,addressWrite,pressL,1,1);
	HAL_I2C_Master_Receive(&hi2c2,addressRead,data,2,1);
	lsb|=data[0]<<8;

	HAL_I2C_Master_Transmit(&hi2c2,addressWrite,pressH,1,1);
	HAL_I2C_Master_Receive(&hi2c2,addressRead,data,2,1);
	lsb|=data[0]<<16;


	/*if(lsb>8388607){
		lsb=lsb-1;
		lsb=~lsb;
	}*/

	*pressure=((float)lsb)/((float)(4096));

}

