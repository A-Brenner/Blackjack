card.o: card.c
	cc -c card.c

all: game.o card.o
	cc -c game.c card.c
	cc -o game game.o card.o

clean: *.o
	rm *.o