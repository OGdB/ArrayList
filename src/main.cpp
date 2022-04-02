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
	testMap["asdasd"] = "czxc it!";
	testMap["asdasdgf"] = "ncvbn it!";
	testMap["gsdfgsdfg"] = "sdfg it!";
	testMap["jdfdf"] = "ncvbn it!";
	testMap["dfghdfv"] = "tert it!";
	testMap["vbcvb"] = "ghh it!";
	testMap["yerty"] = "bxcv it!";
	testMap["jdfgjdf"] = "Damn it!";
	testMap["kkbv"] = "gsgdf it!";
	testMap["gdgfg"] = "gsgdf it!";
	testMap["asd"] = "gsgdf it!";
	testMap["56657"] = "gsgdf it!";

	int testint = 0;

	for (pair<string,string>* pair : testMap)
	{
		testint++;
		cout << testint << ": " << pair->first << endl;
	}

	testMap.remove("Hello There!");
	cout << endl << endl;
	testint = 0;
	for (pair<string, string>* pair : testMap)
	{
		testint++;
		cout << testint << ": " << pair->first << endl;
	}
}
