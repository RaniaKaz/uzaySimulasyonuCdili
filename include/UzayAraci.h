#ifndef UZAYARACI_H
#define UZAYARACI_H
#include "kisiArrayList.h"
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
    void (*birSaatGecir)(struct UZAYARACI*,struct ZAMAN*); //char* şimdiki zaman
    void (*yolcuEkle)(struct UZAYARACI*,struct KISI*);
    void (*yolculariGuncelle)(struct UZAYARACI*);
    kisiArrayList (*hayattakiYolculariAl)(struct UZAYARACI*);
    int (*yoldaMi)(struct UZAYARACI*);
    boolean (*hedefeUlastiMi)(struct UZAYARACI*);
    int (*imhaMi)(struct UZAYARACI*);
    void (*varacagiTarihiHesapla)(struct UZAYARACI*,int);
    char* (*toString)(struct UZAYARACI*);
    void (*yoket)(struct UZAYARACI*);
};
typedef struct UZAYARACI* UzayAraci;

UzayAraci uzayAraciOlusturucu(char*,char*,char*,struct ZAMAN*,int);
char* getIsimUzayAraci(const UzayAraci);
char* getCikisGezegeni(const UzayAraci);
char* getVarisGezegeni(const UzayAraci);
void birSaatGecirUzayAraci(const UzayAraci,struct ZAMAN*);
void yolcuEkle(const UzayAraci,struct KISI*);
void yolculariGuncelle(const UzayAraci);
kisiArrayList hayattakiYolculariAl(const UzayAraci);
int yoldaMi(const UzayAraci);
boolean hedefeUlastiMi(const UzayAraci);
int imhaMi(const UzayAraci);
void varacagiTarihiHesapla(const UzayAraci,int);
char* toStringUzayAraci(const UzayAraci);
void uzayAraciYoket(UzayAraci);

//arrayliste ait fonksiyonlar

#endif