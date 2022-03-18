#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <ordered_set.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    //OrderedSet<string> mList;
    //mList.insert("M");
    //mList.insert("G");
    //mList.insert("S");
    //mList.insert("B");
    //mList.insert("P");
    //mList.insert("Q");
    //mList.insert("A");
    //mList.insert("D");
    //mList.insert("C");

    OrderedSet<int> mList;
    mList.insert(1);
    mList.insert(2);
    mList.insert(3);
    mList.insert(4);
    mList.insert(5);
    mList.insert(6);
    mList.insert(7);

    cout << "\n\nInitial List:\n" << mList << endl << endl;

    cout << "pre-ordered array:\n";
    ArrayList<int> pre_order_list = mList.traversal(pre_order);
    cout << pre_order_list << endl;
    cout << "post-ordered array:\n";
    ArrayList<int> post_order_list = mList.traversal(post_order);
    cout << post_order_list << endl;
    cout << "in-ordered array:\n";
    ArrayList<int> in_order_list = mList.traversal(in_order);
    cout << in_order_list << endl;

    cout << "\nRebalanced mList:\n";
    mList.rebalance();
    cout << mList << endl;
}