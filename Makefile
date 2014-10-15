CC = clang
CFLAGS += -Wall -g

# module definitions
# liblava separate info (to allow library compilation, etc.)
LAVADIR = liblava
LAVASRC = $(LAVADIR)/err/err.c $(LAVADIR)/types/types.c
LAVAHDRS = $(LAVADIR)/lava.h $(LAVADIR)/types/types.h $(LAVADIR)/err/err.h

LEXERDIR = lexer
LEXERSRC = $(LEXERDIR)/lex.c $(LEXERDIR)/lexers.c $(LEXERDIR)/lexeme.c
LEXERHDRS = $(LEXERSRC:.c=.h)

PARSERDIR = parser
PARSERSRC = $(PARSERDIR)/parse.c $(PARSERDIR)/parsers.c
PARSERHDRS = $(PARSERSRC:.c=.h)

# include each module directory for header searching
DIRS = $(LAVADIR) $(LEXERDIR) $(PARSERDIR)
CFLAGS += $(addprefix -I, $(DIRS))

# lava compilation
SRC = main.c $(LAVASRC) $(LEXERSRC) $(PARSERSRC)
HDRS = $(LAVAHDRS) $(LEXERHDRS) $(PARSERHDRS)

OBJ = ${SRC:.c=.o}
BIN = lava

MEMCHK = valgrind
MEMCHKFLAGS = --leak-check=full

DEBUG = lldb
DEBUGFLAGS =

EDITOR = atom

all: lava $(BIN)

# manual compile command, dirs apparently disable autocompiling.
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(HDRS)

clean:
	rm -rf $(OBJ) $(BIN)

run:
	./$(BIN)

# opens all program and header files in sublime
edit:
	$(EDITOR) $(SRC) $(HDRS)

# valgrind memory check on binary
memcheck: $(BIN)
	$(MEMCHK) $(MEMCHKFLAGS) ./$(BIN)

# debugging
debug: $(BIN)
	$(DEBUG) $(DEBUGFLAGS) ./$(BIN)

# properly formats program and header files
fmt:
	cfmt $(SRC) $(HDRS)
