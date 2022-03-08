// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

TEST(BasicTests, BasicTest01)
{
    int x = 47;
    int y = 47;
    EXPECT_EQ(x, y) << "Not equal!";
}


int main(int argc, char**argv)
{
    /*testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
    LinkedList<int> test_list;

    test_list.append(3);
    test_list.append(6);
    test_list.append(9);
    test_list.append(4);
    test_list.append(2);
    test_list.prepend(420);
    cout << test_list[0] << endl;
    cout << test_list << endl;
    test_list.insert(3, 69);
    cout << test_list << endl;
}
