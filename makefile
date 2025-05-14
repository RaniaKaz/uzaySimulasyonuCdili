hepsi: derle calistir

derle:
		gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c
		gcc -I ./include/ -o ./lib/Gezegen.o -c ./src/Gezegen.c
		gcc -I ./include/ -o ./lib/UzayAraci.o -c ./src/UzayAraci.c
		gcc -I ./include/ -o ./lib/DosyaOkuma.o -c ./src/DosyaOkuma.c
		gcc -I ./include/ -o ./lib/Zaman.o -c ./src/Zaman.c
		gcc -I ./include/ -o ./lib/Simulasyon.o -c ./src/Simulasyon.c
		gcc -I ./include/ -o ./lib/Boolean.o -c ./src/Boolean.c
		gcc -I ./include/ -o ./bin/main.exe ./lib/Kisi.o ./lib/Gezegen.o ./lib/UzayAraci.o ./lib/DosyaOkuma.o ./lib/Zaman.o ./lib/Simulasyon.o ./lib/Boolean.o ./src/main.c

calistir:
		./bin/main.exe