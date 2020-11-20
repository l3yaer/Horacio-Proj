#include "TextureManager.h"
#include <JobManager.h>
#include "Texture.h"

template <> TextureManager *Singleton<TextureManager>::_instance = nullptr;

void texture_manager_load_texture(void *data)
{
	auto *texture = (Texture *)data;
	if(texture == nullptr)
		return;

	if (!texture->is_loaded())
		texture->load();
	texture->ready();
}

TextureManager::TextureManager() : Singleton<TextureManager>(), ResourceManager()
{
}

Texture *TextureManager::create(const std::string &name, const std::string &file)
{
	const std::pair<Resource *, bool> &resource = ResourceManager::create_ou_retrieve(name);
	auto *texture = dynamic_cast<Texture *>(resource.first);
	if (resource.second)
		texture->file = file;

	if (!texture->is_ready())
		JobManager::instance().add_job(texture_manager_load_texture, texture, JobManager::Queue::MAIN);

	return texture;
}

Resource *TextureManager::create(const std::string &name, Resource::Handler handler)
{
	return new Texture(this, name, get_next_handler());
}
