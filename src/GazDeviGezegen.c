#include "GazDeviGezegen.h"

GazDeviGezegen gazDeviGezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih) {
    GazDeviGezegen this;
    this = (GazDeviGezegen)malloc(sizeof(struct GAZDEVIGEZEGEN));
    this->super = gezegenOlusturucu(isim, gununSaatSayisi, tarih);
    this->super->yaslanmaKatsayisi=0.1f; // 10 kat daha uzun yaþam
    this->yoket = &yoketGazDevi;
    return this;
}

float getYaslanmaKatSayisiGDG(GazDeviGezegen this){
    return this->super->yaslanmaKatsayisi;
}

void yaslanmaSuresiHesaplaGazDevi(GazDeviGezegen this) {
    // Bu fonksiyonu gerekirse kiþilerin yaþlanma süresini hesaplamak için kullanabilirsiniz
}

void yoketGazDevi(GazDeviGezegen this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}