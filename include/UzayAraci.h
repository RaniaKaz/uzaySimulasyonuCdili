#ifndef UZAYARACI_H
#define UZAYARACI_H
#include "kisi.h"
#include "Zaman.h"
struct UZAYARACI{
    char* isim;
    char* cikisGezegeni;
    char* varisGezegeni;
    char* hedefeVaracagiTarih;
    struct ZAMAN* cikisTarihi;
    int mesafeSaat; // mesafe saat cinsinden
    int kalanSaat;
    int yolda; //boolean
    int imha; //boolean
    kisiArrayList yolcular;
    char* (*getIsim)(struct UZAYARACI*);
    char* (*getCikisGezegeni)(struct UZAYARACI*);
    char* (*getVarisGezegeni)(struct UZAYARACI*);
    void (*birSaatGecir)(struct UZAYARACI*,char*); //char* şimdiki zaman
    void (*yolcuEkle)(struct UZAYARACI*,struct KISI*);
    void (*yolculariGuncelle)(struct UZAYARACI*);
    kisiArrayList (*hayattakiYolculariAl)(struct UZAYARACI*);
    int (*yoldaMi)(struct UZAYARACI*);
    int (*hedefeUlastiMi)(struct UZAYARACI*);
    int (*imhaMi)(struct UZAYARACI*);
    char* (*toString)(struct UZAYARACI*,void*);

};
typedef struct{
    struct UZAYARACI** uzayAraclari;
    int boyut;
    int kapasite;
    void (*add)(uzayAraciArrayList*,struct UZAYARAC*);
    void (*clear)(uzayAraciArrayList*);
} uzayAraciArrayList;
typedef struct UZAYARACI* UzayAraci;

UzayAraci uzayAraciOlusturucu(char*,char*,char*,struct ZAMAN*,int);
char* getIsim(const UzayAraci);
char* getCikisGezegeni(const UzayAraci);
char* getVarisGezegeni(const UzayAraci);
void birSaatGecir(const UzayAraci,struct ZAMAN*);
void yolcuEkle(const UzayAraci,struct KISI*);
void yolculariGuncelle(const UzayAraci);
kisiArrayList hayattakiYolculariAl(const UzayAraci);
int yoldaMi(const UzayAraci);
int hedefeUlastiMi(const UzayAraci);
int imhaMi(const UzayAraci);
char* toString(const UzayAraci,void*);
void uzayAraciYoket(UzayAraci);

//arrayliste ait fonksiyonlar
void addToListUzayAraci(uzayAraciArrayList*,const UzayAraci);
void clearListUzayAraci(uzayAraciArrayList*);
#endif