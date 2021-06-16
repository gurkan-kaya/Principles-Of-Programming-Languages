// Gurkan Kaya G181210102 gurkan.kaya@ogr.sakarya.edu.tr

#include "Portfoy.h"

Portfoy PortfoyOlustur(){
	Portfoy this;
	
	this=(Portfoy)malloc(sizeof(struct PORTFOY));
	
	this->json=NULL;

	this->portfoySembolDizi=NULL;
	this->portfoyMaliyetDizi=NULL;
	this->portfoyAdetDizi=NULL;

	this->portfoyOku=&PortfoyOku;
	this->yoket=&PortfoyYokEt;

	return this;
}
	//portfoy dosyasi okunuyor
void PortfoyOku(Portfoy this)
{
	this->file = fopen("doc/portfoy.json","rb");
    fseek( this->file, 0, SEEK_END);
    this->uzunluk = ftell( this->file);
    fseek( this->file, 0, SEEK_SET);

    this->veri = (char*)malloc(this->uzunluk + 1);

    fread(this->veri, 1,  this->uzunluk,  this->file);
    this->veri[this->uzunluk] = '\0';
    fclose( this->file);

	
    this->json = cJSON_Parse(this->veri);
	

	this->portfoy = cJSON_GetObjectItem(this->json,"Portfoy");

	
	this->portfoyBoyut=cJSON_GetArraySize(this->portfoy);
	
	this->portfoySembolDizi=malloc(sizeof(char*)*cJSON_GetArraySize(this->portfoy));
	this->portfoyMaliyetDizi=malloc(sizeof(double)*cJSON_GetArraySize(this->portfoy));
	this->portfoyAdetDizi=malloc(sizeof(double)*cJSON_GetArraySize(this->portfoy));
	
	//sembol, maliyet, adet degerleri cekilip, atamalari yapiliyor
	for (int i = 0 ; i < cJSON_GetArraySize(this->portfoy) ; i++)
  {
    cJSON * subitem = cJSON_GetArrayItem(this->portfoy, i);
	
    this->sembol = cJSON_GetObjectItem(subitem, "Sembol");

    this->maliyet = cJSON_GetObjectItem(subitem, "Maliyet"); 

	this->adet = cJSON_GetObjectItem(subitem, "Adet"); 
	
	this->portfoySembolDizi[i]= this->sembol->valuestring ;
	this->portfoyMaliyetDizi[i]=this->maliyet->valuedouble;
	this->portfoyAdetDizi[i]=this->adet->valuedouble;
	
	
  }
}
// portfoy icin yikici metot
void PortfoyYokEt(Portfoy this)
{
	if(this==NULL) return;

	if(this->portfoySembolDizi!=NULL) free(this->portfoySembolDizi);
	if(this->portfoyMaliyetDizi!=NULL) free(this->portfoyMaliyetDizi);
	if(this->portfoyAdetDizi!=NULL) free(this->portfoyAdetDizi);

	free(this->veri);

	cJSON_Delete(this->json);

	free(this);	 


	


} 






