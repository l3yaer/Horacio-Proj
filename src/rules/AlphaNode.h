#ifndef _ALPHANODE_H_
#define _ALPHANODE_H_

#include <vector>
#include "Template.h"
#include "AlphaMemoryNode.h"
#include "ReteVisitor.h"

class AlphaNode : public ObjectSink<std::vector<Fact *>>, public ReteVisitableImpl<AlphaNode>
{
public:
	AlphaMemoryNode *memory_node;
	std::vector<AlphaNode *> children;

	virtual bool is_satisfied(Fact *fact, WorkingMemory *memory) const;


	virtual void propagate_assert(std::vector<Fact*> objects, WorkingMemory *memory) override;
	virtual void propagate_update(std::vector<Fact*> objects, WorkingMemory *memory) override;
	virtual void propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory) override;
protected:
	void internal_propagate_update(std::vector<Fact*> objects, WorkingMemory *memory);
	void internal_propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory);
};

class SelectionNode : public AlphaNode, public ReteVisitableImpl<SelectionNode>
{
public:
	bool is_satisfied(Fact *facts, WorkingMemory *memory) const override;
};

class TypeNode : public AlphaNode, public ReteVisitableImpl<TypeNode>
{
public:
	TypeNode(Template *type);

	bool is_satisfied(Fact *facts, WorkingMemory *memory) const override;
	void propagate_update(std::vector<Fact*> objects, WorkingMemory *memory) override;
	void propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory) override;
private:
	Template *type;
};



#endif //_ALPHANODE_H_
