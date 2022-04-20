#include <iostream>
#include <fstream>
#include <level.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();

	Level graph = Level("maps\\map06.txt");
	graph.BreadthFirstTraversal("A");
}