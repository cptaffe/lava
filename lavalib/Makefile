CC = clang
CFLAGS += -Wall -g -fpic

# lava shared library compilation
SRC = err/err.c types/types.c
HDRS = err/err.h types/types.h
OBJ = ${SRC:.c=.o}
LIB = liblava

# create shared library liblava.so # $(LIB).a
lava: $(LIB).so 

$(LIB).so: $(OBJ)
	$(CC) -shared -o $(LIB).so $(OBJ)

$(LIB).a: $(OBJ)
	ar rcs $(LIB).a $(OBJ) # static
	ranlib $(LIB).a

$(OBJ): $(HDRS)

clean:
	rm -rf $(LIB).so $(LIB).a $(OBJ)