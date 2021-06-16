// Gurkan Kaya G181210102 gurkan.kaya@ogr.sakarya.edu.tr

#include "Hisseler.h"

Hisseler HisselerOlustur(){
	Hisseler this;

	this=(Hisseler)malloc(sizeof(struct HISSELER));
	
	this->json=NULL;
	
	this->hisseSembolDizi=NULL;
	this->hisseFiyatDizi=NULL;
		
	this->hisselerOku=&HisselerOku;
	this->yoket=&HisselerYokEt;


  return this;
}
	//Hisselerin okunmasi ve atamalari burada yapiliyor
void HisselerOku(Hisseler this)
{
	this->file = fopen("doc/hisseler.json","rb");

    fseek( this->file, 0, SEEK_END);
	
    this->uzunluk = ftell( this->file);
	
    fseek( this->file, 0, SEEK_SET);

    this->veri = (char*)malloc(this->uzunluk + 1);

    fread(this->veri, 1, this->uzunluk,  this->file);
	
    this->veri[this->uzunluk] = '\0';
	
    fclose( this->file);
	
    this->json = cJSON_Parse(this->veri);

	this->hisseler = cJSON_GetObjectItem(this->json,"Hisseler");	

	this->hisselerBoyut=cJSON_GetArraySize(this->hisseler);
	
	this->hisseSembolDizi=malloc(sizeof(char*)*cJSON_GetArraySize(this->hisseler));	
	this->hisseFiyatDizi=malloc(sizeof(double)*cJSON_GetArraySize(this->hisseler));
	
	//atamalar icin for dongusu
	
	for (int i = 0 ; i < cJSON_GetArraySize(this->hisseler) ; i++)
	{
    cJSON * subitem = cJSON_GetArrayItem(this->hisseler, i);
	
    this->sembol = cJSON_GetObjectItem(subitem, "Sembol");

    this->fiyat = cJSON_GetObjectItem(subitem, "Fiyat"); 
	
	this->hisseSembolDizi[i]= this->sembol->valuestring ;	
	this->hisseFiyatDizi[i]=this->fiyat->valuedouble; 
	}

}
	//ayrilan alanlar bellege iade ediliyor
void HisselerYokEt(Hisseler this)
{
	if(this==NULL) return;
	if(this->hisseSembolDizi!=NULL) free(this->hisseSembolDizi);	
	if(this->hisseFiyatDizi!=NULL) free(this->hisseFiyatDizi);
	
	free(this->veri);

	cJSON_Delete(this->json);

	free(this);
	
} 






