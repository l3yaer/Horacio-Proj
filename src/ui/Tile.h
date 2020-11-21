#ifndef _TILE_H_
#define _TILE_H_

#include <cstdint>
#include <string>
#include "Texture.h"
#include <Movable.h>
#include "Renderable.h"
#include "Mesh.h"
#include "SceneNode.h"
#include "NodeVisitor.h"

class Tile : public SceneNode, public VisitableNodeImpl<Tile>  {
public:
	uint16_t zoom;
	int x;
	int y;
	Texture *texture;
	Mesh<float> *mesh;

	Tile(uint16_t zoom, int x, int y, Texture *texture);

	virtual ~Tile();

	std::string get_filename(const std::string &ext = "") const;

	Coordinate coordinate();

	void update(float msec) override;

	void render() override;
};

#endif
