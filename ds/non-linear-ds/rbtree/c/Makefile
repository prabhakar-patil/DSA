CC=gcc
LD=ld
CFLAGS=-Wall
DEBUGFLAG=-g
LFLAGS=

SRCS=client.c rbt.c
HDRS=rbt.h
EXE=app
EXED=appd

$(EXE): $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS)

debug: $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUGFLAG) $(SRCS)
clean:
	rm -f $(EXE) $(EXED)
	  


