#include "DosyaOkuma.h"
#include <string.h>
#include <stdio.h>
#include "Kisi.h"
kisiArrayList kisileriOku(char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya açilamadi");
        return NULL;
    }

    kisiArrayList liste;
    liste->boyut = 0;
    liste->kapasite = 10;
    liste->kisiler = malloc(liste->kapasite * sizeof(struct KISI*));

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
            liste->addToListKisi(liste, kisi); //burada kaldım
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

    gezegenArrayList liste;
    liste->boyut = 0;
    liste->kapasite = 10;
    liste->gezegenler = malloc(liste->kapasite * sizeof(struct GEZEGEN*));

    char satir[256]; //max line length

    while(fgets(satir, sizeof(satir), dosya) != NULL){
        //satir sonundaki \n karakterini sil
        satir[strcspn(satir, "\n")] = 0;

        char* isim= strtok(satir, "#");
        char* gununKacSaatStr = strtok(NULL, "#");
        char* tarihStr = strtok(NULL, "#");

        char* gun=strtok(tarihStr, ".");
        char* ay=strtok(NULL, ".");
        char* yil=strtok(NULL, ".");

        Zaman tarih= zamanOlusturucu(gun,ay,yil);
        if(isim && gununKacSaatStr && tarihStr){
            Gezegen gezegen = gezegenOlusturucu(isim, atoi(gununKacSaatStr), tarih); 
            addToListKisi(liste, kisi);
        }
    }
    fclose(dosya);
    return liste;
}
uzayAraciArrayList uzayAraclariniOku(const DosyaOkuma,char*);
void dosyaOkumaYoket(DosyaOkuma);