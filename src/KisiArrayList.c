#include "KisiArrayList.h"

kisiArrayList kisiArrayListOlusturucu(){
    kisiArrayList list;
    list=(kisiArrayList) malloc(sizeof(struct KisiArrayList));
    list->boyut = 0;
    list->kapasite = 10;
    list->kisiler = malloc(sizeof(Kisi) * list->kapasite);
    list->add = &addToListKisi;
    list->addAll = &addAllToListKisi;
    list->clear = &clearListKisi;
    list->removeAll = &removeAllListKisi;
    list->removeAndFreeAt = &removeAndFreeAtListKisi;
    list->yoket= &yoketListKisi;
    return list;
}
void addToListKisi(kisiArrayList list,Kisi yeniKisi){
    if(list->boyut==list->kapasite){
        list->kapasite*=2;
        list->kisiler=(Kisi*)realloc(list->kisiler, sizeof(Kisi)*list->kapasite);
    }
    list->kisiler[list->boyut++]=yeniKisi;
}

void addAllToListKisi(kisiArrayList kaynak, const kisiArrayList hedef){
    for (int i=0; i<kaynak->boyut; i++){
        if(hedef->boyut==hedef->kapasite){
            hedef->kapasite*=2;
            hedef->kisiler=(Kisi*)realloc(hedef->kisiler, sizeof(Kisi)*hedef->kapasite);
        }
        hedef->kisiler[hedef->boyut++]=kaynak->kisiler[i];
    }
}

void clearListKisi(kisiArrayList list){
    for(int i=0; i<list->boyut; i++){
        list->kisiler[i]->yoket(list->kisiler[i]);
    }
    free(list->kisiler);
    list->boyut = 0;
    list->kapasite = 10;
    list->kisiler = (Kisi*)malloc(sizeof(Kisi) * list->kapasite);
}

void removeAllListKisi(kisiArrayList hedef,kisiArrayList silinecek){
    for(int i=0;i < silinecek->boyut; i++){
        Kisi kisi=silinecek->kisiler[i];
        for(int j=0; j < hedef->boyut; j++){
            if(hedef->kisiler[j]==kisi){
                hedef->removeAndFreeAt(hedef,j);
                j--;
                break;
            }
        }
    }
}

void removeAndFreeAtListKisi(kisiArrayList list, int index){
    if(index <0 || index >= list->boyut) return;
    
    list->kisiler[index]->yoket(list->kisiler[index]);

    for(int i=index; i<list->boyut-1; i++){
        list->kisiler[i]=list->kisiler[i+1];
    }
    list->boyut--;
}

void yoketListKisi(kisiArrayList list){
    if (list==NULL) return;

    for(int i=0; i<list->boyut; i++){
        if(list->kisiler[i] != NULL){
            list->kisiler[i]->yoket(list->kisiler[i]);
        }
        
    }
    free(list->kisiler);
    free(list);
}