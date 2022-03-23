#pragma once
#include <string>
#include <array_list.h>
#include <array_list_utility.h>
#include <ssuds.h>
#include <stack>

using namespace std;

namespace ssuds
{
	enum order 
	{
		pre_order, // from all lefts to rights
		post_order, // 'left to right'
		in_order // a-b-c order
	};

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

			void clear_recursive()
			{
				// if there is an mLeft, check recursively if those have children (and delete those). Then delete mLeft.
				if (mLeft != nullptr)
				{
					mLeft->clear_recursive(); // Clear all children of mLeft if any
					delete mLeft;
				}
				// if there is an mRight, check recursively if those have children (and delete those). Then delete mRight.
				if (mRight != nullptr)
				{
					mRight->clear_recursive(); // Clear all children of mRight if any
					delete mRight;
				}
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

			/// @brief Looks at its children if any to see if their value matches the searched. Appropiately handles erasion if node with value has children.
			/// @param val The value to look for in the set.
			/// @return Whether the value was succesfully erased.
			bool erase_recursive(const T& val)
			{
				if (mLeft == nullptr && mRight == nullptr)
					return false;

				if (mLeft != nullptr)
				{
					if (mLeft->mData == val) // mLeft is the data we want to erase.
					{
						// Case 1 - leaf node: node has no children.
						if (mLeft->mLeft == nullptr && mLeft->mRight == nullptr)
						{
							delete mLeft;
							mLeft = nullptr;
							return true;
						}

						// Case 2 - node with 1 child: move child node up to take node's place.
						if ((mLeft->mLeft != nullptr && mLeft->mRight == nullptr) || (mLeft->mLeft == nullptr && mLeft->mRight != nullptr)) // mLeft has 1 child
						{
							if (mLeft->mLeft != nullptr) // if mLeft has a left child
							{
								Node* grand_child = mLeft->mLeft;
								delete mLeft;
								mLeft = grand_child;
								return true;
							}
							else // if mLeft has a right child
							{
								Node* grand_child = mLeft->mRight;
								delete mLeft;
								mLeft = grand_child;
								return true;
							}
						}

						// Case 3 - node with 2 children: pick successor to replace node (left-most descendent of right child)
						if (mLeft->mLeft != nullptr && mLeft->mRight != nullptr)
						{
							// copy the value of the successor to this node.
							T& successor_val = mLeft->mRight->mLeft->mData; 
							mLeft->mData = successor_val;

							// delete duplicate value recursively (but not the node we just copied to).
							return mLeft->mRight->erase_recursive(successor_val);
						}
					}

					return mLeft->erase_recursive(val);
				}

				if (mRight != nullptr)
				{
					if (mRight->mData == val) // mRight is the data we want to erase.
					{
						// Case 1 - leaf node: node has no children.
						if (mRight->mLeft == nullptr && mRight->mRight == nullptr)
						{
							delete mRight;
							mRight = nullptr;
							return true;
						}

						// Case 2 - node with 1 child: move child node up to take node's place.
						if ((mRight->mLeft != nullptr && mRight->mRight == nullptr) || (mRight->mLeft == nullptr && mRight->mRight != nullptr)) // mRight has 1 child
						{
							if (mRight->mLeft != nullptr) // if mLeft has a left child
							{
								Node* grand_child = mRight->mLeft;
								delete mRight;
								mRight = grand_child;
								return true;
							}
							else // if mLeft has a right child
							{
								Node* grand_child = mRight->mRight;
								delete mRight;
								mRight = grand_child;
								return true;
							}
						}
						// Case 3 - node with 2 children: 
						if (mRight->mLeft != nullptr && mRight->mRight != nullptr)
						{
							// copy the value of the successor to this node.
							T& successor_val = mRight->mRight->mLeft->mData;
							mRight->mData = successor_val;

							// delete duplicate value recursively (but not the node we just copied to).
							return mRight->mRight->erase_recursive(successor_val);
						}
					}

					return mRight->erase_recursive(val);
				}
			}

			/// @brief Recursively looks for the right spot in the set to insert the value.
			/// @param val The value to insert.
			/// @return 
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

			void print_recursive(ArrayList<T>* returned_set)
			{
				// Add this value to returned set..
				returned_set->append(mData);

				// if this node has mLeft/mRight, call recursively
				if (mLeft != nullptr)
					mLeft->print_recursive(returned_set);
				if (mRight != nullptr)
					mRight->print_recursive(returned_set);
				// else, return node value
			}

			/// @brief Keep calling the method until there are either no more mLeft or mRight nodes. Return the heighest of the 2 values. Ultimately returns the heighest value (lowest node).
			/// @param node The node to check for an mLeft/mRight.
			/// @return The amount of vertical iterations.
			int return_height_recursive()
			{
				int left_branch_height = 0;
				int right_branch_height = 0;

				if (mLeft != nullptr)
					left_branch_height = mLeft->return_height_recursive();
				if (mRight != nullptr)
					right_branch_height = mRight->return_height_recursive();

				return max(left_branch_height, right_branch_height) + 1;  // Return the heighest value (mLeft/mRight's branch).
			}

			/// @brief 
			/// @param order 
			/// @param list 
			/// @return 
			void return_in_order(const order order, ArrayList<T>& list)
			{
				// append values to the arraylist according to the provided order
				if (order == pre_order)
				{
					list.append(mData); // Add myself

					if (mLeft != nullptr)
						mLeft->return_in_order(order, list); // After (first) adding the most mLeft
					if (mRight != nullptr)
						mRight->return_in_order(order, list); // AND thereafter the mRight,
				}
				else if (order == post_order)
				{
					if (mLeft != nullptr)
						mLeft->return_in_order(order, list); // After (first) adding the most mLeft
					if (mRight != nullptr)
						mRight->return_in_order(order, list); // AND thereafter the mRight,

					list.append(mData); // Add myself
				}
				else if (order == in_order)
				{
					// Loop through mLeft and append values before appending this value (if there is one).
					if (mLeft != nullptr)
						mLeft->return_in_order(order, list);

					list.append(mData);

					// Append mRight's value after.
					if (mRight != nullptr)
						mRight->return_in_order(order, list);
				}
			}
		};

		// SET'S ATTRIBUTES
		Node* mRoot;
		int mSize;

	public:
		/// Default-constructor
		OrderedSet() : mRoot(nullptr), mSize(0) {}

		/// Copy-constructor
		OrderedSet(const OrderedSet<T>& other)
		{
			//cout << "Constructor called\n";
			ArrayList<T> other_order = other.traversal(pre_order);
			
			for (T val : other_order)
				insert(val);
		}

		/// Move-constructor: "steals" the data (shallow copy) from a soon-to-be-destroyed other ArrayList
		OrderedSet(const OrderedSet&& other)
		{
			cout << "I LIKE TO MOVE IT- MOVE IT!\n\n";

			ArrayList<T> other_order = other.traversal(pre_order);

			for (T val : other_order)
				insert(val);
		}

		/// Initializer-list constructor
		OrderedSet(initializer_list<T> ilist) : mSize(ilist.size())
		{
			for (T val : ilist)
				insert(val);
		}

		// Destructor
		~OrderedSet()
		{
			clear();
		}
		

#pragma region OPERATOR_OVERRIDES
		bool operator==(const OrderedSet& other) const
		{
			// If the mRoot->mData and all mLefts->mData and mRights->mData of this ordered set are the same as other's.
			if (mSize != other.mSize || mRoot->mData != other.mRoot->mData) // If sets are different sizes or different mRoots, definitely different.
				return false;
			else // Else, compare each value in both sets
			{
				ArrayList<T> this_set = traversal(order::post_order);
				ArrayList<T> other_set = other.traversal(order::post_order);

				if (this_set == other_set)
					return true;
				else
					return false;
			}
		}
		bool operator!=(const OrderedSet& other) const
		{
			// If the mRoot->mData and all mLefts->mData and mRights->mData of this ordered set are the same as other's.
			if (mSize != other.mSize || mRoot->mData != other.mRoot->mData) // If sets are different sizes or different mRoots, definitely different.
				return true;
			else // Else, compare each value in both sets
			{
				ArrayList<T> this_set = traversal(order::post_order);
				ArrayList<T> other_set = other.traversal(order::post_order);

				if (this_set == other_set)
					return false;
				else
					return true;
			}
		}

		friend ostream& operator<<(ostream& os, const OrderedSet<T>& set)
		{
			ArrayList<T> returned_set;

			if (set.mRoot != nullptr)
				set.mRoot->print_recursive(&returned_set);

			os << returned_set;
			return os;
		}
#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONALITIES
		/// @brief Clear the entire set.
		void clear()
		{
			if (mRoot != nullptr)
			{
				mRoot->clear_recursive();
				delete mRoot;
				mRoot = nullptr;
				mSize = 0;
			}
		}

		/// @brief Look in the set for a value.
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
				return mRoot->contains_recursive(val);
			}
		}

		/// @brief Remove a value from set.
		/// @param val The value to remove.
		/// @return true if it was removed, false if it wasn't there.
		bool erase(const T& val)
		{
			if (mRoot == nullptr)
				return false;

			if (mRoot->mData == val) // if the mRoot is the deleted value.
			{
				T& successor_val = mRoot->mRight->mLeft->mData;
				mRoot->mData = successor_val;

				// delete duplicate value recursively (but not the node we just copied to).
				return mRoot->mRight->erase_recursive(successor_val);
			}

			return mRoot->erase_recursive(val);
		}

		/// @brief Calculate the height in amount of nodes.
		/// @return The amount of nodes if counted from mRoot to the lowest node vertically.
		int get_height()
		{
			if (mRoot == nullptr)
				return 1;

			return mRoot->return_height_recursive();
		}

		/// @brief Add value to the set.
		/// @param val The value to add
		void insert(const T& val)
		{
			if (mRoot != nullptr)
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

		/// @brief Balances the ordered set to the lowest possible height
		void rebalance()
		{
			ArrayList<T> sortedArray = traversal(order::in_order);
			clear();

			int start = 0;
			int end = sortedArray.size() - 1;

			rebalance_recursive(sortedArray, start, end);
		}

		/// @brief Get the amount of elements in the set
		/// @return The amount of elements in the set
		int size() const
		{
			return mSize;
		}

		/// @brief Return the set in a specified order.
		/// @return the order
		ArrayList<T> traversal(order order) const
		{
			ArrayList<T> list;

			if (mRoot != nullptr)
				mRoot->return_in_order(order, list);

			return list;
		}

		protected:
			void rebalance_recursive(ArrayList<T>& sortedArray, int start, int end)
			{
				if (start > end)  // return if the array is not big enough
					return;

				int middle = (start + end) / 2;  // get middle integer

				T& middleNode = sortedArray[middle];

				insert(middleNode);

				rebalance_recursive(sortedArray, start, middle - 1);
				rebalance_recursive(sortedArray, middle + 1, end);
			}
#pragma endregion

			public:
				class OrderedSetIterator
				{
				protected:
					Node* mCurrent;
					stack<Node*> nodeStack;

				public:
					// Should start at the far left mCurrent
					OrderedSetIterator(Node* mRoot) : mCurrent(mRoot) 
					{
						// Loop through the array
						while (mCurrent->mLeft != nullptr)
						{
							nodeStack.push(mCurrent); // Save previous node

							mCurrent = mCurrent->mLeft;
						}
					}
					// Should return the end
					OrderedSetIterator(Node* mRoot, bool atEnd) : mCurrent(mRoot)
					{
						// Loop through the array
						if (atEnd) 
						{
							while (mCurrent->mRight != nullptr)
							{
								mCurrent = mCurrent->mRight;
							}
						}
						else
						{
							while (mCurrent->mLeft != nullptr)
							{
								nodeStack.push(mCurrent); // Save previous node

								mCurrent = mCurrent->mLeft;
							}
						}
					}

					void operator++()
					{
						// If there is an mRight go to that value, else go to the previous in the stack.
						// Does not need to check for mLeft because it should be coming from mLeft. Should check for any mLeft of mRight if there is one.
						if (mCurrent->mRight != nullptr)
						{
							mCurrent = mCurrent->mRight;
							while (mCurrent->mLeft != nullptr) // if mRight has mLeft (smaller values) Iterate through mLefts until mCurrent is again the left-est value.
							{
								nodeStack.push(mCurrent); // Save previous node

								mCurrent = mCurrent->mLeft;
							}
						}
						else if (nodeStack.size() > 0)
						{
							mCurrent = nodeStack.top(); // Go to the previous value.
							nodeStack.pop();
						}
					}
					void operator++(int dummy)
					{
						// If there is an mRight go to that value, else go to the previous in the stack.
						// Does not need to check for mLeft because it should be coming from mLeft. Should check for any mLeft of mRight if there is one.
						if (mCurrent->mRight != nullptr)
						{
							mCurrent = mCurrent->mRight;
							while (mCurrent->mLeft != nullptr) // if mRight has mLeft (smaller values) Iterate through mLefts until mCurrent is again the left-est value.
							{
								nodeStack.push(mCurrent); // Save previous node

								mCurrent = mCurrent->mLeft;
							}
						}
						else if (nodeStack.size() > 0)
						{
							mCurrent = nodeStack.top(); // Go to the previous value.
							nodeStack.pop();
						}
					}

					T& operator*()
					{
						return mCurrent->mData;
					}

					bool operator==(const OrderedSet& other) const
					{
						return this == other;
					}

					bool operator!=(const OrderedSet& other) const
					{
						return !(this == other);
					}
				};

				OrderedSetIterator begin()
				{
					return OrderedSetIterator(mRoot);
				}
				OrderedSetIterator end()
				{
					return OrderedSetIterator(mRoot, true);
				}
	};
}