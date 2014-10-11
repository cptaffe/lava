CC = clang
CFLAGS += -Wall -g

# lava compilation
SRC= main.c lexer/lex.c lexer/lexers.c parser/parse.c parser/parsers.c lexer/lexeme.c
HDRS = lexer/lex.h lexer/lexers.h lexer/lexeme.h parser/parse.h parser/parsers.h
OBJ= ${SRC:.c=.o} 
BIN= lava

MEMCHK = valgrind
MEMCHKFLAGS = --leak-check=full

DEBUG = lldb
DEBUGFLAGS = 

all: lava $(BIN)

# manual compile command, dirs apparently disable autocompiling.
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -L/home/cpt/lib/ -llava -o $(BIN) $(OBJ)

$(OBJ): $(HDRS)

clean:
	rm -rf $(OBJ) $(BIN)

run:
	./$(BIN)

# opens all program and header files in sublime
edit:
	subl $(SRC) $(HDRS)

# valgrind memory check on binary
memcheck: $(BIN)
	$(MEMCHK) $(MEMCHKFLAGS) ./$(BIN)

# debugging
debug: $(BIN)
	$(DEBUG) $(DEBUGFLAGS) ./$(BIN)

# properly formats program and header files
fmt:
	cfmt $(SRC) $(HDRS)