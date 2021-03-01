/*
Author: Marco Marasco 834482.
Description: Header file for Dynamic Array.
*/

#ifndef D_H
#define D_H
#include "Element.h"

// Class definition for the Dynamic Array.
class DynamicArray
{
private:
    Element **arr;
    int n;
    int max_size;
    void push_back(Element *el);
    void delArr();
    void shrink();

public:
    DynamicArray();
    void insert(Element *el);
    Element *search(int key);
    void delete_key(int key);
};

#endif