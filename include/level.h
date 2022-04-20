#pragma once
#include <string>
#include <stack>
#include <map>
#include <queue>
#include <array_list.h>

using namespace std;
using namespace ssuds;

class Level
{
public:
	class LevelNode
	{
	private:
		string name;
		int x;
		int y;
		int radius;
		map<string, float> neighbours;  // Neighbour-node name and edge size

		friend ostream& operator <<(ostream& os, const LevelNode& onode)
		{
			os << "(";

			os << onode.name << ":" << onode.x << " : " << onode.y << " : " << onode.radius;

			os << ")";

			os << " | ";

			for (auto &neighbour : onode.neighbours)
			{
				os << "(";

				os << neighbour.first << ":" << neighbour.second;

				os << ") ";
			}

			return os;
		}

	public:
		float& operator[](const string node_name)
		{
			return neighbours[node_name];
		}

		LevelNode() { }

		LevelNode(const string& n, const int& xPos, const int& yPos, const int& rad)
		{
			name = n;
			x = xPos;
			y = yPos;
			radius = rad;
		}

		string getName() const
		{
			return name;
		}

		int neighbourCount() const
		{
			return neighbours.size();
		}

		map<string, float> getNeighbours() const
		{
			return neighbours;
		}
	};

public:
	map<string, LevelNode> mGraph;  // Node info

	Level(const string& file_dir);

	LevelNode& operator[](const string node_name)
	{
		return mGraph[node_name];
	}
	friend ostream& operator<<(ostream& os, const Level& level)
	{
		for (auto pair : level.mGraph)
		{
			os << pair.second << endl;
		}

		return os;
	}

	void BreadthFirstTraversal(const string& start_node_name)
	{
		queue<LevelNode> frontier;
		ArrayList<string> traversed_nodes;  // The visited nodes' names
		LevelNode& start_node = mGraph[start_node_name];

		frontier.push(start_node);
		cout << start_node.getName() << " ";

		while (frontier.size() > 0)
		{
			queue<LevelNode> new_frontier;

			for (int i = 0; i <= frontier.size(); i++)  // For each node in the frontier
			{
				LevelNode this_node = frontier.front();

				// For each neighbour of this node in the frontier
				for (auto& neighbour : this_node.getNeighbours())
				{
					if (!traversed_nodes.contains(neighbour.first))  // If this neighbour has not already been traversed
					{
						// Add to traversed nodes and add to new frontier
						new_frontier.push(mGraph[neighbour.first]);
						traversed_nodes.append(neighbour.first);
						cout << neighbour.first << " ";
					}
				}

				frontier.pop();
			}

			frontier = new_frontier;
		}
	}

	void DepthFirstTraversal(const LevelNode& start_node, const LevelNode& cur_node)
	{

	}

};
