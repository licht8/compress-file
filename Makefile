# Defines the build process for the project. It compiles C source files
# and creates an executable target. The structure includes separate directories for 
# object files, binaries, source files, and includes.

TARGET = Compress-File
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
SRC_DIR = src
INCLUDE_DIR = include
CC = gcc
CFLAGS = -Wall -O2 -I$(INCLUDE_DIR)

# Automatically gather source and header files
SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Define platform-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
    RM = del /Q $(subst /,\,$(1))
    RMDIR = rmdir /S /Q $(subst /,\,$(1))
else
    MKDIR = mkdir -p $(1)
    RM = rm -f $(1)
    RMDIR = rm -rf $(1)
endif

# Default target to build the executable
all: $(BIN_DIR) $(BIN_DIR)/$(TARGET)

# Rule to link object files into the final executable
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(call MKDIR,$(OBJ_DIR))

$(BIN_DIR):
	$(call MKDIR,$(BIN_DIR))

clean:
	$(call RM,$(OBJ_DIR)/*.o)
	$(call RM,$(BIN_DIR)/$(TARGET))
	$(call RMDIR,$(BUILD_DIR))

.PHONY: all clean $(OBJ_DIR) $(BIN_DIR)