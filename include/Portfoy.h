#ifndef PORTFOY_H
#define PORTFOY_H

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cJSON.h"

struct PORTFOY{

    cJSON *portfoy;
	FILE *file;
	long uzunluk;
	char *veri;
	cJSON* sembol;
	cJSON* maliyet;
	cJSON* adet;
	char** portfoySembolDizi;
	double* portfoyMaliyetDizi;
	double* portfoyAdetDizi;
	int portfoyBoyut;
	cJSON *json;

//Nesne yonelimli benzetim icin fonksiyon gostericileri	
	void (*portfoyOku)(struct PORTFOY*);
	void (*yoket)(struct PORTFOY*);
	
};


typedef struct PORTFOY* Portfoy;

Portfoy PortfoyOlustur();

void PortfoyOku(Portfoy);

void PortfoyYokEt(Portfoy);


#endif