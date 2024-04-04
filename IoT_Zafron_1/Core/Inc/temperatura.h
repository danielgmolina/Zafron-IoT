#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include "main.h"

//Temperatura
extern float m;
extern float temperatura;
extern uint16_t T0_Calibracion_Grados;
extern int16_t T0_Calibracion_ADC;

extern void inicializarTemperatura(void);
extern void getTemperatura(float *temperatura);

#endif 
