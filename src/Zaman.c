#include "Zaman.h"
#include <stddef.h>

struct ZAMAN* zamanOlusturucu(int gun,int ay,int yil){
    Zaman this;
    this=(Zaman)malloc(sizeof(struct ZAMAN));
    this->gun=gun;
    this->ay=ay;
    this->yil=yil;
    this->saat=0;
}

int getSaat(const Zaman this){
    return this->saat;
}

void birSaatIlerle(const Zaman this,int gunSaat){
    this->saat++;
    if(this->saat==gunSaat){
        this->saat=0;
        this->gun++;
        if(this->gun>30){
            this->gun=1;
            this->ay++;
            if(this->ay>12){
                this->ay=1;
                this->yil++;
            }
        }
    }
}

Zaman saatAlTarihiHesapla(const Zaman this,int girilenSaat,int girilenGunSaat){
    int yeniSaat = this->saat + girilenSaat;
    int yeniGun = this->gun;
    int yeniAy = this->ay;
    int yeniYil = this->yil;
     while(yeniSaat >= girilenGunSaat) {
         yeniSaat-=girilenGunSaat;
         yeniGun++;
        if(yeniGun>30) {
            yeniGun=1;
            yeniAy++;
            if(yeniAy>12) {
                yeniAy=1;
                yeniYil++;
            }
        }
     }
    Zaman yeniZaman = zamanOlusturucu(yeniGun,yeniAy,yeniYil);
    return yeniZaman;
}

int esitMi(const Zaman this,const Zaman digerZaman){
    return this->gun == digerZaman->gun && this->ay == digerZaman->ay && this->yil == digerZaman->yil;
}

char* toString(const Zaman this){
    int toplamUzunluk=36;
    toplamUzunluk+=strlen(this->gun);
    toplamUzunluk+=strlen(this->ay);
    toplamUzunluk+=strlen(this->yil);

    char* str=(char*)malloc(sizeof(char)* toplamUzunluk);//char 1 byte 1*toplamUzunluk kadar yer açıyoruz
    sprintf(str, "%d.%d.%d", this->gun, this->ay, this->yil);
    return str;
}

void zamanYoket(Zaman this){
    if(this==NULL) return;
    free(this);
}