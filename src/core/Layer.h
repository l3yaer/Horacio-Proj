#ifndef _LAYER_H_
#define _LAYER_H_

#include "SceneNode.h"
#include "Visitor.h"

class Layer : public SceneNode, public VisitableImpl<Layer, Layer, SceneNode> {
public:
	Layer(){};
	~Layer() = default;

	void render() override;

	void update(float msec) override;

	void clear_children();
};

#endif //_LAYER_H_
