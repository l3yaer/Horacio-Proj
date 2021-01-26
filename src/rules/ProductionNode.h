#ifndef _PRODUCTIONNODE_H_
#define _PRODUCTIONNODE_H_

#include <memory>
#include "ReteNode.h"
#include "Condition.h"

class ProductionNode : public ReteNode
{
public:
	ProductionNode(ReteNodePtr left_parent, const ConditionVector &conds, const ConditionVector &info_getter);

	const ConditionVector &get_conds();
	virtual TokenVector &get_output() override;
	virtual void clear() override;
	std::vector<ConditionVector> get_output_infos();

private:
	using PositionIndexer = std::pair<size_t, Triple::Field>;

	void build_indexer();
	ConditionVector get_output_info(const Token &token) const;

	ReteNodePtr left_parent;
	ConditionVector conds;
	ConditionVector info_getter;
	std::vector<ConditionVector> output_info;
	std::vector<std::pair<PositionIndexer, PositionIndexer>> info_getter_indexer;
};

using ProductionNodePtr = std::shared_ptr<ProductionNode>;

namespace std
{
	template<>
	struct hash<ProductionNode>
	{
		size_t operator()(const ProductionNode &node) const
		{
			return hash<size_t>()(node.serial_number);
		}
	};

	template<>
	struct hash<ProductionNodePtr>
	{
		size_t operator()(const ProductionNodePtr &node) const
		{
			return hash<ProductionNode>()(*node);
		}
	};
}

#endif //_PRODUCTIONNODE_H_
