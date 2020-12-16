#ifndef _OBJECTSINK_H_
#define _OBJECTSINK_H_

#include <vector>

template<typename T>
class Memory
{
public:
	virtual std::vector<T> data() const;
	virtual void add(T item);
	virtual void remove(T item);
	virtual bool contains(T item);
};

template<typename T>
class ObjectSink
{
public:
	virtual void propagate_assert(std::vector<T> objects, Memory<T> memory);
	virtual void propagate_update(std::vector<T> objects, Memory<T> memory);
	virtual void propagate_retract(std::vector<T> objects, Memory<T> memory);
};

template<typename T>
class ObjectSource
{
public:
	virtual std::vector<T> get_source(Memory<T> memory);
	virtual void attach(ObjectSink<T> *sink);
};

#endif //_OBJECTSINK_H_
