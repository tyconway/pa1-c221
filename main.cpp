#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

struct EmptyStack : public exception
{
	const char* what() const throw ()
	{
		return "Stack is empty.";
	}
};

template <class Type>
class AbstractStack
{
private:
	// data goes here

public:
	AbstractStack(void) {}

	~AbstractStack(void) {}

	bool isEmpty(void) {}

	int size(void) {}

	Type top() /*throw(exception)*/ {}
	// http://peterforgacs.github.io/2017/06/25/Custom-C-Exceptions-For-Beginners/
	Type pop() /*throw(exception)*/ {}

	void push(Type e) {}
};

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

template <class T>
struct Node
{
    Node<T>* up;
    Node<T>* down;
	T data;
	Node() {}
	Node(T e)
	{
		data = e;
	}
};

template <class T>
class LinkedListStack : public AbstractStack<T>
{
	Node<T>* head = new Node<T>();
	int count = 0;
public:
	LinkedListStack()
	{
	}
	~LinkedListStack()
	{
		delete head;
	}
	bool isEmpty()
	{
		if (count == 0) { return true; }
		return false;
	}
	int size()
	{
		return count;
	}
	T top()
	{
		if (isEmpty()) { throw EmptyStack(); }
        return head->down->data;
	}
    T pop()
    {
        if (isEmpty()) { throw EmptyStack(); }

        Node<T>* popped = head->down;
        T poppedData = popped->data;

        // if final node
        if (count == 1)
        {
            delete popped;
            head->down = nullptr;
            count -= 1;
            return poppedData;
        }

        // if not the final node
        Node<T>* newTop = popped->down;
        head->down = newTop;
        newTop->up = head;
        delete popped;
        count -= 1;
        return poppedData;
    }
	void push(T e)
	{
		Node<T>* added = new Node<T>(e);
		added->down = nullptr;
		
		// if list is empty
		if (isEmpty())
		{
			head->down = added;
            added->up = head;
			count += 1;
			return;
		}
		// if list is not empty
		Node<T>* curr = head->down; // the top element
        added->up = head;
        added->down = curr;
        curr->up = added;
        head->down = added;
		count += 1;
	}
};

int main()
{
	// Request: reduce CPU use (vagrant?)
	// Output: demonstrate basic functionality
	// Extra Credit: alternate structures and analysis
	try
	{
		int testCount = 500000;

		ArrayStack<int> arrStack(1000, 100);
        auto startAS = chrono::high_resolution_clock::now();
		for (int i = 1; i <= testCount; i++)
		{
		    arrStack.push(i);
		}
        auto finishAS = chrono::high_resolution_clock::now();

		DoublingArrayStack<double> doubStack(100);
        auto startDAS = chrono::high_resolution_clock::now();
		for (int i = 1; i <= testCount; i++)
		{
		    doubStack.push(i);
		}
        auto finishDAS = chrono::high_resolution_clock::now();

		LinkedListStack<int> llStack;
        auto startLLS = chrono::high_resolution_clock::now();
		for (int i = 1; i <= testCount; i++)
		{
		    llStack.push(i);
		}
        auto finishLLS = chrono::high_resolution_clock::now();

        // convert nanoseconds (1e-9) to seconds
        double secondsDenominator = 1000000000; 
        auto elapsedAS = (finishAS - startAS)/secondsDenominator;
        auto elapsedDAS = (finishDAS - startDAS)/secondsDenominator;
        auto elapsedLLS = (finishLLS - startLLS)/secondsDenominator;
		cout << "\nArrayStack:         " << elapsedAS.count() << endl;
		cout << "\nDoublingArrayStack: " << elapsedDAS.count() << endl;
		cout << "\nLinkedListStack:    " << elapsedLLS.count() << endl;

        cout << endl;
	}
	catch (const exception& e)
	{
		cerr << e.what() << '\n';
	}
}