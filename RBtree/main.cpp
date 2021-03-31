#include "RedBlackTree.h"
#include "../RedBlackTree/RedBlackTree.cpp"
using namespace std;

int main()
{
	List<int>* lsK;
	List<char>* lsV;
	RBTree<int, char> tr;
	cout << "RBTree: " << endl;
	tr.insert(13, 'a');
	tr.insert(8, 'b');
	tr.insert(17, 'c');
	tr.insert(25, 'd');
	tr.insert(1, 'f');
	tr.insert(11, 'e');
	//tr.print();
	//cout << endl<< "NEW RBTree: " << endl;
	tr.insert(15, 'g');
	tr.insert(22, 'h');
	tr.insert(6, 'i');
	tr.insert(27, 'j');
	tr.print();
	/*cout << "1 -if tree has 22 " << endl;
	cout << "0 -if tree hasn't 22 " << endl;
	cout << "Tree has 1?: ";
	cout << tr.exist(1) << endl;*/
	
	lsK=tr.get_keys();
	cout << "Keys: ";
	lsK->print_to_console();
	cout << endl << "Values: ";
	lsV=tr.get_values();
	lsV->print_to_console();
	tr.remove(13);
	tr.remove(1);
	cout << endl << endl << endl << "Delete 13 and 1" << endl;
	tr.print();
	//tr.insert(12, 'k');
	//tr.insert(21, 'l');
	//tr.print();
	cout << endl;
	lsK = tr.get_keys();
	cout << "Keys: ";
	lsK->print_to_console();
	cout << endl << "Values: ";
	lsV = tr.get_values();
	lsV->print_to_console();
	return 0;
}