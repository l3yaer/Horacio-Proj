#ifndef _NODEVISITOR_H_
#define _NODEVISITOR_H_

#include <Visitor.h>

class VectorArea;

class Area;

class SceneNode;

class Tile;

class GuiActor;

class Actor;

class Map;

class GuiMap;

class Layer;

typedef Visitable<Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, Layer, SceneNode> VisitableNode;
typedef Visitor<Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, Layer, SceneNode> VisitorNode;

template<typename T>
using VisitableNodeImpl =  VisitableImpl<T, Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, Layer, SceneNode>;

#endif //_NODEVISITOR_H_
