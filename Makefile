CC = g++ # linking and stuff
CXX = g++ # actual compiler
CXXFLAGS += -Wall -g

# module definitions
# liblava separate info (to allow library compilation, etc.)
LAVADIR = liblava
LAVAFILE = $(LAVADIR)/lava $(LAVADIR)/err/err $(LAVADIR)/types/types
LAVASRC = $(addsuffix .cc, $(LAVAFILE))
LAVAHDRS = $(LAVASRC:.cc=.h)

LEXERDIR = lexer
LEXERFILE = $(LEXERDIR)/lex $(LEXERDIR)/lexers $(LEXERDIR)/lexeme
LEXERSRC = $(addsuffix .cc, $(LEXERFILE))
LEXERHDRS = $(LEXERSRC:.cc=.h)

PARSERDIR = parser
PARSERFILE = $(PARSERDIR)/parse $(PARSERDIR)/parsers
PARSERSRC = $(addsuffix .cc, $(PARSERFILE))
PARSERHDRS = $(PARSERSRC:.cc=.h)

# include each module directory for header searching
DIRS = $(LAVADIR) $(LEXERDIR) $(PARSERDIR)
CXXFLAGS += $(addprefix -I, $(DIRS))

# lava compilation
SRC = main.c $(LAVASRC) $(LEXERSRC) $(PARSERSRC)
HDRS = $(LAVAHDRS) $(LEXERHDRS) $(PARSERHDRS)

OBJ = ${SRC:.cc=.o}
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
