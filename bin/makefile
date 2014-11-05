all: GUI.o Tamagotchi.o System.o Disease.o ../sources/main.cpp
	g++ GUI.o Tamagotchi.o System.o Disease.o main.cpp -o Tamagotchi.exe
GUI.o:	../headers/GUI.h ../sources/GUI.cpp
	g++ -c ../sources/GUI.cpp
Tamagotchi.o: ../headers/Tamagotchi.h ../sources/Tamagotchi.cpp
	g++ -c ../sources/Tamagotchi.cpp
System.o: ../headers/System.h ../sources/System.cpp
	g++ -c ../sources/System.cpp
Disease.o: ../headers/Disease.h ../sources/Disease.cpp
	g++ -c ../sources/Disease.cpp
clean:
	rm *.o
mrproper: clean
	rm -rf Tamagotchi.exe
