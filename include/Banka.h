#ifndef BANKA_H
#define BANKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "Portfoy.h"
#include "Emirler.h"
#include "Hisseler.h"

struct BANKA{
	
	//kalitim benzetimi yapiliyor
	Hisseler super;
	Emirler super2;
	Portfoy super3;	
	double sonuc;
	
//Nesne yonelimli benzetim icin fonksiyon gostericileri
	void (*emirAlimSatimIslemleri)(struct BANKA*);
	void (*karZararYazdir)(struct BANKA*);
	void (*guncelPortfoyYazdir)(struct BANKA*);
	void (*yoket)(struct BANKA*);
	
	char** karZararSembolDizi;
	double* karZararDizi;
	
};


typedef struct BANKA* Banka;

Banka BankaOlustur();

void EmirAlimSatimIslemleri(const Banka);
void GuncelPortfoyYazdir(const Banka);
void KarZararYazdir(const Banka);

void BankaYokEt(Banka);

#endif
 






