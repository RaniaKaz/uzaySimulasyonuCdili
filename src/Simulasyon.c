#include "Simulasyon.h"
#include <windows.h>
Simulasyon simulasyonOlusturucu(){
    Simulasyon this;
    this=(Simulasyon)malloc(sizeof(struct SIMULASYON));
    this->dosyaOkuma = dosyaOkumaOlusturucu();
    this->kisiler =this->dosyaOkuma->kisileriOku(this->dosyaOkuma,"./src/kisiler.txt");
    this->gezegenler = this->dosyaOkuma->gezegenleriOku(this->dosyaOkuma,"./src/gezegenler.txt");
    this->uzayAraclari = this->dosyaOkuma->uzayAraclariniOku(this->dosyaOkuma,"./src/uzayAraclar.txt");
    this->baslat = &baslat;
    this->birSaatIlerle = &birSaatIlerleSimulasyon;
    this->ekranGuncelle = &ekranGuncelle;
    this->gezegenBul = &gezegenBul;
    this->tumAraclarVardiMi = &tumAraclarVardiMi;
    this->gezegenZamani = &gezegenZamani;
    this->bekle = &bekle;
    this->yoket=&yoketSimulasyon;
    Kisi kisi;
    UzayAraci uzayAraci;
    Gezegen gezegen;
    for(int i=0; i<this->kisiler->boyut; i++){
        kisi=this->kisiler->kisiler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];
            if(strcmp(uzayAraci->getIsim(uzayAraci), kisi->getUzayAraciAdi(kisi)) == 0){
                uzayAraci->yolcuEkle(uzayAraci,kisi);
                //printf("yolcu  %d eklendi",i); bu tamam
                break;
            }
        }

    }
    for(int i=0; i<this->gezegenler->boyut; i++){
        gezegen=this->gezegenler->gezegenler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];  
            if(strcmp(uzayAraci->getCikisGezegeni(uzayAraci),gezegen->getIsim(gezegen))==0){
                //printf(" aracraki yolcu  %d eklendi",i); tamam
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);

            }
            
            if(strcmp(uzayAraci->getVarisGezegeni(uzayAraci),gezegen->getIsim(gezegen))==0){
                uzayAraci->varacagiTarihiHesapla(uzayAraci,gezegen->getGununSaatSayisi(gezegen));
                //printf("varacagi tarih toplandi  %d ",j); tamaam
            }
        }
    }
        return this;
}
void baslat(Simulasyon this){
    int saat=0;
    while(!this->tumAraclarVardiMi(this)){
        this->birSaatIlerle(this);
        this->ekranGuncelle(this,saat);

        this->bekle(500);

        saat++;
    }
    this->ekranGuncelle(this,saat);
}
void birSaatIlerleSimulasyon(const Simulasyon this){
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        gezegen->birSaatGecir(gezegen);
        gezegen->nufusuGuncelle(gezegen);
        //printf("gezegen->nufusuGuncelle(gezegen); calisti");
    }
    for(int i=0; i<this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[i];
        uzayAraci->birSaatGecir(uzayAraci,this->gezegenZamani(this,uzayAraci->getCikisGezegeni(uzayAraci)));
        //printf(" -kontrol- ");
    }
    for(int i=0; i<this->gezegenler->boyut;i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        for(int j=0; j< this->uzayAraclari->boyut; j++){
            UzayAraci uzayAraci= this->uzayAraclari->uzayAraclari[j];
            if(uzayAraci->hedefeUlastiMi(uzayAraci) && strcmp(uzayAraci->getVarisGezegeni(uzayAraci),gezegen->getIsim(gezegen)) == 0){
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);
            }
        }
    }
}

void ekranGuncelle(const Simulasyon this, int saat){
   // system("cls");

    printf("gezegenler : %d\n", saat);
    printf("%-25s", "");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "---%s---", gezegen->getIsim(gezegen));
        printf("%-25s", buffer);
    }

    printf("\n");
    printf("%-25s", "Tarih :");
        for(int i=0; i<this->gezegenler->boyut; i++){
            Gezegen gezegen = this->gezegenler->gezegenler[i];
            char* tarihStr = gezegen->getTarih(gezegen)->toString(gezegen->getTarih(gezegen));
            printf("%-25s", tarihStr);
            free(tarihStr);
        //printf("%-25s",gezegen->getTarih(gezegen)->toString(gezegen->getTarih(gezegen)));
        }
    //printf(" -kontrol- "); tamam
    printf("\n");
    printf("%-25s", "Nufus :");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        printf("%-25d",gezegen->getNufus(gezegen)->boyut); //d√ºzeltilmeli galiba 
    }

    printf("\n\n\nUzay Araclari :\n");
    printf("%-25s %-25s %-25s %-25s %-25s %-25s","Arac Adi","Durum","Cikis","Varis","Hedefe Kalan Saat","Hedefe Varacagi Tarih");
    printf("\n");
//varacagiTarihiHesapla
    for(int i=0; i < this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[i];
        if (uzayAraci == NULL) {
            printf("HATA: %d. uzay araci NULL!\n", i);
            continue;
        }

        //printf(uzayAraci->toString(uzayAraci));
        //printf("\n");
                // toString'ten dˆnen bellei al, yazd˝r, sonra serbest b˝rak
            char* str = uzayAraci->toString(uzayAraci);
            if (str) {
                printf("%s\n", str);
                free(str); // Bellei serbest b˝rak!
            } else {
                printf("HATA: %d. uzay araci toString NULL!\n", i);
            }

        }
}

Zaman gezegenZamani(const Simulasyon this, char* ad){
    Gezegen g=this->gezegenBul(this,ad);
    return g->getTarih(g);
}

Gezegen gezegenBul(const Simulasyon this , char* ad){
    for(int i=0; i < this->gezegenler->boyut; i++){
        Gezegen gezegen =this->gezegenler->gezegenler[i];
        
        if(strcmp(gezegen->getIsim(gezegen),ad)==0)
            return gezegen;
    }
    return NULL;
}

Boolean tumAraclarVardiMi(const Simulasyon this){
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

void yoketSimulasyon(Simulasyon this){
   if(this==NULL) return; 
   this->kisiler->yoket(this->kisiler);
   this->gezegenler->yoket(this->gezegenler);
   this->uzayAraclari->yoket(this->uzayAraclari);
   this->dosyaOkuma->yoket(this->dosyaOkuma);
   free(this);
}