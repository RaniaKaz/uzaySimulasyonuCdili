#ifndef GEZEGEN_H
#define GEZEGEN_H
#include "kisiArrayList.h"
#include "uzayAraciArrayList.h"
#include "Zaman.h"
struct GEZEGEN{
    char* isim;
    int gununSaatSayisi;
    Zaman tarih;
    kisiArrayList nufus;
    uzayAraciArrayList araclar;
    char* (*getIsim)(struct GEZEGEN*);
    int (*getGununSaatSayisi)(struct GEZEGEN*);
    Zaman (*getTarih)(struct GEZEGEN*);
    kisiArrayList (*getNufus)(struct GEZEGEN*);
    void (*birSaatGecir)(struct GEZEGEN*);
    void (*aractakiYolculariEkle)(struct GEZEGEN*, UzayAraci);//kisi yerine uzay araci
    void (*aractakiYolculariSil)(struct GEZEGEN*, UzayAraci);//kisi yerine uzay araci
    void (*nufusuGuncelle)(struct GEZEGEN*); //yolda olan araçlarındaki yolculari nufüstan sil
    void (*yoket)(struct GEZEGEN*);
};

typedef struct GEZEGEN* Gezegen;


Gezegen gezegenOlusturucu(char*, int, Zaman);
char* getIsimGezegen(const Gezegen);
int getGununSaatSayisi(const Gezegen);
Zaman getTarih(const Gezegen);
kisiArrayList getNufus(const Gezegen);
void birSaatGecirGezegen(const Gezegen);
void aractakiYolculariEkle(const Gezegen,UzayAraci);
void aractakiYolculariSil(const Gezegen,UzayAraci);
void nufusuGuncelle(const Gezegen);
void gezegenYoket(Gezegen);

//arrayliste ait fonksiyonlar

#endif