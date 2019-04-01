CC=g++
EXECNAME = jogo.out
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = object
CFLAGS = -std=c++11
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

BIN = $(BINDIR)/$(EXECNAME)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

run: all
	./jogo.out

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(EXECNAME)

%.o: $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@)
	$(CC) $(CFLAGS) -c $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ) *~
