#include "gezegen.h"

Gezegen gezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih){
    Gezegen this;
    this=(Gezegen)malloc(sizeof(struct GEZEGEN));
    this->isim=isim;
    this->gununSaatSayisi=gununSaatSayisi;
    this->tarih=tarih;

    this->nufus=kisiArrayListOlusturucu();
    this->araclar=uzayAraciArrayListOlusturucu();
        
    this->getIsim=&getIsimGezegen;
    this->getGununSaatSayisi=&getGununSaatSayisi;
    this->getTarih=&getTarih;
    this->getNufus=&getNufus;
    this->birSaatGecir=&birSaatGecirGezegen;
    this->aractakiYolculariEkle=&aractakiYolculariEkle;
    this->aractakiYolculariSil=&aractakiYolculariSil;
    this->nufusuGuncelle=&nufusuGuncelle;


    this->yoket=&gezegenYoket;
    return this;
}
char* getIsimGezegen(const Gezegen this){
    return this->isim;
}

int getGununSaatSayisi(const Gezegen this){
    return this->gununSaatSayisi;
}

Zaman getTarih(const Gezegen this){
    return this->tarih;
}

kisiArrayList getNufus(const Gezegen this){
    return this->nufus;
}
void birSaatGecirGezegen(const Gezegen this){
    this->tarih->birSaatIlerle(this->tarih,this->gununSaatSayisi);
}

void aractakiYolculariEkle(const Gezegen this,UzayAraci uzayAraci){
    this->araclar->add(this->araclar,uzayAraci);
    this->nufus->addAll(this->nufus,uzayAraci->hayattakiYolculariAl(uzayAraci));
}
void aractakiYolculariSil(const Gezegen this ,UzayAraci uzayAraci){
    this->araclar->remove(this->araclar, uzayAraci);
    kisiArrayList hayattakiler = uzayAraci->hayattakiYolculariAl(uzayAraci);
    this->nufus->removeAll(this->nufus, hayattakiler);

    //free(hayattakiler->kisiler);
    free(hayattakiler);
}

void nufusuGuncelle(const Gezegen this) {
    //printf(" kontrol 1 ");
    
    // Önce silinecek araçlarýn indekslerini bul
    int* silinecekIndeksler = (int*)malloc(sizeof(int) * this->araclar->boyut);
    int silinecekSayisi = 0;
    
    for(int i = 0; i < this->araclar->boyut; i++) {
       // printf(" kontrol 2 ");
        UzayAraci uzayAraci = this->araclar->uzayAraclari[i];
        //printf(" kontrol 3 ");
        if(uzayAraci != NULL && uzayAraci->yoldaMi(uzayAraci)) {
            //printf(" kontrol 4 ");
            silinecekIndeksler[silinecekSayisi++] = i;
        }
        //printf(" kontrol 5 ");
    }
    
    // Silinecek araçlarý sondan baþlayarak sil (indeks kaymasýný önlemek için)
    for(int i = silinecekSayisi - 1; i >= 0; i--) {
        //printf(" kontrol 6 ");
        int indeks = silinecekIndeksler[i];
        UzayAraci silinecekArac = this->araclar->uzayAraclari[indeks];
        this->aractakiYolculariSil(this, silinecekArac);
        
        // Aracý listeden de kaldýr
        this->araclar->uzayAraclari[indeks] = NULL;
        for(int j = indeks; j < this->araclar->boyut - 1; j++) {
            this->araclar->uzayAraclari[j] = this->araclar->uzayAraclari[j+1];
        }
        this->araclar->boyut--;
        //printf(" kontrol 7 ");
    }
    
    free(silinecekIndeksler);
    //printf(" kontrol 8 ");
}
/*void nufusuGuncelle(const Gezegen this){
    uzayAraciArrayList silinecekAraclar=uzayAraciArrayListOlusturucu();
    printf(" kontrol 1 ");
    for(int i=0; i < this->araclar->boyut; i++){
        printf(" kontrol 2 ");
        UzayAraci uzayAraci= this->araclar->uzayAraclari[i];
        printf(" kontrol 3 ");
        if(uzayAraci->yoldaMi(uzayAraci)){
            printf(" kontrol 4 ");
            silinecekAraclar->add(silinecekAraclar,uzayAraci);
        }
        printf(" kontrol 5 ");
    }
    for(int i=0; i < silinecekAraclar->boyut; i++){
        printf(" kontrol 6 ");
        this->aractakiYolculariSil(this,silinecekAraclar->uzayAraclari[i]); //sorun burada
        printf(" kontrol 7 ");
    }
    printf(" kontrol 8 ");
    
        free(silinecekAraclar->uzayAraclari);
        printf(" kontrol 9 ");
    free(silinecekAraclar);
    printf(" kontrol 10 ");
    /*UzayAraci* silinecekAraclar=malloc(sizeof(UzayAraci) * this->araclar->boyut);  

        if (silinecekAraclar == NULL) {
        fprintf(stderr, "Bellek ayýrma hatasý: nufusuGuncelle\n");
        return;
    }
    
    int silinecekSayisi=0;
    for(int i=0; i < this->araclar->boyut; i++){
        UzayAraci uzayAraci = this->araclar->uzayAraclari[i];
        if(uzayAraci->yoldaMi(uzayAraci)){
            silinecekAraclar[silinecekSayisi++]=uzayAraci;
        }
    }

    //yolculari sil
    for(int i=0; i< silinecekSayisi; i++){
        this->aractakiYolculariSil(this,silinecekAraclar[i]);
    }

    free(silinecekAraclar);
}*/
void gezegenYoket(Gezegen this){
    if(this==NULL) return;
    free(this->isim);
    this->tarih->yoket(this->tarih);

    for(int i=0; i<this->nufus->boyut; i++){
        this->nufus->kisiler[i]->yoket(this->nufus->kisiler[i]);
    }
    free(this->nufus->kisiler);
    free(this->nufus);

    for(int i=0; i<this->araclar->boyut; i++){ //uzay araclari iÃ§ine yoket fonksyonu tanÄ±mla ve brada kullan
        this->araclar->uzayAraclari[i]->yoket(this->araclar->uzayAraclari[i]);
    }
    free(this->araclar->uzayAraclari); // Dizi alanÄ±nÄ± temizle
    free(this->araclar);               // YapÄ±nÄ±n kendisini temizle
    free(this);
}

//arrayliste ait fonksiyonlar
