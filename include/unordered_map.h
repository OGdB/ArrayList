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
			int cur_index;

		public:
			UnorderedMapIterator(const ArrayList<pair<K, V>*>& arr, bool atEnd = false) : mTable(arr)
			{
				// Once first value is found (not a nullptr), break loop and set to current.
				if (!atEnd)
				{
					for (int i = 0; i < mTable.size(); i++)
					{
						if (mTable[i] != nullptr)
						{
							cur_index = i;
							break;
						}
					}
				}
				else 
				{
					for (int i = mTable.size(); i > 0; i--)
					{
						if (mTable[i] != nullptr)
						{
							cur_index = i;
							break;
						}
					}
				}
			}

			void operator++()
			{
				for (int i = cur_index + 1; i < mTable.size(); i++) // Loop until end of mTable. Start at index after current index.
				{
					if (mTable[i] != nullptr)
					{
						cur_index = i;
						break;
					}
				}
			}
			void operator++(int dummy)
			{
				for (int i = cur_index + 1; i < mTable.size(); i++) // Loop until end of mTable. Start at index after current index.
				{
					if (mTable[i] != nullptr)
					{
						cur_index = i;
						break;
					}
				}
			}

			V& operator*()
			{
				return mTable[cur_index]->second;
			}

			bool operator==(const UnorderedMapIterator& other) const
			{
				return mTable == other.mTable && cur_index == other.cur_index;
			}

			bool operator!=(const UnorderedMapIterator& other) const
			{
				return mTable != other.mTable && cur_index != other.cur_index;
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
		UnorderedMap(int startCapacity = 10) : mSize(0), mCapacity(startCapacity) 
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
				grow();
				return mTable[hash_index]->second; // Return the Value at the key
			}
			else  // There is no value at the hash_index -> create one and return reference to the value  the user should set.
			{
				V uninit;
				mTable[hash_index] = new pair<K, V>(key, uninit);
				grow();
				return mTable[hash_index]->second;
			}
		}
#pragma endregion

#pragma region TOP_LEVEL_FUNCTIONS
		void find(V value)
		{

		}

		void test()
		{
			//cout << "After adding value: \n";
			//cout << mTable << endl << endl;
			//cout << "Value at index 6: " << mTable[6] << endl << endl;
			//cout << "'&map_array[6]->first' value: " << mTable[6]->first << endl << endl;

			//cout << "Direct call" << endl;
			//cout << mTable[6]->first << endl;

			////cout << "&map_Array[6] is an " << typeid(mTable[6]->first).name() << endl;
			//////cout << map_array[9]->first << endl;

			for (int i = 0; i < mCapacity; i++)
			{
				if (mTable[i] != nullptr)
				{
					cout << "At index " << i << ": " << "[" << mTable[i]->first << ", " << mTable[i]->second << "]" << endl;
				}
			}
			for (pair<K, V>* pair : mTable)
			{
				if (pair != nullptr)
					cout << pair->first << endl;
			}
		}
#pragma endregion

#pragma region INTERNAL
	protected:
		/// @brief Double capacity once mSize is at about 70% of capacity.
		void grow()
		{
			mSize++;

			if ((float)(mSize / mCapacity) >= 0.7f)
			{
				cout << "70% capacity reached. Grow operation/\n";

				mCapacity *= 2;
				// TODO: also grow array and re-insert all values
				ArrayList<pair<K, V>*> bigger_array = ArrayList<pair<K, V>*>(mCapacity);

				for (int i = 1; i <= mCapacity; i++)
				{
					bigger_array.append(nullptr);
				}

				for (pair<K, V>* pair : mTable)
				{
					if (pair != nullptr)
					{
						size_t index = get_index_from_hash(pair->first); // Get the new hash value (with bigger mCap)
						bigger_array[index] = pair; // Copy the pair over to the bigger array at the correct index
					}
				}

				mTable = bigger_array; // New bigger array
			}
		}

		int get_index_from_hash(const K& key) const
		{
			return hash<K>{}(key) % mCapacity;
		}
#pragma endregion 
	};
}