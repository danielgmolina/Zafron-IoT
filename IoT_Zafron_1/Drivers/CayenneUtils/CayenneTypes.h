/*
The MIT License(MIT)

Cayenne MQTT Client Library
Copyright (c) 2016 myDevices

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files(the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CAYENNETYPES_h
#define _CAYENNETYPES_h

// Data types
#define TYPE_BAROMETRIC_PRESSURE "Presion" // Barometric pressure
#define TYPE_BATTERY "batt" // Battery
#define TYPE_LUMINOSITY "Luminosidad" // Luminosity
#define TYPE_PROXIMITY "Proximidad en cm" // Proximity
#define TYPE_RELATIVE_HUMIDITY "Humedad relativa (%)" // Relative Humidity
#define TYPE_TEMPERATURE "Temperatura" // Temperature
#define TYPE_VOLTAGE "Voltaje" // Voltage
#define TYPE_ACELERACION "aceleracion"
#define TYPE_ACELERACION_X "Aleceracion en X" // Voltage
#define TYPE_ACELERACION_Y "Aceleracion en Y" // Voltage
#define TYPE_ACELERACION_Z "Aceleracion en Z" // Voltage

#define TYPE_GIROS "giros" // Voltage
#define TYPE_GIROS_X "Giroscopio en X" // Voltage
#define TYPE_GIROS_Y "Giroscopio en Y" // Voltage
#define TYPE_GIROS_Z "Giroscopio en Z" // Voltage

#define TYPE_MAGNETICO "magnetico" // Voltage
#define TYPE_MAGNETICO_X "Campo magnetico en X" // Voltage
#define TYPE_MAGNETICO_Y "Campo magnetico en Y" // Voltage
#define TYPE_MAGNETICO_Z "Campo magnetico en Z" // Voltage

#define TYPE_NUMERO "Numero pulsaciones" // Voltage
#define TYPE_VOLUMEN "Volumen" // Voltage


//#define MAX_TYPE_LENGTH 7
#define MAX_TYPE_LENGTH 40


// Unit types
#define UNIT_UNDEFINED "null"
#define UNIT_PASCAL "pa" // Pascal
#define UNIT_HECTOPASCAL "hpa" // Hectopascal
#define UNIT_PERCENT "p" // % (0 to 100)
#define UNIT_RATIO "r" // Ratio
#define UNIT_VOLTS "v" // Volts
#define UNIT_LUX "lux" // Lux
#define UNIT_CENTIMETER "cm" // Centimeter
#define UNIT_MILIMETRO "mm" // Centimeter
#define UNIT_METER "m" // Meter
#define UNIT_DIGITAL "d" // Digital (0/1)
#define UNIT_FAHRENHEIT "f" // Fahrenheit
#define UNIT_CELSIUS "c" // Celsius
#define UNIT_KELVIN "k" // Kelvin
#define UNIT_MILLIVOLTS "mv" // Millivolts
#define UNIT_GAUSS "Gauss" // Millivolts
#define UNIT_GRAVEDADES "g" // Millivolts
#define UNIT_mGRAVEDADES "mG"
#define UNIT_GRADOSPORSEG "dps" // Millivolts
#define UNIT_VECES "veces" // Millivolts
#define UNIT_VOLUMEN "volumen" // Millivolts


#define MAX_UNIT_LENGTH 4

#endif
