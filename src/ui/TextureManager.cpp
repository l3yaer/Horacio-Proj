#include "TextureManager.h"
#include "Texture.h"

template<> TextureManager *Singleton<TextureManager>::_instance = nullptr;

TextureManager::TextureManager () : Singleton<TextureManager>(), ResourceManager()
{}

Texture *TextureManager::create (const std::string &name, const std::string &file)
{
	auto *texture = dynamic_cast<Texture*>(ResourceManager::create(name));

	texture->file = file;

	return texture;
}

Resource *TextureManager::create (const std::string &name, Resource::Handler handler)
{
	return new Texture(this, name, get_next_handler());
}
