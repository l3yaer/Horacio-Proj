#ifndef _LAYER_H_
#define _LAYER_H_

#include "SceneNode.h"

namespace Map
{
class Layer : public SceneNode {
    public:
	Layer(){};
	~Layer() = default;

	void render() override
	{
	}
	void update(float msec) override;
};
} // namespace Map

#endif //_LAYER_H_
