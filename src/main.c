#include "Simulasyon.h"
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(){
    setlocale(LC_ALL, "tr_TR.UTF-8");  // Türkçe karakterler için UTF-8 desteği
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Windows için konsol kodlamasını UTF-8 yap
#endif

    Simulasyon simulasyon = simulasyonOlusturucu();
    simulasyon->baslat(simulasyon);
    simulasyon->yoket(simulasyon);
    return 0;
}