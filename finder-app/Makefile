# Makefile del finder-app (Assignment 2)
# - make                              -> compila "writer" para la plataforma nativa
# - make CROSS_COMPILE=aarch64-none-linux-gnu-  -> compila con el cross-compiler ARM
# - make clean                        -> borra "writer" y los .o

CC      = $(CROSS_COMPILE)gcc
CFLAGS  = -Wall -g

all: writer

writer: writer.c
	$(CC) $(CFLAGS) -o writer writer.c

clean:
	rm -f writer *.o

.PHONY: all clean
