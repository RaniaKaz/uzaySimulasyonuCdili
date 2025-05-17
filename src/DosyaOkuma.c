#include "DosyaOkuma.h"
#include <string.h>
#include <stdio.h>
#include "KisiArrayList.h"
#include "GezegenArrayList.h"
#include "UzayAraciArrayList.h"

DosyaOkuma dosyaOkumaOlusturucu(){
    DosyaOkuma this;
    this=(DosyaOkuma)malloc(sizeof(struct DOSYAOKUMA));
    this->gezegenleriOku=&gezegenleriOku;
    this->kisileriOku=&kisileriOku;
    this->uzayAraclariniOku=&uzayAraclariniOku;
    this->yoket=&dosyaOkumaYoket;
    return this;
}
kisiArrayList kisileriOku(char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya açilamadi");
        return NULL;
    }

    kisiArrayList liste = kisiArrayListOlusturucu();

    char satir[256]; //max line length

    while(fgets(satir, sizeof(satir), dosya) != NULL){
        //satir sonundaki \n karakterini sil
        satir[strcspn(satir, "\n")] = 0;

        char* isim= strtok(satir, "#");
        char* yasStr = strtok(NULL, "#");
        char* kalanOmurStr = strtok(NULL, "#");
        char* uzayAraciAdi = strtok(NULL, "#");

        if(isim && yasStr && kalanOmurStr && uzayAraciAdi){
            Kisi kisi = kisiOlustur(isim, atoi(yasStr), atoi(kalanOmurStr), uzayAraciAdi); 
            liste->add(liste, kisi); //burada kaldım
        }
    }
    fclose(dosya);
    return liste;
}

gezegenArrayList gezegenleriOku(char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya açilamadi");
        return NULL;
    }

    gezegenArrayList liste = gezegenArrayListOlusturucu();

    char satir[256]; //max line length

    while(fgets(satir, sizeof(satir), dosya) != NULL){
        //satir sonundaki \n karakterini sil
        satir[strcspn(satir, "\n")] = 0;

        char* isim= strtok(satir, "#");
        char* gununKacSaatStr = strtok(NULL, "#");
        char* tarihStr = strtok(NULL, "#");

        char* gunStr=strtok(tarihStr, ".");
        char* ayStr=strtok(NULL, ".");
        char* yilStr=strtok(NULL, ".");

        Zaman tarih=zamanOlusturucu(atoi(gunStr),atoi(ayStr),atoi(yilStr));
        if(isim && gununKacSaatStr && tarihStr){
            Gezegen gezegen = gezegenOlusturucu(isim, atoi(gununKacSaatStr), tarih); 
            liste->add(liste, gezegen);
        }
    }
    fclose(dosya);
    return liste;
}
uzayAraciArrayList uzayAraclariniOku(char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya açilamadi");
        return NULL;
    }

    uzayAraciArrayList liste = uzayAraciArrayListOlusturucu();

    char satir[256]; //max line length

    while(fgets(satir, sizeof(satir), dosya) != NULL){
        //satir sonundaki \n karakterini sil
        satir[strcspn(satir, "\n")] = 0;

        char* isim= strtok(satir, "#");
        char* cikisGezegeni = strtok(NULL, "#");
        char* varisGezegeni = strtok(NULL, "#");
        char* cikisTarihiStr = strtok(NULL, "#");
        char* mesafeSaatStr = strtok(NULL, "#");

        char* gunStr= strtok(cikisTarihiStr, ".");
        char* ayStr= strtok(NULL, ".");
        char* yilStr= strtok(NULL, ".");
        Zaman tarih=zamanOlusturucu(atoi(gunStr),atoi(ayStr),atoi(yilStr));
        if(isim && cikisGezegeni && varisGezegeni && cikisTarihiStr && mesafeSaatStr){
            UzayAraci uzayAraci = uzayAraciOlusturucu(isim,cikisGezegeni, varisGezegeni,
                tarih, atoi(mesafeSaatStr)); 
            liste->add(liste, uzayAraci);
        }
    }
    fclose(dosya);
    return liste;
}

void dosyaOkumaYoket(DosyaOkuma this){
    if(this==NULL)
        return;
    
    free(this);
}