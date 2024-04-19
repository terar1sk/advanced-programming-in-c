CC=gcc
CFLAGS=-std=gnu99 -Werror -Wall -lm
LDLIBS=null
OUTPUT=game.exe
DEPENDENCIES=bmp.o transformations.o

transformations.o: transformations.c
	$(CC) $(CFLAGS) -c transformations.c

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c

all: $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(DEPENDENCIES) main.c -o $(OUTPUT)

clean:
	rm -rf *.o $(OUTPUT)


