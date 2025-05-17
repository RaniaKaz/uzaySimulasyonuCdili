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
    this->birSaatGecir=&birSaatGecirKisi;
    this->hayattaMi=&hayattaMi;
    this->yoket=&kisiYoket;
    return this;
}

char* getUzayAraciAdi(const Kisi this){
    return this->uzayAraciAdi;
}

void birSaatGecirKisi(const Kisi this){
    if(this==NULL && !this->hayatta) return;
    if(this->hayatta)
        this->kalanOmur--;
    if(this->kalanOmur <=0){
        this->hayatta=FALSE;
        //this->yoket(this);
    }

}

boolean hayattaMi(const Kisi this){
    if(this==NULL) return FALSE;
    return this->hayatta;
}

void kisiYoket(Kisi this){
    if (this==NULL)return;
    free(this);
}

//arraylist e ait fonlsyonlar

