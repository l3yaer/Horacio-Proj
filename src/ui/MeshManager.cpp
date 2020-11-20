#include "MeshManager.h"
#include "Mesh.h"
#include "Square.h"

template <> MeshManager *Singleton<MeshManager>::_instance = nullptr;

MeshManager::MeshManager() : Singleton<MeshManager>(), ResourceManager()
{
}

Resource *MeshManager::create(const std::string &name, Resource::Handler handler)
{
	if(name == "square")
		return new Shape::Square(this, name, get_next_handler());
	return new Mesh<int>(this, name, get_next_handler());
}
