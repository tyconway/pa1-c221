#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
using namespace std;

struct EmptyStack : public exception
{
	const char* what() const throw ()
	{
		return "Stack is empty.";
	}
};

#endif