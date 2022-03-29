#include <iostream>
#include <array_list.h>
#include <linked_list.h>
#include <ordered_set.h>
#include <unordered_map.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace ssuds;

int main(int argc, char** argv)
{
	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();

	UnorderedMap<string, string> testMap;
	testMap.append("General Kenobi", "Hello There!");
	testMap.append("How Uncivilized!", "We can be civilized about this!");
	testMap.append("What did the beaver say when he slipped on water?", "Dam it!");
}