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

#pragma region ITERATOR
	public:
		class UnorderedMapIterator
		{
		protected:
			// Attributes
			ArrayList<pair<K, V>*> mTable;
			int spot;

		public:
			UnorderedMapIterator(const ArrayList<pair<K, V>*>& arr, bool at_end = false) : mTable(arr)
			{
				// Once first value is found (not a nullptr), break loop and set to current.
				if (!at_end)
				{
					for (int i = 0; i < mTable.size(); i++)
					{
						if (mTable[i] != nullptr)
						{
							spot = i;
							break;
						}
					}
				}
				else 
					spot = mTable.size();
			}
			UnorderedMapIterator(const ArrayList<pair<K, V>*>& arr, int start_spot) : mTable(arr) { }

			void operator++()
			{
				for (int i = spot + 1; i < mTable.size() + 1; i++) // Loop until end of mTable. Start at index after current index.
				{
					if (i == mTable.size() || mTable[i] != nullptr) // If this index is not a nullptr
					{
						spot = i; // Set that to the current index.
						break;
					}
				}
			}
			void operator++(int dummy)
			{
				for (int i = spot + 1; i < mTable.size() + 1; i++) // Loop until end of mTable. Start at index after current index.
				{
					if (i == mTable.size() || mTable[i] != nullptr) // If this index is not a nullptr
					{
						spot = i; // Set that to the current index.
						break;
					}
				}
			}

			pair<K, V>*& operator*()
			{
				if (mTable[spot] != nullptr)
					return mTable[spot];
			}

			bool operator==(const UnorderedMapIterator& other) const
			{
				return spot == other.spot;
			}

			bool operator!=(const UnorderedMapIterator& other) const
			{
				return spot != other.spot;
			}
		};

		UnorderedMapIterator begin() const
		{
			return UnorderedMapIterator(mTable, false);
		}
		UnorderedMapIterator end() const
		{
			return UnorderedMapIterator(mTable, true);
		}
#pragma endregion

	protected:
		int mSize;			// number of key-value pairs.
		int mCapacity;		// number of available spots in our table.
		
		ArrayList<pair<K, V>*> mTable; // Arraylist with pointers to pairs in it.

#pragma region Constructors
	public:
		UnorderedMap(int startCapacity = 11) : mSize(0), mCapacity(startCapacity) 
		{
			// Should fill each value of the mCapacity with a nullptr
			for (int i = 1; i <= mCapacity; i++)
			{
				mTable.append(nullptr);
			}
		}

		// Destructor
		~UnorderedMap()
		{
			for (pair<K, V>* pair : mTable)
			{
				delete pair;
			}
		}
#pragma endregion

#pragma region OPERATOR_OVERRIDES

		friend ostream& operator <<(ostream& os, const UnorderedMap<K, V>& omap)
		{
			os << "{";

			int mValues_added = 0;

			for (int i = 0; i < omap.mCapacity; i++)
			{
				if (omap.mTable[i] != nullptr)
				{
					os << omap.mTable[i]->first;
					os << ": ";
					os << omap.mTable[i]->second;
					mValues_added += 1;

					if (mValues_added != omap.mSize)  // Add a comma if all values haven't been added yet.
						os << ", ";
				}
			}

			os << "}";
			return os;
		}

		V& operator[](const K& key)
		{
			int hash_index = get_index_from_hash(key);

			if (mTable[hash_index] != nullptr)  // If there is a pair at this hash_index
			{
				for (int i = 1; i < mCapacity; i++) // Start at i=1 as the prev. check already established that the index was not 'this' hash.
				{
					int test_index = (i + hash_index) % mCapacity;

					if (mTable[test_index] == nullptr)
					{
						hash_index = test_index;
						break;
					}
				}

				V uninit;
				mTable[hash_index] = new pair<K, V>(key, uninit);

				if (grow())
					hash_index = get_index_from_hash(key);

				return mTable[hash_index]->second; // Return the Value at the key
			}
			else  // There is no value at the hash_index -> create one and return reference to the value  the user should set.
			{
				V uninit;
				mTable[hash_index] = new pair<K, V>(key, uninit);

				if (grow())
					hash_index = get_index_from_hash(key);			

				return mTable[hash_index]->second;
			}
		}
#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONS
		//UnorderedMapIterator find(K search_key)
		//{
		//	for (pair<K, V>* pair : this)
		//	{
		//		if (pair->first == search_key)
		//		{
		//			return *pair;
		//		}
		//	}

		//	return end();
		//}

#pragma endregion

#pragma region INTERNAL
	protected:
		/// @brief Double capacity once mSize is at about 70% of capacity.
		/// @return Returns true if 70% capacity was reached.
		bool grow()
		{
			mSize++;
			if (((float)mSize / (float)mCapacity) >= 0.7f)
			{
				// cout << "70% capacity reached. Grow operation/\n";

				mCapacity *= 2;
				ArrayList<pair<K, V>*> bigger_array;
				for (int i = 1; i <= mCapacity; i++)
				{
					bigger_array.append(nullptr);
				}

				for (pair<K, V>* old_pair : mTable)
				{
					if (old_pair != nullptr)
					{
						int hash_index = get_index_from_hash(old_pair->first);
						bigger_array[hash_index] = new pair<K, V>(old_pair->first, old_pair->second);

					}
				}

				mTable = bigger_array; // New bigger array
				return true;
			}

			return false;
		}

		int size()
		{
			return mCapacity;
		}

		int get_index_from_hash(const K& key) const
		{
			return hash<K>{}(key) % mCapacity;
		}
#pragma endregion 
	};
}