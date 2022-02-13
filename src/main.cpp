// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
using namespace std;
using namespace ssuds;

#pragma region GOOGLE TESTS
TEST(ArrayTests, AppendAndBracketsOverload)
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
TEST(ArrayTests, SizeAndCapacity)
{
    ArrayList<float> test_list;
    test_list.append(2.0f);
    EXPECT_EQ(test_list.size(), 1) << "Wrong size";
    test_list.append(2.0f);
    EXPECT_EQ(test_list.size(), 2) << "Wrong size";
    test_list.append(1.0f);
    test_list.append(1.0f);
    test_list.append(1.0f);
    test_list.append(1.0f);

    EXPECT_EQ(test_list.capacity(), 10) << "Wrong capacity. Should have increased double";

    test_list.remove_all(2.0f);
    EXPECT_EQ(test_list.capacity(), 5) << "Wrong capacity. Should have gone back to minCapacity";
}
TEST(ArrayTests, RemoveFunction)
{
    ArrayList<int> test_list;
    test_list.append(1);
    test_list.append(2);
    test_list.append(3);
    EXPECT_EQ(test_list.size(), 3) << "Wrong size";
    test_list.remove(0);
    EXPECT_EQ(test_list.size(), 2) << "Wrong size";

    EXPECT_EQ(test_list[0], 2) << "Wrong value at index";
    EXPECT_EQ(test_list[1], 3) << "Wrong value at index";

    test_list.remove(1);
    EXPECT_EQ(test_list.size(), 1) << "Wrong size";
    EXPECT_EQ(test_list[0], 2) << "Wrong value at index";

    EXPECT_THROW(test_list.remove(2), out_of_range) << "Should throw out-of-range error";
}
TEST(ArrayTests, RemoveAllFunction)
{
    ArrayList<int> test_list;
    test_list.append(1);
    test_list.append(2);
    test_list.append(2);
    test_list.append(2);
    test_list.append(3);

    int instances_removed = test_list.remove_all(2);

    EXPECT_EQ(instances_removed, 3) << "Wrong size";
    EXPECT_EQ(test_list.size(), 2) << "Wrong size";
    EXPECT_EQ(test_list[0], 1) << "wr value at index";
    EXPECT_EQ(test_list[1], 3) << "Wrong value at index";
}
TEST(ArrayTests, ClearFunction)
{
    ArrayList<string> test_list_string;
    test_list_string.append("Old McDonald");
    test_list_string.append("Had a farm.");
    test_list_string.append("Ee-aa-ee-aa-oo");
    test_list_string.clear();
    EXPECT_EQ(test_list_string.size(), 0) << "Wrong size";
}
TEST(ArrayTests, InsertInArray)
{
    ArrayList<float> test_list;
    test_list.append(1.1f);
    test_list.append(2.2f);
    test_list.append(3.3f);
    test_list.append(4.4f);
    test_list.append(5.5f);

    test_list.insert(420.0f, 1);
    test_list.insert(69.0f, 4);

    EXPECT_EQ(test_list[0], 1.1f) << "Wrong value at index!";
    EXPECT_EQ(test_list[1], 420.0f) << "Wrong value at index!";
    EXPECT_EQ(test_list[2], 2.2f) << "Wrong value at index!";
    EXPECT_EQ(test_list[3], 3.3f) << "Wrong value at index!";
    EXPECT_EQ(test_list[4], 69.0f) << "Wrong value at index!";
    EXPECT_EQ(test_list[5], 4.4f) << "Wrong value at index!";
    EXPECT_EQ(test_list[6], 5.5f) << "Wrong value at index!";

    EXPECT_THROW(test_list.insert(44.0f, -10), out_of_range) << "Should throw out of range exception!";
    EXPECT_THROW(test_list.insert(44.0f, 20), out_of_range) << "Should throw out of range exception!";
}
TEST(ArrayTests, FindAtIndex)
{
    ArrayList<float> test_list;
    test_list.append(1.1f);
    test_list.append(2.2f);
    test_list.append(3.3f);

    EXPECT_EQ(test_list.find(1.1f, 0), 0) << "Value not at expected index!";
    EXPECT_EQ(test_list.find(1.1f, 2), -1) << "Should return -1 as value (not found)!";
    
    EXPECT_THROW(test_list.find(100.0f, 100), out_of_range) << "Should throw out of range exception!";
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
TEST(ArrayTests, UnequalityOperatorOverload)
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
TEST(ArrayTests, AssignOperatorOverload)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> second_list = first_list;
    EXPECT_EQ(first_list, second_list);
}
TEST(ArrayTests, InitializerConstuctor)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> test_list_with_initializer { 1, 2, 3};

    EXPECT_EQ(first_list, test_list_with_initializer) << "Arrays not similar!";
}
TEST(ArrayTests, CopyConstructor)
{
    ArrayList<int> first_list;
    first_list.append(1);
    first_list.append(2);
    first_list.append(3);

    ArrayList<int> copied_test_list = first_list;

    EXPECT_EQ(first_list, copied_test_list) << "Arrays not similar!";
}
TEST(ArrayTests, StreamInsertionOverload)
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

ArrayList<float> moveFunction()
{
    ArrayList<float> this_list;
    this_list.append(34.0f);
    return this_list;
}

int main()
{
    //testing::InitGoogleTest();
    //return RUN_ALL_TESTS();

    // The basic test program (for floats)
    ArrayList<float> my_list;
    my_list.append(1.1f);
    my_list.append(2.2f);
    my_list.append(3.3f);

    //ArrayList<float> my_list4(moveFunction());  // Calls Move Constructor. This does  not seem to work in Release version?
                // (SI also couldn't figure it out)
    ArrayList<float> test(move(my_list));

    ArrayList<float>::ArrayListIterator it(&my_list, 0);
    cout << *it << endl; // 1.1f;
    it++;
    cout << *it << endl; // 2.2f;
    it++;
    cout << *it << endl; // 3.3f

    cout << "Begin: " << *my_list.begin() << endl; // 1.1f;
    cout << "End: " << *my_list.end() << endl; // 3.3f;

    my_list.append(4.4f);
    cout << "Added value 4.4" << endl;
    cout << "End: " << *my_list.end() << endl; // 3.3f;

}
