#ifndef ACELEROMETRO_H
#define ACELEROMETRO_H

#include "main.h"

//Acelerometro

extern void inicializarAcelerometro(void);
extern void getAxisAccelerometer(int16_t *accx, int16_t *accy, int16_t *accz);

extern int16_t accx;
extern int16_t accy;
extern int16_t accz;

extern float accx_g;
extern float accy_g;
extern float accz_g;

#endif
