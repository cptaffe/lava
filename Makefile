CC = clang
CFLAGS += -Wall -g
SRC= main.c lexer/lex.c lexer/lexers.c err/err.c parser/parse.c
OBJ= ${SRC:.c=.o} 
HDRS = lexer/lex.h lexer/lexers.h lexer/lexeme.h
HDRS += err/err.h parser/parse.h types.h
BIN= lex

all: $(BIN)

# manual compile command, dirs apparently disable autocompiling.
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(HDRS)

clean:
	rm -rf $(OBJ) $(BIN)