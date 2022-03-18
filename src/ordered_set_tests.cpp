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
	OrderedSet<int> mList;
	OrderedSet<int> mList2;
	OrderedSet<string> mList3;

	void SetUp() override
	{
		mList.insert(0);
		mList.insert(1);
		mList.insert(2);
		mList.insert(3);
		mList.insert(4);

		mList3.insert("M");
		mList3.insert("G");
		mList3.insert("S");
		mList3.insert("B");
		mList3.insert("P");
		mList3.insert("Q");
		mList3.insert("A");
		mList3.insert("D");
		mList3.insert("C");
	}
};

TEST_F(OrderedSetFixture, ClearSet)
{
	EXPECT_EQ(mList.size(), 5);
	mList.clear();
	EXPECT_EQ(mList.size(), 0);
	mList.clear(); // Attempt to clear an empty set
	EXPECT_EQ(mList.size(), 0);
}

TEST_F(OrderedSetFixture, ContainsValue)
{
	EXPECT_EQ(mList.contains(3), true);
	EXPECT_EQ(mList2.contains(6), false);
}

TEST_F(OrderedSetFixture, SetSizes)
{
	EXPECT_EQ(mList.size(), 5);
	EXPECT_EQ(mList2.size(), 0);
}

TEST_F(OrderedSetFixture, TraversalMethod)
{
	stringstream ss;
	ss << mList3;
	EXPECT_EQ(ss.str(), "[M, G, B, A, D, C, S, P, Q]");
	ss.str(string());

	ArrayList<string> pre_order_list = mList3.traversal(pre_order);
	ss << pre_order_list;
	EXPECT_EQ(ss.str(), "[M, G, B, A, D, C, S, P, Q]");
	ss.str(string());

	ArrayList<string> post_order_list = mList3.traversal(post_order);
	ss << post_order_list;
	EXPECT_EQ(ss.str(), "[A, C, D, B, G, Q, P, S, M]");
	ss.str(string());

	ArrayList<string> in_order_list = mList3.traversal(in_order);
	ss << in_order_list;
	EXPECT_EQ(ss.str(), "[A, B, C, D, G, M, P, Q, S]");
	ss.str(string());

}

TEST_F(OrderedSetFixture, OS_Stream)
{
	stringstream ss;
	ss << mList2;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(string());
	ss << mList;
	EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4]");
	ss.str(string());
	mList.clear();
	ss << mList;
	EXPECT_EQ(ss.str(), "[]");
}

#endif