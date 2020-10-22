#ifndef _DEBUGSQUARE_H_
#define _DEBUGSQUARE_H_

#include <Movable.h>
#include "../Renderable.h"

class Mesh;

class Program;
namespace Debug
{
class Square : public Movable, public Renderable {
private:
	Mesh *mesh;
	Program *program;

public:
	Square();

	virtual ~Square();

	void render() override;
};
} // namespace Debug
#endif //_DEBUGSQUARE_H_
