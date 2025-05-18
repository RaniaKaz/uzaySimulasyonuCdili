#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H
#include "Gezegen.h"
struct CUCEGEZEGEN {
    Gezegen super; // 0.01 - yaþlanma faktörü (100 kat daha uzun yaþam)
    float (*getYaslanmaKatSayisi)(struct CUCEGEZEGEN*);
    void (*yoket)(struct CUCEGEZEGEN*);
};
typedef struct CUCEGEZEGEN* CuceGezegen;

CuceGezegen cuceGezegenOlusturucu(char*, int, Zaman);
float getYaslanmaKatSayisiCG(CuceGezegen);
void yaslanmaSuresiHesaplaCuce(CuceGezegen);
void yoketCuce(CuceGezegen);

#endif