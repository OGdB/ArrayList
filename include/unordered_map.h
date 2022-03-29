#pragma once
#include <string>
#include <array_list.h>
#include <stack>

using namespace std;

namespace ssuds
{
	template <class K, class V>
	class UnorderedMap
	{
	protected:
		int mSize;			// number of key-value pairs.
		int mCapacity;		// number of available spots in our table.
		
		ArrayList< pair<K, V>* > map_array; // Arraylist with pointers to pairs in it.

#pragma region Constructors
	public:
		UnorderedMap(int startCapacity = 10) : mSize(0), mCapacity(startCapacity) 
		{
			// Should fill each value of the mCapacity with a nullptr
			for (int i = 1; i < mCapacity; i++)
			{
				map_array.append(nullptr);
			}

		}
#pragma endregion

#pragma region OPERATOR_OVERRIDES

		friend ostream& operator <<(ostream& os, const UnorderedMap<K, V>& omap)
		{
			os << "[";

			for (int i = 0; i < omap.mSize; i++)
			{
				os << omap[i].first;
				os << ", ";
				os << omap[i].second;
				if (i < omap.mSize - 1)
					os << ", ";
			}

			os << "]";
			return os;
		}
#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONS
		void append(const K key, const V value)
		{
			grow();
			unsigned int index = get_hash(key);

			pair<K, V> new_pair = make_pair(key, value);

			map_array.insert(&new_pair, index);
		}
#pragma endregion

#pragma region INTERNAL
	protected:
		/// @brief Double capacity once mSize is at about 70% of capacity.
		void grow()
		{
			mSize++;

			if ((int)(mSize == mCapacity / 1.4286f))
				mCapacity *= 2;
		}

		unsigned int get_hash(const K& key) const
		{
			return hash<K>{}(key) % mCapacity;
		}
#pragma endregion 
	};
}