#ifndef _ALPHANODE_H_
#define _ALPHANODE_H_

#include <memory>
#include "MemoryElement.h"
#include "Node.h"

class AlphaNode : public Node<MemoryElementVector>
{
public:
	void add(const MemoryElement &wme);
	const MemoryElementVector &get_output() override;
	void clear() override;
};

using AlphaNodePtr = std::shared_ptr<AlphaNode>;

namespace std
{
	template<>
	struct hash<AlphaNode>
	{
		size_t operator()(const AlphaNode &mem) const
		{
			return hash<size_t>()(mem.serial_number);
		}
	};
}

#endif //_ALPHANODE_H_
