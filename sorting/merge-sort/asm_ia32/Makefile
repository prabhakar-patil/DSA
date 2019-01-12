AS=as
LD=ld
LFLAGS=-lc
DYNAMIC_LINKER=-dynamic-linker 
DYNAMIC_LINKER_PATH="/lib/ld-linux.so.2"
ENTRY_POINT_FUNC=main

SRC=merge_sort.s
OBJ=merge_sort.o
EXE=merge_sort

$(EXE): $(OBJ)
	$(LD) -o $(EXE) $(LFLAGS) $(DYNAMIC_LINKER) $(DYNAMIC_LINKER_PATH) -e $(ENTRY_POINT_FUNC) $(OBJ)

$(OBJ): $(SRC)
	$(AS) -o $(OBJ) $(SRC)

clean:
	rm -f $(OBJ) $(EXE)
	  


