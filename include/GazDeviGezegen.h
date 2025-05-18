#ifndef GAZDEVIGEZEGEN_H
#define GAZDEVIGEZEGEN_H
#include "Gezegen.h"
struct GAZDEVIGEZEGEN {
    Gezegen super; // 0.1 - yaþlanma faktörü (10 kat daha uzun yaþam)
    float (*getYaslanmaKatSayisi)(struct GAZDEVIGEZEGEN*);
    void (*yoket)(struct GAZDEVIGEZEGEN*);
};
typedef struct GAZDEVIGEZEGEN* GazDeviGezegen;

GazDeviGezegen gazDeviGezegenOlusturucu(char*, int, Zaman );
float getYaslanmaKatSayisiGDG(GazDeviGezegen);
void yaslanmaSuresiHesaplaGazDevi(GazDeviGezegen);
void yoketGazDevi(GazDeviGezegen);
#endif
