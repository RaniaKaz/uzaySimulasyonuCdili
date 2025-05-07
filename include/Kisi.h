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
    boolean (*hayattaMi)(struct KISI*);
    void (*yoket)(struct KISI*);
};
typedef struct{
    struct KISI** kisiler;
    int boyut;
    int kapasite;
    void (*add)(kisiArrayList*,struct KISI*);
    void (*clear)(kisiArrayList*);
} kisiArrayList;
//this->clear=&clear nerede demeliyim
typedef struct KISI* Kisi;
Kisi kisiOlusturucu(char*, int, int, char*);
char* getUzayAraciAdi(const Kisi);
void birSaatGecir(const Kisi);
boolean hayattaMi(const Kisi);
void kisiYoket(Kisi);

//arrayliste ait fonksiyonlar
void addToListKisi(kisiArrayList*,const Kisi);
void clearListKisi(kisiArrayList*);
 #endif
