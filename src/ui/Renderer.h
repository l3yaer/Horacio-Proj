#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <string>

class SceneNode;

class Program;

class Renderer {
public:
enum Programs
{
	TILE, ACTOR, VECTOR
};

public:
	unsigned int frame;

	Renderer();
	~Renderer() = default;

	void begin();
	void end();

	void setup(Renderer::Programs program);

	void draw_node(SceneNode &node);

	Program *get_current_program();
private:
	Program *current_program;
	std::string program_name(Renderer::Programs program) const;
};

#endif //_RENDERER_H_
