CC = gcc
CFLAGS = -g -Wall -I$(IDIR) -o

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

.PHONY: all
.SILENT: all

all: clean find

find:
	$(CC) $(SOURCES) $(CFLAGS) $@

clean:
	rm -f ./myping