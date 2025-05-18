#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H
#include "Gezegen.h"
struct CUCEGEZEGEN {
    Gezegen super; // 0.01 - ya�lanma fakt�r� (100 kat daha uzun ya�am)
    float (*getYaslanmaKatSayisi)(struct CUCEGEZEGEN*);
    void (*yoket)(struct CUCEGEZEGEN*);
};
typedef struct CUCEGEZEGEN* CuceGezegen;

CuceGezegen cuceGezegenOlusturucu(char*, int, Zaman);
float getYaslanmaKatSayisiCG(CuceGezegen);
void yaslanmaSuresiHesaplaCuce(CuceGezegen);
void yoketCuce(CuceGezegen);

#endif