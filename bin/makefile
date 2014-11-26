all: GUI.o Tamagotchi.o System.o Disease.o tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o ../sources/main.cpp
	g++ GUI.o Tamagotchi.o System.o Disease.o tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o ../sources/main.cpp -o Tamagotchi.exe -lSDL2-2.0 -lSDL2main -lSDL2_ttf `sdl2-config --libs`
	
GUI.o:	../headers/GUI.h ../sources/GUI.cpp
	g++ -c ../sources/GUI.cpp -o GUI.o
	
Tamagotchi.o: ../headers/Tamagotchi.h ../sources/Tamagotchi.cpp
	g++ -c ../sources/Tamagotchi.cpp -o Tamagotchi.o
	
System.o: ../headers/System.h ../sources/System.cpp tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o
	g++ -c ../sources/System.cpp -o System.o
	
Disease.o: ../headers/Disease.h ../sources/Disease.cpp
	g++ -c ../sources/Disease.cpp -o Disease.o
	
tinyxml.o: ../includes/tinyxml/tinyxml.h ../includes/tinyxml/tinyxml.cpp
	g++ -c ../includes/tinyxml/tinyxml.cpp -o tinyxml.o
	
tinyxmlerror.o: ../includes/tinyxml/tinyxml.h ../includes/tinyxml/tinyxmlerror.cpp
	g++ -c ../includes/tinyxml/tinyxmlerror.cpp -o tinyxmlerror.o
	
tinyxmlparser.o: ../includes/tinyxml/tinyxml.h ../includes/tinyxml/tinyxmlparser.cpp
	g++ -c ../includes/tinyxml/tinyxmlparser.cpp -o tinyxmlparser.o
	
tinystr.o: ../includes/tinyxml/tinystr.h ../includes/tinyxml/tinystr.cpp
	g++ -c ../includes/tinyxml/tinystr.cpp -o tinystr.o
	
clean:
	rm *.o
	
mrproper: clean
	rm -rf Tamagotchi.exe
