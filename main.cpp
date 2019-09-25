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
        delete [] stack;
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
        delete [] stack;
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

template <class T>
struct Node
{
    Node<T>* next;
    T data;
    Node(T e)
    {
        data = e;
    }
};

template <class T>
class LinkedListStack : public AbstractStack<T>
{
    // Node<T>* top;
    int count = 0;
public:
    LinkedListStack() {}
    ~LinkedListStack() {}
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

    }
    void push(T e)
    {
        Node<T>* added = new Node<T>(e);
        // added->next = nullptr;
        count += 1;
        // if list is empty
        if (isEmpty())
        {
            // top = added;
            return;
        }
        // if list is not empty
        // set the head's next to the added 
        // head->added;
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

        LinkedListStack<int> llStack;
        llStack.push(2);
        cout << "LinkedListStack: " << llStack.isEmpty() << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}