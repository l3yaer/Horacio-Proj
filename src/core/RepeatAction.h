#ifndef _REPEATACTION_H_
#define _REPEATACTION_H_

#include "Action.h"

class RepeatAction : public Action
{
public:
	RepeatAction(Action * action);
	~RepeatAction();

	void update(float msec) override;
	void reset() override;
private:
	Action *action;
};

#endif //_REPEATACTION_H_
