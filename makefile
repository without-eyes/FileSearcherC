CC = gcc
CFLAGS = -g -Wall -I$(IDIR) -lpthread

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(wildcard $(SRCDIR)*.c)
OBJS = $(SOURCES:.c=.o)

TARGET = find

.PHONY: all clean
.SILENT: all

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
