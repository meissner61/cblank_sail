output_dir := ./bin
executable := $(output_dir)/main.out
debug_executable := $(output_dir)/debug.out
src_files := $(wildcard src/*.c)

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs) -lGL -ldl -lm

# Default build type
BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE), debug)
    CFLAGS += -g
    TARGET := $(debug_executable)
else
    TARGET := $(executable)
endif

.PHONY: all clean run

all: $(TARGET)

$(executable): $(src_files)
	mkdir -p $(output_dir)
	$(CC) $(CFLAGS) $(src_files) $(LDFLAGS) -o $(executable)

$(debug_executable): $(src_files)
	mkdir -p $(output_dir)
	$(CC) $(CFLAGS) $(src_files) $(LDFLAGS) -o $(debug_executable)

run: $(TARGET)
	cd $(output_dir) && ./$(notdir $(TARGET))

clean:
	rm -rf $(output_dir)
