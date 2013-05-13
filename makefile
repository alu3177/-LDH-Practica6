# makefile programa pg1

CC = g++
PFLAGS = -lmenu -lncurses
CFLAGS = -ansi -pedantic
CDEBUG = -g
OBJS = pg2.o grafo.o
MAIN = pg2
EXEC = pg2

MAIN: $(OBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(EXEC) $^ $(PFLAGS)

main.o: pg2.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

grafo.o: lib/grafo.cpp lib/grafo.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $@
