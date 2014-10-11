CC = clang
CFLAGS += -Wall -g -fPIC

# lava shared library compilation
SRC = err/err.c types/types.c
HDRS = err/err.h types/types.h
OBJ = ${SRC:.c=.o}
LIB = liblava.so

# create shared library liblava.so
lava: $(LIB)

$(LIB): $(OBJ)
	$(CC) -shared -o $(LIB) $(OBJ)

$(OBJ): $(HDRS)

clean:
	rm -rf $(LIB) $(OBJ)