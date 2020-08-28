CC = gcc
CFLAGS = -Wall -g -std=c99
SOURCES = main.c functions.c FileFunctions.c
OBJECTS = $(SOURCES:.c=.o)
OUTFILE = Departments

all: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
	
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)
