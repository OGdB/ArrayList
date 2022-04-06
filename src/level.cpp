#include <iostream>
#include <fstream>
#include <level.h>
#include <gtest/gtest.h>
#include <string>

using namespace std;

Level::Level(const string& file_directory) 
{
	// Load in data
	ifstream fp;
	fp.open(file_directory);

	if (fp.is_open())
	{
		string line_type, name;
		int x, y, radius;

		string node1, node2;
		float edge_thickness;

		while (!fp.eof())
		{
			fp >> line_type; // Reads until first whitespace (and consumes that whitespace).
			if (!fp.eof())
			{ // Succesfully read line_type. Now read the other pieces of data on this line.
				if (line_type == "n")
				{
					fp >> name >> x >> y >> radius;
					// Create a new Node with all values and add to mGraph.
					LevelNode this_node = LevelNode(name, x, y, radius);
					mGraph[name] = this_node;
				}
				else if (line_type == "e")
				{
					// Create a new edge with all values and add to node_info.
					fp >> node1 >> node2 >> edge_thickness;
					//if (node1 != node2)  // Cannot connect a node with itself
					mGraph[node1][node2] = edge_thickness;

					cout << "Found edge from " << node1 << " to " << node2 << endl;
				}
			}
		}

		fp.close();
	}
	else
	{
		cout << "Unable to open map file\n";
	}
}