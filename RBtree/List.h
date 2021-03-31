#include <iostream>

using namespace std;

template <class type>
class List
{
private:

	class Node
	{
	public:
		Node* Next;//pointer to the next element in the list
		type data;//element value

		Node(type data = type(), Node* Next = NULL)//creating element
		{
			this->data = data;
			this->Next = Next;
		}
	};
	int Size;//list size
	Node* head;//pointer to the head of the list
public:
	List()
	{
		Size = 0;//list size
		head = NULL;//zeroing head element
	}
	~List()
	{
		clear();
	}
	type at(size_t index)//getting an element by index
	{
		if (isEmpty() == 1)
		{
			throw out_of_range("The list is empty");
		}
		else if (isEmpty() != 1 && index >= Size)
		{
			throw out_of_range("Index is greater than list size");
		}
		else
		{
			Node* current = this->head;//go to the beginning of the list
			for (int i = 0; i < index; i++)//find the element by index
			{
				current = current->Next;
			}
			return current->data;//return the value of the element
		}
	}
	void push_back(type data)//insert element in the end of the list
	{
		if (isEmpty() != 0)//insert first element if list is empty
		{
			head = new Node(data);//element creation
		}
		else//insert element in the end of the list
		{
			Node* current = head;//creation a new element
			while (current->Next != NULL)//while the next element exists, move throuth the list to the end
			{
				current = current->Next;
			}
			current->Next = new Node(data);//creating the last element
		}
		Size++;//increasing list size
	}
	bool isEmpty()//checking the list for emptiness
	{
		if (head == NULL) return true;
		else return false;
	}
	void clear()//clear list
	{
		while (Size)
		{
			pop_front();
		}
	}
	void pop_front()//remove an element from the beginning of the list
	{
		if (isEmpty() == 1)
		{
			throw out_of_range("The list is empty");
		}
		else
		{
			Node* current = head;//remember the first element
			head = head->Next;//make the second element first
			delete current;//delete first element
			Size--;//reduce list size
		}
	}
	void print_to_console()//output the list to the console
	{
		Node* current = this->head;//go to the beginning of the list
		while (current != NULL)//while new element exist
		{
			cout << current->data << " ";//display the value of the element
			current = current->Next;//move on to the next element
		}
	}
};