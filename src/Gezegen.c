#include "gezegen.h"

Gezegen gezegenOlusturucu(char* isim, int gununSaatSayisi, Zaman tarih){
    Gezegen this;
    this=(Gezegen)malloc(sizeof(struct GEZEGEN));
    this->isim=isim;
    this->gununSaatSayisi=gununSaatSayisi;
    this->tarih=tarih;

    this->nufus->boyut=0;
    this->nufus->kapasite=10;
    this->nufus->kisiler=(struct KISI**)malloc(sizeof(struct KISI*)*this->nufus->kapasite);
    this->nufus->clear=&clearListKisi;
    this->nufus->add=&addToListKisi;
    this->nufus->removeAll=&removeAllListKisi;
    this->nufus->removeAndFreeAt=&removeAndFreeAtListKisi;

    this->araclar->boyut=0;
    this->araclar->kapasite=10;
    this->araclar->uzayAraclari=(struct UzayAraci**)malloc(sizeof(struct UzayAraci*)*this->araclar->kapasite); 
    this->araclar->clear=&clearListUzayAraci;
    this->araclar->add=&addToListUzayAraci;
    
    this->getIsim=&getIsim;
    this->getGununSaatSayisi=&getGununSaatSayisi;
    this->getTarih=&getTarih;
    this->getNufus=&getNufus;
    this->birSaatGecir=&birSaatGecir;
    this->aractakiYolculariEkle=&aractakiYolculariEkle;
    this->aractakiYolculariSil=&aractakiYolculariSil;
    this->nufusuGuncelle=&nufusuGuncelle;


    this->yoket=&gezegenYoket;
    return this;
}

char* getIsim(const Gezegen this){
    return this->isim;
}

int getGununSaatSayisi(const Gezegen this){
    return this->gununSaatSayisi;
}

struct ZAMAN* getTarih(const Gezegen this){
    return this->tarih;
}

kisiArrayList getNufus(const Gezegen this){
    return this->nufus;
}
void birSaatGecir(const Gezegen this){
    this->tarih->birSaatIlerle(this->tarih,this->gununSaatSayisi);
}

void aractakiYolculariEkle(const Gezegen this,UzayAraci uzayAraci){
    this->araclar->add(this->araclar,uzayAraci);
    this->nufus->addAll(uzayAraci->hayattakiYolculariAl(uzayAraci),this);
}
void aractakiYolculariSil(const Gezegen this ,UzayAraci uzayAraci){
    this->araclar->remove(this->araclar,uzayAraci);
    this->nufus->removeAll(this->nufus,uzayAraci->hayattakiYolculariAl(uzayAraci));
}

void nufusuGuncelle(const Gezegen this, uzayAraciArrayList list){
    UzayAraci* silinecekAraclar=malloc(sizeof(UzayAraci)*list->boyut);   
    int silinecekSayisi=0;
    for(int i=0; i < list->boyut; i++){
        UzayAraci uzayAraci = list->uzayAraclari[i];
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

    free(this->tarih);

    for(int i=0; i<this->nufus->boyut; i++){ //burada aynı şekilde
        free(this->nufus->kisiler[i]);
    }
    free(this->nufus->kisiler);

    for(int i=0; i<this->araclar->boyut; i++){ //uzay araclari içine yoket fonksyonu tanımla ve brada kullan
        free(this->araclar->uzayAraclari[i]);
    }
    free(this->araclar->uzayAraclari);

    free(this);
}

//arrayliste ait fonksiyonlar
void addToListGezegen(gezegenArrayList list, const Gezegen yeniGezegen){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->gezegenler=(Gezegen*)realloc(list->gezegenler, sizeof(Gezegen)*list->kapasite);
    }
    list->gezegenler[list->boyut++]=yeniGezegen;
}
void addAllToListGezegen(gezegenArrayList kaynak, const gezegenArrayList hedef){
    for(int i=0; i<hedef->boyut; i++){
        kaynak->add(kaynak,hedef->gezegenler[i]);
    }

}
void clearListGezegen(gezegenArrayList list){
    for(int i=0; i<list->boyut; i++){
        free(list->gezegenler[i]);
    }
    free(list->gezegenler);
    list->boyut=0;
    list->kapasite=0;
}