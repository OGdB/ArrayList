#pragma once
#include <string>
using namespace std;

namespace ssuds
{
	template <class T>
	class LinkedList
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mPrev;
			Node* mNext;

			Node(T value) : mData(value), mNext(nullptr), mPrev(nullptr)
			{
			}

			/*void clear()
			{
				mPrev* = nullptr;
				mNext* = nullptr;
			}*/
		};

		Node* mStart; // First element of LinkedList
		Node* mEnd; // Last element of LinkedList
		int mSize; // Amount of elements in LinkedList

	public:
		// CONSTRUCTORS //
		LinkedList() : mStart(nullptr), mEnd(nullptr), mSize(0)
		{

		}
		~LinkedList()
		{
			// Need to clear every node (clear function)
		}

		// OVERRIDES
		T& operator[](int index)
		{
			Node* node = get_node_at_index(index);

			return node->mData;
		}

		friend ostream& operator<<(ostream& os, const LinkedList<T>& linked_list)
		{
			os << "[";

			Node* cur_node = linked_list.mStart;

			while (cur_node != nullptr)
			{
				os << cur_node->mData;
				cur_node = cur_node->mNext;

				if (cur_node != nullptr)
				{
					os << ", ";
				}
			}

			os << "]";
			return os;
		}

		//////// TOP_LEVEL FUNCTIONS

		/// @brief Inserts a new element at the end of the array
		/// @param new_val the new value to add
		void append(const T& new_val)
		{
			Node* new_node = new Node(new_val);

			if (mSize == 0)
				mStart = mEnd = new_node;
			else
			{
				// Previous node of new_val
				new_node->mPrev = mEnd; // Next node of current end_val is the new val
				mEnd->mNext = new_node; // Previous node of new_val is current end_val
				mEnd = new_node; // new end_val = new_val
			}

			mSize += 1; // Size increased
		}

		void prepend(const T& new_val)
		{
			Node* new_node = new Node(new_val);

			if (mSize == 0)
				mStart = mEnd = new_node;
			else
			{
				new_node->mNext = mStart;
				mStart->mPrev = new_node;
				mStart = new_node;
			}

			mSize += 1; // Size increased
		}

		void insert(int spot, const T& new_val)
		{
			if (mSize == 0)
			{
				append(new_val);
				return;
			}
			else if (spot == 0)
			{
				prepend(new_val);
				return;
			}
			else if (spot == mSize - 1)
			{
				append(new_val);
				return;
			}
						
			// spot is somewhere in middle
			Node* new_node = new Node(new_val);
			Node* cur_node = get_node_at_index(spot);
			Node* prev_node = cur_node->mPrev;

			new_node->mPrev = prev_node;
			new_node->mNext = cur_node;

			prev_node->mNext = new_node;
			cur_node->mPrev = new_node;
			
			// invalid index

		}

		//void clear()
		//{
		//	Node* cur_node = mStart;

		//	while (cur_val != nullptr)
		//	{
		//		Node* next_node = cur_node.mNext;
		//		cur_node.clear();
		//		cur_node = next_node;
		//	}
		//}

		int size()
		{
			return mSize;
		}

		Node* get_node_at_index(int index)
		{
			if (index >= mSize || index < 0)
				throw out_of_range("Invalid index: " + to_string(index));

			Node* cur_node = mStart;
			int cur_index = 0;
			while (cur_node != nullptr && cur_index != index)
			{
				cur_node = cur_node->mNext;
				cur_index++;
			}

			return cur_node;
		}
	};

}