#ifndef _MESH_H_
#define _MESH_H_
#include <Resource.h>

template <typename T> class Mesh : public Resource {
public:
	Mesh(ResourceCallback *creator, const std::string &name, Handler handler) : Resource(creator, name, handler)
	{
	}

	Mesh(ResourceCallback *creator, const std::string &name, Handler handler, T data)
			: data(data), Resource(creator, name, handler)
	{
	}

	virtual ~Mesh()
	{
	}

	virtual void unready() override{};
	virtual void clear_out() override{};
	virtual void load_in() override{};
	virtual void prepare() override{};

	virtual void draw(){};

	T data;
};

#endif //_MESH_H_
