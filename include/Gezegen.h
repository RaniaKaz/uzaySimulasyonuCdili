#ifndef GEZEGEN_H
#define GEZEGEN_H
#include "kisi.h"

struct GEZEGEN{
    char* isim;
    int gununSaatSayisi;
    struct ZAMAN* tarih;
    kisiArrayList nufus;
    //uzay araciArrayList uzayAraclari;
    char* (*getIsim)(struct GEZEGEN*);
    int (*getGununSaatSayisi)(struct GEZEGEN*);
    struct ZAMAN* (*getTarih)(struct GEZEGEN*);
    kisiArrayList (*getNufus)(struct GEZEGEN*);
    void (*birSaatGecir)(struct GEZEGEN*);
    void (*aractakiYolculariEkle)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*aractakiYolculariSil)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*nufusuGuncelle)(struct GEZEGEN*); //yolda olan araçlarındaki yolculari nufüstan sil
    void (*yoket)(struct GEZEGEN*);
};
typedef struct{
    struct GEZEGEN** gezegenler;
    int gezegenSayisi;
    int maxGezegenSayisi;
} gezegenArrayList;
typedef struct GEZEGEN* Gezegen;

Gezegen gezegenOlusturucu(char*, int, struct ZAMAN*);
char* getIsim(const Gezegen);
int getGununSaatSayisi(const Gezegen);
struct ZAMAN* getTarih(const Gezegen);
kisiArrayList getNufus(const Gezegen);
void birSaatGecir(const Gezegen);
void aractakiYolculariEkle(const Gezegen, Kisi);//kisi yerine uzay araci
void aractakiYolculariSil(const Gezegen, Kisi);//kisi yerine uzay araci
void nufusuGuncelle(const Gezegen);
void gezegenYoket(Gezegen);
#endif