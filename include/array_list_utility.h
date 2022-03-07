#pragma once
#include <string>
#include <random>

using namespace std;

namespace ssuds
{
	enum SortType { ASCENDING, DESCENDING };

	/// An ArrayList is an array-based data structure. 
	template <class T>
	class array_list_utility
	{
	public:
		void quicksort(ArrayList<T>& arrayList)
		{

		}
		// random_device funtion

		//void shuffle_list(ArrayList& list)
		//{
		//	for (size_t i = 0; i < list.size(); i++)
		//	{
		//		random
		//	}
		//}
		//void bubblesort<float>(ArrayList& list, SortType::ASCENDING, int num_ops)
		//{
		//	
		//}
		//void quicksort()
		//{

		//}
		//bool out_of_order(SortType type, const T& val1, const& T alist)
		//{
		//	type == SortType::Ascending ? return val1 > val2 : return val1 < val2;
		//}
		//int binary_search(const ArrayList& alist, SortType type, const T& search_val, int * num = nullptr)
		//{
		//	int comparisons = 0;
		//	// Return the index where search_value appears in alist (or -1 if it doesn't)
		//		// if we check/compare a value, do this:
		//		comparisons++;

		//		// right before the return statement
		//		if (num_ops != nullptr)
		//		{
		//			*num_ops = comparisons;
		//		}
		//		return found_index;

		//}

	};
}

//enum Color { red, green, blue };
//Color r = red;
//
//switch (r)
//{
//case red: std::cout << "red\n";   break;
//case green: std::cout << "green\n"; break;
//case blue: std::cout << "blue\n";  break;
//}

//pivot(L, left, right)
//{
//	pivot_val = L[something between left and right]
//		rearrange the elements of L from left to right so all values less than 
//		(for ascending) are to the left of the pivot value, and all values bigger 
//		are to the right
//	return the index where the pivot value is now
//
//		L = [..., 2.9f, 5.5f, 7.6f, 2.3f, ...]
//		and we choose 7.6 for our pivot, we might end up with
//		[..., 2.9f, 7.6f, 5.5f, 2.3f, ...]
//		2.9f and 5.5f are swapped
//}