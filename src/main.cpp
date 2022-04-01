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

	testMap["Hello There!"] = "General Kenobi!";
	testMap["What did the beaver say when he slipped on water?"] = "Damn it!";

	UnorderedMap<string, string>::UnorderedMapIterator it = testMap.begin();
	for (pair<string,string>* pair : testMap)
	{
		cout << pair->first << endl;
	}
}
