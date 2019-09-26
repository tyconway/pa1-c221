
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