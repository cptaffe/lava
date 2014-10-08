CC = clang
CFLAGS += -Wall -g
SRC= main.c lex.c lexers.c err.c
OBJ= ${SRC:.c=.o} 
HDRS= lex.h lexers.h err.h
BIN= lex

all: $(BIN)

$(BIN): $(OBJ)

$(OBJ): $(HDRS)

clean:
	rm -rf $(OBJ) $(BIN)