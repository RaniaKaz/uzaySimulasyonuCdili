#ifndef UZAYARACI_H
#define UZAYARACI_H
#include "kisi.h"

struct UZAYARACI{
    char* isim;
    char* cikisGezegeni;
    char* varisGezegeni;
    char* hedefeVaracagiTarih;
    char* cikisTarihi;
    int mesafeSaat; // mesafe saat cinsinden
    int kalanSaat;
    int yolda; //boolean
    int imha; //boolean
    kisiArrayList yolcular;
    char* (*getIsim)(struct UZAYARACI*);
    char* (*getCikisGezegeni)(struct UZAYARACI*);
    char* (*getVarisGezegeni)(struct UZAYARACI*);
    void (*birSaatGecir)(struct UZAYARACI*,char*);
    
};
#endif