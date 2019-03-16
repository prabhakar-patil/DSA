CC=gcc
LD=ld
CFLAGS=-Wall
LFLAGS=
DEBUG_FLAGS=-g

SRCS=client.c graph.c
HDRS=graph.h
EXE=app
EXED=appd

$(EXE): $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS)

debug: $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS)

clean:
	rm -f $(EXE) $(EXED)
	  


