#ifndef EMIRLER_H
#define EMIRLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

struct EMIRLER{

    cJSON *emirler;
	FILE *file;
	long uzunluk;
	char *veri;
	cJSON* sembol;
	cJSON* islem;
	cJSON* adet;
	char** emirlerSembolDizi;
	char** emirlerIslemDizi;
	double* emirlerAdetDizi;
	int emirlerBoyut;
	cJSON *json;

//Nesne yonelimli benzetim icin fonksiyon gostericileri	
	void (*emirlerOku)(struct EMIRLER*);
	void (*yoket)(struct EMIRLER*);
	
};


typedef struct EMIRLER* Emirler;

Emirler EmirlerOlustur();

void EmirlerOku(Emirler);

void EmirlerYokEt(Emirler);


#endif