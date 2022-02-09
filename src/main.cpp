// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <gtest/gtest.h>

using namespace std;
using namespace ssuds;

ArrayList<float> moveFunction()
{
    ArrayList<float> this_list;
    this_list.append(34.0f);
    return this_list;
}

TEST(BasicTests, BasicTest01)
{
    int x = 47;
    int y = 47;
    EXPECT_EQ(x, y) << "Not equal!";
}


int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    // The basic test program (for floats)
    ArrayList<float> my_list;
    my_list.append(1.1f);
    my_list.append(1.2f);
    my_list.append(1.3f);

    ArrayList<float> my_list2;
    my_list2.append(1.1f);
    my_list2.append(1.2f);
    my_list2.append(1.3f);

    ArrayList<float> my_list3(my_list2);  // Copy Constructor
    ArrayList<float> my_list4 = moveFunction();  // Move Constructor gets called
    cout << my_list4[0] << endl;

    ArrayList<float>::ArrayListIterator it(&my_list, 0);
    it++;
    float test_val = *it;
    cout << test_val << endl;
    test_val = *my_list.begin();
    cout << test_val << endl;

}
