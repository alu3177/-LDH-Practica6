# makefile programa pg1

CC = g++
CFLAGS = -ansi -pedantic
CDEBUG = -g
OBJS = pg1.o grafo.o
MAIN = pg1
EXEC = pg1

MAIN: $(OBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(EXEC) $^

main.o: pg1.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

grafo.o: lib/grafo.cpp lib/grafo.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $@
