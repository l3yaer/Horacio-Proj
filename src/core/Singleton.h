#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

template <typename T> class Singleton {
private:
	Singleton(const Singleton<T> &);

	Singleton &operator=(const Singleton<T> &);

protected:
	static T *_instance;

public:
	Singleton()
	{
		assert(!_instance);
		_instance = static_cast<T *>(this);
	}

	~Singleton()
	{
		assert(_instance);
		_instance = 0;
	}

	static T &instance()
	{
		assert(_instance);
		return (*_instance);
	}

	static T *instance_ptr()
	{
		return _instance;
	}
};

#define IMPLEMENT_SINGLETON(NAME) template <> NAME *Singleton<NAME>::_instance = nullptr;

#endif //_SINGLETON_H_
