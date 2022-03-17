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

	void SetUp() override
	{
		mList.insert(0);
		mList.insert(1);
		mList.insert(2);
		mList.insert(3);
		mList.insert(4);
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