#ifndef STACK_H
#define STACK_H


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
#endif