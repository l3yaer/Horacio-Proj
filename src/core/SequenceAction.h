#ifndef _SEQUENCEACTION_H_
#define _SEQUENCEACTION_H_

#include "Action.h"
#include <vector>

class SequenceAction : public Action
{
public:
	SequenceAction(std::vector<Action *> actions);
	~SequenceAction();

	void update(float msec) override;
	void reset() override;
private:
	std::vector<Action *>actions;
	std::vector<Action *>::iterator current_action;
};

#endif //_SEQUENCEACTION_H_
