// Gurkan Kaya G181210102 gurkan.kaya@ogr.sakarya.edu.tr

#include "Banka.h"

Banka BankaOlustur(){
	Banka this;
	this=(Banka)malloc(sizeof(struct BANKA));
	
	//kalitim benzetimi sebebiyle hisseler emirler ve portfoyun kuruculari burada cagrildi
	
	this->super= HisselerOlustur();
	this->super2= EmirlerOlustur();
	this->super3= PortfoyOlustur();
	
	this->karZararSembolDizi=malloc(sizeof(char*)*1);
	this->karZararDizi=malloc(sizeof(double)*1);

	this->emirAlimSatimIslemleri=&EmirAlimSatimIslemleri;
	this->karZararYazdir=&KarZararYazdir;
	this->guncelPortfoyYazdir=&GuncelPortfoyYazdir;
	
	this->yoket=&BankaYokEt;
		
  return this;
}

int kzDiziBoyut=0;


//emirlerin islenmesi alim satimlarin gerceklesmesi icin gerekli hesaplamalar bu fonksiyonla yapiliyor
void EmirAlimSatimIslemleri(const Banka this)
{
int result;
int result2;
int resultSatis;
int resultAlis;

	for(int i=0;i<this->super2->emirlerBoyut;i++)
	{

		for(int j=0;j<this->super->hisselerBoyut;j++)
		{
			char* satis="SATIS";
			char* alis="ALIS";

			int result2Sayac=0;		
			result = strcmp(this->super->hisseSembolDizi[j],this->super2->emirlerSembolDizi[i]);
			resultSatis = strcmp(this->super2->emirlerIslemDizi[i],satis);	
			resultAlis = strcmp(this->super2->emirlerIslemDizi[i],alis);	
				
			for(int k=0;k<this->super3->portfoyBoyut;k++)
			{				

				result2=strcmp(this->super2->emirlerSembolDizi[i],this->super3->portfoySembolDizi[k]);
				if(result2==0)result2Sayac++;
				
				if(result==0&&result2==0&&resultSatis==0)
				{
					if(this->super2->emirlerAdetDizi[i]>this->super3->portfoyAdetDizi[k])
					{
						this->super2->emirlerAdetDizi[i]=this->super3->portfoyAdetDizi[k];
						
						this->sonuc=	((this->super->hisseFiyatDizi[j]* this->super2->emirlerAdetDizi[i]) - (this->super3->portfoyMaliyetDizi[k]* this->super2->emirlerAdetDizi[i]));

					}
					else if(this->super2->emirlerAdetDizi[i]<=this->super3->portfoyAdetDizi[k])
					{
						this->sonuc=	((this->super->hisseFiyatDizi[j]* this->super2->emirlerAdetDizi[i]) - (this->super3->portfoyMaliyetDizi[k]* this->super2->emirlerAdetDizi[i]));
				
					}
										
					int kzresult=0;
					int kzresultSayac=0;
					
					for(int m=0;m<kzDiziBoyut;m++)
					{
						kzresult = strcmp(this->karZararSembolDizi[m],this->super2->emirlerSembolDizi[i]);
						if(kzresult==0)
						{
							this->karZararDizi[m]+=this->sonuc;
							kzresultSayac=kzresultSayac+1;
						}
						
					}
					if(kzresultSayac==0&&kzDiziBoyut==0)
					{	
						this->karZararSembolDizi[kzDiziBoyut] =this->super2->emirlerSembolDizi[i];
						this->karZararDizi[kzDiziBoyut] =this->sonuc;
						kzDiziBoyut=kzDiziBoyut+1;
							
					}
					else if(kzresultSayac==0&&kzDiziBoyut!=0)
					{
						this->karZararSembolDizi = realloc(this->karZararSembolDizi, (kzDiziBoyut+1) * sizeof(char*));
						this->karZararDizi = realloc(this->karZararDizi, (kzDiziBoyut+1) * sizeof(double));
						this->karZararSembolDizi[kzDiziBoyut] =this->super2->emirlerSembolDizi[i];
						this->karZararDizi[kzDiziBoyut] =this->sonuc;
						kzDiziBoyut=kzDiziBoyut+1;							
					}
					this->super3->portfoyAdetDizi[k]=(this->super3->portfoyAdetDizi[k] - this->super2->emirlerAdetDizi[i]);
			
				
				}
				
				
				if(result==0&&result2==0&&resultAlis==0)
				{
					double yeniMaliyet=0;
					double yeniAdet=0;
				    yeniMaliyet=(((this->super3->portfoyMaliyetDizi[k]*this->super3->portfoyAdetDizi[k])+ (this->super2->emirlerAdetDizi[i]*this->super->hisseFiyatDizi[j]))/(this->super2->emirlerAdetDizi[i] + this->super3->portfoyAdetDizi[k]));						
					this->super3->portfoyMaliyetDizi[k]=yeniMaliyet;
					
					yeniAdet=(this->super3->portfoyAdetDizi[k] + this->super2->emirlerAdetDizi[i]);
					this->super3->portfoyAdetDizi[k]=yeniAdet;
				}
				
			}
			
			
			if(result==0&&resultAlis==0&&result2Sayac==0)
			{		
				//eger alim yapilacak hisse portfoyde yoksa boyut degisecegi icin realloc ile boyut artiriliyor
					this->super3->portfoySembolDizi = realloc(this->super3->portfoySembolDizi, (this->super3->portfoyBoyut+1) * sizeof(char*));
					this->super3->portfoyMaliyetDizi = realloc(this->super3->portfoyMaliyetDizi, (this->super3->portfoyBoyut+1) * sizeof(double));
					this->super3->portfoyAdetDizi =realloc(this->super3->portfoyAdetDizi, (this->super3->portfoyBoyut+1) * sizeof(double));
					
					this->super3->portfoySembolDizi[this->super3->portfoyBoyut]=this->super2->emirlerSembolDizi[i];
					this->super3->portfoyMaliyetDizi[this->super3->portfoyBoyut]=this->super->hisseFiyatDizi[j];
					this->super3->portfoyAdetDizi[this->super3->portfoyBoyut]=this->super2->emirlerAdetDizi[i];
					
					this->super3->portfoyBoyut=this->super3->portfoyBoyut+1;
							
			}
		}		
	}
}

// tum emir islemleri bittikten sonra portfoyun guncel hali yazdiriliyor
void GuncelPortfoyYazdir(const Banka this)
{
	printf("%s", "Guncel Portfoy:");
	 
	for (int i = 0 ; i < this->super3->portfoyBoyut ; i++)
	{		  
		  if(this->super3->portfoyAdetDizi[i]>0)
		  {
			   printf("\n");
			   printf("Hisse: ");
			   printf("%s\n",this->super3->portfoySembolDizi[i]);
			   printf("Adet: ");
			   printf("%.0lf\n", this->super3->portfoyAdetDizi[i]);
			   printf("Maliyet: ");
			   printf("%.2lf\n", this->super3->portfoyMaliyetDizi[i]);
			   
			   printf("--------------------------");			  
		  }		  
	}
	printf("\n");
}


// alim satim islemleri sonucunda hesaplanan kar zarar durumlarinin yazdirilmasi burada yapiliyor
void KarZararYazdir(const Banka this)
{
	double toplam=0;
	printf("\n");
	printf("%s\n", "Satislar Kar/Zarar:");
	
	for(int i=0;i<kzDiziBoyut;i++)
	{
		printf("%s : ",this->karZararSembolDizi[i]);
		if(this->karZararDizi[i]>0)
		{
			printf("%.2lf TL Kar",this->karZararDizi[i]);
			printf("\n");
		}
		
		else if(this->karZararDizi[i]==0)
		{
			printf("Kar - Zarar Yok");
			printf("\n");
		}
		
		else
		{
			printf("%.2lf TL Zarar",(this->karZararDizi[i]*(-1)));
			printf("\n");
		}
		
		toplam+=this->karZararDizi[i];
	}
	
	printf("%s", "Toplam Kar/Zarar: ");
	if(toplam>=0)
	{
		printf("+ ");
		printf("%.2lf TL", toplam);
	}
	else
	{
		printf("- ");
		printf("%.2lf TL", toplam);
	}

	printf("\n\n");
}


// ayrilan alanlarin bellege iadesi saglaniyor
void BankaYokEt(Banka this)
{
	if(this==NULL) return;

	this->super->yoket(this->super);
	this->super2->yoket(this->super2);
	this->super3->yoket(this->super3);
	
	if(this->karZararSembolDizi!=NULL) free(this->karZararSembolDizi);
	if(this->karZararDizi!=NULL) free(this->karZararDizi);

	free(this);
}