#include "RedBlackTree.h"

using namespace std;

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::SetLeft(NodeTree* curr, NodeKey key, NodeValue val)
{
	curr->left = new NodeTree(key, val, curr);//white the element
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::SetRight(NodeTree* curr, NodeKey key, NodeValue val)
{
	curr->right = new NodeTree(key, val, curr);//white the element
}


template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::BalanceInsert(NodeTree* curr)
{
	while (curr != root && curr->parent->black == false) 
	{
		NodeTree* GrPa = GrandPa(curr);
		if (curr->parent == GrPa->left) //if the left subtree
		{
			NodeTree* un = Uncle(curr);
			if (un->black == false) //if uncle is red
			{
				curr->parent->black = true;//parent is black
				un->black = true;//uncle is black
				GrPa->black = false;//grandfather is black
				curr = GrPa;
			}
			else //if uncle is black
			{
				if (curr == curr->parent->right) //if curr is right subtree
				{
					curr = curr->parent;
					TurnLeft(curr);//left turn
				}
				/* recolor and rotate */
				curr->parent->black = true;
				GrPa->black = false;
				TurnRight(GrPa);
			}
		}
		else //if the right subtree
		{
			/* mirror image of above code */
			NodeTree* un =Uncle(curr);
			if (un->black == false) 
			{
				curr->parent->black = true;
				un->black = true;
				GrPa->black = false;
				curr = GrPa;
			}
			else 
			{
				if (curr == curr->parent->left) 
				{
					curr = curr->parent;
					TurnRight(curr);
				}
				curr->parent->black = true;
				GrPa->black = false;
				TurnLeft(GrPa);
			}
		}
	}
	root->black = true;//root is black
}

template<typename NodeKey, typename NodeValue>
typename RBTree<NodeKey, NodeValue>::NodeTree* RBTree<NodeKey, NodeValue>::GrandPa(NodeTree* curr)
{
	if (curr != NULL && curr->parent != NULL)//if grandfather is exist
	{
		return curr->parent->parent;
	}
	else 
		return NULL;
}

template<typename NodeKey, typename NodeValue>
typename RBTree <NodeKey, NodeValue>::NodeTree* RBTree<NodeKey, NodeValue>::Uncle(NodeTree* curr)
{
	NodeTree* GrPa = GrandPa(curr);
	if (GrPa == NULL)//if grandfather doesn't exist
	{
		return NULL;
	}
	else if (curr->parent == GrPa->left)//find uncle
	{
		return GrPa->right;
	}
	else
		return GrPa->left;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::TurnLeft(NodeTree* curr)
{
	NodeTree* pivot = curr->right;//support element-right subtree
	pivot->parent = curr->parent;
	if (curr->parent != NULL)//if curr have parent
	{
		if (curr->parent->left == curr)//if curr is left subtree
			curr->parent->left = pivot;
		else//if curr is right left subtree
			curr->parent->right = pivot;
	}
	curr->right = pivot->left;
	if (pivot->left != NULL)//if support have left subtree
	{
		pivot->left->parent = curr;//the parent of the pivot element's left subtree is the current
	}	
	curr->parent = pivot;//the parent of the current element is the pivot
	pivot->left = curr;
	if (curr == root)
	{
		root = pivot;
	}
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::TurnRight(NodeTree* curr)
{
	/* mirror image of above code TurnLeft*/
	NodeTree* pivot = curr->left;
	pivot->parent = curr->parent;
	if (curr->parent != NULL) 
	{
		if (curr->parent->left == curr)
			curr->parent->left = pivot;
		else
			curr->parent->right = pivot;
	}
	curr->left = pivot->right;
	if (pivot->right != NULL)
		pivot->right->parent = curr;
	curr->parent = pivot;
	pivot->right = curr;
	if (curr == root)
		root = pivot;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::DeleteNode(NodeTree* curr)
{
	NodeTree* child = new NodeTree;
	NodeTree* del = new NodeTree;
	NodeTree* nill = new NodeTree(0, 0, curr);
	if (!curr || curr == NULL)//if curr is exist
		return;

	if (curr->left == NULL || curr->right == NULL)//if the deleted node has a NIL child
	{
		del = curr;
	}
	else// find tree successor with a NIL node as a child
	{
		del = curr->right;
		while (del->left != NULL)
		del = del->left;
	}
	if (del->left == NULL && del->right == NULL)//if the item to be deleted is a leaf item
	{
		child = nill;
	}
	/* if the deleted one has one child */
	else if (del->left != NULL)
		child = del->left;
	else
		child = del->right;

	/* remove dell from the parent chain */
	child->parent = del->parent;//changes child with parent
	if (del->parent)//If there is no grandfather, then the child becomes the root of the tree
	{
		if (del == del->parent->left)
			del->parent->left = child;
		else
			del->parent->right = child;
	}
	else
		root = child;

	if (del != curr)//change values
	{
		curr->key = del->key;
		curr->val = del->val;
	}

	if (del->black == true)//if dell is black, then we balance
		BalanceDelete(child);
	
	if (child->parent->right == child)//remove nill element values
	{
		if (child==nill)
			child->parent->right = NULL;
	}
	else
	{
		if (child==nill)
			child->parent->left = NULL;
	}
	delete(del);//delete
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::BalanceDelete(NodeTree* curr)
{
	while (curr != root && curr->black == true) 
	{
		if (curr == curr->parent->left) // if this left subtree
		{
			NodeTree* sister = curr->parent->right;
			if (sister->black == false) //if sistre is red
			{
				sister->black = true;//sister is black
				curr->parent->black = false;//parent is red
				TurnLeft(curr->parent);//left turn for parent
				sister = curr->parent->right;
			}
			if (sister->left->black == true && sister->right->black == true) //if both children are black
			{
				sister->black = false;
				curr = curr->parent;
			}
			else 
			{
				if (sister->right->black == true)
				{
					sister->left->black = true;
					sister->black = false;
					TurnRight(sister);
					sister = curr->parent->right;
				}
				sister->black = curr->parent->black;
				curr->parent->black = true;
				sister->right->black = true;
				TurnLeft(curr->parent);
				curr = root;
			}
		}
		else //if this right subtree
		{
			/* mirror image of above code */
			NodeTree* sister = curr->parent->left;
			if (sister->black == false)
			{
				sister->black = true;
				curr->parent->black = false;
				TurnRight(curr->parent);
				sister = curr->parent->left;
			}
			if (sister->right->black == true && sister->left->black == true)
			{
				sister->black = false;
				curr = curr->parent;
			}
			else 
			{
				if (sister->left->black == true)
				{
					sister->right->black = true;
					sister->black = false;
					TurnLeft(sister);
					sister = curr->parent->left;
				}
				sister->black = curr->parent->black;
				curr->parent->black = true;
				sister->left->black = true;
				TurnRight(curr->parent);
				curr = root;
			}
		}
	}
	curr->black = true;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::DeleteTree(NodeTree* current)
{
	if (current)
	{
		DeleteTree(current->left);
		DeleteTree(current->right);
		delete current;
	}
}

template<typename NodeKey, typename NodeValue>
inline RBTree<NodeKey, NodeValue>::RBTree()
{
	root = NULL;
}

template<typename NodeKey, typename NodeValue>
RBTree<NodeKey, NodeValue>::~RBTree()
{
	delete root;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::insert(NodeKey key, NodeValue val)
{
	NodeTree* curr;
	NodeTree* next;
	if (root == NULL)//if tree is no tree
	{
		root = new NodeTree(key, val);//create root element
		root->black = true;//root is black
	}
	else//if tree is exist
	{
		curr = next = root;
		while (next != NULL)//loking for a place to insert
		{
			curr = next;
			if (key < curr->key)
				next = curr->left;
			if (key > curr->key)
				next = curr->right;
			if (key == curr->key)
			{
				curr->val = val;
			}
		}
		/* insert the element */
		if (key < curr->key) {
			SetLeft(curr, key, val);
			next = curr->left;
		}
		else {
			SetRight(curr, key, val);
			next = curr->right;
		}
		BalanceInsert(next);//Balance tree
	}
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::print()
{
	Iterator* it = create_bft_iterator();
	NodeTree* curr;
	while (it->has_next())
	{
		curr = it->next();
		cout << curr->key << "(" << curr->black << "):" << curr->val << "   ";
	}
	cout << endl;
}

template<typename NodeKey, typename NodeValue>
bool RBTree<NodeKey, NodeValue>::exist(NodeKey key)
{
	NodeTree* curr;
	NodeTree* next;
	curr = next = root;
	while (next != NULL) {//loking for a element
		curr = next;
		if (key < curr->key)
			next = curr->left;
		if (key > curr->key)
			next = curr->right;
		if (key == curr->key) {
			return true;
		}
	}
	return false;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::clear()
{
	DeleteTree(root);
	root = NULL;
}

template<typename NodeKey, typename NodeValue>
NodeValue RBTree<NodeKey, NodeValue>::find(NodeKey key)
{
	NodeTree* curr; 
	NodeTree* next;
	curr = next = root;
	if (exist(key))//if element is exist
	{
		while (next != NULL)//find thil element
		{
			curr = next;
			if (key < curr->key)
				next = curr->left;
			if (key > curr->key)
				next = curr->right;
			if (key == curr->key) 
			{
				return curr->val;
			}
		}
	}
	else 
		return NodeValue();
}

template<typename NodeKey, typename NodeValue>
List<NodeKey>* RBTree<NodeKey, NodeValue>::get_keys()
{
	List <NodeKey>* list=new List<NodeKey>;
	Iterator* it= create_bft_iterator();
	while (it->has_next()) 
	{
		list->push_back(it->next()->key);//write each item to the list
	}
	return list;
}

template<typename NodeKey, typename NodeValue>
List<NodeValue>* RBTree<NodeKey, NodeValue>::get_values()
{
	Iterator* it = create_bft_iterator();
	List<NodeValue>* list = new List<NodeValue>;
	while (it->has_next())
	{
		list->push_back(it->next()->val);//write each item to the list
	}
	return list;
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::remove(NodeKey key)
{
	if (!exist(key))//if element is exist
		return;
	NodeTree* curr;
	NodeTree* next;
	curr = next = root;
	while (next != NULL) //find this element
	{
		curr = next;
		if (key < curr->key)
			next = curr->left;
		if (key > curr->key)
			next = curr->right;
		if (key == curr->key) {
			DeleteNode(curr); //delete element
			return;
		}
	}
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::print_map(NodeTree* curr)
{
	if (curr) // Checking for a non-null pointer
	{
		print(curr->left);
		cout << curr->key << " " << curr->val << endl;
		print(curr->right);
	}
}

template<typename NodeKey, typename NodeValue>
void RBTree<NodeKey, NodeValue>::print_tree(NodeTree* curr, int h)
{
	if (curr)
	{
		print_tree(curr->left, h + 3);
		for (int i = 0; i < h; i++)
		{
			cout << "   ";
		}
		cout << curr->key << "(" << curr->black << "):" << curr->val << endl;
		print_tree(curr->right, h + 3);
	}
}

template<typename NodeKey, typename NodeValue>
inline bool RBTree<NodeKey, NodeValue>::bft_iterator::has_next()
{
	return (!queue.isEmpty());
}

template<typename NodeKey, typename NodeValue>
typename RBTree<NodeKey, NodeValue>::NodeTree* RBTree<NodeKey, NodeValue>::bft_iterator::next()
{
	if (!has_next()) throw std::out_of_range("has next is false");
	current = queue.pop();
	if (current->left != NULL)
	{
		queue.push(current->left);

	}
	if (current->right != NULL)
	{
		queue.push(current->right);
	}
	return current;
}