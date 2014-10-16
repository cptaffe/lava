CC = clang++ # linking and stuff
CXX = clang++ # actual compiler
CXXFLAGS += -Wall -g

SRCDIR = src

# module definitions
# liblava separate info (to allow library compilation, etc.)
LAVADIR = $(SRCDIR)/liblava
LAVAFILE = $(LAVADIR)/lava $(LAVADIR)/err/err $(LAVADIR)/types/types
LAVASRC = $(addsuffix .cc, $(LAVAFILE))
LAVAHDRS = $(LAVASRC:.cc=.h)

LEXERDIR = $(SRCDIR)/lexer
LEXERFILE = $(LEXERDIR)/lex $(LEXERDIR)/lexers $(LEXERDIR)/lexeme
LEXERSRC = $(addsuffix .cc, $(LEXERFILE))
LEXERHDRS = $(LEXERSRC:.cc=.h)

PARSERDIR = $(SRCDIR)/parser
PARSERFILE = $(PARSERDIR)/parse $(PARSERDIR)/parsers
PARSERSRC = $(addsuffix .cc, $(PARSERFILE))
PARSERHDRS = $(PARSERSRC:.cc=.h)

# include each module directory for header searching
DIRS = $(LAVADIR) $(LEXERDIR) $(PARSERDIR)
CXXFLAGS += $(addprefix -I, $(DIRS))

# lava compilation
SRC = $(SRCDIR)/main.cc $(LAVASRC) $(LEXERSRC) $(PARSERSRC)
HDRS = $(LAVAHDRS) $(LEXERHDRS) $(PARSERHDRS)

OBJ = $(SRC:.cc=.o)
BIN = lava

MEMCHK = valgrind
MEMCHKFLAGS = --leak-check=full

DEBUG = lldb
DEBUGFLAGS =

EDITOR = atom

all: $(BIN)
	rm $(OBJ) # some clean up

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
