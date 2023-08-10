.POSIX:

TARGET = pxem
OBJECT = main.o pxem.o

moreflags = -DNDEBUG
CFLAGS = -Wall -Wextra -Werror -O3 $(moreflags)

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGC) -o $(TARGET) $(OBJECT)

clean:
	rm -Rf main main.o pxem.o
