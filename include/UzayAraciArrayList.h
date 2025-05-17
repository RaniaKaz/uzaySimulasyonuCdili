#ifndef UZAYARACIARRAYLIST_H
#define UZAYARACIARRAYLIST_H
#include "UzayAraci.h"
struct UzayAraciArrayList{
    struct UZAYARACI** uzayAraclari;
    int boyut;
    int kapasite;
    void (*add)(struct UzayAraciArrayList*,const UzayAraci);
    void (*clear)(struct UzayAraciArrayList*);
    void (*remove)(struct UzayAraciArrayList*, UzayAraci); //yazılmamış
    void (*yoket)(struct UzayAraciArrayList*);
};
typedef struct UzayAraciArrayList *uzayAraciArrayList;

uzayAraciArrayList uzayAraciArrayListOlusturucu();
void addToListUzayAraci(uzayAraciArrayList,const UzayAraci);
void clearListUzayAraci(uzayAraciArrayList);
void removeFromListUzayAraci(uzayAraciArrayList,UzayAraci);
void yoketListUzayAraci(uzayAraciArrayList);
#endif