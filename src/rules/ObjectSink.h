#ifndef _OBJECTSINK_H_
#define _OBJECTSINK_H_

class WorkingMemory;

template<typename T>
class ObjectSink
{
public:
	virtual void propagate_assert(T object, WorkingMemory *memory);
	virtual void propagate_update(T object, WorkingMemory *memory);
	virtual void propagate_retract(T object, WorkingMemory *memory);
};

template<typename T>
class ObjectSource
{
public:
	virtual T get_source(WorkingMemory *memory);
	virtual void attach(ObjectSink<T> *sink);
};

#endif //_OBJECTSINK_H_
