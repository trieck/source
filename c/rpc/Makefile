CC = gcc
CFLAGS = -Wall
OBJECTS = rpctest.o

rpctest: $(OBJECTS)
	$(CC) -o rpctest $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:	
	@-rm -f $(OBJECTS)
	@-rm -f rpctest.exe


