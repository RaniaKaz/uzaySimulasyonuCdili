#include "BuzDeviGezegen.h"
BuzDeviGezegen buzDeviGezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih) {
    BuzDeviGezegen this;
    this = (BuzDeviGezegen)malloc(sizeof(struct BUZDEVIGEZEGEN));
    this->super = gezegenOlusturucu(isim, gununSaatSayisi, tarih);
    this->super->yaslanmaKatsayisi=0.5f; // 2 kat daha uzun ya�am
    this->yoket = &yoketBuzDevi;
    return this;
}

float getYaslanmaKatSayisiBDG(BuzDeviGezegen this){
    return this->super->yaslanmaKatsayisi;
}
void yaslanmaSuresiHesaplaBuzDevi(BuzDeviGezegen this) {
    // Bu fonksiyonu gerekirse ki�ilerin ya�lanma s�resini hesaplamak i�in kullanabilirsiniz
}

void yoketBuzDevi(BuzDeviGezegen this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}