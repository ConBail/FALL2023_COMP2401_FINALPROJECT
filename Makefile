OBJ= main.o logger.o nodes.o rooms.o utils.o hunters.o house.o ghost.o evidence.o controlFlow.o
CFLAGS=-g -Wall -Wextra
CC=gcc
EXE=ACGame


all:  ${OBJ}
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: main.c defs.h
	$(CC) $(CFLAGS) -c main.c

logger.o: logger.c defs.h
	$(CC) $(CFLAGS) -c logger.c

nodes.o: nodes.c defs.h
	$(CC) $(CFLAGS) -c nodes.c

rooms.o: rooms.c defs.h
	$(CC) $(CFLAGS) -c rooms.c

utils.o: utils.c defs.h
	$(CC) $(CFLAGS) -c utils.c

hunters.o: hunters.c defs.h
	$(CC) $(CFLAGS) -c hunters.c

house.o: house.c defs.h
	$(CC) $(CFLAGS) -c house.c

ghost.o: ghost.c defs.h
	$(CC) $(CFLAGS) -c ghost.c

evidence.o: evidence.c defs.h
	$(CC) $(CFLAGS) -c evidence.c

controlFlow.o: controlFlow.c defs.h 
	$(CC) $(CFLAGS) -c controlFlow.c

clean:
			rm -f ${OBJ} ${EXE}
