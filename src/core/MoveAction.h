#ifndef _MOVEACTION_H_
#define _MOVEACTION_H_

#include "Action.h"
#include "Actor.h"

class MoveAction : public Action {
public:
	MoveAction(Actor *actor, Position position, float duration);

	virtual void update(float msec) override;
	void reset() override;
protected:
	Actor *actor;
	Position target_position;
	Position starting_position;
	float elapsed_time;
	float duration;
};

class RelativeMoveAction : public MoveAction {
public:
	RelativeMoveAction(Actor *actor, Position position, float duration);

	void update(float msec) override;
private:
	Position relative_position;
};

#endif // _MOVEACTION_H_
