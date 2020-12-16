#ifndef _ALPHANODE_H_
#define _ALPHANODE_H_

#include "Template.h"
#include "AlphaMemoryNode.h"

class AlphaNode : public FactSink
{
public:
	AlphaMemoryNode *memory_node;
	std::vector<AlphaNode *> children;

	virtual bool is_satisfied(Fact *fact, Memory<Fact *> memory) const;


	virtual void propagate_assert(std::vector<Fact*> objects, Memory<Fact*> memory) override;
	virtual void propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory) override;
	virtual void propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory) override;
protected:
	void internal_propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory);
	void internal_propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory);
};

class SelectionNode : public AlphaNode
{
public:
	bool is_satisfied(Fact *facts, Memory<Fact *> memory) const override;
};

class TypeNode : public AlphaNode
{
public:
	TypeNode(Template *type);

	bool is_satisfied(Fact *facts, Memory<Fact *> memory) const override;
	void propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory) override;
	void propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory) override;
private:
	Template *type;
};



#endif //_ALPHANODE_H_
