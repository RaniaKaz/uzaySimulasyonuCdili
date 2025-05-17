#ifndef SIMULASYON_H
#define SIMULASYON_H
#include "KisiArrayList.h"
#include "GezegenArrayList.h"
#include "UzayAraciArrayList.h"
#include "DosyaOkuma.h"
#include <string.h>   // strcmp için
struct SIMULASYON{
    DosyaOkuma dosyaOkuma;
    kisiArrayList kisiler;
    gezegenArrayList gezegenler;
    uzayAraciArrayList uzayAraclari;
    void (*baslat)(struct SIMULASYON*);
    void (*birSaatIlerle)(struct SIMULASYON*);
    void (*ekranGuncelle)(struct SIMULASYON*,int);
    Gezegen (*gezegenBul)(struct SIMULASYON*, char*);
    Boolean (*tumAraclarVardiMi)(struct SIMULASYON*);
    Zaman (*gezegenZamani)(struct SIMULASYON*, char*);
    void (*bekle)(int);
    void (*yoket)(struct SIMULASYON*);
};
typedef struct SIMULASYON* Simulasyon;

Simulasyon simulasyonOlusturucu();
void baslat(Simulasyon);
void birSaatIlerleSimulasyon(const Simulasyon);
void ekranGuncelle(const Simulasyon, int);
Zaman gezegenZamani(const Simulasyon, char*);
Gezegen gezegenBul(const Simulasyon, char*);
Boolean tumAraclarVardiMi(const Simulasyon);
void bekle(int);
void yoketSimulasyon(Simulasyon);
#endif