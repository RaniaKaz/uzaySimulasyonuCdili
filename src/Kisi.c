#include "Kisi.h"
#include <stdlib.h>

Kisi kisiOlusturucu(char* isim, int yas, int kalanOmur, char* uzayAraciAdi){
    Kisi this;
    this=(Kisi)malloc(sizeof(struct KISI));
    this->isim=isim;
    this->yas=yas;
    this->kalanOmur=kalanOmur;
    this->uzayAraciAdi=uzayAraciAdi;
    this->hayatta=TRUE;
    this->getUzayAraciAdi=&getUzayAraciAdi;
    this->birSaatGecir=&birSaatGecir;
    this->hayattaMi=&hayattaMi;
    this->yoket=&kisiYoket;
    return this;
}

char* getUzayAraciAdi(const Kisi this){
    return this->uzayAraciAdi;
}

void birSaatGecir(const Kisi this){
    if(this->hayatta)
        this->kalanOmur--;
    if(this->kalanOmur <=0){
        this->hayatta=FALSE;
        this->yoket(this);
    }

}

boolean hayattaMi(const Kisi this){
    return this->hayatta;
}

void kisiYoket(Kisi this){
    if (this==NULL)return;
    free(this);
}

void addToListKisi(kisiArrayList list, const Kisi yeniKisi){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->kisiler=(Kisi*)realloc(list->kisiler, sizeof(Kisi)*list->kapasite);
    }
    list->kisiler[list->boyut++]=yeniKisi;
}

void addAllToListKisi(kisiArrayList hedef, const kisiArrayList kaynak){
    for (int i=0; i<kaynak->boyut; i++){
        if(hedef->boyut==hedef->kapasite){
            hedef->kapasite*=2;
            hedef->kisiler=(Kisi*)realloc(hedef->kisiler, sizeof(Kisi)*hedef->kapasite);
        }
        hedef->kisiler[hedef->boyut++]=kaynak->kisiler[i];
    }
}

void clearListKisi(kisiArrayList list){
    for(int i=0; i<list->boyut; i++){
        kisiYoket(list->kisiler[i]);
    }
    free(list->kisiler);
    list->boyut=0;
    list->kapasite=0;
}

void removeAllListKisi(kisiArrayList hedef,const kisiArrayList silinecek){
    for(int i=0;i < silinecek->boyut; i++){
        Kisi kisi=silinecek->kisiler[i];
        for(int j=0; j < hedef->boyut; j++){
            if(hedef->kisiler[j]==kisi){
                removeAndFreeAt(hedef,j);
                j--;
                break;
            }
        }
    }
}

void removeAndFreeAtListKisi(kisiArrayList list, int index){
    if(index <0 || index >= list->boyut) return;
    
    free(list->kisiler[index]);

    for(int i=index; i<list->boyut-1; i++){
        list->kisiler[i]=list->kisiler[i+1];
    }
    list->boyut--;
}