#include "Resource.h"
#include "ResourceManager.h"

Resource::Resource (ResourceManager *creator, const std::string &name, Handler handler)
		: creator (creator), name (name), size (0), current_state (UNLOADED), handler (handler)
{}

Resource::Resource () : creator (nullptr), size (0), current_state (UNLOADED), handler (0)
{}

bool Resource::is_loaded ()
{
	return current_state.load () == LOADED;
}
bool Resource::is_ready ()
{
	return current_state.load () == READY;
}

void Resource::load ()
{

	current_state.store (LOADING);

	{
		LOCK_MUTEX;
		load_in ();
	}

	size = check_size ();

	current_state.store (LOADED);
}

void Resource::unload ()
{
	auto old_state = current_state.load ();
	if (old_state != LOADED && old_state != READY) return;

	if (!current_state.compare_exchange_strong (old_state, UNLOADING)) return;

	{
		LOCK_MUTEX;
		if (old_state == READY)
			{
				unready ();
			}
		else
			{
				clear_out ();
			}
	}

	current_state.store (UNLOADED);
}

void Resource::ready ()
{

	current_state.store (READING);

	{
		LOCK_MUTEX;
		prepare ();
	}

	current_state.store (READY);
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

size_t Resource::check_size ()
{
	size_t mem_size = 0;
	mem_size += name.size() * sizeof(char);

	return mem_size;
}
