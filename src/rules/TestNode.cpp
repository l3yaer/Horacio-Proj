#include "TestNode.h"
#include <memory>

TestNode::TestNode(Triple::Field first_arg_field, Triple::Field second_arg_field, size_t second_arg_cond_num)
	: first_arg_field(first_arg_field), second_arg_field(second_arg_field), second_arg_cond_num(second_arg_cond_num)
{
}

bool TestNode::operator==(const TestNode &rhs) const
{
	return first_arg_field == rhs.first_arg_field &&
		second_arg_field == rhs.second_arg_field &&
		second_arg_cond_num == rhs.second_arg_cond_num;
}

bool TestNode::test(const Token &token, const MemoryElement &wme) const
{
	return token.at(second_arg_cond_num).get(second_arg_field) == wme.get(first_arg_field);
}

TestNodeVector TestNode::generate(const Condition &condition, const ConditionVector &condition_higher)
{
	TestNodeVector result;
	std::unordered_map<std::string, std::pair<size_t, Triple::Field>> dict = generate_dict(condition_higher);
	for(auto name : {Triple::Field::ID, Triple::Field::ATTR, Triple::Field::VALUE})
	{
		std::string field = condition.get(name);
		if(Triple::is_param(field))
		{
			auto it = dict.find(field.substr(1));
			if(it != dict.end())
				result.emplace_back(TestNode(name, it->second.second, it->second.first));
		}
	}
	return result;
}


std::unordered_map<std::string, std::pair<size_t, Triple::Field>> TestNode::generate_dict(const ConditionVector &condition_higher)
{
	std::unordered_map<std::string, std::pair<size_t, Triple::Field>> dict;
	for(size_t i = 0; i < condition_higher.size(); ++i)
	{
		auto cond = condition_higher.at(i);
		if(cond.get_type() == Condition::Type::POSITIVE)
		{
			for(auto name : {Triple::Field::ID, Triple::Field::ATTR, Triple::Field::VALUE})
			{
				std::string field = cond.get(name);
				if(Triple::is_param(field))
					dict[field.substr(1)] = std::make_pair(i, name);
			}
		}
	}
	return dict;
}
