#include "RepeatAction.h"

RepeatAction::RepeatAction(Action * action)
	: action(action)
{}

RepeatAction::~RepeatAction()
{
	delete action;
}

void RepeatAction::update(float msec)
{
	action->update(msec);
	if(Action::did_finish(action))
		action->reset();
}

void RepeatAction::reset()
{
	action->reset();
}
