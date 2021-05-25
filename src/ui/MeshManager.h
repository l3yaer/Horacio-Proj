#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#include <string>
#include <ResourceManager.h>
#include <Singleton.h>
#include "Mesh.h"

class MeshManager : public ResourceManager, public Singleton<MeshManager> {
public:
	MeshManager();

	template <typename T> Mesh<T> *create_shape(const std::string &name, T data)
	{
		const std::pair<Resource *, bool> &resource = ResourceManager::create_ou_retrieve(name);
		Mesh<T> *mesh = dynamic_cast<Mesh<T> *>(resource.first);

		if (resource.second)
			mesh->data = data;

		if (!mesh->is_ready())
        {
            if (!mesh->is_loaded())
                mesh->load();
			mesh->ready();
        }
		return mesh;
	}

protected:
	Resource *create(const std::string &name, Resource::Handler handler) override;
};

#endif //_MESHMANAGER_H_
