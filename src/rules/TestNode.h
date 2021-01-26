#ifndef _TESTNODE_H_
#define _TESTNODE_H_

#include <unordered_map>
#include <unordered_set>
#include "Token.h"
#include "MemoryElement.h"
#include "Triple.h"
#include "Condition.h"

class TestNode
{
public:
	TestNode(Triple::Field first_arg_field, Triple::Field second_arg_field, size_t second_arg_cond_num);
	bool operator==(const TestNode &rhs) const;
	bool test(const Token &token, const MemoryElement &wme) const;
	static std::vector<TestNode> generate(const Condition &condition, const ConditionVector &condition_higher);

	Triple::Field first_arg_field;
	Triple::Field second_arg_field;
	size_t second_arg_cond_num;
private:
	static std::unordered_map<std::string, std::pair<size_t, Triple::Field>> generate_dict(const ConditionVector &condition_higher);
};


using TestNodeVector = std::vector<TestNode>;

namespace std {
	template<>
	struct hash<TestNode> {
		size_t operator() (const TestNode& node) const {
			size_t ret = 2166136261;
			ret = (ret * 16777619) ^ hash<int>()(node.first_arg_field);
			ret = (ret * 16777619) ^ hash<int>()(node.second_arg_field);
			ret = (ret * 16777619) ^ hash<size_t>()(node.second_arg_cond_num);
			return ret;
		}
	};

	template<>
	struct hash<TestNodeVector> {
		size_t operator() (const TestNodeVector& nodes) const {
			size_t ret = 2166136261;
			for (auto&& node : nodes)
				ret = (ret * 16777619) ^ hash<TestNode>()(node);
			return ret;
		}
	};
}
#endif //_TESTNODE_H_
