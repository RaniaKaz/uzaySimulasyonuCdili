#ifndef KISI_H
#define KISI_H
struct KISI{
    char *isim;
    int yas;
    int kalanOmur;
    char *uzayAraciAdi;
    int hayatta;
    char* (*getUzayAraciAdi)(struct KISI*);
    void (*birSaatGecir)(struct KISI*);
    int (*hayattaMi)(struct KISI*);
    void (*yoket)(struct KISI*);
};
typedef struct{
    struct KISI** kisiler;
    int kisiSayisi;
    int maxKisiSayisi;
} kisiArrayList;

typedef struct KISI* Kisi;
Kisi kisiOlusturucu(char*, int, int, char*);
char* getUzayAraciAdi(const Kisi);
void birSaatGecir(const Kisi);
int hayattaMi(const Kisi);
void yoket(const Kisi);
 #endif
