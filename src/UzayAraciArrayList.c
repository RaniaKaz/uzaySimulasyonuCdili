#include "UzayAraciArrayList.h"

uzayAraciArrayList uzayAraciArrayListOlusturucu(){
    uzayAraciArrayList list = (uzayAraciArrayList)malloc(sizeof(struct UzayAraciArrayList));
    list->boyut = 0;
    list->kapasite = 10;
    list->uzayAraclari = (struct UZAYARACI**)malloc(sizeof(struct UZAYARACI*) * list->kapasite);
    list->add = &addToListUzayAraci;
    list->clear = &clearListUzayAraci;
    list->yoket= &yoketListUzayAraci;
    return list;
}
void addToListUzayAraci(uzayAraciArrayList list,const UzayAraci yeniArac){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->uzayAraclari=(UzayAraci*)realloc(list->uzayAraclari, sizeof(UzayAraci)*list->kapasite);
    }
    list->uzayAraclari[list->boyut++]=yeniArac;
}

void clearListUzayAraci(uzayAraciArrayList list){
    for(int i=0; i< list->boyut; i++){
        if(list->uzayAraclari[i]!=NULL){
            list->uzayAraclari[i]->yoket(list->uzayAraclari[i]);
        }
    }
    free(list->uzayAraclari);
    list->boyut = 0;
    list->kapasite = 10;
    list->uzayAraclari = (UzayAraci*)malloc(sizeof(UzayAraci) * list->kapasite);
}

void removeFromListUzayAraci(uzayAraciArrayList list ,UzayAraci arac){
    for ( int i=0; i < list->boyut; i++){
        if(list->uzayAraclari[i]==arac){
            list->uzayAraclari[i]->yoket( list->uzayAraclari[i]);
            for(int j=0; j < list->boyut; j++){
                list->uzayAraclari[i]=list->uzayAraclari[i++];
            }
            list->boyut--;
            return;
        }
    }
}
void yoketListUzayAraci (uzayAraciArrayList list) {
    if (list==NULL) return;

    for(int i=0; i<list->boyut; i++){
        if(list->uzayAraclari[i] != NULL){
            list->uzayAraclari[i]->yoket(list->uzayAraclari[i]);
        }
        
    }
    free(list->uzayAraclari);
    free(list);
}