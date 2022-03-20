// Define a Macro. 1 == True, 0 == False
#define EXECUTE_ORDERED_SET_TESTS 1

#include <iostream>
#include <array_list.h>
#include <ordered_set.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

// If the Macro is defined with 'True' or 'False' > '1' or '0'
#if EXECUTE_ORDERED_SET_TESTS

class OrderedSetFixture : public ::testing::Test
{
protected:
	OrderedSet<string> mList;
	OrderedSet<int> mList2;
	OrderedSet<int> mList3;

	void SetUp() override
	{
		mList.insert("M");
		mList.insert("G");
		mList.insert("S");
		mList.insert("B");
		mList.insert("P");
		mList.insert("Q");
		mList.insert("A");
		mList.insert("D");
		mList.insert("C");
		/*
				M 
			  /   \
			 G	   S
			/	  /
		   B	 P
		  / \     \
		 A   D	   Q
			/
		   C
		*/

		mList2.insert(0);
		mList2.insert(1);
		mList2.insert(2);
		mList2.insert(3);
		mList2.insert(4);
	}
};

TEST_F(OrderedSetFixture, ClearSet)
{
	EXPECT_EQ(mList2.size(), 5);
	mList2.clear();
	EXPECT_EQ(mList2.size(), 0);
	mList2.clear(); // Attempt to clear an empty set
	EXPECT_EQ(mList2.size(), 0);
}

TEST_F(OrderedSetFixture, ContainsValue)
{
	EXPECT_EQ(mList2.contains(3), true);
	EXPECT_EQ(mList.contains("Z"), false);
	EXPECT_EQ(mList3.contains(6), false);
}

TEST_F(OrderedSetFixture, BinaryTreeHeight)
{
	EXPECT_EQ(mList.get_height(), 5);
	EXPECT_EQ(mList2.get_height(), 5);
}

TEST_F(OrderedSetFixture, EraseValue)
{
	// Leaf without children.
	mList.erase("A");
	EXPECT_EQ(mList.contains("A"), false);

	// Node with 1 child.
	mList.erase("B");
	EXPECT_EQ(mList.contains("B"), false);

	// Node with 2 children.
	mList.erase("M");
	EXPECT_EQ(mList.contains("M"), false);

	EXPECT_EQ(mList.erase("O"), false);
}

TEST_F(OrderedSetFixture, OS_Stream)
{
	stringstream ss;
	ss << mList3;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(string());
	ss << mList2;
	EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4]");
	ss.str(string());
	mList2.clear();
	ss << mList2;
	EXPECT_EQ(ss.str(), "[]");
}

TEST_F(OrderedSetFixture, SetSizes)
{
	EXPECT_EQ(mList2.size(), 5);
	EXPECT_EQ(mList3.size(), 0);
}

TEST_F(OrderedSetFixture, TraversalMethod)
{
	stringstream ss;
	ss << mList;
	EXPECT_EQ(ss.str(), "[M, G, B, A, D, C, S, P, Q]");
	ss.str(string());

	ArrayList<string> pre_order_list = mList.traversal(pre_order);
	ss << pre_order_list;
	EXPECT_EQ(ss.str(), "[M, G, B, A, D, C, S, P, Q]");
	ss.str(string());

	ArrayList<string> post_order_list = mList.traversal(post_order);
	ss << post_order_list;
	EXPECT_EQ(ss.str(), "[A, C, D, B, G, Q, P, S, M]");
	ss.str(string());

	ArrayList<string> in_order_list = mList.traversal(in_order);
	ss << in_order_list;
	EXPECT_EQ(ss.str(), "[A, B, C, D, G, M, P, Q, S]");
	ss.str(string());

}

#endif