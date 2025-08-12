CC = gcc
CFLAGS = -Wall -g

# List all source files
SRC = code.c hop.c reveal.c log.c main.c proclore.c seek.c

# List all object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Define the executable name
EXEC = shell_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
