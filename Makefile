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

# Queue (que) Module
QUEDIR = $(SRCDIR)/que
QUEFILES = que
QUEFILE = $(addprefix $(QUEDIR)/, $(QUEFILES))

# LLVM Module
LLVMFLAGS = `llvm-config --cxxflags --ldflags --libs core`
LLVMDIR = $(SRCDIR)/llvm
LLVMFILES = llvm
LLVMFILE = $(addprefix $(LLVMDIR)/, $(LLVMFILES))
CXXFLAGS += -I$(LLVMDIR)/llvm/include -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS

# small .cc files without headers
HDRLESSDIR = $(SRCDIR)
HDRLESSFILES = main
HDRLESSFILE = $(addprefix $(HDRLESSDIR)/, $(HDRLESSFILES))

HDRONLYFILE = $(QUEFILE) $(LAVADIR)/keywords/keywords

# include each module directory for header searching
DIRS = $(LAVADIR) $(LEXERDIR) $(PARSERDIR) $(FIRSTPASSDIR) $(LLVMDIR) $(QUEDIR)
CXXFLAGS += $(addprefix -I, $(DIRS))

# lava compilation
FILES = $(LAVAFILE) $(LEXERFILE) $(PARSERFILE) $(FIRSTPASSFILE) $(LLVMFILE)
MODULESRC = $(addsuffix .cc, $(FILES))
HDRS = $(MODULESRC:.cc=.h) $(addsuffix .h, $(HDRONLYFILE))
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
	$(CC) $(CFLAGS) $(LLVMFLAGS) -lpthread -o $(BIN) $(OBJ)

$(OBJ): $(HDRS)

info:
	# $(FILES)

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
