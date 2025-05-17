#ifndef SIMULASYON_H
#define SIMULASYON_H
#include <stdlib.h>  // malloc için
#include "KisiArrayList.h"
#include "GezegenArrayList.h"
#include "UzayAraciArrayList.h"
#include "DosyaOkuma.h"
struct SIMULASYON{
    kisiArrayList kisiler;
    gezegenArrayList gezegenler;
    uzayAraciArrayList uzayAraclari;
    void (*baslat)(struct SIMULASYON*);
    void (*birSaatIlerle)(struct SIMULASYON*);
    void (*ekranGuncelle)(struct SIMULASYON*);
    Gezegen (*gezegenBul)(struct SIMULASYON*, char*);
    boolean (*tumAraclarVardiMi)(struct SIMULASYON*);
    Zaman (*gezegenZamani)(struct SIMULASYON*, char*);
    void (*bekle)(int);
    void (*yoket)(struct SIMULASYON*)
};
typedef struct SIMULASYON* Simulasyon;

Simulasyon simulasyonOlusturucu();
void baslat(const Simulasyon);
void birSaatIlerle(const Simulasyon);
void ekranGuncelle(const Simulasyon, int);
Zaman gezegenZamani(const Simulasyon, char*);
Gezegen gezegenBul(const Simulasyon, char*);
boolean tumAraclarVardiMi(const Simulasyon);
void bekle(int);
void yoketSimulasyon(Simulasyon);
#endif