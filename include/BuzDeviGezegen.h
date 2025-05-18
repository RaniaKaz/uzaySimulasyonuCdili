#ifndef BUZDEVIGEZEGEN_H
#define BUZDEVIGEZEGEN_H
#include "Gezegen.h"
struct BUZDEVIGEZEGEN {
    Gezegen super;// 0.5 - yaþlanma faktörü (2 kat daha uzun yaþam)
    float (*getYaslanmaKatSayisi)(struct BUZDEVIGEZEGEN*);
    void (*yoket)(struct BUZDEVIGEZEGEN*);
};
typedef struct BUZDEVIGEZEGEN* BuzDeviGezegen;

BuzDeviGezegen buzDeviGezegenOlusturucu(char*, int, Zaman);
float getYaslanmaKatSayisiBDG(BuzDeviGezegen);
void yaslanmaSuresiHesaplaBuzDevi(BuzDeviGezegen);
void yoketBuzDevi(BuzDeviGezegen);
#endif