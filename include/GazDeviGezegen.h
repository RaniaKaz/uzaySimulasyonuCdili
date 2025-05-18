#ifndef GAZDEVIGEZEGEN_H
#define GAZDEVIGEZEGEN_H
#include "Gezegen.h"
struct GAZDEVIGEZEGEN {
    Gezegen super; // 0.1 - ya�lanma fakt�r� (10 kat daha uzun ya�am)
    float (*getYaslanmaKatSayisi)(struct GAZDEVIGEZEGEN*);
    void (*yoket)(struct GAZDEVIGEZEGEN*);
};
typedef struct GAZDEVIGEZEGEN* GazDeviGezegen;

GazDeviGezegen gazDeviGezegenOlusturucu(char*, int, Zaman );
float getYaslanmaKatSayisiGDG(GazDeviGezegen);
void yaslanmaSuresiHesaplaGazDevi(GazDeviGezegen);
void yoketGazDevi(GazDeviGezegen);
#endif
