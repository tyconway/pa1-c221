
template <class T>
class DoublingArrayStack : public AbstractStack<T>
{
	T* stack;
	int topIndex = -1;
	int capacity;
public:
	DoublingArrayStack(int initialCapacity)
	{
		capacity = initialCapacity;
		stack = new T[capacity];
	}
	~DoublingArrayStack()
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
		return capacity;
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
			T* newStack = new T[capacity * 2];
			for (int index = 0; index < capacity; index++)
			{
				newStack[index] = stack[index];
			}
			stack = newStack;
			capacity *= 2;
			topIndex += 1;
			stack[topIndex] = e;

			return;
		}
		topIndex += 1;
		stack[topIndex] = e;
	}
};