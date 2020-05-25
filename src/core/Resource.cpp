#include "Resource.h"
#include "ResourceManager.h"

Resource::Resource (ResourceManager *creator, const std::string &name, Handler handler)
		: creator (creator), name (name), size (0), current_state (UNLOADED), handler(handler)
{}

Resource::Resource () : creator (nullptr), size (0), current_state (UNLOADED), handler(0)
{}

bool Resource::is_loaded ()
{
	return current_state.load() == LOADED;
}
bool Resource::is_ready ()
{
	return current_state.load() == READY;
}

void Resource::load ()
{
	current_state.store(LOADED);
}

void Resource::unload ()
{
	current_state.store(UNLOADED);
}

void Resource::ready ()
{
	current_state.store(READY);
}

std::string Resource::get_name () const
{
	return name;
}

Resource::Handler Resource::get_handler () const
{
	return handler;
}

size_t Resource::get_size () const
{
	return size;
}
ResourceManager *Resource::get_creator () const
{
	return creator;
}
