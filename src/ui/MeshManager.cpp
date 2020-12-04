#include "MeshManager.h"
#include "Mesh.h"
#include "Square.h"
#include "RegularPolygon.h"

IMPLEMENT_SINGLETON(MeshManager)

MeshManager::MeshManager() : Singleton<MeshManager>(), ResourceManager()
{
}

Resource *MeshManager::create(const std::string &name, Resource::Handler handler)
{
	if(name.rfind("square", 0) == 0)
		return new Shape::Square(this, name, get_next_handler());
	if(name.rfind("rpoly", 0) == 0)
		return new Shape::RegularPolygon(this, name, get_next_handler());
	return new Mesh<int>(this, name, get_next_handler());
}
