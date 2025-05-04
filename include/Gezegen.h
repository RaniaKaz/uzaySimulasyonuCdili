#ifndef GEZEGEN_H
#define GEZEGEN_H
#include "kisi.h"

struct GEZEGEN{
    char* isim;
    int gununSaatSayisi;
    char* tarih;
    kisiArrayList nufus;
    //uzay araciArrayList uzayAraclari;
    char* (*getIsim)(struct GEZEGEN*);
    int (*getGununSaatSayisi)(struct GEZEGEN*);
    char* (*getTarih)(struct GEZEGEN*);
    kisiArrayList (*getNufus)(struct GEZEGEN*);
    void (*birSaatGecir)(struct GEZEGEN*);
    void (*aractakiYolculariEkle)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*aractakiYolculariSil)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*nufusuGuncelle)(struct GEZEGEN*); //yolda olan araçlarındaki yolculari nufüstan sil
    void (*yoket)(struct GEZEGEN*);
};
typedef struct GEZEGEN* Gezegen;

Gezegen gezegenOlusturucu(char*, int, char*);
char* getIsim(const Gezegen);
int getGununSaatSayisi(const Gezegen);
char* getTarih(const Gezegen);
kisiArrayList getNufus(const Gezegen);
void birSaatGecir(const Gezegen);
void aractakiYolculariEkle(const Gezegen, Kisi);//kisi yerine uzay araci
void aractakiYolculariSil(const Gezegen, Kisi);//kisi yerine uzay araci
void nufusuGuncelle(const Gezegen);
void yoket(Gezegen);
#endif