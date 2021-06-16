// Gurkan Kaya G181210102 gurkan.kaya@ogr.sakarya.edu.tr

#include "Emirler.h"
	
Emirler EmirlerOlustur(){
	Emirler this;
	this=(Emirler)malloc(sizeof(struct EMIRLER));
	
	this->json=NULL;
	
	this->emirlerOku=&EmirlerOku;
	this->yoket=&EmirlerYokEt;
	
	this->emirlerSembolDizi=NULL;
	this->emirlerIslemDizi=NULL;
	this->emirlerAdetDizi=NULL;
	
  return this;
}
	//emirler dosyasi okuma islemi yapiliyor
void EmirlerOku(Emirler this)
{
	this->file = fopen("doc/emirler.json","rb");
    fseek(this->file, 0, SEEK_END);
    this->uzunluk = ftell(this->file);
    fseek(this->file, 0, SEEK_SET);

    this->veri = (char*)malloc(this->uzunluk + 1);

    fread(this->veri, 1, this->uzunluk, this->file);
    this->veri[this->uzunluk] = '\0';
    fclose(this->file);
	
    this->json = cJSON_Parse(this->veri);
	
	this->emirler = cJSON_GetObjectItem(this->json,"Emirler");

	
	this->emirlerBoyut=cJSON_GetArraySize(this->emirler);
	
	this->emirlerSembolDizi=malloc(sizeof(char*)*cJSON_GetArraySize(this->emirler));
	this->emirlerIslemDizi=malloc(sizeof(double)*cJSON_GetArraySize(this->emirler));
	this->emirlerAdetDizi=malloc(sizeof(double)*cJSON_GetArraySize(this->emirler));
	
	//okunan dosyadaki sembol islem adet degerleri ataniyor
	
	for (int i = 0 ; i < cJSON_GetArraySize(this->emirler) ; i++)
    {
		cJSON * subitem = cJSON_GetArrayItem(this->emirler, i);
		
		this->sembol = cJSON_GetObjectItem(subitem, "Sembol");

		this->islem = cJSON_GetObjectItem(subitem, "Islem"); 

		this->adet = cJSON_GetObjectItem(subitem, "Adet"); 
		
		this->emirlerSembolDizi[i]= this->sembol->valuestring ;
		this->emirlerIslemDizi[i]=this->islem->valuestring;
		this->emirlerAdetDizi[i]=this->adet->valuedouble;		
   }
}

//emirler icin yikici metot
void EmirlerYokEt(Emirler this)
{
	if(this==NULL) return;

	if(this->emirlerSembolDizi!=NULL) free(this->emirlerSembolDizi);
	if(this->emirlerIslemDizi!=NULL) free(this->emirlerIslemDizi);
	if(this->emirlerAdetDizi!=NULL) free(this->emirlerAdetDizi);

	free(this->veri);

	cJSON_Delete(this->json);

	free(this);
	

} 






