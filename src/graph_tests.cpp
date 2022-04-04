// Define a Macro. 1 == True, 0 == False
#define EXECUTE_ORDERED_SET_TESTS 1

#include <iostream>
#include <array_list.h>
#include <graph.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

// If the Macro is defined with 'True' or 'False' > '1' or '0'
#if EXECUTE_ORDERED_SET_TESTS

class GraphFixture : public ::testing::Test
{
protected:


	void SetUp() override
	{

	}
};

TEST_F(GraphFixture, BracketOperatorGetValue)
{

}

TEST_F(GraphFixture, ContainsValue)
{

}

TEST_F(GraphFixture, RemoveValue)
{

}

TEST_F(GraphFixture, PrettyIteration)
{

}
#endif