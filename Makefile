CC = clang++ # linking and stuff
CXX = clang++ # actual compiler
CXXFLAGS += -Wall -g -std=c++11

SRCDIR = src

# module definitions
# liblava separate info (to allow library compilation, etc.)
LAVADIR = $(SRCDIR)/lava
LAVAFILES = lava err/err types/types
LAVAFILE = $(addprefix $(LAVADIR)/, $(LAVAFILES))

# Lexer Module
LEXERDIR = $(SRCDIR)/lexer
LEXERFILES = lex lexers lexeme
LEXERFILE = $(addprefix $(LEXERDIR)/, $(LEXERFILES))

# Parser Module
PARSERDIR = $(SRCDIR)/parser
PARSERFILES = parse parsers
PARSERFILE = $(addprefix $(PARSERDIR)/, $(PARSERFILES))

# FirstPass Module
FIRSTPASSDIR = $(SRCDIR)/firstpass
FIRSTPASSFILES = firstpass
FIRSTPASSFILE = $(addprefix $(FIRSTPASSDIR)/, $(FIRSTPASSFILES))

# small .cc files without headers
HDRLESSDIR = $(SRCDIR)
HDRLESSFILES = main
HDRLESSFILE = $(addprefix $(HDRLESSDIR)/, $(HDRLESSFILES))

# include each module directory for header searching
DIRS = $(LAVADIR) $(LEXERDIR) $(PARSERDIR) $(FIRSTPASSDIR)
CXXFLAGS += $(addprefix -I, $(DIRS))

# lava compilation
FILES = $(LAVAFILE) $(LEXERFILE) $(PARSERFILE) $(FIRSTPASSFILE)
MODULESRC = $(addsuffix .cc, $(FILES))
HDRS = $(MODULESRC:.cc=.h)
SRC = $(addsuffix .cc, $(HDRLESSFILE)) $(MODULESRC) # headerless

OBJ = $(SRC:.cc=.o)
BIN = lava

MEMCHK = valgrind
MEMCHKFLAGS = --leak-check=full

DEBUG = lldb
DEBUGFLAGS =

EDITOR = atom

all: $(BIN)

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
