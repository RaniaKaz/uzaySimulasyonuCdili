#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H
#include "KisiArrayList.h"
#include "GezegenArrayList.h"
#include "UzayAraciArrayList.h"
#include "KayacGezegen.h"
#include "BuzDeviGezegen.h"
#include "GazDeviGezegen.h"
#include "CuceGezegen.h"
#include <string.h>
#include <stdio.h>

struct DOSYAOKUMA{
    kisiArrayList kisiListesi;
    gezegenArrayList gezegenListesi;
    uzayAraciArrayList aracListesi;
    kisiArrayList (*kisileriOku)(struct DOSYAOKUMA*,char*);
    gezegenArrayList (*gezegenleriOku)(struct DOSYAOKUMA*,char*);
    uzayAraciArrayList (*uzayAraclariniOku)(struct DOSYAOKUMA*,char*);
    void (*yoket)(struct DOSYAOKUMA*);
};
typedef struct DOSYAOKUMA* DosyaOkuma;

DosyaOkuma dosyaOkumaOlusturucu();
char* strdup_safeD(const char*);
kisiArrayList kisileriOku(DosyaOkuma,char*);
gezegenArrayList gezegenleriOku(DosyaOkuma,char*);
uzayAraciArrayList uzayAraclariniOku(DosyaOkuma,char*);
void dosyaOkumaYoket(DosyaOkuma);

#endif