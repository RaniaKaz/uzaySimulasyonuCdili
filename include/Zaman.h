#ifndef ZAMAN_H
#define ZAMAN_H

struct ZAMAN {
    int gun;
    int ay;
    int yil;
    int saat;
    int (*getSaat)(struct ZAMAN*);
    void (*birSaatIlerle)(struct ZAMAN*,int);
    struct ZAMAN* (*saatAlTarihiHesapla)(struct ZAMAN*,int,int);
    int(*esitMi)(struct ZAMAN*,struct ZAMAN*);
    char* (*toString)(struct ZAMAN*);
    void (*yoket)(struct ZAMAN*);
};
typedef struct ZAMAN* Zaman;

struct ZAMAN* zamanOlusturucu(int,int,int);
int getSaat(const Zaman);
void birSaatIlerle(const Zaman,int);
Zaman saatAlTarihiHesapla(const Zaman,int,int);
int esitMi(const Zaman,const Zaman);
char* toString(const Zaman);
void zamanYoket(Zaman);
#endif
