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
	testMap.append("Hello There!", "General Kenobi!");
	cout << "Value at key 'Hello There!': ";
	cout << testMap["Hello There!"] << endl;
	//testMap.append("Hello There!", "General Kenobi!");
	//testMap.append("Hello There!", "General Kenobi!");
	//testMap.append("Hello There!", "General Kenobi!");
	//testMap.append("Hello There!", "General Kenobi!");
	//testMap.append("Hello There!", "General Kenobi!");
	//testMap.test();
}
