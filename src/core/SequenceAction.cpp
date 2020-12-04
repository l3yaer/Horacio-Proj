#include "SequenceAction.h"
#include "LogManager.h"

SequenceAction::SequenceAction(std::vector<Action *> actions)
	: actions(actions)
{
	current_action = this->actions.begin();
}

SequenceAction::~SequenceAction()
{
	for(auto action : actions)
		delete action;

}

void SequenceAction::update(float msec)
{
	(*current_action)->update(msec);

	if(Action::did_finish((*current_action)))
	{
		++current_action;

		if(current_action == actions.end())
			done = true;
	}
}

void SequenceAction::reset()
{
	done = false;
	current_action = actions.begin();
	for(auto action : actions)
		action->reset();
}
