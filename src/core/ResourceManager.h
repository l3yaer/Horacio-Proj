#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "Singleton.h"
#include "types.h"
#include "Resource.h"
#include <list>
#include <atomic>
#include <unordered_map>
#include <map>

template <typename T> class Pool {
protected:
	typedef typename std::list<T> ItemList;
	ItemList items;
	MUTEX;

public:
	Pool() = default;
	virtual ~Pool() = default;

	virtual std::pair<bool, T> remove_item()
	{
		LOCK_MUTEX;
		std::pair<bool, T> ret;
		if (items.empty()) {
			ret.first = false;
		} else {
			ret.first = true;
			ret.second = items.front();
			items.pop_front();
		}
		return ret;
	}

	virtual void add_item(const T &item)
	{
		LOCK_MUTEX;
		items.push_front(item);
	}

	virtual void clear()
	{
		LOCK_MUTEX;
		items.clear();
	}
};

class ResourceCallback {
public:
	virtual void resource_loaded(Resource *) = 0;
	virtual void resource_unloaded(Resource *) = 0;
	virtual void resource_ready(Resource *) = 0;
	virtual void resource_clear(Resource::Handler) = 0;
};

class ResourceManager : public ResourceCallback {
public:
	class ResourcePool : public Pool<Resource *> {
	protected:
		std::string name;

	public:
		ResourcePool(const std::string &name);

		const std::string &get_name() const;

		void clear();
	};
	typedef std::unordered_map<std::string, Resource *> ResourceMap;
	typedef std::map<Resource::Handler, Resource *> ResourceHandleMap;

	MUTEX;
	ResourceManager();

	~ResourceManager();

	Resource *create(const std::string &name);

	std::pair<Resource *, bool> create_ou_retrieve(const std::string &name);

	Resource *load(const std::string &name);

	Resource *ready(const std::string &name);

	void unload(const std::string name);

	void unload(Resource::Handler handler);

	void unload_all();

	void reload_all();

	void remove(const std::string name);

	void remove(Resource *resource);

	void remove(Resource::Handler handler);

	void remove_all();

	Resource *get_resource(Resource::Handler handler);

	Resource *get_resource(const std::string &name);

	bool resource_exists(Resource::Handler handler);

	bool resource_exists(const std::string &name);

	void set_memory_budget(size_t bytes);

	size_t get_memory_budget() const;

	size_t get_memory_usage() const;

	ResourcePool *get_resource_pool(const std::string &name);

	void destroy_resource_pool(const std::string &name);

	void destroy_resource_pool(ResourcePool *pool);

	void destroy_all_resource_pools();

	void resource_loaded(Resource *resource) override;

	void resource_unloaded(Resource *resource) override;

	void resource_ready(Resource *resource) override;

	void resource_clear(Resource::Handler handler) override;

protected:
	typedef std::map<std::string, ResourcePool *> ResourcePoolMap;
	size_t memory_budget;
	std::atomic<size_t> memory_usage;
	std::atomic<Resource::Handler> next_handler;
	ResourceHandleMap resources_by_handle;
	ResourceMap resources;
	ResourcePoolMap resource_pool_map;

	Resource::Handler get_next_handler();

	virtual Resource *create(const std::string &name, Resource::Handler handler) = 0;

	void add(Resource *resource);

	void remove_resource(Resource *resource);
};

#endif //_RESOURCEMANAGER_H_
