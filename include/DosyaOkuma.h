#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H
#include "kisi.h"
#include "Gezegen.h"
#include "UzayAraci.h"

struct DOSYAOKUMA{
    kisiArrayList (*kisileriOku)(char*);
    gezegenArrayList (*gezegenleriOku)(char*);
    uzayAraciArrayList (*uzayAraclariniOku)(char*);
    void (*yoket)(struct DOSYAOKUMA*);
};
typedef struct DOSYAOKUMA* DosyaOkuma;

DosyaOkuma dosyaOkumaOlusturucu();
kisiArrayList kisileriOku(char*);
gezegenArrayList gezegenleriOku(char*);
uzayAraciArrayList uzayAraclariniOku(char*);
void dosyaOkumaYoket(DosyaOkuma);

#endif