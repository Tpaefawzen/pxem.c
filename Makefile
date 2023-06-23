.POSIX:

moreflags = 
CFLAGS = -Wall -Wextra -Werror -O3 -g $(moreflags)

all: main

main: main.o pxem.o

clean:
	rm -Rf main main.o pxem.o
