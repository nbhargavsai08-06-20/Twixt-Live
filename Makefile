CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

OBJS = main.o game.o

all: twixt

twixt: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c twixt.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c twixt.h
	$(CC) $(CFLAGS) -c game.c

clean:
	rm -f $(OBJS) twixt
