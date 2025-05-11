#include "UzayAraci.h"

UzayAraci uzayAraciOlusturucu(char* isim ,char* cikisGezegeni,char* varisGezegeni ,struct ZAMAN* cikisTarihi,int mesafeSaat){
    UzayAraci this;
    this=(UzayAraci)malloc(sizeof(struct UZAYARACI));
    this->isim=isim;
    this->cikisGezegeni=cikisGezegeni;
    this->varisGezegeni=varisGezegeni;
    this->cikisTarihi=cikisTarihi;
    this->mesafeSaat=mesafeSaat;
    this->kalanSaat=mesafeSaat;
    this->hedefeVaracagiTarih="";

    this->yolcular->boyut=0;
    this->yolcular->kapasite=10;
    this->yolcular->kisiler=(struct KISI**)malloc(sizeof(struct KISI*)*this->yolcular->kapasite);
    this->yolcular->clear=&clearListKisi;
    this->yolcular->add=&addToListKisi;
    this->yolcular->removeAll=&removeAllListKisi;
    this->yolcular->removeAndFreeAt=&removeAndFreeAtListKisi;

    this->imha=FALSE;
    this->yolda=FALSE;
}

char* getIsim(const UzayAraci this){
    return this->isim;
}

char* getCikisGezegeni(const UzayAraci this){
    return this->cikisGezegeni;
}

char* getVarisGezegeni(const UzayAraci this){
    return this->varisGezegeni;
}

void birSaatGecir(const UzayAraci this ,struct ZAMAN* simdikiZaman){
    if(!(this->yolda) && simdikiZaman->esitMi(simdikiZaman,this->cikisTarihi)){
        this->yolda=TRUE;
    }
    else if(this->yolda && !(this->imha)){
        this->kalanSaat--;
        if(this->kalanSaat <= 0){
            this->kalanSaat=0;
        }
    }
}

void yolcuEkle(const UzayAraci this,struct KISI* kisi){
    this->yolcular->add(this->yolcular,kisi);
}

void yolculariGuncelle(const UzayAraci this){
    for(int i=0; i<this->yolcular->boyut; i++){
        this->yolcular->kisiler[i]->birSaatGecir(this->yolcular->kisiler[i]);
    }

    boolean hayattaVar=FALSE;    

    for(int i=0; i<this->yolcular->boyut; i++){
        if(this->yolcular->kisiler[i]->hayattaMi(this->yolcular->kisiler[i])){
            hayattaVar=TRUE;
            break;
        }
    }
    this->imha= (hayattaVar ==FALSE ) ? TRUE : FALSE;
}

kisiArrayList hayattakiYolculariAl(const UzayAraci this){
    kisiArrayList hayattakiler;
    hayattakiler->boyut=0;
    hayattakiler->kapasite=10;
    hayattakiler->kisiler=(struct KISI**)malloc(sizeof(struct KISI)* hayattakiler->kapasite);
    for(int i=0; i<this->yolcular->boyut; i++){
        if(this->yolcular->kisiler[i]->hayattaMi(this->yolcular->kisiler[i])){
            hayattakiler->add(hayattakiler,this->yolcular->kisiler[i]);
        }
    }
    return hayattakiler;
}

int yoldaMi(const UzayAraci this){
    return this->yolda;
}

int hedefeUlastiMi(const UzayAraci this){
    return this->kalanSaat<=0;
}

int imhaMi(const UzayAraci this){
    return this->imha;
}

char* toString(const UzayAraci this){
    char* yolDurumu;
    int toplamUzunluk=36;
    toplamUzunluk+=strlen(this->isim);
    toplamUzunluk+=strlen(this->cikisGezegeni);
    toplamUzunluk+=strlen(this->varisGezegeni);
    if(this->imha){
        yolDurumu="İMHA";
        toplamUzunluk+=strlen(yolDurumu);
        char* str=(char*)malloc(sizeof(char)*toplamUzunluk);
        sprintf(str, "%-25s %-25s %-25s %-25s %-25s %-25s", this->isim, 
            yolDurumu,this->cikisGezegeni,this->varisGezegeni,"--","--");
            return str;
    }
    else{
        if(this->hedefeUlastiMi){
            yolDurumu="Vardi";
            toplamUzunluk+=strlen(yolDurumu);
        }
        else if(this->yolda){
            yolDurumu="Yolda";
            toplamUzunluk+=strlen(yolDurumu);
        }
        else{
            yolDurumu="Bekliyor";
            toplamUzunluk+=strlen(yolDurumu);
        }

        char* str=(char*)malloc(sizeof(char)*toplamUzunluk);
        sprintf(str, "%-25s %-25s %-25s %-25s %-25s %-25s", this->isim, 
            yolDurumu,this->cikisGezegeni,this->varisGezegeni,this->kalanSaat,this->hedefeVaracagiTarih);
            return str;
    }

}
void uzayAraciYoket(UzayAraci this){
    if(this->yolcular!=NULL){
        for(int i=0; i < this->yolcular->boyut; i++){
            if(this->yolcular->kisiler[i]!=NULL){ //arrraylistteki yoket fonksyonları kullan
                free(this->yolcular->kisiler[i]);
            }
        }
        free(this->yolcular->kisiler);
        free(this->yolcular);
    }

    if(this->isim!=NULL)
        free(this->isim);
    if(this->cikisGezegeni!=NULL)
        free(this->cikisGezegeni);
    if(this->varisGezegeni!=NULL)
        free(this->varisGezegeni);
    if(this->cikisTarihi!=NULL)
        free(this->cikisTarihi);
    free(this);
}

//arrayliste ait fonksiyonlar
void addToListUzayAraci(uzayAraciArrayList list,const UzayAraci yeniArac){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->uzayAraclari=(UzayAraci*)realloc(list->uzayAraclari, sizeof(UzayAraci)*list->kapasite);
    }
    list->uzayAraclari[list->boyut++]=yeniArac;
}

void clearListUzayAraci(uzayAraciArrayList list){
    for(int i=0; i< list->boyut; i++){
        if(list->uzayAraclari[i]!=NULL){
            uzayAraciYoket(list->uzayAraclari[i]);
        }
    }
    free(list->uzayAraclari);
    list->uzayAraclari=NULL;
    list->boyut=0;
    list->kapasite=0;
}