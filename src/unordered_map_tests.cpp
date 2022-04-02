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
	UnorderedMap<string, int> mList2;

	void SetUp() override
	{
		mList["Oeds"] = 1998;
		mList["Weed"] = 420;
		mList["Nice"] = 69;
	}
};

TEST_F(UnorderedMapFixture, ClearSet)
{

}

TEST_F(UnorderedMapFixture, ContainsValue)
{

}

TEST_F(UnorderedMapFixture, CopyConstructor)
{

}

TEST_F(UnorderedMapFixture, EqualOperator)
{

}

TEST_F(UnorderedMapFixture, EraseValue)
{

}

TEST_F(UnorderedMapFixture, InitializerList)
{

}

TEST_F(UnorderedMapFixture, ManualIteration)
{

}

TEST_F(UnorderedMapFixture, PrettyIteration)
{

}

TEST_F(UnorderedMapFixture, MoveConstructor)
{

}

TEST_F(UnorderedMapFixture, Rebalance)
{

}

TEST_F(UnorderedMapFixture, OS_Stream)
{
	
}

TEST_F(UnorderedMapFixture, SetSizes)
{

}

TEST_F(UnorderedMapFixture, TraversalMethod)
{
	
}

#endif