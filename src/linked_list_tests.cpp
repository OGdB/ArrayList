#include <gtest/gtest.h>

#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS

class LinkedListFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST(LinkedListTests, Test_TEST)
{
	int x = 47;
	int y = 47;
	EXPECT_EQ(x, y) << "Not equal!";
}

#endif