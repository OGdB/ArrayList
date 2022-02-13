// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
using namespace std;
using namespace ssuds;

ArrayList<float> moveFunction()
{
    ArrayList<float> this_list;
    this_list.append(34.0f);
    return this_list;
}

#pragma region TESTS
/// @brief Test overload of [] after ArrayList var. e.g: test_list[0] accessing test_list.mData[0]
TEST(ArrayTests, AppendAndBracketsOverloadTest)
{
    ArrayList<int> test_list_int;
    test_list_int.append(-10);
    test_list_int.append(5);
    test_list_int.append(9);

    int first_int = test_list_int[0];
    int second_int = test_list_int[1];
    int third_int = test_list_int[2];

    EXPECT_EQ(first_int, -10) << "Wrong value at index!";
    EXPECT_EQ(second_int, 5) << "Wrong value at index!";
    EXPECT_EQ(third_int, 9) << "Wrong value at index!";

    ArrayList<string> test_list_string;
    test_list_string.append("Hello");
    test_list_string.append("There!");
    test_list_string.append("General");
    test_list_string.append("Kenobi!");

    string first_string = test_list_string[0];
    string second_string = test_list_string[1];
    string third_string = test_list_string[2];
    string fourth_string = test_list_string[3];

    EXPECT_EQ(first_string, "Hello") << "Wrong value at index!";
    EXPECT_EQ(second_string, "There!") << "Wrong value at index!";
    EXPECT_EQ(third_string, "General") << "Wrong value at index!";
    EXPECT_EQ(fourth_string, "Kenobi!") << "Wrong value at index!";
}

/// @brief Test if the size and capacity increase and decrease appropiately.
TEST(ArrayTests, SizeAndCapacityTest)
{
    ArrayList<float> test_list;
    test_list.append(1.6f);
    EXPECT_EQ(test_list.size(), 1) << "Wrong size";
    test_list.append(1.9f);
    EXPECT_EQ(test_list.size(), 2) << "Wrong size";
}


TEST(ArrayTests, EqualityOperatorOverload)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> second_list;
    second_list.append(1);
    second_list.append(2);
    second_list.append(3);
}
TEST(ArrayTests, AssignOperatorOverload)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> second_list = first_list;
    EXPECT_EQ(first_list, second_list);
}
TEST(ArrayTests, UnequalOperatorOverloadTest)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> second_list;
    second_list.append(55);
    second_list.append(5234);
    second_list.append(555);

    ASSERT_NE(first_list, second_list);
}

TEST(ArrayTests, InitializerTest)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);
    ArrayList<int> test_list_with_initializer(first_list);

}

/// @brief Test the Insertion overload (<<)
TEST(ArrayTests, InsertionOverload)
{
    ArrayList<float> test_list;
    test_list.append(1);
    test_list.append(2);
    test_list.append(3);

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    cout << test_list;

    cout.rdbuf(p_cout_streambuf);

    EXPECT_EQ("[1, 2, 3]", oss.str()) << "Cout did not print intended output";
}
#pragma endregion

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();


    //// The basic test program (for floats)
    //ArrayList<float> my_list;
    //my_list.append(1.1f);
    //my_list.append(1.2f);
    //my_list.append(1.3f);

    //ArrayList<float> my_list2;
    //my_list2.append(1.1f);
    //my_list2.append(1.2f);
    //my_list2.append(1.3f);

    //ArrayList<float> my_list3(my_list2);  // Copy Constructor
    //ArrayList<float> my_list4 = moveFunction();  // Move Constructor gets called
    //cout << my_list4[0] << endl;

    //ArrayList<float>::ArrayListIterator it(&my_list, 0);
    //it++;
    //float test_val = *it;
    //cout << test_val << endl;
    //test_val = *my_list.begin();
    //cout << test_val << endl;
}
