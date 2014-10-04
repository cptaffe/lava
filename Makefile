CC= clang
SRC= main.c lex.c
OBJ= ${SRC:.c=.o} 
BIN= lex

all: $(BIN)

$(BIN): $(OBJ)

clean:
	rm -rf $(OBJ) $(BIN)