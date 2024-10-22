CC = gcc

CFLAGS = -Wall -g

INCLUDES = mat.h msgassert.h

OBJ = mat.o matop.o

TARGET = matop

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

mat.o: mat.c $(INCLUDES)
	$(CC) $(CFLAGS) -c mat.c

matop.o: matop.c $(INCLUDES)
	$(CC) $(CFLAGS) -c matop.c

clean:
	rm -f $(OBJ) $(TARGET)

mrproper: clean
	rm -f *~ *.bak

