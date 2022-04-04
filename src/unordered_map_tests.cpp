// Define a Macro. 1 == True, 0 == False
#define EXECUTE_ORDERED_SET_TESTS 1

#include <iostream>
#include <array_list.h>
#include <unordered_map.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

// If the Macro is defined with 'True' or 'False' > '1' or '0'
#if EXECUTE_ORDERED_SET_TESTS

class UnorderedMapFixture : public ::testing::Test
{
protected:
	UnorderedMap<string, int> mList;
	UnorderedMap<int, int> mList2;

	void SetUp() override
	{
		mList["Oeds"] = 1998;
		mList["Weed"] = 420;
		mList["Nice"] = 69;

		mList2[0] = 0;
		mList2[1] = 1;
		mList2[2] = 2;
	}
};

TEST_F(UnorderedMapFixture, BracketOperatorGetValue)
{
	EXPECT_EQ(mList["Oeds"], 1998);
	EXPECT_EQ(mList["Weed"], 420);
	EXPECT_EQ(mList["Nice"], 69);
}

TEST_F(UnorderedMapFixture, ContainsValue)
{
	string searchVal = "Oeds";
	EXPECT_EQ(mList.contains(searchVal), true);

	searchVal = "Weed";
	EXPECT_EQ(mList.contains(searchVal), true);

	searchVal = "Jason";
	EXPECT_EQ(mList.contains(searchVal), false);
}

TEST_F(UnorderedMapFixture, RemoveValue)
{
	mList.remove("Oeds");
	string searchVal = "Oeds";
	EXPECT_EQ(mList.contains(searchVal), false);
}

TEST_F(UnorderedMapFixture, PrettyIteration)
{
	int testint = 0;

	for (pair<int, int>* pair : mList2)
	{
		EXPECT_EQ(mList2[testint], testint);
		cout << mList2[testint] << endl;
		testint++;
	}
}
#endif