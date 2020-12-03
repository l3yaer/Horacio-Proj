#ifndef _ACTORVISITOR_H_
#define _ACTORVISITOR_H_

#include <Visitor.h>

class VectorArea;

class Area;

class SceneNode;

class Tile;

class GuiActor;

class Actor;

class Map;

class GuiMap;

typedef Visitable<Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, SceneNode> VisitableNode;
typedef Visitor<Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, SceneNode> VisitorNode;

template<typename T>
using VisitableNodeImpl =  VisitableImpl<T, Actor, GuiActor, Area, VectorArea, Tile, GuiMap, Map, SceneNode>;

#endif //_ACTORVISITOR_H_
