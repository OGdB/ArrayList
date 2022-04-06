#pragma once
#include <string>
#include <stack>
#include <map>

using namespace std;

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
		int neighbour_count() const
		{
			return neighbours.size();
		}
	};

#pragma region ITERATOR
//public:
//	class GraphIterator
//	{
//	protected:
//		// Attributes
//
//
//	public:
//		GraphIterator()
//		{
//
//		}
//
//		void operator++()
//		{
//
//		}
//		void operator++(int dummy)
//		{
//
//		}
//
//		bool operator==(const GraphIterator& other) const
//		{
//		}
//
//		bool operator!=(const GraphIterator& other) const
//		{
//		}
//	};
//
//	GraphIterator begin() const
//	{
//	}
//	GraphIterator end() const
//	{
//	}
#pragma endregion

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
		
		//(A:300 : 300 : 30) | (B:1.5) (C:9.4) (D:4.2)
		//(B:100 : 100 : 30) |
		//(C:250 : 550 : 30) | (E:5.3)
		//(E:520 : 300 : 30) | (B:12.4)
		//(D:550 : 100 : 30) | (A:4.2) (B:0.6)
	}

};
