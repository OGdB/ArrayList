#pragma once
#include <string>
#include <array_list.h>
#include <array_list_utility.h>
#include <ssuds.h>

using namespace std;

namespace ssuds
{
	enum order {
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

			/// @brief 
			/// @param order 
			/// @param list 
			/// @return 
			void return_in_order(order order, ArrayList<T>& list)
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
					// If there is only an mLeft, first recursive, then append
					if (mLeft != nullptr && mRight == nullptr)
					{
						mLeft->return_in_order(order, list);
						list.append(mData);
						return;
					}
					else if (mLeft == nullptr && mRight != nullptr)
					{
						list.append(mData);
						mRight->return_in_order(order, list);
						return;
					}
					else if (mLeft != nullptr && mRight != nullptr)
					{
						mLeft->return_in_order(order, list);
						list.append(mData);
						mRight->return_in_order(order, list);
						return;
					}

					list.append(mData);
				}
			}
		};

		// SET ATTRIBUTES
		Node* mRoot;
		int mSize;

	public:
		OrderedSet() : mRoot(nullptr), mSize(0) {}

		~OrderedSet()
		{
			clear();
			// super-important!!
		}

#pragma region OPERATOR_OVERRIDES
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

		/// @brief Calculate the height in amount of nodes.
		/// @return The amount of nodes if counted from mRoot to the lowest node vertically.
		int get_height()
		{
			if (mRoot == nullptr)
				return 1;

			return return_height_recursive(mRoot);
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
		ArrayList<T> traversal(order order) 
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

			/// @brief Keep calling the method until there are either no more mLeft or mRight nodes. Return the heighest of the 2 values. Ultimately returns the heighest value (lowest node).
			/// @param node The node to check for an mLeft/mRight.
			/// @return The amount of vertical iterations.
			int return_height_recursive(Node* node)
			{
				int left_branch_height = 0;
				int right_branch_height = 0;

				if (node->mLeft != nullptr)
					left_branch_height = return_height_recursive(node->mLeft);
				if (node->mRight != nullptr)
					right_branch_height = return_height_recursive(node->mRight);

				return max(left_branch_height, right_branch_height) + 1;  // Return the heighest value (mLeft/mRight's branch).
			}
#pragma endregion
	};
}