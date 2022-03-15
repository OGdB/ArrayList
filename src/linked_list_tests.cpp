#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS

class LinkedListFixture : public ::testing::Test
{
protected:
	LinkedList<int> mList;
	LinkedList<int> mList2;

	void SetUp() override
	{
		mList.append(1);
		mList.prepend(0);
		mList.append(2);
		mList.append(3);
		mList.append(4);
		mList.append(5);
		mList.append(6);
	}

	void TearDown() override
	{
	}
};

TEST_F(LinkedListFixture, InitiallyEmpty)
{
	EXPECT_EQ(mList2.size(), 0);
}

TEST_F(LinkedListFixture, AddingItems)
{
	ASSERT_EQ(mList.size(), 7);
	EXPECT_EQ(mList[0], 0);
	EXPECT_EQ(mList[1], 1);
	EXPECT_EQ(mList[2], 2);
	EXPECT_EQ(mList[3], 3);
}

TEST_F(LinkedListFixture, RemoveItem)
{
	EXPECT_EQ(mList.size(), 7);
	
	// 'Normal' Remove with spot/index:
	mList.remove(0); // Remove index 0 (mData 0)
	EXPECT_EQ(mList.size(), 6);
	EXPECT_EQ(mList[0], 1);

	// Remove with LinkedList Iterator as argument and returned:
	LinkedList<int>::LinkedListIterator it = mList.begin();
	it++;
	mList.remove(&it); // Remove second index (1)
	EXPECT_EQ(mList.size(), 5);
	EXPECT_EQ(mList[0], 1);
	EXPECT_EQ(mList[1], 3);
	EXPECT_EQ(mList[2], 4);
	EXPECT_EQ(mList[3], 5);
}

TEST_F(LinkedListFixture, ClearItems)
{
	// Clearing filled list
	EXPECT_EQ(mList.size(), 7);
	mList.clear();
	EXPECT_EQ(mList.size(), 0);

	// Trying to clear already empty list
	EXPECT_EQ(mList2.size(), 0);
	mList2.clear(); 
	EXPECT_EQ(mList2.size(), 0);
}

TEST_F(LinkedListFixture, ManualForwardIteration)
{
	LinkedList<int>::LinkedListIterator it = mList.begin();
	LinkedList<int>::LinkedListIterator it_end = mList.end();
	ASSERT_NE(it, it_end);
	int val1, val2, val3, val4, val5, val6, val7;
	val1 = *it; // 0
	EXPECT_EQ(*it, 0);
	++it;
	val2 = *it; // 1
	++it;
	val3 = *it; // 2
	++it;
	val4 = *it; // 3
	++it;
	val5 = *it; // 4
	++it;
	val6 = *it; // 5
	++it;
	val7 = *it; // 6

	// Backwards once again to 5, then to end.
	--it;
	EXPECT_EQ(*it, 5);
	it++;
	it++;

	EXPECT_EQ(val1, 0);
	EXPECT_EQ(val2, 1);
	EXPECT_EQ(val3, 2);
	EXPECT_EQ(val4, 3);
	EXPECT_EQ(val5, 4);
	EXPECT_EQ(val6, 5);
	EXPECT_EQ(val7, 6);

	EXPECT_EQ(it, it_end);
}

TEST_F(LinkedListFixture, ManualReverseIteration)
{
	LinkedList<int>::LinkedListIterator it = mList.rbegin();
	LinkedList<int>::LinkedListIterator it_end = mList.rend();
	ASSERT_NE(it, it_end);
	int val1, val2, val3, val4, val5, val6, val7;
	val1 = *it; // 6
	++it;
	val2 = *it; // 5
	++it;
	val3 = *it; // 4
	++it;
	val4 = *it; // 3
	++it;
	val5 = *it; // 2
	++it;
	val6 = *it; // 1
	++it;
	val7 = *it; // 0
	++it;

	EXPECT_EQ(val1, 6);
	EXPECT_EQ(val2, 5);
	EXPECT_EQ(val3, 4);
	EXPECT_EQ(val4, 3);
	EXPECT_EQ(val5, 2);
	EXPECT_EQ(val6, 1);
	EXPECT_EQ(val7, 0);
	EXPECT_EQ(it, it_end);
}

TEST_F(LinkedListFixture, InsertTest)
{
	// 'Normal' insert with index/spot
	mList.insert(0, 55);
	EXPECT_EQ(mList[0], 55);

	mList.insert(4, 66);
	EXPECT_EQ(mList[4], 66);

	// With LinkedListIterator spot
	LinkedList<int>::LinkedListIterator it = mList.begin(); // 55
	it++; // 0
	it++; // 1 at 'index' 2
	EXPECT_EQ(it.index(), 2);

	mList.insert(it, 77); // Insert 77 at index 2
	EXPECT_EQ(mList[2], 77);
}

TEST_F(LinkedListFixture, FindTest)
{
	LinkedList<int>::LinkedListIterator it = mList.find(3);
	EXPECT_EQ(*it, 3);
	it++;
	EXPECT_EQ(*it, 4);

	// Value not in list
	LinkedList<int>::LinkedListIterator it2 = mList.find(123);
	EXPECT_EQ(*it2, 6);

}

TEST_F(LinkedListFixture, PrettyIteration)
{
	int i = 0;
	for (int nr : mList)
	{
		if (i == 0)
			EXPECT_EQ(nr, i);
		i++;
	}
}

TEST_F(LinkedListFixture, OS_Stream)
{
	stringstream ss;
	ss << mList2;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(string());
	ss << mList;
	EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6]");
}

TEST_F(LinkedListFixture, CopyConstructor)
{
	LinkedList<int> slist_copy1 = mList;
	LinkedList<int> slist_copy2(mList);

	EXPECT_EQ(slist_copy1.size(), 7);

	EXPECT_EQ(slist_copy2[0], 0);
	EXPECT_EQ(slist_copy2[1], 1);
	EXPECT_EQ(slist_copy2[2], 2);
	EXPECT_EQ(slist_copy2[3], 3);

	slist_copy2.remove(0);
	EXPECT_EQ(slist_copy1.size(), 7);

	// Same thing, really, but just to make sure...
	ASSERT_EQ(slist_copy2.size(), 6);
	EXPECT_EQ(slist_copy2[0], 1);
	EXPECT_EQ(slist_copy2[1], 2);
	EXPECT_EQ(slist_copy2[2], 3);
	EXPECT_EQ(slist_copy2[3], 4);
}

TEST_F(LinkedListFixture, Assignment)
{
	LinkedList<int> slist3;
	slist3.append(7);
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], 7);

	slist3 = mList;
	ASSERT_EQ(slist3.size(), 7);

	EXPECT_EQ(slist3[0], 0);
	EXPECT_EQ(slist3[1], 1);
	EXPECT_EQ(slist3[2], 2);
	EXPECT_EQ(slist3[3], 3);

	mList.remove(0);
	EXPECT_EQ(slist3.size(), 7);
}

TEST_F(LinkedListFixture, InitializerListConstructor)
{
	LinkedList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}

LinkedList<float> move_func()
{
	LinkedList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}
TEST_F(LinkedListFixture, MoveConstructor)
{
	LinkedList<float> test_list = move_func();
	ASSERT_EQ(test_list.size(), 2);
	EXPECT_EQ(test_list[0], 3.1f);
	EXPECT_EQ(test_list[1], 4.2f);
	test_list.remove(0);
	EXPECT_EQ(test_list.size(), 1);
}

#endif