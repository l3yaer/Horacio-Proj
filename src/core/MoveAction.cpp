#include "MoveAction.h"

MoveAction::MoveAction(Actor *actor, Position position, float duration)
	: actor(actor), target_position(position), starting_position(actor->position),
	  elapsed_time(0), duration(duration)
{}

void MoveAction::update(float msec)
{
	elapsed_time = fmin(duration, elapsed_time + msec / 1000.0f);
	float movement_percentage = elapsed_time / duration;
	Position position = glm::mix(starting_position, target_position, movement_percentage);
	actor->position = position;

	if(duration <= elapsed_time)
		done = true;
}
