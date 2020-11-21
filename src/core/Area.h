#ifndef _AREA_H_
#define _AREA_H_

#include "Actor.h"

class Area : public Actor, public VisitableImpl<Area, Actor, Area, SceneNode> {
public:
	Area(const std::string &name, Coordinate coordinate, Scale scale);
};

#endif //_AREA_H_
