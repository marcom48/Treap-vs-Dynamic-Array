/*
Author: Marco Marasco 834482.
Description: Contains constructor and methods for Data Generator.
*/

#include "Generator.h"

// Constructor for Data Generator.
Generator::Generator()
{
    id_next = 1;
}

// Method returns a new element for data structures.
Element *Generator::gen_element()
{

    // Pseudo-randomly generate key.
    int key = rand() % KEY_RANGE;

    // Assign id of element.
    int id = id_next++;

    // Store key number for ID for gen_deletion() method.
    elements[id] = key;

    return new Element(id, key);
}

// Method returns a new Insertion instruction.
Instruction Generator::gen_insertion()
{
    // Generate element to insert.
    Element *x = gen_element();

    return Instruction(INSERT, 0, x);
}

// Method returns a new Search instruction.
Instruction Generator::gen_search()
{
    // Generate pseudo-random key to search.
    int key = rand() % KEY_RANGE;

    return Instruction(SEARCH, key, NULL);
}

// Method returns a new Deletion instruction.
Instruction Generator::gen_deletion()
{

    // No elements in the structure, dummy deletion.
    if (id_next == 1)
        return Instruction(DELETION, 0, NULL);

    // Pseudo-randomly select ID of inserted element to delete.
    int id = 1 + rand() % (id_next - 1);
    int key;

    // Element already deleted.
    if (elements[id] == DELETED)
    {
        // Generate pseudo-random key to delete.
        key = rand() % KEY_RANGE;
    }
    else
    {
        key = elements[id];

        // Mark key as deleted.
        elements[id] = DELETED;
    }
    return Instruction(DELETION, key, NULL);
}
