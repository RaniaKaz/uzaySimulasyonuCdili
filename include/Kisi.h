#ifndef KISI_H
#define KISI_H
#include <stdlib.h>
#include "Boolean.h"
struct KISI{
    char *isim;
    int yas;
    int kalanOmur;
    char *uzayAraciAdi;
    int hayatta;
    char* (*getUzayAraciAdi)(struct KISI*);
    void (*birSaatGecir)(struct KISI*);
    Boolean (*hayattaMi)(struct KISI*);
    void (*yoket)(struct KISI*);
};

typedef struct KISI* Kisi;


Kisi kisiOlusturucu(char*, int, int, char*);
char* getUzayAraciAdi(const Kisi);
void birSaatGecirKisi(const Kisi);
Boolean hayattaMi(const Kisi);
void kisiYoket(Kisi);

//arrayliste ait fonksiyonlar

 #endif
