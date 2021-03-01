/*
Author: Marco Marasco 834482.
Description: Header file for Element structure.
*/

#ifndef EL_H
#define EL_H
#include <bits/stdc++.h>

struct Element
{
    int id, key;
    Element(int id_, int key_)
    {
        id = id_;
        key = key_;
    }
    Element(Element *e2)
    {
        id = e2->id;
        key = e2->key;
    }
};

#endif