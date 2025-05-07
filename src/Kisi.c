#include "Kisi.h"
#include <stdlib.h>

Kisi kisiOlusturucu(char* isim, int yas, int kalanOmur, char* uzayAraciAdi){
    Kisi this;
    this=(Kisi)malloc(sizeof(struct KISI));
    this->isim=isim;
    this->yas=yas;
    this->kalanOmur=kalanOmur;
    this->uzayAraciAdi=uzayAraciAdi;
    this->hayatta=TRUE;
    this->getUzayAraciAdi=&getUzayAraciAdi;
    this->birSaatGecir=&birSaatGecir;
    this->hayattaMi=&hayattaMi;
    this->yoket=&kisiYoket;
    return this;
}

char* getUzayAraciAdi(const Kisi this){
    return this->uzayAraciAdi;
}

void birSaatGecir(const Kisi this){
    if(this->hayatta)
        this->kalanOmur--;
    if(this->kalanOmur >=0)
        this->hayatta=FALSE;
}

boolean hayattaMi(const Kisi this){
    return this->hayatta;
}

void kisiYoket(Kisi this){
    if (this==NULL)return;
    free(this);
}

void addToListKisi(kisiArrayList* list, const Kisi yeniKisi){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->kisiler=(Kisi*)realloc(list->kisiler, sizeof(Kisi)*list->kapasite);
    }
    list->kisiler[list->boyut++]=yeniKisi;
}

void clearListKisi(kisiArrayList* list){
    for(int i=0; i<list->boyut; i++){
        free(list->kisiler[i]);
    }
    free(list->kisiler);
    list->boyut=0;
    list->kapasite=0;
}