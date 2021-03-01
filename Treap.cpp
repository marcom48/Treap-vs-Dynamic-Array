/*
Author: Marco Marasco 834482.
Description: Contains constructor and methods for Treap.
*/

#include "Treap.h"

Treap::Treap()
{
	root = NULL;
}

/*
Method rotates an input node in the Treap with a rotation
determined by the input direction. Method returns the node
that is rotated into the input node's position.
*/
TreapNode *Treap::rotate(TreapNode *old_parent, Direction dir)
{
	TreapNode *new_parent, *new_child;

	if (dir == LEFT)
	{

		new_parent = old_parent->right;

		new_child = new_parent->left;

		// Rotate.
		new_parent->left = old_parent;

		// Update original parent right child.
		old_parent->right = new_child;
	}
	else
	{

		new_parent = old_parent->left;

		new_child = new_parent->right;

		// Rotate.
		new_parent->right = old_parent;

		// Update original parent left child.
		old_parent->left = new_child;
	}

	// Return new parent.
	return new_parent;
}

/*
Method searches for the first element in the Treap with input key.
Returns element if found, else NULL.
*/
Element *Treap::search(int key)
{
	// Initialise pointer node to traverse tree.
	TreapNode *curr = root;

	while (curr != NULL)
	{

		// Required element found.
		if (curr->el->key == key)
		{
			return curr->el;
		}

		// Traverse right subtree for element.
		if (curr->el->key < key)
		{
			curr = curr->right;
		}
		else
		{
			// Traverse left subtree.
			curr = curr->left;
		}
	}

	// Element not found.
	return NULL;
}

/*
Public interface to insert an element into the Treap.
*/
void Treap::insert(Element *el)
{
	root = insert_element(root, el);
}

/* Recursive implementation of insertion in Treap */
TreapNode *Treap::insert_element(TreapNode *curr_root, Element *el)
{

	// If root is NULL, create a new node and return it
	if (curr_root == NULL)
		return new TreapNode(el);

	// Boolean flag if new element hass smaller key.
	bool smaller_key = el->key < curr_root->el->key;

	// Boolean flag if new element has same key as current root but smaller ID value.
	bool smaller_id = el->key == curr_root->el->key && el->id < curr_root->el->id;

	// If key is smaller than current root or same value but smaller id.
	if (smaller_key || smaller_id)
	{
		// Insert new element into left subtree.
		curr_root->left = insert_element(curr_root->left, el);

		// Fix heap property for current root if required.
		if (curr_root->left->priority < curr_root->priority)
		{
			curr_root = rotate(curr_root, RIGHT);
		}
	}
	else
	{
		// Insert new element int right subtree if required.
		curr_root->right = insert_element(curr_root->right, el);

		// Fix heap property for current root.
		if (curr_root->right->priority < curr_root->priority)
		{
			curr_root = rotate(curr_root, LEFT);
		}
	}

	return curr_root;
}

/*
Public interface to delete an element with an input key.
*/
void Treap::delete_key(int key)
{
	// Treap is empty.
	if (root == NULL)
	{
		return;
	}

	// Update Treap with removed element.
	root = delete_element(root, key);
}

/*
Method searches for node in Treap containing element key
for deletion. If the element is found, it is removed from
the Treap.
*/
TreapNode *Treap::delete_element(TreapNode *curr_root, int key)
{
	// Node has been removed or element has not been found.
	// Element not found in scenario where element was previously
	// deleted by randomly choosing the search KEY in the generator,
	// but was not able to record the element key ID.
	if (curr_root == NULL)
	{
		return curr_root;
	}

	// Element hasn't been found, continue to search Treap.
	if (curr_root->el->key != key)
	{
		if (key < curr_root->el->key)
		{
			curr_root->left = delete_element(curr_root->left, key);
			return curr_root;
		}
		else
		{
			curr_root->right = delete_element(curr_root->right, key);
			return curr_root;
		}
	}

	// Key has been found.
	// Update priority to rotate to leaf.
	curr_root->priority = INT_MAX;

	// Able to move node to leaf.
	if (curr_root->left == NULL)
	{
		// Move node to be deleted to leaf.
		TreapNode *temp = curr_root->right;
		delete (curr_root);
		// Move right child up.
		curr_root = temp;
	}
	else if (curr_root->right == NULL)
	{
		// Move node to be deleted to leaf.
		TreapNode *temp = curr_root->left;
		delete (curr_root);
		// Move left child up.
		curr_root = temp;
	}
	else if (curr_root->left->priority < curr_root->right->priority)
	{
		// Perform left rotation.
		curr_root = rotate(curr_root, LEFT);

		// Proceed to remove left child.
		curr_root->left = delete_element(curr_root->left, key);
	}
	else if (curr_root->left->priority > curr_root->right->priority)
	{
		// Perform right rotation.
		curr_root = rotate(curr_root, RIGHT);

		// Proceed to remove right child.
		curr_root->right = delete_element(curr_root->right, key);
	}
	else
	{
		// Handle case of same priority.
		// Perform right rotation.
		curr_root = rotate(curr_root, RIGHT);

		// Proceed to remove right child.
		curr_root->right = delete_element(curr_root->right, key);
	}

	return curr_root;
}
