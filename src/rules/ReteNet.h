#ifndef _RETENET_H_
#define _RETENET_H_

#include <unordered_map>
#include "BetaNode.h"
#include "Condition.h"
#include "AlphaNode.h"
#include "ProductionNode.h"
#include "TestNode.h"
#include "TokenFilterNode.h"
#include "DummyNode.h"

struct NetGroup
{
	ReteNodePtr parent;
	AlphaNodePtr alpha_memory;
	TestNodeVector tests;
	Condition condition;
	bool operator==(const NetGroup &rhs) const;
};

namespace std
{
	template<>
	struct hash<NetGroup>
	{
		size_t operator()(const NetGroup &obj) const
		{
			size_t ret = 2166136261;
			ret = (ret * 16777619) ^ hash<ReteNode>()(*obj.parent);
			ret = (ret * 16777619) ^ hash<AlphaNode>()(*obj.alpha_memory);
			ret = (ret * 16777619) ^ hash<TestNodeVector>()(obj.tests);
			ret = (ret * 16777619) ^ hash<Condition>()(obj.condition);
			return ret;
		}
	};
}

class ReteNet
{
private:
	ReteNodePtr build_join_node(ReteNodePtr parent, AlphaNodePtr alpha_mem, TestNodeVector tests, const Condition &condition);
	ReteNodePtr build_token_filter_node(ReteNodePtr parent, AlphaNodePtr alpha_mem, TestNodeVector tests, const Condition &condition);
	ReteNodePtr build_network_for_conditions(ReteNodePtr parent, const ConditionVector &conditions, ConditionVector high_conditions);
	AlphaNodePtr build_alpha_node(const Condition &condition);
	TestNodeVector tests_from_conditions(Condition condition, const ConditionVector &high_conditions);

	ReteNodePtr dummy_node;
	TokenFilterNode::Test token_filter_test_node;
	std::unordered_map<Condition, AlphaNodePtr> condition_to_alpha;
	std::unordered_map<NetGroup, ReteNodePtr> nodes;
	std::unordered_set<ProductionNodePtr> result_nodes;
public:
	ReteNet();
	void add(const ConditionVector &lhs, const ConditionVector &rhs);
	std::vector<ConditionVector> run();
	void clear();
	void add(const MemoryElement &wme);
	void add(const std::string &key, TokenFilterNode::Test::JudgeFunc judge_function);
};
#endif //_RETENET_H_
