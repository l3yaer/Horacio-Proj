#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#include <string>
#include <ResourceManager.h>
#include <Singleton.h>
#include <JobManager.h>
#include "Mesh.h"

template <typename T> void mesh_manager_load_mesh(void *data)
{
	Mesh<T> *mesh = reinterpret_cast<Mesh<T> *>(data);
	if (mesh == nullptr)
		return;

	if (!mesh->is_loaded())
		mesh->load();
	mesh->ready();
}

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
			JobManager::instance().add_job(mesh_manager_load_mesh<T>, mesh, JobManager::Queue::MAIN);

		return mesh;
	}

protected:
	Resource *create(const std::string &name, Resource::Handler handler) override;
};

#endif //_MESHMANAGER_H_
