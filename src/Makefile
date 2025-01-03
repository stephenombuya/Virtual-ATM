# Define the compiler
CC = gcc

# Define flags for compiling C code
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`

# Define flags for linking C code
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Define the target executable
TARGET = atm

# Define all source code files
SOURCES = main.c \
          account.h \
          transaction.h \
          database.c \
          ui.c \
          # Add other source files here

# Define the object files
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
  $(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# Define a rule to compile each source file into its corresponding object file
%.o: %.c
  $(CC) $(CFLAGS) -c $<

# Phony target to clean up object files and the executable
clean:
  rm -f $(OBJECTS) $(TARGET)
