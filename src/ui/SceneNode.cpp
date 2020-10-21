#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = nullptr;
}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); ++i)
		delete children[i];
}

void SceneNode::add_child(SceneNode *child)
{
	this->children.push_back(child);
	child->parent = this;
}

void SceneNode::update(float msec)
{
	if (parent)
		world_transform = parent->world_transform * Movable::matrix();
	else
		world_transform = Movable::matrix();

	for (SceneNode *s : children) {
		s->update(msec);
	}
}

AffineMatrix SceneNode::matrix() const
{
	return world_transform;
}
