#ifndef _REGULARPOLYGON_H_
#define _REGULARPOLYGON_H_

#include "Mesh.h"

namespace Shape
{
struct RegularPolygonData {
	float radius;
	int sides;
};

class RegularPolygon : public Mesh<RegularPolygonData> {
public:
	RegularPolygon(ResourceCallback *creator, const std::string &name, Handler handler, RegularPolygonData data);

	RegularPolygon(ResourceCallback *creator, const std::string &name, Handler handler);

	virtual ~RegularPolygon();

	void draw() override;

	void unready() override;

	void clear() override;

	void load_in() override;

	size_t check_size() override;

	void prepare() override;

	float opacity;

	Color color;

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};
} // namespace Shape

#endif //_REGULARPOLYGON_H_
