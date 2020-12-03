#include "SceneNode.h"
#include <algorithm>

SceneNode::SceneNode() : parent(nullptr)
{}

SceneNode::~SceneNode()
{
}

void SceneNode::add_child(SceneNode *child)
{
	this->children.push_back(child);
	child->parent = this;
}

void SceneNode::update(float msec)
{
	if (parent != nullptr)
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

void SceneNode::remove_from_parent()
{
	if(parent != nullptr)
	{
		parent->children.erase(std::remove(parent->children.begin(),
										   parent->children.end(),
										   this),
							   parent->children.end());
		parent = nullptr;
	}
}
