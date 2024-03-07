OUTPUT = ps1
CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
SOURCES = main.c bmp.c playfair.c

all: ps1

codeanalysis: $(SOURCES)
	cppcheck --enable=unusedFunction --error-exitcode=1 $^

$(OUTPUT): main.o bmp.o playfair.o
	echo "Running compilation"
	cppcheck --enable=unusedFunction --error-exitcode=1 $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	echo "Building object file bmp.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

playfair.o: playfair.c
	echo "Building object file playfair.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -rf *.o $(OUTPUT)

