#include "UzayAraci.h"

UzayAraci uzayAraciOlusturucu(char* isim ,char* cikisGezegeni,char* varisGezegeni ,struct ZAMAN* cikisTarihi,int mesafeSaat){
    UzayAraci this;
    this=(UzayAraci)malloc(sizeof(struct UZAYARACI));
    this->isim=isim;
    this->cikisGezegeni=cikisGezegeni;
    this->varisGezegeni=varisGezegeni;
    this->hedefeVaracagiTarih="";
    this->cikisTarihi=cikisTarihi;
    this->mesafeSaat=mesafeSaat;
    this->kalanSaat=mesafeSaat;
    this->yolda=FALSE;
    this->imha=FALSE;
    this->yolcular=kisiArrayListOlusturucu();
    this->getIsim=&getIsimUzayAraci;
    this->getCikisGezegeni=&getCikisGezegeni;
    this->getVarisGezegeni=&getVarisGezegeni;
    this->birSaatGecir=&birSaatGecirUzayAraci;
    this->yolcuEkle=&yolcuEkle;
    this->yolculariGuncelle=&yolculariGuncelle;
    this->hayattakiYolculariAl=&hayattakiYolculariAl;
    this->yoldaMi=&yoldaMi;
    this->hedefeUlastiMi=&hedefeUlastiMi;
    this->imhaMi=&imhaMi;
    this->varacagiTarihiHesapla=&varacagiTarihiHesapla;
    this->toString=&toStringUzayAraci;
    this->yoket=&uzayAraciYoket;
    return this;
}

char* getIsimUzayAraci(const UzayAraci this){
    return this->isim;
}

char* getCikisGezegeni(const UzayAraci this){
    return this->cikisGezegeni;
}

char* getVarisGezegeni(const UzayAraci this){
    return this->varisGezegeni;
}

void birSaatGecirUzayAraci(const UzayAraci this ,struct ZAMAN* simdikiZaman){
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
    boolean hayattaVar=FALSE; 
    for(int i=0; i<this->yolcular->boyut; i++){
        if(this->yolcular->kisiler[i]!=NULL){
            this->yolcular->kisiler[i]->birSaatGecir(this->yolcular->kisiler[i]);
                if(this->yolcular->kisiler[i]->hayattaMi(this->yolcular->kisiler[i])){
                hayattaVar=TRUE;
                
            }
        }

    }
    this->imha= (hayattaVar ==FALSE ) ? TRUE : FALSE;
}

kisiArrayList hayattakiYolculariAl(const UzayAraci this){
    kisiArrayList hayattakiler=kisiArrayListOlusturucu();

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

boolean hedefeUlastiMi(const UzayAraci this){
    return this->kalanSaat<=0;
}

int imhaMi(const UzayAraci this){
    return this->imha;
}

void varacagiTarihiHesapla(const UzayAraci this,int gezegeninGunSaat){
    Zaman hedefeVaracagiTarih= this->cikisTarihi->saatAlTarihiHesapla(this->cikisTarihi,this->mesafeSaat,gezegeninGunSaat);
    this->hedefeVaracagiTarih= hedefeVaracagiTarih->toString(hedefeVaracagiTarih);
}

char* toStringUzayAraci(const UzayAraci this){
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
        if(this->hedefeUlastiMi(this)){
            yolDurumu="Vardi";
            toplamUzunluk+=strlen(yolDurumu);
        }
        else if(this->yoldaMi(this)){
            yolDurumu="Yolda";
            toplamUzunluk+=strlen(yolDurumu);
        }
        else{
            yolDurumu="Bekliyor";
            toplamUzunluk+=strlen(yolDurumu);
        }

        char* str=(char*)malloc(sizeof(char)*toplamUzunluk);
        sprintf(str, "%-25s %-25s %-25s %-25s %-25d %-25s", this->isim, 
            yolDurumu,this->cikisGezegeni,this->varisGezegeni,this->kalanSaat,this->hedefeVaracagiTarih);
            return str;
    }

}
void uzayAraciYoket(UzayAraci this){
    if(this->yolcular!=NULL){
        for(int i=0; i < this->yolcular->boyut; i++){
            if(this->yolcular->kisiler[i]!=NULL){
                this->yolcular->kisiler[i]->yoket(this->yolcular->kisiler[i]);
            }
        }
        free(this->yolcular->kisiler);
        free(this->yolcular);
    }

    free(this);
}

//arrayliste ait fonksiyonlar