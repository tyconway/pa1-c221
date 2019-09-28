// Source Code
template <class T>
class ArrayStack : public AbstractStack<T>
{
	T* stack; // array
	int topIndex = -1;
	int capacity;
	int constant;
public:
	ArrayStack() {}
	ArrayStack(int initialCapacity, int growthConstant)
	{
		capacity = initialCapacity;
		constant = growthConstant;
		stack = new T[capacity];
	}
	~ArrayStack()
	{
		delete[] stack;
	}
	bool isEmpty()
	{
		if (topIndex == -1)
		{
			return true;
		}
		return false;
	}
	int size()
	{
		return topIndex + 1;
	}
	T top()
	{
		if (isEmpty()) { throw EmptyStack(); }
		return stack[topIndex];
	}
	T pop()
	{
		if (isEmpty()) { throw EmptyStack(); }
		T popped = stack[topIndex];
		topIndex -= 1;
		return popped;
	}
	void push(T e)
	{
		if (topIndex + 1 == capacity)
		{
			T* newStack = new T[capacity + constant];
			for (int index = 0; index < capacity; index++)
			{
				newStack[index] = stack[index];
			}
			stack = newStack;
			capacity += constant;
			topIndex += 1;
			stack[topIndex] = e;

			return;
		}
		topIndex += 1;
		stack[topIndex] = e;
	}
};