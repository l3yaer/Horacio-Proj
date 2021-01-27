#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>

template<typename T>
class Node
{
public:
	size_t serial_number;
	Node() : serial_number(count++)
	{
	}
	virtual const T& get_output() = 0;
	virtual void clear() = 0;

	bool operator==(const Node<T> &rhs) const
	{
		return serial_number == rhs.serial_number;
	}

protected:
	T output;
private:
	static size_t count;

};

template<typename T>
size_t Node<T>::count = 0;

#endif //_NODE_H_
