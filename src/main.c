#include "Simulasyon.h"
int main(){
    Simulasyon simulasyon = simulasyonOlusturucu();
    simulasyon->baslat(simulasyon);
    simulasyon->yoket(simulasyon);
}