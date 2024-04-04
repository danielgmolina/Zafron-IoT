#include "acelerometro.h"

//Acelerometro

void inicializarAcelerometro(void);
void getAxisAccelerometer(int16_t *accx, int16_t *accy, int16_t *accz);

int16_t accx;
int16_t accy;
int16_t accz;

float accx_g;
float accy_g;
float accz_g;

void inicializarAcelerometro(void){

	 uint8_t addressWrite=0xd4;
	 uint8_t turnOn[]={0x10,0x10};
	 HAL_I2C_Master_Transmit(&hi2c2,addressWrite,turnOn,2,1);


	}

void getAxisAccelerometer(int16_t *accx, int16_t *accy, int16_t *accz) {

	uint8_t addressWrite = 0xd4;
	uint8_t addressRead = 0xd5;

	uint8_t ACCcmd[1];
	uint8_t ACCread[1];

	//ACC X
	ACCcmd[0] = 0x28;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accx = ACCread[0];

	ACCcmd[0] = 0x29;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accx |= ((ACCread[0]) << 8);

	//ACC Y

	ACCcmd[0] = 0x2a;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accy = ACCread[0];

	ACCcmd[0] = 0x2b;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accy |= ((ACCread[0]) << 8);

	//ACC Z

	ACCcmd[0] = 0x2c;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accz = ACCread[0];

	ACCcmd[0] = 0x2d;
	HAL_I2C_Master_Transmit(&hi2c2, addressWrite, ACCcmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, addressRead, ACCread, 1, 1);
	*accz |= ((ACCread[0]) << 8);

	accx_g = (*accx *2) / 16384.0;
	accy_g = (*accy *2) / 16384.0;
	accz_g = (*accz *2)/ 16384.0;

}

