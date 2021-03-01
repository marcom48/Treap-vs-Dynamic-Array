# Author: Marco Marasco 834482.
# Description: Makefile for COMP90077 Assignment 1.

CC = g++
CFLAGS  = -O3

default: prog


prog:  Assignment1.o Treap.o DynamicArray.o Generator.o 
	$(CC) $(CFLAGS) -o prog Assignment1.o Treap.o DynamicArray.o Generator.o

Assignment1.o: Assignment1.cpp Assignment1.h
	$(CC) $(CFLAGS) -c Assignment1.cpp

Generator.o:  Generator.cpp Generator.h Element.h 
	$(CC) $(CFLAGS) -c Generator.cpp

DynamicArray.o:  DynamicArray.cpp DynamicArray.h Element.h
	$(CC) $(CFLAGS) -c DynamicArray.cpp

Treap.o:  Treap.cpp Treap.h Element.h 
	$(CC) $(CFLAGS) -c Treap.cpp
