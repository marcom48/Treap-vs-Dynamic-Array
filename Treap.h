/*
Author: Marco Marasco 834482.
Description: Header file for Treap data structure.
*/

#include "Element.h"
#ifndef T_H
#define T_H

#define PRIORITY_RANGE INT_MAX
using namespace std;

// Direction flags for rotation.
enum Direction
{
    LEFT,
    RIGHT
};

// A Treap Node
struct TreapNode
{
    Element *el;
    int priority;
    TreapNode *left, *right;

    TreapNode(Element *el_)
    {
        // Copy element.
        el = new Element(el_);

        // Set pseudo-random priority.
        priority = rand() % PRIORITY_RANGE;

        left = NULL;
        right = NULL;
    }
};

class Treap
{
private:
    TreapNode *root;
    TreapNode *insert_element(TreapNode *curr_root, Element *el);
    TreapNode *rotate(TreapNode *old_parent, Direction dir);
    TreapNode *delete_element(TreapNode *curr_root, int key);

public:
    Treap();
    void insert(Element *el);
    void delete_key(int key);
    Element *search(int key);
};

#endif