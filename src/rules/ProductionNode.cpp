#include "ProductionNode.h"
#include <unordered_map>

ProductionNode::ProductionNode(ReteNodePtr left_parent, const ConditionVector &conds, const ConditionVector &info_getter) : ReteNode(false), left_parent(left_parent), conds(conds), info_getter(info_getter)
{
	build_indexer();
}

const ConditionVector &ProductionNode::get_conds()
{
	return conds;
}

TokenVector &ProductionNode::get_output()
{
//	if(!ready_for_output)
//	{
	std::cout << "Production output" << std::endl;
	output.clear();

	std::cout << "Left parent: ";
	output = left_parent->get_output();
	ready_for_output = true;
//	}

	return output;
}

void ProductionNode::clear()
{
	if(ready_for_output)
	{
		ready_for_output = false;
		output.clear();
		output_info.clear();
		left_parent->clear();
	}
}

std::vector<ConditionVector> ProductionNode::get_output_infos()
{
//	if(!ready_for_output)
//	{
	get_output();
	output_info.clear();
	output_info.reserve(output.size());
	for (auto token : output)
		output_info.push_back(get_output_info(token));
//	}
	return output_info;
}

void ProductionNode::build_indexer()
{
	std::unordered_map<std::string, std::vector<PositionIndexer>> dict;
	for(size_t i = 0; i < info_getter.size(); ++i)
		for (auto field : {Triple::Field::ID, Triple::Field::ATTR, Triple::Field::VALUE}) {
			std::string field_string = info_getter.at(i).get(field);
			if(Triple::is_param(field_string))
				dict[field_string].emplace_back(std::make_pair(i, field));
		}
	for(size_t i = 0; i < conds.size(); ++i)
		for (auto field : {Triple::Field::ID, Triple::Field::ATTR, Triple::Field::VALUE})
		{
			std::string field_string = conds.at(i).get(field);
			auto it = dict.find(field_string);
			if(it != dict.end())
			{
				for (auto pos_info_getter : it->second) {
					info_getter_indexer.emplace_back(std::make_pair(i, field), pos_info_getter);
				}
				dict.erase(it);
			}
		}
}

ConditionVector ProductionNode::get_output_info(const Token &token) const
{
	ConditionVector ret = info_getter;
	for (auto pair : info_getter_indexer) {
		ret.at(pair.second.first)
			.set(pair.second.second,
				 token.at(pair.first.first).get(pair.first.second));
	}
	return ret;
}
