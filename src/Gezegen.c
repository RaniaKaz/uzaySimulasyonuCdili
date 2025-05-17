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
    this->nufus->addAll(uzayAraci->hayattakiYolculariAl(uzayAraci),this);
}
void aractakiYolculariSil(const Gezegen this ,UzayAraci uzayAraci){
    this->araclar->remove(this->araclar,uzayAraci);
    this->nufus->removeAll(this->nufus,uzayAraci->hayattakiYolculariAl(uzayAraci)); //free etmem mi gerek?
}

void nufusuGuncelle(const Gezegen this){
    UzayAraci* silinecekAraclar=malloc(sizeof(UzayAraci) * this->araclar->boyut);   
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
}
void gezegenYoket(Gezegen this){
    if(this==NULL) return;

    this->tarih->yoket(this->tarih);

    for(int i=0; i<this->nufus->boyut; i++){
        this->nufus->kisiler[i]->yoket(this->nufus->kisiler[i]);
    }
    free(this->nufus->kisiler);
    free(this->nufus);

    for(int i=0; i<this->araclar->boyut; i++){ //uzay araclari içine yoket fonksyonu tanımla ve brada kullan
        this->araclar->uzayAraclari[i]->yoket(this->araclar->uzayAraclari[i]);
    }
    free(this->araclar->uzayAraclari); // Dizi alanını temizle
    free(this->araclar);               // Yapının kendisini temizle
    free(this);
}

//arrayliste ait fonksiyonlar
