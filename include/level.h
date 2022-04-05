#pragma once
#include <string>
#include <stack>

using namespace std;

namespace ssuds
{
	class Level
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

			bool operator==(const GraphIterator& other) const
			{
			}

			bool operator!=(const GraphIterator& other) const
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
		Level()
		{

		}

		// Destructor
		~Level()
		{
		}
#pragma endregion

#pragma region OPERATOR_OVERRIDES

		friend ostream& operator <<(ostream& os, const Level& omap)
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