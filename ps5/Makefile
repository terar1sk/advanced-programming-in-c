CC = gcc
CFLAGS = -std=c11 -Werror -Wall
LDLIBS = -lm
OUTPUT=ps5

all: $(OUTPUT)

$(OUTPUT): backpack.o command.o container.o main.o game.o item.o parser.o room.o world.o
	$(CC) $(CFLAGS) $(LDLIBS) backpack.o command.o container.o main.o game.o item.o parser.o room.o world.o -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

backpack.o: backpack.c backpack.h
	$(CC) -std=c11 -Wall -Werror -c backpack.c -o backpack.o

command.o: command.c command.h
	$(CC) -std=c11 -Wall -Werror -c command.c -o command.o

container.o: container.c container.h
	$(CC) -std=c11 -Wall -Werror -c container.c -o container.o

game.o: game.c game.h
	$(CC) -std=c11 -Wall -Werror -c game.c -o game.o

item.o: item.c item.h
	$(CC) -std=c11 -Wall -Werror -c item.c -o item.o

parser.o: parser.c parser.h
	$(CC) -std=c11 -Wall -Werror -c parser.c -o parser.o

room.o: room.c room.h
	$(CC) -std=c11 -Wall -Werror -c room.c -o room.o

world.o: world.c world.h
	$(CC) -std=c11 -Wall -Werror -c world.c -o world.o

clean:
	rm -rf $(OUTPUT) *.o -rf *.o $(OUTPUT)

