/*
Author: Marco Marasco 834482.
Description: Header file for Data Generator.
*/
#ifndef G_H
#define G_H

#include "Element.h"
#include "Treap.h"
#include "DynamicArray.h"

#define KEY_RANGE 10000001
#define DELETED -1

using namespace std;

// Different actions for the experiments.
enum Actions
{
    INSERT,
    DELETION,
    SEARCH
};

// Structure encapsulates data for a sequence operation.
struct Instruction
{
    Actions action;
    int key;
    Element *el;
    Instruction(Actions a_, int key_, Element *el_)
    {
        action = a_;
        key = key_;
        el = el_;
    }
};

// Class definition for Data Generator.
class Generator
{
private:
    map<int, int> elements; // Record (ID, Key) pairs to keep track of deleted elements.
    Element *gen_element();
    int id_next;

public:
    Generator();
    Instruction gen_insertion();
    Instruction gen_search();
    Instruction gen_deletion();
};

#endif