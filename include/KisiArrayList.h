#ifndef KISIARRAYLIST_H
#define KISIARRAYLIST_H
#include "Kisi.h"
#include <string.h>
struct KisiArrayList{
    struct KISI** kisiler;
    int boyut;
    int kapasite;
    void (*add)(struct KisiArrayList*,Kisi);
    void (*addAll)(struct KisiArrayList*,struct KisiArrayList*);
    void (*clear)(struct KisiArrayList*);
    void (*removeAll)(struct KisiArrayList*,struct KisiArrayList*);
    void (*removeAndFreeAt)(struct KisiArrayList*, int);
    void (*yoket)(struct KisiArrayList*);
};

typedef struct KisiArrayList* kisiArrayList;

kisiArrayList kisiArrayListOlusturucu();
char* strdup_safeK(const char*);
void addToListKisi(kisiArrayList,Kisi);
void addAllToListKisi(kisiArrayList,kisiArrayList);
void clearListKisi(kisiArrayList);
void removeAllListKisi(kisiArrayList,kisiArrayList);
void removeAndFreeAtListKisi(kisiArrayList, int);
void yoketListKisi(kisiArrayList);
#endif