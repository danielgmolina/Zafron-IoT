#include "microfono.h"

void volumenMicrofono(int max_val);

uint16_t volumenMicro;

void volumenMicrofono(int max_val){
	
	if (max_val > 0 && max_val < 150)
				volumenMicro = 0;
			if (max_val > 150 && max_val < 300)
				volumenMicro = 1;
			if (max_val > 300 && max_val < 450)
				volumenMicro = 2;
			if (max_val > 450 && max_val < 600)
				volumenMicro = 3;
			if (max_val > 600 && max_val < 750)
				volumenMicro = 4;
			if (max_val > 750 && max_val < 900)
				volumenMicro = 5;
			if (max_val > 900 && max_val < 1050)
				volumenMicro = 6;
			if (max_val > 1050 && max_val < 1200)
				volumenMicro = 7;
			if (max_val > 1200 && max_val < 1450)
				volumenMicro = 8;
			if (max_val > 1450 && max_val < 1600)
				volumenMicro = 9;
			if (max_val > 1600 && max_val < 1750)
				volumenMicro = 10;
			if (max_val > 1750 && max_val < 1900)
				volumenMicro = 11;
			if (max_val > 1900 && max_val < 2050)
				volumenMicro = 12;
			if (max_val > 2050)
				volumenMicro = 13;

}

