#ifndef HUMEDAD_H
#define HUMEDAD_H

#include "main.h"

//Humedad

extern void inicializarHumedad(void);
extern void getHumedad(float *humedad);

extern float mh;
extern float humedad;
extern uint8_t H0_Calibracion_RH;
extern int16_t H0_Calibracion_ADC;

#endif
