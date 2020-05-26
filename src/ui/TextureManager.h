#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <string>
#include <ResourceManager.h>
#include <Singleton.h>

class Texture;

class TextureManager : public ResourceManager , public Singleton<TextureManager>
{
 public:
	TextureManager();

	Texture *create (const std::string &name, const std::string &file);

 protected:
	Resource *create (const std::string &name, Resource::Handler handler) override;
};

#endif //_TEXTUREMANAGER_H_
