CC = clang++
CFLAGS = -Wall -Wpedantic -Wextra -ggdb -std=c++20
CINCLUDES = -I./includes/raylib/src
CLIBS = -L./includes/raylib/src -lm -lraylib

SRC = src
OBJ = obj

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR = bin
BIN = $(BINDIR)/2048

all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(CLIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

clean:
	rm -rf $(BINDIR) $(OBJ)

run: $(BIN)
	./$(BIN)

$(OBJ):
	@mkdir -p $@

