#pragma once
#include <iostream>
#include "Queue.h"
#include "List.h"
#include "Iterator.h"

template <typename NodeKey, typename NodeValue>
class RBTree
{
public:
	struct NodeTree
	{
		NodeKey key;
		NodeValue val;
		NodeTree* left;
		NodeTree* right;
		NodeTree* parent;
		bool black; //true is black, false is red

		NodeTree(NodeKey key = 0, NodeValue val = 0, NodeTree* parent = NULL)
		{
			this->key = key;
			this->val = val;
			this->left = NULL;
			this->right = NULL;
			this->parent = parent;
			this->black = false;
		}
	};
	class Iterator
	{
	public:
		virtual NodeTree* next() = 0;
		virtual bool has_next() = 0;
	};
	NodeTree* root;
	RBTree();
	~RBTree();
	void insert(NodeKey, NodeValue);//adding an element to the tree by key
	void print();//print a tree
	bool exist(NodeKey);// search for an element in the tree by key
	void clear();// clear a tree
	NodeValue find(NodeKey);//getting the value of an element by key
	List<NodeKey>* get_keys(); //getting a list of keys
	List<NodeValue>* get_values();//getting a list of values
	void remove(NodeKey);// deleting a tree element by key
	void print_map(NodeTree*);
	void print_tree(NodeTree*, int);

	Iterator* create_bft_iterator()// create an iterator that implements breadth-first traversal method
	{
		return new bft_iterator(root);
	}
	class bft_iterator : public Iterator
	{
	public:
		bft_iterator(NodeTree* start)
		{
			current = start;
			queue.push(current);
		}
		~bft_iterator()
		{
			delete current;
		};
		bool has_next() override;
		NodeTree* next() override;

	private:
		NodeTree* current;
		Queue <NodeTree*> queue;
	};
private:
	void SetLeft(NodeTree*, NodeKey, NodeValue);//set left node
	void SetRight(NodeTree*, NodeKey, NodeValue);// set right node
	void BalanceInsert(NodeTree*);//restoring the properties of red-black tree after insertion
	NodeTree* GrandPa(NodeTree*);//fing granfather
	NodeTree* Uncle(NodeTree*);//find uncle
	void TurnLeft(NodeTree*);//left turn
	void TurnRight(NodeTree*);//right turn
	void DeleteNode(NodeTree*);//delete node
	void BalanceDelete(NodeTree*);//restoring the properties of red-black tree after removing
	void DeleteTree(NodeTree*);//delete tree
};
