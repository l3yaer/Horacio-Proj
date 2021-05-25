#include "TextureManager.h"
#include "Texture.h"

IMPLEMENT_SINGLETON(TextureManager)

TextureManager::TextureManager() : Singleton<TextureManager>(), ResourceManager()
{
}

Texture *TextureManager::create(const std::string &name, const std::string &file)
{
	const std::pair<Resource *, bool> &resource = ResourceManager::create_ou_retrieve(name);
	Texture *texture = dynamic_cast<Texture *>(resource.first);
	if (resource.second)
		texture->file = file;

	if (!texture->is_ready())
    {
        if (!texture->is_loaded())
            texture->load();
		texture->ready();
    }
	return texture;
}

Resource *TextureManager::create(const std::string &name, Resource::Handler handler)
{
	return new Texture(this, name, get_next_handler());
}
