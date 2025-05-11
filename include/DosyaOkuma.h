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

kisiArrayList kisileriOku(char*);
gezegenArrayList gezegenleriOku(char*);
uzayAraciArrayList uzayAraclariniOku(char*);
void dosyaOkumaYoket(DosyaOkuma);

#endif