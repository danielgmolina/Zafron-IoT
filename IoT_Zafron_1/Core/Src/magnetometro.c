#include "magnetometro.h"

//Magnetometro

void inicializarMagneto(void);
void getMagnetoAxis(int16_t *magx, int16_t *magy, int16_t *magz);

int16_t magx;
int16_t magy;
int16_t magz;

void inicializarMagneto(void){

	uint16_t direccionEscritura = 0x3c;
	uint8_t powerOn[] = {0x22,0x00};

	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, powerOn,2,1);

}

void getMagnetoAxis(int16_t *magx, int16_t *magy, int16_t *magz){

	uint16_t direccionEscritura = 0x3c;
	uint16_t direccionLectura= 0x3d;

	uint8_t cmd[1];
	uint8_t recepcion[1];

	//Eje X
	cmd[0] = 0x28;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magx = recepcion[0];

	cmd[0] = 0x29;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magx |= (recepcion[0] << 8);

	//Eje Y
	cmd[0] = 0x2a;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magy = recepcion[0];

	cmd[0] = 0x2b;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magy |= (recepcion[0] << 8);

	//Eje Z
	cmd[0] = 0x2c;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magz = recepcion[0];

	cmd[0] = 0x2d;
	HAL_I2C_Master_Transmit(&hi2c2, direccionEscritura, cmd, 1, 1);
	HAL_I2C_Master_Receive(&hi2c2, direccionLectura, recepcion, 1, 1);
	*magz |= (recepcion[0] << 8);


}

