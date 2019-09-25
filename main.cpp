#include <iostream>

using namespace std;

struct EmptyStack : public exception
{
	const char * what () const throw ()
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
   
   void push ( Type e ) {}
};

template <class T>
class ArrayStack 
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
        T popped = stack[topIndex];
        topIndex -= 1;
        return popped;
    }
    void push(T e)
    {
        // TODO if not full
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
class DoublingArrayStack : public ArrayStack<T>
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
        // TODO
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

int main() 
{
    // Request: reduce CPU use (vagrant?)
    // Extra Credit: alternate structures and analysis
    try
    {
        ArrayStack<int> arrStack(1000, 1000);
        for (int i = 1; i <= 10000; i++)
        {
            arrStack.push(i);
            printf("[%i, %i]\n", arrStack.top(), arrStack.size());
        }
        cout << "Pop: " << arrStack.pop() << endl;

        DoublingArrayStack<double> doubStack(1000);
        cout << "\nDoublingArrayStack:\n";
        for (int i = 1; i <= 10000; i++)
        {
            doubStack.push(i);
            printf("[%f, %i]\n", doubStack.top(), doubStack.size());
        }
        cout << "Popped: " << doubStack.pop() << endl;
        cout << doubStack.size() << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}