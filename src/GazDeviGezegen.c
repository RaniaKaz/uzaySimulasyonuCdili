#include "GazDeviGezegen.h"

GazDeviGezegen gazDeviGezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih) {
    GazDeviGezegen this;
    this = (GazDeviGezegen)malloc(sizeof(struct GAZDEVIGEZEGEN));
    this->super = gezegenOlusturucu(isim, gununSaatSayisi, tarih);
    this->super->yaslanmaKatsayisi=0.1f; // 10 kat daha uzun ya�am
    this->yoket = &yoketGazDevi;
    return this;
}

float getYaslanmaKatSayisiGDG(GazDeviGezegen this){
    return this->super->yaslanmaKatsayisi;
}

void yaslanmaSuresiHesaplaGazDevi(GazDeviGezegen this) {
    // Bu fonksiyonu gerekirse ki�ilerin ya�lanma s�resini hesaplamak i�in kullanabilirsiniz
}

void yoketGazDevi(GazDeviGezegen this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}