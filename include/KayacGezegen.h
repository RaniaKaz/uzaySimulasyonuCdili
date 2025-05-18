#ifndef KAYACGEZEGEN_H
#define KAYACGEZEGEN_H
#include "Gezegen.h"

struct KAYACGEZEGEN{
    Gezegen super;
    float (*getYaslanmaKatSayisi)(struct KAYACGEZEGEN*);
    void (*yoket)(struct KAYACGEZEGEN*);
};
typedef struct KAYACGEZEGEN* KayacGezegen;

KayacGezegen kayacGezegenOlusturucu(char*,int,Zaman);
float getYaslanmaKatSayisiKG(KayacGezegen);
void yoketKayac(KayacGezegen);
#endif