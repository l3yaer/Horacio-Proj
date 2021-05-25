#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <atomic>
#include "types.h"

class ResourceCallback;

class Resource {
public:
	enum State { UNLOADED, LOADING, LOADED, READING, READY, UNLOADING };

	typedef size_t Handler;

protected:
	ResourceCallback *creator;
	std::string name;
	size_t size;
	std::atomic<State> current_state;
	Handler handler;

	Resource();
	Resource &operator=(const Resource &rhs);

	virtual void unready() = 0;

	virtual void clear() = 0;

	virtual void load_in() = 0;

	virtual void prepare() = 0;

	virtual size_t check_size();

public:
	MUTEX;

	Resource(ResourceCallback *creator, const std::string &name, Handler handler);

	virtual ~Resource() = default;

	bool is_loaded();

	bool is_ready();

	virtual void load();

	virtual void unload();

	virtual void ready();

	std::string get_name() const;

	Handler get_handler() const;

	size_t get_size() const;

	ResourceCallback *get_creator() const;
};

#endif //_RESOURCE_H_
