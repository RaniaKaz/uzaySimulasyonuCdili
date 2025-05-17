#ifndef GEZEGENARRAYLIST_H
#define GEZEGENARRAYLIST_H
#include "Gezegen.h"
struct GezegenArrayList{
    struct GEZEGEN** gezegenler;
    int boyut;
    int kapasite;
    void (*add)(struct GezegenArrayList*,Gezegen);
    void (*addAll)(struct GezegenArrayList*,struct GezegenArrayList*);
    void (*clear)(struct GezegenArrayList*);
    void (*yoket)(struct GezegenArrayList*);
};

typedef struct GezegenArrayList* gezegenArrayList;

gezegenArrayList gezegenArrayListOlusturuxu();
void addToListGezegen(gezegenArrayList, Gezegen);
void addAllToListGezegen(gezegenArrayList,  gezegenArrayList);
void clearListGezegen(gezegenArrayList);
void yoketListGezegen(gezegenArrayList);
#endif