#include "MoveAction.h"

MoveAction::MoveAction(Actor *actor, Position position, float duration)
		: actor(actor), target_position(position), starting_position({ 0 }), elapsed_time(0), duration(duration)
{
}

void MoveAction::update(float msec)
{
	if (elapsed_time == 0.f)
		starting_position = actor->position;

	elapsed_time = fmin(duration, elapsed_time + msec / 1000.0f);
	float movement_percentage = elapsed_time / duration;
	Position position = glm::mix(starting_position, target_position, movement_percentage);
	actor->position = position;

	if (duration <= elapsed_time)
		done = true;
}

void MoveAction::reset()
{
	done = false;
	elapsed_time = 0.f;
}

RelativeMoveAction::RelativeMoveAction(Actor *actor, Position position, float duration)
		: MoveAction(actor, position, duration), relative_position(position)
{
}

void RelativeMoveAction::update(float msec)
{
	if (elapsed_time == 0.f)
		target_position = actor->position + relative_position;

	MoveAction::update(msec);
}
