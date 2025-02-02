# file: Makefile
# author: Mangos, Cameron Tucker and Ella Self 
# date: 2024-10-14
# brief: Makefile for Steganography Project



CC = g++
TARGET = steganography
CFLAGS = -g -Wall -Wextra

all: $(TARGET)

$(TARGET): Steganography.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) Steganography.o main.o

Steganography.o: Steganography.cpp Steganography.h 
	$(CC) $(CFLAGS) -c Steganography.cpp

main.o: main.cpp Steganography.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) *.o *~
