#ifndef _ACTORVISITOR_H_
#define _ACTORVISITOR_H_

#include <Visitor.h>

class VectorArea;

class Area;

class SceneNode;

class Tile;

class GuiActor;

class Actor;

typedef Visitable<Actor, GuiActor, Area, VectorArea, Tile, SceneNode> VisitableNode;
typedef Visitor<Actor, GuiActor, Area, VectorArea, Tile, SceneNode> VisitorNode;

template<typename T>
using VisitableNodeImpl =  VisitableImpl<T, Actor, GuiActor, Area, VectorArea, Tile, SceneNode> ;

#endif //_ACTORVISITOR_H_
