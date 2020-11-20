#ifndef _DEBUGSQUARE_H_
#define _DEBUGSQUARE_H_

#include <Movable.h>
#include "../Renderable.h"
#include "../Mesh.h"

class Program;
namespace Debug
{
class Square : public Movable, public Renderable {
private:
	Mesh<float> *mesh;
	Program *program;

public:
	Square();

	virtual ~Square();

	void render() override;
};
} // namespace Debug
#endif //_DEBUGSQUARE_H_
