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
class ArrayStack {
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
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}