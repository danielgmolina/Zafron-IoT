#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H

#include "main.h"

//Giroscopio

extern void inicializarGiro(void);
extern void getAxisGyro(int16_t *gyrox, int16_t *gyroy, int16_t *gyroz);

extern int16_t gyrox;
extern int16_t gyroy;
extern int16_t gyroz;

extern float gyrox_g;
extern float gyroy_g;
extern float gyroz_g;

#endif
