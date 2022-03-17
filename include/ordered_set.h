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

			Node(const T& val) : mData(val), mLeft(nullptr), mRight(nullptr) {}

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

			bool contains_recursive(const T& val)
			{
				if (mData == val)
					return true;
				else
				{
					if (mLeft != nullptr && mData > val) // if this node's value is bigger than the node we look for, go left (to smaller value)
						return mLeft->contains_recursive(val);
					else if (mRight != nullptr && mData < val) // if bigger, go right.
						return mRight->contains_recursive(val);
				}

				return false; // Else the value is not there.
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

#pragma region OPERATOR_OVERRIDES
		friend ostream& operator<<(ostream& os, const OrderedSet<T>& set)
		{
			ArrayList<string> returned_set;

			if (set.mRoot)
				set.mRoot->print_recursive(&returned_set);

			os << returned_set;
			return os;
		}
#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONALITIES
		void clear()
		{

		}

		/// @brief Look in the set for a value
		/// @param val The value to look for
		/// @return Whether the value is found in the set
		bool contains(const T& val)
		{
			if (mRoot == nullptr)
			{
				return false;
			}
			else
			{
				mRoot->contains_recursive(val);
			}
		}

		/// @brief Add value to the set.
		/// @param val The value to add
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

		/// @brief Get the amount of elements in the set
		/// @return The amount of elements in the set
		int size() const
		{
			return mSize;
		}
#pragma endregion
	};
}