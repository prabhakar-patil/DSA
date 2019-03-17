CC=gcc
LD=ld
CFLAGS=-Wall
LFLAGS=
DEBUG_FLAGS=-g

SRCS=graph.c graph_algo.c
SRC_BASIC_CLIENT=client_base_graph.c
SRC_ALGO_DFS_BFS_CLIENT=client_algo_dfs_bfs.c
SRC_ALGO_SHORTEST_PATH_CLIENT=client_algo_shortest_path.c
HDRS=graph.h graph_algo.h
EXE=app
EXED=appd

$(EXE): $(SRC_BASIC_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(SRC_BASIC_CLIENT)

debug: $(SRC_BASIC_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(SRC_BASIC_CLIENT)


algo-dfs-bfs: $(SRC_ALGO_DFS_BFS_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(SRC_ALGO_DFS_BFS_CLIENT)


debug-algo-dfs-bfs: $(SRC_ALGO_DFS_BFS_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(SRC_ALGO_DFS_BFS_CLIENT)


algo-shortest-path: $(SRC_ALGO_SHORTEST_PATH_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(SRC_ALGO_SHORTEST_PATH_CLIENT)

debug-algo-shortest-path: $(SRC_ALGO_SHORTEST_PATH_CLIENT) $(SRCS) $(HDRS)
	$(CC) -o $(EXED) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(SRC_ALGO_SHORTEST_PATH_CLIENT)

clean:
	rm -f $(EXE) $(EXED)
	  


