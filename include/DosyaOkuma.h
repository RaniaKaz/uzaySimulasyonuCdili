#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H
#include "kisi.h"
#include "Gezegen.h"
#include "UzayAraci.h"

struct DOSYAOKUMA{
    kisiArrayList (*kisileriOku)(struct DOSYAOKYMA*,char*);
    gezegenArrayList (*gezegenleriOku)(struct DOSYAOKYMA*,char*);
    uzayAraciArrayList (*uzayAraclariniOku)(struct DOSYAOKYMA*,char*);
    void (*yoket)(struct DOSYAOKUMA*);
};
typedef struct DOSYAOKUMA* DosyaOkuma;

kisiArrayList kisileriOku(const DosyaOkuma, char*);
gezegenArrayList gezegenleriOku(const DosyaOkuma,char*);
uzayAraciArrayList uzayAraclariniOku(const DosyaOkuma,char*);
void dosyaOkumaYoket(DosyaOkuma);

#endif