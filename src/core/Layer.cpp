#include "Layer.h"
#include <iostream>

void Layer::update(float msec)
{
	SceneNode::update(msec);
}

void Layer::render()
{
}

void Layer::clear_children()
{
	this->children.clear();
}
