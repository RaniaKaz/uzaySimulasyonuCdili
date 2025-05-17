#include "DosyaOkuma.h"

DosyaOkuma dosyaOkumaOlusturucu(){
    DosyaOkuma this;
    this=(DosyaOkuma)malloc(sizeof(struct DOSYAOKUMA));
    this->gezegenleriOku=&gezegenleriOku;
    this->kisileriOku=&kisileriOku;
    this->uzayAraclariniOku=&uzayAraclariniOku;
    this->yoket=&dosyaOkumaYoket;
    return this;
}
kisiArrayList kisileriOku(DosyaOkuma this,char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(!dosya){
    printf("kisiler.txt a calisildi ama basarisiz oldu!\n");
    perror("fopen hatasi");
    exit(EXIT_FAILURE);
    }
    if(dosya==NULL){
        printf("Dosya acilamadi");
        return NULL;
    }

    this->kisiListesi =kisiArrayListOlusturucu();

    char satir[256]; //max line length

    while(fgets(satir, sizeof(satir), dosya) != NULL){
        //satir sonundaki \n karakterini sil
        satir[strcspn(satir, "\n")] = 0;

        char* isim= strtok(satir, "#");
        char* yasStr = strtok(NULL, "#");
        char* kalanOmurStr = strtok(NULL, "#");
        char* uzayAraciAdi = strtok(NULL, "#");

        if(isim && yasStr && kalanOmurStr && uzayAraciAdi){
            Kisi kisi = kisiOlusturucu(strdup_safe(isim), atoi(yasStr), atoi(kalanOmurStr), strdup_safe(uzayAraciAdi)); 
            this->kisiListesi->add(this->kisiListesi, kisi); 
        }
    }
    fclose(dosya);
    return this->kisiListesi;
}

gezegenArrayList gezegenleriOku(DosyaOkuma this,char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya acilamadi");
        return NULL;
    }

    this->gezegenListesi = gezegenArrayListOlusturucu();

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
            Gezegen gezegen = gezegenOlusturucu(strdup_safe(isim), atoi(gununKacSaatStr), tarih); 
            this->gezegenListesi->add(this->gezegenListesi, gezegen);
        }
    }
    fclose(dosya);
    return this->gezegenListesi;
}
uzayAraciArrayList uzayAraclariniOku(DosyaOkuma this,char* dosyaAdi){
    FILE* dosya = fopen(dosyaAdi, "r");
    if(dosya==NULL){
        printf("Dosya acilamadi");
        return NULL;
    }

    this->aracListesi = uzayAraciArrayListOlusturucu();

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
            UzayAraci uzayAraci = uzayAraciOlusturucu(strdup_safe(isim),strdup_safe(cikisGezegeni), strdup_safe(varisGezegeni),
                tarih, atoi(mesafeSaatStr)); 
            this->aracListesi->add(this->aracListesi, uzayAraci);
        }
    }
    fclose(dosya);
    return this->aracListesi;
}
char* strdup_safe(const char* src) {
    if (!src) return NULL;
    char* dst = (char*)malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}
void dosyaOkumaYoket(DosyaOkuma this){
    if(this==NULL)
        return;
    this->kisiListesi->yoket(this->kisiListesi);
    this->gezegenListesi->yoket(this->gezegenListesi);
    this->aracListesi->yoket(this->aracListesi);
    free(this);
}