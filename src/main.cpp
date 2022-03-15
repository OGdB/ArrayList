// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

//LinkedList<int> func()
//{
//    LinkedList<int> mList;
//
//    mList.append(69);
//    mList.append(69);
//    mList.append(69);
//    mList.append(69);
//    mList.append(69);
//
//    return mList;
//}

int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    /*LinkedList<int> mList;

    mList.append(3);
    mList.prepend(420);
    mList.append(6);
    mList.append(69);
    mList.append(9);
    mList.append(4);
    mList.append(2);

    LinkedList<int> mList2;
    mList2 = mList;
    cout << mList2 << endl;*/

    //cout << mList << endl; // [420, 3, 6, 69, 9, 4, 2]

    //mList.clear();

    //cout << mList << endl; // [] 

    //LinkedList<int> mList_copy = mList;

    //// REMOVE & COPY CONSTRUCTOR
    //mList_copy.remove(0);
    //cout << mList_copy << endl; // [3, 6, 69, 9, 4, 2]
    //mList_copy.remove(5);
    //cout << mList_copy << endl; // [3, 6, 69, 9, 4]
    //mList_copy.remove(2);
    //cout << mList_copy << endl; // [3, 6, 9, 4]

    //cout << "Getting iterator at begin().." << endl;
    //LinkedList<int>::LinkedListIterator it = mList.begin();
    //cout << "Iterator value: " << *it << endl; // 420
    //cout << "Using remove function with iterator-parameter...\n";
    //LinkedList<int>::LinkedListIterator it2 = mList.remove(it);
    //cout << "Iterator value: " << *it2 << endl; // 3
    //cout << mList << endl; // [3, 6, 69, 9, 4, 2] (420 removed)

    //// Find method
    //LinkedList<int>::LinkedListIterator findit = mList.find(3);
    //cout << "\nTrying to find value 3.." << "\nValue found: " << *findit << " at index: " << findit.index() << endl << endl;

    //// Insert Method
    //cout << "Insert Function\n";
    //cout << "Current iterator Spot/Index: " << findit.index() << endl;
    //cout << "Adding value 5 at iterator location...\n";
    //mList.insert(findit, 5);
    //cout << mList << endl << endl;

    //// COPY CONSTRUCTOR
    //LinkedList<int> mList2 = mList;
    //cout << "\nCopying previous linked list..\n" <<
    //    mList2 << endl;

    //// MOVE CONSTRUCTOR
    //LinkedList<int> mList3 = func();
    //cout << mList3 << endl;

    //// INITIALIZER CONSTRUCTOR
    //LinkedList<int> mList4 { 1, 2, 3, 4 };
    //cout << mList4 << endl;
}