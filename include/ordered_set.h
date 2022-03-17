#pragma once
#include <string>
#include <array_list.h>

using namespace std;

namespace ssuds
{
	template <class T>
	class OrderedSet
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;

			Node(const T& val) : mData(val), mLeft(nullptr), mRight(nullptr)
			{
			}

			int insert_recursive(const T& val)
			{
				if (val < mData)
				{
					// The value is less than me, so it should
					// go to my left.
					// Two sub-posibilities: 
					if (mLeft != nullptr)
					{
						//    we have a left child -- it should be
						//       told to handle the rest of insert
						return mLeft->insert_recursive(val);
					}
					else
					{
						//    we don't have a left child -- make
						//       one!
						mLeft = new Node(val);
						return 1;
					}
				}
				else if (val > mData)
				{
					if (mRight != nullptr)
					{
						return mRight->insert_recursive(val);
					}
					else 
					{
						mRight = new Node(val);
						return 1;
					}
				}

				// The value is equal to me -- duplicate!!
				// nothing to do...or is there?
				return 0;
			}

			void print_recursive(ArrayList<string>* returned_set)
			{
				// Add this value to returned set..
				returned_set->append(to_string(mData));

				// if this node has mLeft/mRight, call recursively
				if (mLeft != nullptr)
					mLeft->print_recursive(returned_set);
				if (mRight != nullptr)
					mRight->print_recursive(returned_set);
				// else, return node value
			}
		};

		Node* mRoot;
		int mSize;

	public:
		OrderedSet() : mRoot(nullptr), mSize(0) {}

		~OrderedSet()
		{
			// super-important!!
		}

		// The user is calling this method
		void insert(const T& val)
		{
			if (mRoot)
			{
				// We have elements already -- tell the root
				// to handle it!
				mSize += mRoot->insert_recursive(val);
			}
			else
			{
				mRoot = new Node(val);
				mSize = 1;
			}
		}

		ArrayList<string> print_all()
		{
			ArrayList<string> returned_set;

			if (mRoot)
				mRoot->print_recursive(&returned_set);

			return returned_set;
		}
	};
}