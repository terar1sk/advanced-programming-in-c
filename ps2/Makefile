OUTPUT = ps2
CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
SOURCES = main.c k.c hof.c

all: ps2

codeanalysis: $(SOURCES)
	cppcheck --enable=unusedFunction --error-exitcode=1 $^

$(OUTPUT): main.o k.o hof.o
	echo "Running compilation"
	cppcheck --enable=unusedFunction --error-exitcode=1 $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: k.c
	echo "Building object file k.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: hof.c
	echo "Building object file hof.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	rm -rf *.o $(OUTPUT)
