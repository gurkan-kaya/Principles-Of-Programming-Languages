// Gurkan Kaya G181210102 gurkan.kaya@ogr.sakarya.edu.tr

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "cJSON.h"
#include "Hisseler.h"
#include "Portfoy.h"
#include "Emirler.h"
#include "Banka.h"

int main()
{
	Banka b=BankaOlustur();		//Kalitim benzetimi yapildigi icin BankaOlustur cagrildiginda ayni zamanda Hisse,Portfoy,Emir olusturuyor.
	b->super->hisselerOku(b->super); //Hisse okuma islemleri yapiliyor.	
	b->super2->emirlerOku(b->super2); //Emir okuma islemleri yapiliyor.	
	b->super3->portfoyOku(b->super3); ////Portfoy okuma islemleri yapiliyor.	
	b->emirAlimSatimIslemleri(b);	//Alim satim islemleri yapiliyor.	
	b->karZararYazdir(b); //Kar Zarar durumu yazdırılıyor.	
	b->guncelPortfoyYazdir(b); //Guncel portfoy yazdiriliyor.	
	b->yoket(b); 	//Bu metot cagirildiginda kalitim benzetimi sayesinde hem Hisse,Portfoy,Emir yok ediliyor hem de Banka yok ediliyor.

    return 0;
}