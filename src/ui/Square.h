#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Mesh.h"

namespace Shape
{
class Square : public Mesh<float> {
public:
	Square(ResourceCallback *creator, const std::string &name, Handler handler, float data);

	Square(ResourceCallback *creator, const std::string &name, Handler handler);

	virtual ~Square();

	void draw() override;

	void unready() override;

	void clear_out() override;

	void load_in() override;

	size_t check_size() override;
	void prepare() override;

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};
} // namespace Shape

#endif //_SQUARE_H_
