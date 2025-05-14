#include "Simulasyon.h"

Simulasyon simulasyonOlusturucu(){
    Simulasyon this;
    this=(Simulasyon)malloc(sizeof(struct SIMULASYON));
    DosyaOkuma dosyaOkuma;
    this->kisiler =dosyaOkuma->kisileriOku(dosyaOkuma,"kisiler.txt");
    this->gezegenler = dosyaOkuma->gezegenleriOku(dosyaOkuma,"gezegenler.txt");
    this->uzayAraclari = dosyaOkuma->uzayAraclariniOku(dosyaOkuma,"uzayAraclari.txt");

    Kisi kisi;
    UzayAraci uzayAraci;
    Gezegen gezegen;
    for(int i=0; i<this->kisiler->boyut; i++){
        kisi=this->kisiler->kisiler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];
            if(uzayAraci->getIsim(uzayAraci) ==kisi->getUzayAraciAdi(kisi)){
                uzayAraci->yolcuEkle(uzayAraci,kisi);
                break;
            }
        }

    }
    for(int i=0; i<this->gezegenler->boyut; i++){
        gezegen=this->gezegenler->gezegenler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];
            if(uzayAraci->getCikisGezegeni(uzayAraci) == gezegen->getIsim(gezegen)){
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);
            }
            if(uzayAraci->getVarisGezegeni(uzayAraci) == gezegen->getIsim(gezegen)){
                uzayAraci->varacagiTarihiHesapla(uzayAraci,gezegen->getGununSaatSayisi(gezegen));
            }
        }
    }
}
void baslat(const Simulasyon this){
    int saat=0;
    while(!this->tumAraclarVardiMi(this)){
        this->birSaatIlerle(this);
        this->ekranGuncelle(saat);
        this->bekle(500);
        saat++;
    }
    this->ekranGuncelle(saat);
}
void birSaatIlerle(const Simulasyon this){
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        gezegen->birSaatGecir(gezegen);
        gezegen->nufusuGuncelle(gezegen,this->uzayAraclari);//javada parametresiz
    }
    for(int i=0; i<this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[i];
        uzayAraci->birSaatGecir(uzayAraci,this->gezegenZamani(uzayAraci,uzayAraci->getCikisGezegeni(uzayAraci)));
    }
    for(int i=0; i<this->gezegenler->boyut;i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        for(int j=0; j< this->uzayAraclari->boyut; i++){
            UzayAraci uzayAraci= this->uzayAraclari->uzayAraclari[j];
            if(uzayAraci->hedefeUlastiMi(uzayAraci) && uzayAraci->getVarisGezegeni== gezegen->getIsim(gezegen)){
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);
            }
        }
    }
}

void ekranGuncelle(const Simulasyon this, int saat){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("gezegenler : %d\n", saat);
    printf("%-25s", "");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        printf("%-25s---%s---",gezegen->getIsim(gezegen));
    }

    printf("\n");
    printf("%-25s", "Tarih :");
        for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        printf("%-25s---%s---",gezegen->getTarih(gezegen));
    }

    printf("\n");
    printf("%-25s", "Nüfüs :");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        printf("%-25s---%d---",gezegen->getNufus(gezegen)->boyut);
    }

    printf("\n\n\nUzay Araçları :\n");
    printf("%-25s %-25s %-25s %-25s %-25s %-25s","Araç Adı","Durum","Çıkış","Varış","Hedefe Kalan Saat","Hedefe Varacağı Tarih");
    printf("\n");

    for(int i=0; i < this->uzayAraclari->boyut; i++){
        printf(this->uzayAraclari->uzayAraclari[i]->toString(this->uzayAraclari->uzayAraclari[i]));
        printf("\n");
    }
}

Zaman gezegenZamani(const Simulasyon this, char* ad){
    return this->gezegenBul(this,ad)->getTarih;
}

Gezegen gezegenBul(const Simulasyon this , char* ad){
    for(int i=0; i < this->gezegenler->boyut; i++){
        Gezegen gezegen =this->gezegenler->gezegenler[i];
        if(gezegen->getIsim==ad)
            return gezegen;
    }
    return NULL;
}

boolean tumAraclarVardiMi(const Simulasyon this){
    for(int i=0; i < this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci=this->uzayAraclari->uzayAraclari[i];
        if(!uzayAraci->imhaMi(uzayAraci) && !uzayAraci->hedefeUlastiMi(uzayAraci))
            return FALSE;
    }
    return TRUE;
}

void bekle(int ms){
    Sleep(ms);
}