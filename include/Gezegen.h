#ifndef GEZEGEN_H
#define GEZEGEN_H
#include "kisi.h"
#include "uzayAraci.h"
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
    void (*aractakiYolculariEkle)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*aractakiYolculariSil)(struct GEZEGEN*, Kisi);//kisi yerine uzay araci
    void (*nufusuGuncelle)(struct GEZEGEN*); //yolda olan araçlarındaki yolculari nufüstan sil
    void (*yoket)(struct GEZEGEN*);
};

typedef struct GEZEGEN* Gezegen;
typedef struct GezegenArrayList* gezegenArrayList;

struct GezegenArrayList{
    struct GEZEGEN** gezegenler;
    int boyut;
    int kapasite;
    void (*add)(gezegenArrayList*,struct GEZEGEN*);
    void (*addAll)( gezegenArrayList*,struct gezegenArrayList*);
    void (*clear)(gezegenArrayList*);
};

Gezegen gezegenOlusturucu(char*, int, Zaman);
char* getIsim(const Gezegen);
int getGununSaatSayisi(const Gezegen);
Zaman getTarih(const Gezegen);
kisiArrayList getNufus(const Gezegen);
void birSaatGecir(const Gezegen);
void aractakiYolculariEkle(const Gezegen,UzayAraci);//kisi yerine uzay araci
void aractakiYolculariSil(const Gezegen,UzayAraci);//kisi yerine uzay araci
void nufusuGuncelle(const Gezegen);
void gezegenYoket(Gezegen);

//arrayliste ait fonksiyonlar
void addToListGezegen(gezegenArrayList, const Gezegen);
void addAllToListGezegen(gezegenArrayList, const gezegenArrayList);
void clearListGezegen(gezegenArrayList);
#endif