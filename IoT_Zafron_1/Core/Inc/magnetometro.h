#ifndef MAGNETOMETRO_H
#define MAGNETOMETRO_H

#include "main.h"

//Magnetometro

extern void inicializarMagneto(void);
extern void getMagnetoAxis(int16_t *magx, int16_t *magy, int16_t *magz);

extern int16_t magx;
extern int16_t magy;
extern int16_t magz;

#endif
