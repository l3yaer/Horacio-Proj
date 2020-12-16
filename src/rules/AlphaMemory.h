#ifndef _ALPHAMEMORY_H_
#define _ALPHAMEMORY_H_

#include <vector>
#include "ObjectSink.h"
#include "Fact.h"

class AlphaMemory : public Memory<Fact*>
{
public:
	std::vector<Fact *> facts;

	std::vector<Fact *> data() const override;
	void add(Fact* item) override;
	void remove(Fact* item) override;
	bool contains(Fact* item) override;
};

#endif //_ALPHAMEMORY_H_
