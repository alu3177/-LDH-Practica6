# makefile programa pg1

CC = g++
PFLAGS = -lmenu -lncurses
CFLAGS = -ansi -pedantic
CDEBUG = -g
OBJS = pg1.o menu.o grafo.o
MAIN = pg1
EXEC = pg1

MAIN: $(OBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(EXEC) $^ $(PFLAGS)

main.o: pg1.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

menu.o: lib/menu.cpp lib/menu.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

grafo.o: lib/grafo.cpp lib/grafo.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $@
