#ifndef _RETENODE_H_
#define _RETENODE_H_

#include <memory>
#include "Node.h"
#include "Token.h"

class ReteNode : public Node<TokenVector>
{
public:
	ReteNode(bool ready_for_output);
protected:
	bool ready_for_output;
};

using ReteNodePtr = std::shared_ptr<ReteNode>;

namespace std
{
	template<>
	struct hash<ReteNode> {
		size_t operator()(const ReteNode &node) const
		{
			return hash<size_t>()(node.serial_number);
		}
	};
}

#endif //_RETENODE_H_
