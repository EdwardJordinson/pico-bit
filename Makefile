CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -MMD -MP -g -O0

INCLUDES = -Iinclude

LIB_PATHS = -Llib
LIB_NAMES = -lSDL3
LIBRARIES = $(LIB_PATHS) $(LIB_NAMES)

SOURCE := src
BUILDER := build
TARGET := bin
EXEC := $(TARGET)/main

SRC_MAIN := $(wildcard $(SOURCE)/main.c)
SRC_ENGINE_INIT := $(wildcard $(SOURCE)/Engine/Engine_Initialise.c)
SRC_ENGINE_SHUT := $(wildcard $(SOURCE)/Engine/Engine_Shutdown.c)
SRC_ENGINE_LOOP := $(wildcard $(SOURCE)/Engine/Engine_Loop.c)
SRC_ENGINE_ENTITY := $(wildcard $(SOURCE)/Engine/Engine_Entity.c)
SRCS := $(SRC_MAIN) $(SRC_ENGINE_INIT) $(SRC_ENGINE_SHUT) $(SRC_ENGINE_LOOP) $(SRC_ENGINE_ENTITY)
#SRCS := $(shell find $(SOURCE) -name '*.c')
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