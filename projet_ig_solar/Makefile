
CC=gcc
CPP=g++
CFLAGS=-Wall -ansi -lGL -lGLU -lglut -lGLEW `libpng12-config --cflags --libs` -lz
LFLAGS=-Wall -ansi -lGL -lGLU -lglut `libpng12-config --cflags --libs`   
SFLAGS=-lGL -lGLEW
EXEC=planet


all: $(EXEC)

planet: shader.o depart.o png_use.o camera.o
	$(CPP) -o planet shader.o depart.o png_use.o camera.o $(CFLAGS)

shader.o: shader.c shader.h
	$(CPP) -o shader.o -c shader.c $(SFLAGS)

camera.o: camera.c camera.h
	$(CPP) -o camera.o -c camera.c 

png_use.o: png_use.c png_use.h
	$(CPP) -o png_use.o -c png_use.c $(LFLAGS)

depart.o: depart.c depart.h shader.h camera.h png_use.h
	$(CPP) -o depart.o -c depart.c $(CFLAGS)

clean:
	rm *.o

mrproper: clean
	rm -f $(EXEC)

