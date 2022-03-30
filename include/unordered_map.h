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
		
		ArrayList< pair<K, V>* > mTable; // Arraylist with pointers to pairs in it.

#pragma region Constructors
	public:
		UnorderedMap(int startCapacity = 10) : mSize(0), mCapacity(startCapacity) 
		{
			// Should fill each value of the mCapacity with a nullptr
			for (int i = 1; i <= mCapacity; i++)
			{
				mTable.append(nullptr);
			}

			cout << "Before inserting any value: \n";
			cout << mTable << endl << endl;
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
			size_t index = get_hash(key);

			// If index is occupied. Add 1 to index until empty spot is found. If at last index, start back at index 0
			if (mTable[index] != nullptr)
			{
				for (int i = 1; i < mCapacity; i++) // Start at i=1 as the prev. check already established that the index was occupied.
				{
					int test_index = (i + index) % mCapacity;
					//cout << "Check if value: " << test_index << " is empty.\n";
					if (mTable[test_index] == nullptr)
					{
						//cout << "Index " << test_index << " is not used.\n";
						index = test_index;
						break;
					}
				}
			}

			//cout << "Inserting value at index: " << index << endl;
			pair<K, V>* new_pair = new pair<K, V>(key, value); // Need to use 'new' to 'keep' the object outside of this void.

			mTable[index] = new_pair; // Does not grow array or map size/capacity.
			
			//pair<K, V> test_pair = *mTable[index]; // De-referencing a pointer to a 'normal' variable.
			//cout << test_pair.first << endl; // Now I can use it like 'normal'.
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
				ArrayList<pair<K, V>*> bigger_array = ArrayList<pair<K, V>*>(mCapacity * 2);

				mTable = ArrayList< pair<K, V>* >(mCapacity * 2); // New bigger array
			}
		}

		unsigned int get_hash(const K& key) const
		{
			return hash<K>{}(key) % mCapacity;
		}
#pragma endregion 
	};
}