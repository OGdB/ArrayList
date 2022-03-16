#pragma once
template <class T>
class OrderedSet
{
protected:
	class Node
	{
	public:
		T mData;
		Node* mLeft;
		Node* mRight;

		Node(const T& value) : mData(value), mNext(nullptr), mPrev(nullptr)
		{
		}
	};
}