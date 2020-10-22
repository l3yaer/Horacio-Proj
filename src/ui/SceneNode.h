#ifndef _SCENENODE_H_
#define _SCENENODE_H_

#include <vector>
#include <types.h>
#include <Movable.h>

class Renderer;

class SceneNode : public Movable {
public:
	SceneNode();
	virtual ~SceneNode();

	void add_child(SceneNode *child);

	virtual void update(float msec);
	virtual void render() = 0;

	AffineMatrix matrix() const override;

protected:
	SceneNode *parent;
	std::vector<SceneNode *> children;
	AffineMatrix world_transform;
};

#endif //_SCENENODE_H_
