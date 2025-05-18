#include "CuceGezegen.h"

CuceGezegen cuceGezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih) {
    CuceGezegen this;
    this = (CuceGezegen)malloc(sizeof(struct CUCEGEZEGEN));
    this->super = gezegenOlusturucu(isim, gununSaatSayisi, tarih);
    this->super->yaslanmaKatsayisi=0.01f; // 100 kat daha uzun ya�am
    this->yoket = &yoketCuce;
    return this;
}

float getYaslanmaKatSayisiCG(CuceGezegen this){
    return this->super->yaslanmaKatsayisi;
}

void yaslanmaSuresiHesaplaCuce(CuceGezegen this) {
    // Bu fonksiyonu gerekirse ki�ilerin ya�lanma s�resini hesaplamak i�in kullanabilirsiniz
}

void yoketCuce(CuceGezegen this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}