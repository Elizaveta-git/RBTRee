#include "pch.h"
#include "CppUnitTest.h"
#include "../RedBlackTree.h"
#include "..\RedBlackTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlackTreeTests
{
	TEST_CLASS(RedBlackTreeTests)
	{
	public:
		RBTree<int, char> tr;
		RBTree<int, char>::Iterator* it;
		RBTree<int, char>::NodeTree* curr;

		//////BFT//ITERATOR//////
		TEST_METHOD(bft_iterator)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(11, 'e');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			curr = it->next();
			Assert::AreEqual(curr->key, 8);
			Assert::AreEqual(curr->val, 'b');
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 11);
			Assert::AreEqual(curr->val, 'e');
		}

		TEST_METHOD(bft_iterator_error)
		{
			tr.insert(13, 'a');
			it = tr.create_bft_iterator();
			try
			{
				it->next();
				it->next();
				it->next();
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("has next is false", error.what());
			}
		}

		////////INSERT////////
		TEST_METHOD(insert_root)
		{
			tr.insert(13, 'a');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
		}
		TEST_METHOD(insert_four)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(11, 'e');
			tr.insert(1, 'f');
			tr.insert(15, 'g');
			tr.insert(22, 'h');
			tr.insert(6, 'i');
			tr.insert(27, 'j');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			curr = it->next();
			Assert::AreEqual(curr->key, 8);
			Assert::AreEqual(curr->val, 'b');
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 1);
			Assert::AreEqual(curr->val, 'f');
		}
		TEST_METHOD(insert_end)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			curr = it->next();
			Assert::AreEqual(curr->key, 8);
			Assert::AreEqual(curr->val, 'b');
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 1);
			Assert::AreEqual(curr->val, 'f');
			curr = it->next();
			Assert::AreEqual(curr->key, 11);
			Assert::AreEqual(curr->val, 'e');
			curr = it->next();
			Assert::AreEqual(curr->key, 25);
			Assert::AreEqual(curr->val, 'd');
		}
		////////SET//LEFT////////
		TEST_METHOD(set_left)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			Assert::AreEqual(curr->left->key, 8);
			Assert::AreEqual(curr->left->val, 'b');
		}
		////////SET//RIGHT////////
		TEST_METHOD(set_right)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			Assert::AreEqual(curr->right->key, 17);
			Assert::AreEqual(curr->right->val, 'c');
		}
		////////EXIST////////
		TEST_METHOD(exist_true)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			Assert::AreEqual(tr.exist(25), true);
		}
		TEST_METHOD(exist_false)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			Assert::AreEqual(tr.exist(12), false);
		}
		////////FIND////////
		TEST_METHOD(find_not_error)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			Assert::AreEqual(tr.find(25), 'd');
		}
		TEST_METHOD(find_error)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			try
			{
				tr.find(12);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("has next is false", error.what());
			}
		}
		////////remove////////
		TEST_METHOD(remove_end)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			tr.remove(11);
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			curr = it->next();
			Assert::AreEqual(curr->key, 8);
			Assert::AreEqual(curr->val, 'b');
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 1);
			Assert::AreEqual(curr->val, 'f');
			curr = it->next();
			Assert::AreEqual(curr->key, 25);
			Assert::AreEqual(curr->val, 'd');
		}
		TEST_METHOD(remove_mid)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			tr.remove(8);
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 13);
			Assert::AreEqual(curr->val, 'a');
			curr = it->next();
			Assert::AreEqual(curr->key, 11);
			Assert::AreEqual(curr->val, 'e');
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 1);
			Assert::AreEqual(curr->val, 'f');
			curr = it->next();
			Assert::AreEqual(curr->key, 25);
			Assert::AreEqual(curr->val, 'd');
		}
		TEST_METHOD(remove_root)
		{
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			tr.remove(13);
			it = tr.create_bft_iterator();
			curr = it->next();
			Assert::AreEqual(curr->key, 17);
			Assert::AreEqual(curr->val, 'c');
			curr = it->next();
			Assert::AreEqual(curr->key, 8);
			Assert::AreEqual(curr->val, 'b');
			curr = it->next();
			Assert::AreEqual(curr->key, 25);
			Assert::AreEqual(curr->val, 'd');
			curr = it->next();
			Assert::AreEqual(curr->key, 1);
			Assert::AreEqual(curr->val, 'f');
			curr = it->next();
			Assert::AreEqual(curr->key, 11);
			Assert::AreEqual(curr->val, 'e');
		}
		TEST_METHOD(remove_error)
		{
			tr.insert(13, 'a');
			try
			{
				tr.remove(20);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("has next is false", error.what());
			}
		}
		////////GET//KEYS////////
		TEST_METHOD(get_keys)
		{
			List<int>* keys;
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			it = tr.create_bft_iterator();
			keys = tr.get_keys();
			curr = it->next();
			Assert::AreEqual(curr->key, keys->at(0));
			curr = it->next();
			Assert::AreEqual(curr->key, keys->at(1));
			it->next();
			it->next();
			it->next();
			curr = it->next();
			Assert::AreEqual(curr->key, keys->at(5));
		}
		////////GET//VALUES////////
		TEST_METHOD(get_values)
		{
			List<char>* keys;
			tr.insert(13, 'a');
			tr.insert(8, 'b');
			tr.insert(17, 'c');
			tr.insert(25, 'd');
			tr.insert(1, 'f');
			tr.insert(11, 'e');
			it = tr.create_bft_iterator();
			keys = tr.get_values();
			curr = it->next();
			Assert::AreEqual(curr->val, keys->at(0));
			curr = it->next();
			Assert::AreEqual(curr->val, keys->at(1));
			it->next();
			it->next();
			it->next();
			curr = it->next();
			Assert::AreEqual(curr->val, keys->at(5));
		}
	};
}
