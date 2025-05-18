#include "KisiArrayList.h"

kisiArrayList kisiArrayListOlusturucu(){
    kisiArrayList list;
    list=(kisiArrayList) malloc(sizeof(struct KisiArrayList));
    list->boyut = 0;
    list->kapasite = 10;
    list->kisiler = malloc(sizeof(Kisi) * list->kapasite);
    list->add = &addToListKisi;
    list->addAll=&addAllToListKisi;
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

void addAllToListKisi(kisiArrayList kaynak, kisiArrayList hedef) {
    while (kaynak->boyut + hedef->boyut > kaynak->kapasite) {
        kaynak->kapasite *= 2;
        kaynak->kisiler = (Kisi*)realloc(kaynak->kisiler, sizeof(Kisi) * kaynak->kapasite);
        if (kaynak->kisiler == NULL) {
            exit(1);
        }
    }

    for (int i = 0; i < hedef->boyut; i++) {
        Kisi orijinal = hedef->kisiler[i];
        Kisi kopya = kisiOlusturucu(
            strdup_safeK(orijinal->isim),
            orijinal->yas,
            orijinal->kalanOmur,
            strdup_safeK(orijinal->uzayAraciAdi)
        );
        kaynak->kisiler[kaynak->boyut++] = kopya;
    }
}
char* strdup_safeK(const char* src) {
    if (!src) return NULL;
    char* dst = (char*)malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
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

void removeAllListKisi(kisiArrayList kaynak, kisiArrayList hedef) {
    //printf("removeAllListKisi ba�lad�\n");
    
    if (kaynak == NULL || hedef == NULL) {
        //printf("Kaynak veya hedef NULL\n");
        return;
    }
    
    if (kaynak->boyut == 0 || hedef->boyut == 0) {
        //printf("Kaynak veya hedef bo�\n");
        return;
    }
    
    // Yeni bir array olu�turup, silinmeyecek ki�ileri bu array'e kopyalayal�m
    Kisi* yeniKisiler = (Kisi*)malloc(sizeof(Kisi) * kaynak->kapasite);
    if (yeniKisiler == NULL) {
        //printf("Bellek ay�rma hatas�\n");
        exit(1);
    }
    
    int yeniIndeks = 0;
    
    for (int i = 0; i < kaynak->boyut; i++) {
        Kisi kaynakKisi = kaynak->kisiler[i];
        int silinecekMi = 0;
        
        for (int j = 0; j < hedef->boyut; j++) {
            Kisi hedefKisi = hedef->kisiler[j];
            
            // Ki�ileri kar��la�t�r (isim �zerinden)
            if (kaynakKisi != NULL && hedefKisi != NULL && 
                kaynakKisi->isim != NULL && hedefKisi->isim != NULL &&
                strcmp(kaynakKisi->isim, hedefKisi->isim) == 0) {
                
                //printf("E�le�me bulundu: %s\n", kaynakKisi->isim);
                silinecekMi = 1;
                break;
            }
        }
        
        if (!silinecekMi) {
            yeniKisiler[yeniIndeks++] = kaynakKisi;
        }
    }
    
    // Eski diziyi serbest b�rak ve yeni diziyi kullan
    free(kaynak->kisiler);
    kaynak->kisiler = yeniKisiler;
    kaynak->boyut = yeniIndeks;
    
    printf("removeAllListKisi tamamland�\n");
}
/*void removeAllListKisi(kisiArrayList kaynak, kisiArrayList hedef) { en son sildi�im
    if (kaynak == NULL || hedef == NULL || kaynak->boyut == 0 || hedef->boyut == 0) {
        return; // Bo� listeler i�in erken d�n��
    }
    
    int yazmaIndeksi = 0; // Kaynak dizisinde yaz�lacak yeni pozisyon
    
    // Kaynaktaki her eleman i�in
    for (int i = 0; i < kaynak->boyut; i++) {
        Kisi kaynakKisi = kaynak->kisiler[i];
        int silinecekMi = 0;
        
        // Bu ki�i hedef listede var m� kontrol et
        for (int j = 0; j < hedef->boyut; j++) {
            Kisi hedefKisi = hedef->kisiler[j];
            
            if (strcmp(kaynakKisi->isim, hedefKisi->isim) == 0 && 
                kaynakKisi->yas == hedefKisi->yas && 
                kaynakKisi->kalanOmur == hedefKisi->kalanOmur) {
                
                // E�le�me bulundu, bu ki�i silinecek
                kaynakKisi->yoket(kaynakKisi);
                silinecekMi = 1;
                break; // E�le�me bulundu�unda i� d�ng�den ��k
            }
        }
        
        if (!silinecekMi) {
            // Bu ki�iyi koruyaca��z, yazma indeksine ta��
            kaynak->kisiler[yazmaIndeksi++] = kaynakKisi;
        }
    }
    
    // Yeni boyutu g�ncelle
    kaynak->boyut = yazmaIndeksi;
    
    // E�er liste �ok bo�ald�ysa kapasiteyi k���ltmeyi d���nebiliriz
    if (kaynak->boyut < kaynak->kapasite / 4 && kaynak->kapasite > 10) {
        kaynak->kapasite /= 2;
        kaynak->kisiler = (Kisi*)realloc(kaynak->kisiler, sizeof(Kisi) * kaynak->kapasite);
        if (kaynak->kisiler == NULL) {
            exit(1);
        }
    }
}
/*void removeAllListKisi(kisiArrayList kaynak, kisiArrayList hedef) {
    for (int i = 0; i < hedef->boyut; i++) {
        Kisi hedefKisi = hedef->kisiler[i];

        for (int j = 0; j < kaynak->boyut;) {
            Kisi kaynakKisi = kaynak->kisiler[j];

            if (                strcmp(kaynakKisi->isim, hedefKisi->isim) == 0 &&
                kaynakKisi->yas == hedefKisi->yas &&
                kaynakKisi->kalanOmur == hedefKisi->kalanOmur) {
                
                // Ki�iyi yok et ve kayd�r
                kaynakKisi->yoket(kaynakKisi);

                for (int k = j; k < kaynak->boyut - 1; k++) {
                    kaynak->kisiler[k] = kaynak->kisiler[k + 1];
                }

                kaynak->boyut--;
                // j'yi art�rma ��nk� bu indeks yeni elemanla doldu
            } else {
                j++; // e�le�mediyse s�radakine ge�
            }
        }
    }
}*/

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