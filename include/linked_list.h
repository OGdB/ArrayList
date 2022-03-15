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
		};

#pragma region Iterator
	public:
		class LinkedListIterator
		{
		protected:
			LinkedList& lili;
			Node* current;
			bool reverse;

		public:
			LinkedListIterator(LinkedList& lili) : lili(lili), current(lili.mStart), reverse(false)
			{
			}
			LinkedListIterator(LinkedList& lili, bool at_end) : lili(lili), current(at_end ? lili.mEnd->mNext : lili.mStart), reverse(false)
			{
			}
			LinkedListIterator(LinkedList& lili, bool at_end, bool reversed) : lili(lili), current(at_end ? lili.mEnd : lili.mStart->mPrev), reverse(reversed)
			{
			}
			LinkedListIterator(LinkedList& lili, Node* start_node) : lili(lili), current(start_node), reverse(false)
			{
			}

			bool operator!=(const LinkedListIterator& other) const
			{
				return current != other.current;
			}
			bool operator==(const LinkedListIterator& other) const
			{
				return current == other.current;
			}

			T& operator*()
			{
				if (current == nullptr)
				{
					throw runtime_error("Current is a nullpointer");
				}

				return current->mData;
			}
			
			void operator++()
			{
				if (!reverse)
					current = current->mNext;
				else
					current = current->mPrev;
			}
			void operator++(int dummy)
			{
				if (!reverse)
					current = current->mNext;
				else
					current = current->mPrev;
			}
			void operator--()
			{
				if (!reverse)
					current = current->mPrev;
				else
					current = current->mNext;
			}
			void operator--(int dummy)
			{
				if (!reverse)
					current = current->mPrev;
				else
					current = current->mNext;
			}

			/// @brief Get the spot at which the current node is in the linked list.
			/// @return The index at which the current node is in the linked list.
			int index()
			{
				Node* cur_node = lili.mStart;
				int cur_index = 0;

				// Loop through the entire linked list until the current node is found.
				while (cur_node != nullptr && current != cur_node)
				{
					cur_node = cur_node->mNext;
					cur_index++;
				}

				return cur_index;
			}
		};

		LinkedListIterator begin()
		{
			return LinkedListIterator(*this);
		}
		LinkedListIterator end()
		{
			return LinkedListIterator(*this, true);
		}
		LinkedListIterator rbegin()
		{
			return LinkedListIterator(*this, true, true);
		}
		LinkedListIterator rend()
		{
			return LinkedListIterator(*this, false, true);
		}

		/// @brief Find the first instance of a value in the Linked List.
		/// @param value The value to find in the Linked List.
		/// @return LinkedListIterator spot at which value is found. End of Iterator if value is not found.
		LinkedListIterator find(T value)
		{
			Node* cur_node = mStart;

			// Loop through the entire linked list until element is found.
			while (cur_node != nullptr && cur_node->mData != value)
			{
				cur_node = cur_node->mNext;
			}

			if (cur_node == nullptr || cur_node->mData != value)
				return LinkedListIterator(*this, mEnd);

			return LinkedListIterator(*this, cur_node);
		}
#pragma endregion

		Node* mStart; // First element of LinkedList
		Node* mEnd; // Last element of LinkedList
		int mSize; // Amount of elements in LinkedList

#pragma region Constructors
		LinkedList() : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
		}
		// Copy-Constructor
		LinkedList(const LinkedList& other) : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			Node* cur_node = other.mStart; // Loop though the other array

			while (cur_node != nullptr)
			{
				append(cur_node->mData);
				cur_node = cur_node->mNext;
			}
		}
		// Move-Constructor
		LinkedList(LinkedList&& other) : mStart(other.mStart), mEnd(other.mEnd), mSize(other.mSize)
		{
			//cout << "Move constructor called!" << endl;
			other.mStart = nullptr;
			other.mEnd = nullptr;
		};
		// Initializer-List-Constructor
		LinkedList(const initializer_list<T>& ilist) : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			for (T val : ilist)
			{
				append(val);
			}
		}

		~LinkedList()
		{
			clear();
		}
#pragma endregion

#pragma region Overrides
		T& operator[](int index)
		{
			Node* node = get_node_at_index(index);

			return node->mData;
		}

		LinkedList<T>& operator= (const LinkedList<T>& other)
		{
			clear();

			Node* cur_node = other.mStart;

			while (cur_node != nullptr)
			{
				append(cur_node->mData);
				cur_node = cur_node->mNext;
			}

			return *this;
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
#pragma endregion

#pragma region Top-Level-Functionality
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

			mSize++; // Size increased
		}

		/// @brief Empty the entire Linked List
		void clear()
  		{
			Node* cur_node = mStart;

			while (cur_node != nullptr)
			{
				Node* next = cur_node->mNext;
				delete cur_node;
				cur_node = next;
			}

			mStart = nullptr;
			mEnd = nullptr;
			mSize = 0;
		}

		/// @brief Remove an element from the Linked List
		/// @param index The index of the value to remove
		void remove(int index)
		{
			Node* node_to_remove = get_node_at_index(index);
			Node* prev_node = node_to_remove->mPrev;
			Node* next_node = node_to_remove->mNext;

			if (node_to_remove == mStart)
				mStart = next_node;
			if (node_to_remove == mEnd)
				mEnd = prev_node;

			mSize--;

			delete node_to_remove;
		}

		/// @brief Remove the value at which the iterator finds itself
		/// @param The iterator
		/// @return The value right of the iterator
		LinkedListIterator remove(LinkedListIterator& it)
		{
			int index = it.index();
			it++;

			remove(index);

			return it;
		}

		/// @brief Add a value at the beginning of the Linked List
		/// @param new_val The value to add
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

			mSize++; // Size increased
		}

		/// @brief Insert a value at a specified spot in the Linked List
		/// @param spot The index to insert the value at
		/// @param new_val The value to insert
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

			if (spot > mSize || spot < 0)
			{
				throw out_of_range("Invalid index: " + to_string(spot));
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

			mSize++;
		}
		/// @brief Insert a value at a specified spot in the Linked List
		/// @param it The iteration value to insert the value at
		/// @param new_val The value to insert
		void insert(LinkedListIterator& it, const T& new_val)
		{
			int spot = it.index();
			insert(spot, new_val);
		}

		/// @brief Get the amount of elements in the Linked List
		/// @return The amount of elements in the Linked List
		int size()
		{
			return mSize;
		}
#pragma endregion

		protected:
		/// @brief Return the Node at the specified index
		/// @param index the index to retrieve the node of
		/// @return The node at the specified index
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