/*
Author: Marco Marasco 834482.
Description: Contains constructor and methods for Dynamic Array.
*/

#include "DynamicArray.h"

using namespace std;

DynamicArray::DynamicArray()
{
    arr = (Element **)malloc(sizeof(Element *));
    max_size = 1;
    n = 0;
}

/*
Public interface to insert an element.
*/
void DynamicArray::insert(Element *el)
{

    push_back(el);
}

/*
Method inserts an element into the Dynamic Array.
*/
void DynamicArray::push_back(Element *el)
{

    // If space left in array for new element.
    if (n + 1 < max_size)
    {
        arr[n++] = el;
    }
    else
    {
        // Array needs to be increased.
        // Create new array.
        Element **new_arr = (Element **)malloc(sizeof(Element *) * 2 * max_size);

        // Copy over old array;
        for (int i = 0; i < n; i++)
        {
            new_arr[i] = new Element(arr[i]);
        }

        // Delete original array.
        delArr();

        // Insert new element.
        new_arr[n++] = el;

        // Increase maximum capacity of array.
        max_size *= 2;

        // Reassign namespace.
        arr = new_arr;
    }
}

/*
Method searches for an element with input key and returns it.
Returns NULL if element in array.
*/
Element *DynamicArray::search(int key)
{
    // Perform linear search.
    for (int i = 0; i < n; i++)
    {
        if (arr[i]->key == key)
        {

            return arr[i];
        }
    }

    // Element not found.
    return NULL;
}

/*
Method searches for element in array with input key value
to delete. No element deleted if key is not in array.
*/
void DynamicArray::delete_key(int key)
{

    // Perform linear search.
    for (int i = 0; i < n; i++)
    {
        // Found element.
        if (arr[i]->key == key)
        {

            // Swap element to delete with last element.
            swap(arr[i], arr[n - 1]);

            // Remove last element.
            delete (arr[n - 1]);

            // Reduce number of elements in array.
            n -= 1;

            if (n < max_size / 4)
            {
                // Shrink array capacity by half.
                shrink();
            }

            return;
        }
    }

    // Element not found in scenario where element was previously
    // deleted by randomly choosing the search KEY in the generator,
    // but was not able to record the element key ID.
    return;
}

/*
Method shrink the dynamic array to half its capacity.
*/
void DynamicArray::shrink()
{

    // Update maximum size.
    max_size = max_size / 2;

    // Initialise new array.
    Element **new_arr = (Element **)malloc(sizeof(Element *) * max_size);

    // Copy old array.
    for (int i = 0; i < n; i++)
    {
        new_arr[i] = new Element(arr[i]);
    }
    // Delete old array.
    delArr();

    arr = new_arr;
}

/*
Method deletes current array in Dynamic Array.
*/
void DynamicArray::delArr()
{

    for (int i = 0; i < n; i++)
    {
        delete (arr[i]);
    }

    delete[] arr;
}