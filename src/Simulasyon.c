#include "Simulasyon.h"
#include <windows.h>
Simulasyon simulasyonOlusturucu(){
    Simulasyon this;
    this=(Simulasyon)malloc(sizeof(struct SIMULASYON));
    this->dosyaOkuma = dosyaOkumaOlusturucu();
    this->kisiler =this->dosyaOkuma->kisileriOku(this->dosyaOkuma,"./src/kisiler.txt");
    this->gezegenler = this->dosyaOkuma->gezegenleriOku(this->dosyaOkuma,"./src/gezegenler.txt");
    this->uzayAraclari = this->dosyaOkuma->uzayAraclariniOku(this->dosyaOkuma,"./src/uzayAraclar.txt");
    this->baslat = &baslat;
    this->birSaatIlerle = &birSaatIlerleSimulasyon;
    this->ekranGuncelle = &ekranGuncelle;
    this->gezegenBul = &gezegenBul;
    this->tumAraclarVardiMi = &tumAraclarVardiMi;
    this->gezegenZamani = &gezegenZamani;
    this->yoket=&yoketSimulasyon;
    Kisi kisi;
    UzayAraci uzayAraci;
    Gezegen gezegen;
    for(int i=0; i<this->kisiler->boyut; i++){
        kisi=this->kisiler->kisiler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];
            if(strcmp(uzayAraci->getIsim(uzayAraci), kisi->getUzayAraciAdi(kisi)) == 0){
                uzayAraci->yolcuEkle(uzayAraci,kisi);
                //printf("yolcu  %d eklendi",i); bu tamam
                break;
            }
        }

    }
    for(int i=0; i<this->gezegenler->boyut; i++){
        gezegen=this->gezegenler->gezegenler[i];
        for(int j=0; j<this->uzayAraclari->boyut; j++){
            uzayAraci=this->uzayAraclari->uzayAraclari[j];  
            if(strcmp(uzayAraci->getCikisGezegeni(uzayAraci),gezegen->getIsim(gezegen))==0){
                //printf(" aracraki yolcu  %d eklendi",i); tamam
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);

            }
            
            if(strcmp(uzayAraci->getVarisGezegeni(uzayAraci),gezegen->getIsim(gezegen))==0){
                uzayAraci->varacagiTarihiHesapla(uzayAraci,gezegen->getGununSaatSayisi(gezegen));
                //printf("varacagi tarih toplandi  %d ",j); tamaam
            }
        }
    }
        return this;
}

void baslat(Simulasyon this){
    int saat=0;
    while(!this->tumAraclarVardiMi(this)){
        this->birSaatIlerle(this);
        this->ekranGuncelle(this,saat);
        saat++;
    }
    this->ekranGuncelle(this,saat);
}

void birSaatIlerleSimulasyon(const Simulasyon this){
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        gezegen->birSaatGecir(gezegen);
        //printf(" birsaatgexir calisti ");
        gezegen->nufusuGuncelle(gezegen); //sorun burada
        //printf(" gezegen->nufusuGuncelle(gezegen); calisti ");
    }
    //buraya hiç girmiyor
    for(int i=0; i<this->uzayAraclari->boyut; i++){
        UzayAraci arac=this->uzayAraclari->uzayAraclari[i];
        arac->birSaatGecir(arac,gezegenZamani(this,arac->getCikisGezegeni(arac)));
        arac->yolculariGuncelle(arac);

       // printf(" -kontrol- 3 ");
    }
   for(int i = 0; i < this->gezegenler->boyut; i++) {
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        if (gezegen == NULL) continue;
        
        for(int j = 0; j < this->uzayAraclari->boyut; j++) {
            UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[j];
            if (uzayAraci == NULL) continue;
            
            if(uzayAraci->hedefeUlastiMi(uzayAraci) && 
               !uzayAraci->imhaMi(uzayAraci) &&
               strcmp(uzayAraci->getVarisGezegeni(uzayAraci), gezegen->getIsim(gezegen)) == 0) {
                
                // ÖNEMLÝ: Burada aracýn içindeki yolcular gezegene taþýnýyor
                // Bu yolcularýn referansýný takip etmeliyiz, aksi takdirde double free olabilir
                gezegen->aractakiYolculariEkle(gezegen, uzayAraci);
            }
        }
    }
}

void ekranGuncelle(const Simulasyon this, int saat){
   // system("cls");

    printf("gezegenler : %d\n", saat);
    printf("%-25s", "");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "---%s---", gezegen->getIsim(gezegen));
        printf("%-25s", buffer);
    }

    printf("\n");
    printf("%-25s", "Tarih :");
        for(int i=0; i<this->gezegenler->boyut; i++){
            Gezegen gezegen = this->gezegenler->gezegenler[i];
            char* tarihStr = gezegen->getTarih(gezegen)->toString(gezegen->getTarih(gezegen));
            printf("%-25s", tarihStr);
            free(tarihStr);
        //printf("%-25s",gezegen->getTarih(gezegen)->toString(gezegen->getTarih(gezegen)));
        }
    //printf(" -kontrol- "); tamam
    printf("\n");
    printf("%-25s", "Nufus :");
    for(int i=0; i<this->gezegenler->boyut; i++){
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        printf("%-25d",gezegen->getNufus(gezegen)->boyut); //dÃ¼zeltilmeli galiba 
    }

    printf("\n\n\nUzay Araclari :\n");
    printf("%-25s %-25s %-25s %-25s %-25s %-25s","Arac Adi","Durum","Cikis","Varis","Hedefe Kalan Saat","Hedefe Varacagi Tarih");
    printf("\n");
//varacagiTarihiHesapla
    for(int i=0; i < this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[i];
        if (uzayAraci == NULL) {
            printf("HATA: %d. uzay araci NULL!\n", i);
            continue;
        }

        //printf(uzayAraci->toString(uzayAraci));
        //printf("\n");
                // toString'ten dönen belleði al, yazdýr, sonra serbest býrak
        char* str = uzayAraci->toString(uzayAraci);
        if (str) {
            printf("%s\n", str);
            free(str); // Belleði serbest býrak!
        } else {
            printf("HATA: %d. uzay araci toString NULL!\n", i);
        }

        }
}

Zaman gezegenZamani(const Simulasyon this, char* ad){
    Gezegen g=this->gezegenBul(this,ad);
    return g->getTarih(g);
}

Gezegen gezegenBul(const Simulasyon this , char* ad){
    for(int i=0; i < this->gezegenler->boyut; i++){
        Gezegen gezegen =this->gezegenler->gezegenler[i];
        
        if(strcmp(gezegen->getIsim(gezegen),ad)==0)
            return gezegen;
    }
    return NULL;
}

Boolean tumAraclarVardiMi(const Simulasyon this){
    for(int i=0; i < this->uzayAraclari->boyut; i++){
        UzayAraci uzayAraci=this->uzayAraclari->uzayAraclari[i];
        if(!uzayAraci->imhaMi(uzayAraci) && !uzayAraci->hedefeUlastiMi(uzayAraci))
            return FALSE;
    }
    return TRUE;
}

void yoketSimulasyon(Simulasyon this) {
    if(this == NULL) return; 
    
    // Önce gezegen ve uzay araçlarý arasýndaki karþýlýklý referanslarý temizleyelim
    for(int i = 0; i < this->gezegenler->boyut; i++) {
        Gezegen gezegen = this->gezegenler->gezegenler[i];
        if (gezegen == NULL) continue;
        
        // Gezegenin yolcu listesini temizle ama yolcularý serbest býrakma
        // Çünkü bu yolcular kisiler içinde de olabilir ve iki kez serbest býrakýlabilir
        if (gezegen->getNufus != NULL && gezegen->getNufus(gezegen) != NULL) {
            // Sadece listeyi temizle, içeriði yoketme
            gezegen->getNufus(gezegen)->clear(gezegen->getNufus(gezegen));
        }
    }
    
    // Benzer þekilde uzay araçlarýndaki yolcu referanslarýný temizleyelim
    for(int i = 0; i < this->uzayAraclari->boyut; i++) {
        UzayAraci uzayAraci = this->uzayAraclari->uzayAraclari[i];
        if (uzayAraci == NULL) continue;
        
        // Uzay aracýndaki yolcu listesini temizle ama yolcularý serbest býrakma
        if (uzayAraci->yolcular != NULL && uzayAraci->yolcular != NULL) {
            // Sadece listeyi temizle, içeriði yoketme
            uzayAraci->yolcular->clear(uzayAraci->yolcular);
        }
    }
    
    // Þimdi ana listeleri yokedelim
    if (this->kisiler != NULL) {
        this->kisiler->yoket(this->kisiler);
    }
    
    if (this->gezegenler != NULL) {
        this->gezegenler->yoket(this->gezegenler);
    }
    
    if (this->uzayAraclari != NULL) {
        this->uzayAraclari->yoket(this->uzayAraclari);
    }
    
    if (this->dosyaOkuma != NULL) {
        this->dosyaOkuma->yoket(this->dosyaOkuma);
    }
    
    free(this);
}
/*void yoketSimulasyon(Simulasyon this){
   if(this==NULL) return; 
   this->kisiler->yoket(this->kisiler);
   this->gezegenler->yoket(this->gezegenler);
   this->uzayAraclari->yoket(this->uzayAraclari);
   this->dosyaOkuma->yoket(this->dosyaOkuma);
   free(this);
}*/