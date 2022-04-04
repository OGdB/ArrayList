#pragma once
#include <string>
#include <stack>

using namespace std;

namespace ssuds
{
	template <class K, class V>
	class Graph
	{

#pragma region ITERATOR
	public:
		class GraphIterator
		{
		protected:
			// Attributes


		public:
			GraphIterator()
			{

			}

			void operator++()
			{

			}
			void operator++(int dummy)
			{

			}

			bool operator==(const UnorderedMapIterator& other) const
			{
			}

			bool operator!=(const UnorderedMapIterator& other) const
			{
			}
		};

		GraphIterator begin() const
		{
		}
		GraphIterator end() const
		{
		}
#pragma endregion

	protected:
		
		
#pragma region Constructors
	public:
		Graph()
		{

		}

		// Destructor
		~Graph()
		{
		}
#pragma endregion

#pragma region OPERATOR_OVERRIDES

		friend ostream& operator <<(ostream& os, const UnorderedMap<K, V>& omap)
		{
			
			return os;
		}

#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONS

#pragma endregion

#pragma region INTERNAL

#pragma endregion 
	};
}