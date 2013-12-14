# makefile programa pg1

CC = g++
PFLAGS = -lmenu -lncurses
CFLAGS = -ansi -pedantic
CDEBUG = -g
OBJS = pg2.o grafo.o
MAIN = pg2
EXEC = pg2
TOBJS = grafo.o GrafoTest.o runTests.o
TEXEC = tpg2
TPFLAGS = -lcppunit

MAIN: $(OBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(EXEC) $^ $(PFLAGS)

main.o: pg2.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

grafo.o: lib/grafo.cpp lib/grafo.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $@
	rm -f $(TOBJS) $(TEXEC) $@


runTests.o: tests/runTests.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<
	
GrafoTest.o: tests/GrafoTest.cpp tests/GrafoTest.h 
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

test:	$(TOBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(TEXEC) $^ $(TPFLAGS)