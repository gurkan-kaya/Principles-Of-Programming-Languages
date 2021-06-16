#ifndef HISSELER_H
#define HISSELER_H

#include <stdio.h>
#include<stdlib.h>
#include "cJSON.h"
#include<string.h>


struct HISSELER{

    cJSON *hisseler;
	FILE *file;
	long uzunluk;
	char *veri;
	cJSON *json;
	cJSON* sembol;
	cJSON* fiyat;
	char** hisseSembolDizi;
	double* hisseFiyatDizi;
	int hisselerBoyut;

//Nesne yonelimli benzetim icin fonksiyon gostericileri
	void (*hisselerOku)(struct HISSELER*);
	void (*yoket)(struct HISSELER*);
		
};


typedef struct HISSELER* Hisseler;

Hisseler HisselerOlustur();

void HisselerOku(Hisseler);

void HisselerYokEt(Hisseler);



#endif