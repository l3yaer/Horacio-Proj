#ifndef _ACTION_H_
#define _ACTION_H_

class Action {
public:
	virtual ~Action() = default;

	virtual void update(float msec)
	{
		force_termination();
	}

	void force_termination()
	{
		done = true;
	}

	static bool did_finish(Action *action)
	{
		return action == nullptr ? true : action->done;
	}

	virtual void reset()
	{}

protected:
	bool done = false;
};

#endif //_ACTION_H_
