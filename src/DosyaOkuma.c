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

    uzayAraciArrayList liste;
    liste->boyut = 0;
    liste->kapasite = 10;
    liste->uzayAraclari = malloc(liste->kapasite * sizeof(struct UZAYARACI*));

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