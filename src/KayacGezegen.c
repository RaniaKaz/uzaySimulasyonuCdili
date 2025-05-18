#include "KayacGezegen.h"
KayacGezegen kayacGezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih){
    KayacGezegen this;
    this=(KayacGezegen)malloc(sizeof(struct KAYACGEZEGEN));
    this->super=gezegenOlusturucu(isim,gununSaatSayisi,tarih);
    this->super->yaslanmaKatsayisi=1.0f;
    this->yoket=&yoketKayac;
    return this;
}

float getYaslanmaKatSayisiKG(KayacGezegen this){
    return this->super->yaslanmaKatsayisi;
}

void yoketKayac(KayacGezegen this){
    if(this==NULL) return;
    this->super->yoket(this->super);
    free(this);
}