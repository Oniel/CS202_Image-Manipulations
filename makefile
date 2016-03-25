# Make file for spirograph program

## note, uses bitmapImage shared object file (library).

OBJS = main.o imageType.o
CC	= g++
DEPS1 = imageType.h
DEPS2 = bitmapImage.h

all: main

main: $(OBJS)
	$(CC) -g -o main $(OBJS) bitmapImage.so

main.o:	main.cpp $(DEPS1)
	$(CC) -c -g main.cpp

imageType.o:	imageType.cpp $(DEPS1) $(DEPS2)
	$(CC) -c -g imageType.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

