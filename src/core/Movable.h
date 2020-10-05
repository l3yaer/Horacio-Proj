#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include <cstdint>
#include <string>
#include "types.h"

class Movable {
    protected:
	AffineMatrix calculate_matrix(const Position &position,
				      const Scale &scale,
				      const Rotation &rotation) const;

    public:
	Position position = Position(0.0f);
	Scale scale = Scale(1.0f);
	Rotation rotation = Rotation(0.0f);

	virtual AffineMatrix matrix() const;
};

#endif //_MOVABLE_H_
