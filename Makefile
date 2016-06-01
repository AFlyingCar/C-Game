OBJS = $(wildcard src/*.c)

CC = gcc

COMPILER_FLAGS = -w `sdl2-config --cflags --libs` -g -Wall

INCLUDES = -I.

LINKER_FLAGS = -lSDL2

OBJ_NAME = game

all: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDES) $(LINKER_FLAGS) -o $(OBJ_NAME)

