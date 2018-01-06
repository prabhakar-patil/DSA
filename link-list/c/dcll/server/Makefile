CC	= gcc
CFLAGS	= 
LDFLAGS	= 

SRCS	= client.c list_interface.c list_aux.c

EXE_NAME = client
LOG_FILE_NAME = *.log

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(SRCS) $(LDFLAGS)

debug: $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(SRCS) $(LDFLAGS) -g
clean:
	rm -f *.o $(EXE_NAME) $(LOG_FILE_NAME)
