CC = gcc
CFLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

SRC = symnmf.c

# Derive object file names from source file names
OBJ = $(SRC:.c=.o)

# Name of the final executable
EXECUTABLE = symnmf

# Header files directory (if any)
INCLUDES = -I.

all: $(EXECUTABLE)

 $(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

 %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: rm -f $(OBJ) $(EXECUTABLE)