#include "gezegenArrayList.h"

gezegenArrayList gezegenArrayListOlusturucu() {
    gezegenArrayList list = (gezegenArrayList)malloc(sizeof(struct GezegenArrayList));
    list->boyut = 0;
    list->kapasite = 10;
    list->gezegenler = (struct GEZEGEN**)malloc(sizeof(struct GEZEGEN*) * list->kapasite);
    list->add = &addToListGezegen;
    list->clear = &clearListGezegen;
    list->yoket= &yoketListGezegen;
    return list;
}

void addToListGezegen(gezegenArrayList list,Gezegen yeniGezegen){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->gezegenler=(Gezegen*)realloc(list->gezegenler, sizeof(Gezegen)*list->kapasite);
    }
    list->gezegenler[list->boyut++]=yeniGezegen;
}
void addAllToListGezegen(gezegenArrayList kaynak, gezegenArrayList hedef){
    for (int i=0; i<kaynak->boyut; i++){
        if(hedef->boyut==hedef->kapasite){
            hedef->kapasite*=2;
            hedef->gezegenler=(Kisi*)realloc(hedef->gezegenler, sizeof(Kisi)*hedef->kapasite);
        }
        hedef->gezegenler[hedef->boyut++]=kaynak->gezegenler[i];
    }

}
void clearListGezegen(gezegenArrayList list){
    for(int i=0; i<list->boyut; i++){
        list->gezegenler[i]->yoket(list->gezegenler[i]);
    }
    free(list->gezegenler);
    list->boyut = 0;
    list->kapasite = 10;
    list->gezegenler = (Gezegen*)malloc(sizeof(Gezegen) * list->kapasite);
}

void yoketListGezegen(gezegenArrayList list){
    if (list==NULL) return;

    for(int i=0; i<list->boyut; i++){
        if(list->gezegenler[i] != NULL){
            list->gezegenler[i]->yoket(list->gezegenler[i]);
        }
        
    }
    free(list->gezegenler);
    free(list);
}