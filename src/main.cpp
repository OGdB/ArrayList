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
    return RUN_ALL_TESTS();

    //OrderedSet<int> mList;
    //mList.insert(1);
    //mList.insert(2);
    //mList.insert(3);
    //mList.insert(4);
    //mList.insert(5);

    //cout << "Does mList contain 3?\n";
    //cout << mList.contains(3) << "!\n";

    //cout << mList << endl;
}