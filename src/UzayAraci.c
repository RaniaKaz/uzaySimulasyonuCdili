#include "UzayAraci.h"

UzayAraci uzayAraciOlusturucu(char* isim ,char* cikisGezegeni,char* varisGezegeni ,struct ZAMAN* cikisTarihi,int mesafeSaat){
    UzayAraci this;
    this=(UzayAraci)malloc(sizeof(struct UZAYARACI));
    this->isim=isim;
    this->cikisGezegeni=cikisGezegeni;
    this->varisGezegeni=varisGezegeni;
    this->hedefeVaracagiTarih=NULL;
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
    Boolean hayattaVar=FALSE; 
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

Boolean hedefeUlastiMi(const UzayAraci this){
    return this->kalanSaat<=0;
}

int imhaMi(const UzayAraci this){
    return this->imha;
}

void varacagiTarihiHesapla(const UzayAraci this,int gezegeninGunSaat){
    if (this->hedefeVaracagiTarih != NULL) {
        free(this->hedefeVaracagiTarih);
        this->hedefeVaracagiTarih = NULL;
    }
    Zaman hedefeVaracagiTarih= this->cikisTarihi->saatAlTarihiHesapla(this->cikisTarihi,this->mesafeSaat,gezegeninGunSaat);
    char* tarihStr = hedefeVaracagiTarih->toString(hedefeVaracagiTarih);
    this->hedefeVaracagiTarih = strdup(tarihStr);
    //daha sonra yazýlmýþ
    free(tarihStr);
    hedefeVaracagiTarih->yoket(hedefeVaracagiTarih);
    //this->hedefeVaracagiTarih= hedefeVaracagiTarih->toString(hedefeVaracagiTarih);
}

char* toStringUzayAraci(const UzayAraci this) {
    char* yolDurumu;
    char kalanSaatStr[25];
    char* tarihGosterim;
    
    // Buffer için yeterli alan ayýr
    char* str = (char*)malloc(sizeof(char) * 256);
    if (str == NULL) {
        return NULL; // Bellek hatasý durumunda NULL dön
    }
    
    if (this->imha) {
        yolDurumu = "IMHA";
        sprintf(str, "%-25s %-25s %-25s %-25s %-25s %-25s", 
                this->isim, yolDurumu, this->cikisGezegeni, 
                this->varisGezegeni, "--", "--");
    } else {
        if (this->hedefeUlastiMi(this)) {
            yolDurumu = "Vardi";
        } else if (this->yoldaMi(this)) {
            yolDurumu = "Yolda";
        } else {
            yolDurumu = "Bekliyor";
        }
        
        sprintf(kalanSaatStr, "%d", this->kalanSaat);
        
        // Eðer hedefeVaracagiTarih NULL ise güvenli bir alternatif kullan
        tarihGosterim = (this->hedefeVaracagiTarih != NULL) ? 
                         this->hedefeVaracagiTarih : "--";
        
        sprintf(str, "%-25s %-25s %-25s %-25s %-25s %-25s", 
                this->isim, yolDurumu, this->cikisGezegeni, 
                this->varisGezegeni, kalanSaatStr, tarihGosterim);
    }
    
    return str;
}

void uzayAraciYoket(UzayAraci this) {
    if (this == NULL) return;
    
    if (this->yolcular != NULL) {
        for (int i = 0; i < this->yolcular->boyut; i++) {
            if (this->yolcular->kisiler[i] != NULL) {
                this->yolcular->kisiler[i]->yoket(this->yolcular->kisiler[i]);
            }
        }
        free(this->yolcular->kisiler);
        free(this->yolcular);
    }
    
    if (this->isim != NULL) free(this->isim);
    if (this->cikisGezegeni != NULL) free(this->cikisGezegeni);
    if (this->varisGezegeni != NULL) free(this->varisGezegeni);
    if (this->hedefeVaracagiTarih != NULL) free(this->hedefeVaracagiTarih);
    
    free(this);
}
