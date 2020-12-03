#include <algorithm>
#include "ResourceManager.h"

ResourceManager::ResourceManager() : next_handler(1), memory_usage(0)
{
	memory_budget = std::numeric_limits<unsigned long>::max();
}

ResourceManager::~ResourceManager()
{
	destroy_all_resource_pools();
	remove_all();
}

Resource *ResourceManager::create(const std::string &name)
{
	Resource *resource = create(name, get_next_handler());

	add(resource);

	return resource;
}

std::pair<Resource *, bool> ResourceManager::create_ou_retrieve(const std::string &name)
{
	Resource *resource = get_resource(name);
	if (resource)
		return { resource, false };

	return { create(name), true };
}

Resource *ResourceManager::load(const std::string &name)
{
	Resource *resource = create_ou_retrieve(name).first;

	resource->load();

	return resource;
}

Resource *ResourceManager::ready(const std::string &name)
{
	Resource *resource = create_ou_retrieve(name).first;

	resource->ready();

	return resource;
}

void ResourceManager::unload(std::string name)
{
	Resource *resource = get_resource(name);

	if (resource) {
		resource->unload();
	}
}

void ResourceManager::unload(Resource::Handler handler)
{
	Resource *resource = get_resource(handler);

	if (resource) {
		resource->unload();
	}
}

void ResourceManager::unload_all()
{
	LOCK_MUTEX;

	for (auto resource : resources) {
		resource.second->unload();
	}
}

void ResourceManager::reload_all()
{
	LOCK_MUTEX;

	for (auto resource : resources) {
		resource.second->load();
	}
}

void ResourceManager::remove(std::string name)
{
	Resource *resource = get_resource(name);

	if (resource)
		remove_resource(resource);
}

void ResourceManager::remove(Resource *resource)
{
	remove_resource(resource);
}

void ResourceManager::remove(Resource::Handler handler)
{
	Resource *resource = get_resource(handler);

	if (resource)
		remove_resource(resource);
}

void ResourceManager::remove_all()
{
	LOCK_MUTEX;
	resources.clear();
	resources_by_handle.clear();
}

Resource *ResourceManager::get_resource(Resource::Handler handler)
{
	LOCK_MUTEX;
	ResourceHandleMap::iterator it = resources_by_handle.find(handler);
	return it == resources_by_handle.end() ? nullptr : it->second;
}

Resource *ResourceManager::get_resource(const std::string &name)
{
	LOCK_MUTEX;
	ResourceMap::iterator it = resources.find(name);
	return it == resources.end() ? nullptr : it->second;
}

bool ResourceManager::resource_exists(Resource::Handler handler)
{
	return get_resource(handler) != nullptr;
}

bool ResourceManager::resource_exists(const std::string &name)
{
	return get_resource(name) != nullptr;
}

void ResourceManager::set_memory_budget(size_t bytes)
{
	memory_budget = bytes;
}

size_t ResourceManager::get_memory_budget() const
{
	return memory_budget;
}

size_t ResourceManager::get_memory_usage() const
{
	return memory_usage.load();
}

ResourceManager::ResourcePool *ResourceManager::get_resource_pool(const std::string &name)
{
	LOCK_MUTEX;
	ResourcePoolMap::iterator it = resource_pool_map.find(name);
	if (it == resource_pool_map.end()) {
		it = resource_pool_map.insert(ResourcePoolMap::value_type(name, new ResourcePool(name))).first;
	}
	return it->second;
}

void ResourceManager::destroy_resource_pool(const std::string &name)
{
	LOCK_MUTEX;
	ResourcePoolMap::iterator it = resource_pool_map.find(name);
	if (it != resource_pool_map.end()) {
		delete it->second;
		resource_pool_map.erase(it);
	}
}

void ResourceManager::destroy_resource_pool(ResourceManager::ResourcePool *pool)
{
	if (pool) {
		LOCK_MUTEX;
		ResourcePoolMap::iterator it = resource_pool_map.find(pool->get_name());
		if (it != resource_pool_map.end())
			resource_pool_map.erase(it);

		delete pool;
	}
}

void ResourceManager::destroy_all_resource_pools()
{
	LOCK_MUTEX;
	for (auto &it : resource_pool_map)
		delete it.second;

	resource_pool_map.clear();
}

Resource::Handler ResourceManager::get_next_handler()
{
	return next_handler++;
}

void ResourceManager::add(Resource *resource)
{
	LOCK_MUTEX;
	resources.emplace(resource->get_name(), resource);
	resources_by_handle.emplace(resource->get_handler(), resource);
}

void ResourceManager::remove_resource(Resource *resource)
{
	LOCK_MUTEX;
	ResourceMap::iterator it = resources.find(resource->get_name());
	if (it != resources.end()) {
		resources.erase(it);
	}

	ResourceHandleMap::iterator it_handler = resources_by_handle.find(resource->get_handler());
	if (it_handler != resources_by_handle.end()) {
		resources_by_handle.erase(it_handler);
	}
}

void ResourceManager::resource_loaded(Resource *resource)
{
	memory_usage += resource->get_size();
}

void ResourceManager::resource_unloaded(Resource *resource)
{
	memory_usage -= resource->get_size();
}

void ResourceManager::resource_ready(Resource *resource)
{
}

void ResourceManager::resource_clear(Resource::Handler handler)
{
	remove(handler);
}

ResourceManager::ResourcePool::ResourcePool(const std::string &name) : name(name)
{
}

const std::string &ResourceManager::ResourcePool::get_name() const
{
	return name;
}

void ResourceManager::ResourcePool::clear()
{
	LOCK_MUTEX;
	for (auto &item : items)
		item->get_creator()->resource_clear(item->get_handler());

	items.clear();
}
