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
    //printf("removeAllListKisi baþladý\n");
    
    if (kaynak == NULL || hedef == NULL) {
        //printf("Kaynak veya hedef NULL\n");
        return;
    }
    
    if (kaynak->boyut == 0 || hedef->boyut == 0) {
        //printf("Kaynak veya hedef boþ\n");
        return;
    }
    
    // Yeni bir array oluþturup, silinmeyecek kiþileri bu array'e kopyalayalým
    Kisi* yeniKisiler = (Kisi*)malloc(sizeof(Kisi) * kaynak->kapasite);
    if (yeniKisiler == NULL) {
        //printf("Bellek ayýrma hatasý\n");
        exit(1);
    }
    
    int yeniIndeks = 0;
    
    for (int i = 0; i < kaynak->boyut; i++) {
        Kisi kaynakKisi = kaynak->kisiler[i];
        int silinecekMi = 0;
        
        for (int j = 0; j < hedef->boyut; j++) {
            Kisi hedefKisi = hedef->kisiler[j];
            
            // Kiþileri karþýlaþtýr (isim üzerinden)
            if (kaynakKisi != NULL && hedefKisi != NULL && 
                kaynakKisi->isim != NULL && hedefKisi->isim != NULL &&
                strcmp(kaynakKisi->isim, hedefKisi->isim) == 0) {
                
                //printf("Eþleþme bulundu: %s\n", kaynakKisi->isim);
                silinecekMi = 1;
                break;
            }
        }
        
        if (!silinecekMi) {
            yeniKisiler[yeniIndeks++] = kaynakKisi;
        }
    }
    
    // Eski diziyi serbest býrak ve yeni diziyi kullan
    free(kaynak->kisiler);
    kaynak->kisiler = yeniKisiler;
    kaynak->boyut = yeniIndeks;
    
    printf("removeAllListKisi tamamlandý\n");
}
/*void removeAllListKisi(kisiArrayList kaynak, kisiArrayList hedef) { en son sildiðim
    if (kaynak == NULL || hedef == NULL || kaynak->boyut == 0 || hedef->boyut == 0) {
        return; // Boþ listeler için erken dönüþ
    }
    
    int yazmaIndeksi = 0; // Kaynak dizisinde yazýlacak yeni pozisyon
    
    // Kaynaktaki her eleman için
    for (int i = 0; i < kaynak->boyut; i++) {
        Kisi kaynakKisi = kaynak->kisiler[i];
        int silinecekMi = 0;
        
        // Bu kiþi hedef listede var mý kontrol et
        for (int j = 0; j < hedef->boyut; j++) {
            Kisi hedefKisi = hedef->kisiler[j];
            
            if (strcmp(kaynakKisi->isim, hedefKisi->isim) == 0 && 
                kaynakKisi->yas == hedefKisi->yas && 
                kaynakKisi->kalanOmur == hedefKisi->kalanOmur) {
                
                // Eþleþme bulundu, bu kiþi silinecek
                kaynakKisi->yoket(kaynakKisi);
                silinecekMi = 1;
                break; // Eþleþme bulunduðunda iç döngüden çýk
            }
        }
        
        if (!silinecekMi) {
            // Bu kiþiyi koruyacaðýz, yazma indeksine taþý
            kaynak->kisiler[yazmaIndeksi++] = kaynakKisi;
        }
    }
    
    // Yeni boyutu güncelle
    kaynak->boyut = yazmaIndeksi;
    
    // Eðer liste çok boþaldýysa kapasiteyi küçültmeyi düþünebiliriz
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
                
                // Kiþiyi yok et ve kaydýr
                kaynakKisi->yoket(kaynakKisi);

                for (int k = j; k < kaynak->boyut - 1; k++) {
                    kaynak->kisiler[k] = kaynak->kisiler[k + 1];
                }

                kaynak->boyut--;
                // j'yi artýrma çünkü bu indeks yeni elemanla doldu
            } else {
                j++; // eþleþmediyse sýradakine geç
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