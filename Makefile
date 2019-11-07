CC = gcc
CFLAGS = -lncursesw -I${INCDIR} -g -Wall

INCDIR = ./inc/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: clean roqu

roqu: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

clean:
	rm -f roqu
