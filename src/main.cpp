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

LinkedList<int> func()
{
    LinkedList<int> mList;

    mList.append(69);
    mList.append(69);
    mList.append(69);
    mList.append(69);
    mList.append(69);

    return mList;
}

int main(int argc, char**argv)
{
    /*testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
    
    LinkedList<int> mList;

    mList.append(3);
    mList.append(6);
    mList.append(69);
    mList.append(9);
    mList.append(4);
    mList.append(2);
    // cout << mList << endl; // [3, 6, 9, 4, 2]

    mList.prepend(420);
    // cout << mList[0] << endl; // 420
    // cout << mList << endl; // [420, 3, 6, 9, 4, 2]

    //mList.insert(3, 69);
    // cout << mList[3] << endl; // 69

    // cout << mList << endl << endl; // [420, 3, 6, 69, 9, 4, 2]

    //cout << "Pretty loop through list:" << endl;
    LinkedList<int>::LinkedListIterator it = mList.begin();

   /* for (int number : mList)
    {
        cout << number << endl;
    }*/

    cout << mList << endl;
    // Copy constructor //
    LinkedList<int> mList2 = mList;
    cout << mList2 << endl;

    // Find method
    LinkedList<int>::LinkedListIterator findit = mList.find(3);

    // MOVE CONSTRUCTOR //
    cout << endl << *findit << endl;
    LinkedList<int> mList3 = func();
    cout << mList3 << endl;

    // INITIALIZER CONSTRUCTOR //
    LinkedList<int> mList4 { 1, 2, 3, 4 };
    cout << mList4 << endl;
}