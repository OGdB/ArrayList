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

    OrderedSet<string> mList;
    mList.insert("M");
    mList.insert("G");
    mList.insert("S");
    mList.insert("B");
    mList.insert("P");
    mList.insert("Q");
    mList.insert("A");
    mList.insert("D");
    mList.insert("C");

    cout << "\n\nInitial List:\n" << mList << endl << endl;

    cout << "pre-ordered array:\n";
    ArrayList<string> pre_order_list = mList.traversal(pre_order);
    cout << pre_order_list << endl;
    cout << "post-ordered array::\n";
    ArrayList<string> post_order_list = mList.traversal(post_order);
    cout << post_order_list << endl;
    cout << "in-ordered array::\n";
    ArrayList<string> in_order_list = mList.traversal(in_order);
    cout << in_order_list << endl;
}