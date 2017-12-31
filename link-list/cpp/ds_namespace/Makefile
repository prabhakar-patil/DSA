CC	= g++
INSTALL	= install
OBJS	= *.o
SRCS	= *.cpp

CFLAGS	= -c -fPIC
LDFLAGS	= --shared 

LIB_NAME	= libds.so
INSTALL_DIR	= /usr/lib
INSTALL		= install

#make rules
all: library 

${OBJS}: ${SRCS}
	$(CC) $(CFLAGS) ${SRCS} 

library: ${OBJS}
	$(CC) $(LDFLAGS) -o $(LIB_NAME) ${OBJS}

install: library
	@test -d $(INSTALL_DIR) || echo "$(INSTALL_DIR) not present, exiting ..."
	@$(INSTALL) -m 755 $(LIB_NAME) $(INSTALL_DIR) && echo "$(LIB_NAME) successfully installed at $(INSTALL_DIR)" || echo "To install $(LIB_NAME) at $(INSTALL_DIR), you need su perm, try using sudo make install" 

clean:
	rm -f *.o $(LIB_NAME)
