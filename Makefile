CC = gcc
CFLAGS = -ggdb -Wall -Wextra -std=c17 -MMD -MP -O0

INCLUDES = -Iinclude

LIB_PATHS = -Llib
LIB_NAMES = -lSDL3
LIBRARIES = $(LIB_PATHS) $(LIB_NAMES)

SOURCE := src
BUILDER := build
TARGET := bin
EXEC := $(TARGET)/main

SRC_MAIN := $(wildcard $(SOURCE)/main.c)
SRC_ENGINE_ALL := $(wildcard $(SOURCE)/Engine/*.c)
SRC_GAME_ALL := $(wildcard $(SOURCE)/Game/*.c)
#SRCS := $(shell find $(SOURCE) -name '*.c')
SRCS := $(SRC_MAIN) $(SRC_ENGINE_ALL)
OBJS := $(patsubst %.c, $(BUILDER)/%.o, $(SRCS:$(SOURCE)/%=%))


all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS) | $(TARGET)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBRARIES)

# Compile source files to object files
$(BUILDER)/%.o: $(SOURCE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(OBJS:.o=.d)

$(BUILDER) $(TARGET):
	mkdir -p $@

clean:
	rm -rf $(BUILDER)/*.o $(EXEC)

run: all
	./$(EXEC)