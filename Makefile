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
SRC_ENGINE_INIT := $(wildcard $(SOURCE)/Engine/Engine_Initialise.c)
SRC_ENGINE_SHUT := $(wildcard $(SOURCE)/Engine/Engine_Shutdown.c)
SRC_ENGINE_EVENT := $(wildcard $(SOURCE)/Engine/Engine_EventHandler.c)
SCR_ENGINE_GAMESTATE := $(wildcard $(SOURCE)/Engine/Engine_GameState.c)
SRC_ENGINE_VECTOR2 := $(wildcard $(SOURCE)/Engine/Engine_Vector2.c)
SRC_ENGINE_ENTITY := $(wildcard $(SOURCE)/Engine/Engine_Entity.c)
SRC_ENGINE_ENTITYMANAGER := $(wildcard $(SOURCE)/Engine/Engine_EntityManager.c)
SCR_ENGINE_RENDERSTATE := $(wildcard $(SOURCE)/Engine/Engine_RenderState.c)
SCR_ENGINE_RENDERMANAGER := $(wildcard $(SOURCE)/Engine/Engine_RenderManager.c)
SRC_ENGINE_LOOP := $(wildcard $(SOURCE)/Engine/Engine_MainLoop.c)
SRCS := $(SRC_MAIN) $(SRC_ENGINE_INIT) $(SRC_ENGINE_SHUT) $(SRC_ENGINE_EVENT) $(SCR_ENGINE_GAMESTATE) $(SRC_ENGINE_ENTITY) $(SRC_ENGINE_ENTITYMANAGER) $(SRC_ENGINE_VECTOR2) $(SCR_ENGINE_RENDERSTATE) $(SCR_ENGINE_RENDERMANAGER) $(SRC_ENGINE_LOOP)
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