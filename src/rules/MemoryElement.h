#ifndef _MEMORYELEMENT_H_
#define _MEMORYELEMENT_H_

#include "Triple.h"

class MemoryElement : public Triple
{
public:

	template<typename Id, typename Attr, typename Value>
	MemoryElement(const Id &id, const Attr &attr, const Value &value)
		: Triple(id, attr, value)
	{
	}
};

using MemoryElementVector = std::vector<MemoryElement>;

#endif //_MEMORYELEMENT_H_
