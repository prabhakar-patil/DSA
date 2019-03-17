CC=gcc
LD=ld
CFLAGS=-Wall
LFLAGS=
DEBUG_FLAGS=-g

SRCS=graph.c graph_algo.c
SRC_BASIC_CLIENT=client.c
SRC_ALGO_CLIENT=client_algo.c
HDRS=graph.h graph_algo.h
EXE=app
EXED=appd

$(EXE): $(SRC_BASIC_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(SRC_BASIC_CLIENT)

debug: $(SRC_BASIC_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(SRC_BASIC_CLIENT)

algo: $(SRC_ALGO_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(SRC_ALGO_CLIENT)

debug-algo: $(SRC_ALGO_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(SRC_ALGO_CLIENT)

clean:
	rm -f $(EXE) $(EXED)
	  


