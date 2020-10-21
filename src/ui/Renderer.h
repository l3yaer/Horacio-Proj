#ifndef _RENDERER_H_
#define _RENDERER_H_

class SceneNode;

class Program;

class Renderer {
    public:
	unsigned int frame;

	Renderer();
	~Renderer() = default;

	void begin();
	void end();

	void setup_map();
	void draw_node(SceneNode *);

    private:
	Program *program;
};

#endif //_RENDERER_H_
