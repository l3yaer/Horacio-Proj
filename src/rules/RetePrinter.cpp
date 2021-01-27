#include "Rete.h"

using namespace Rete;

std::ostream& operator<<(std::ostream &os, const WME &wme)
{
	os << "(";
	for(int i = 0; i < WME::Field::COUNT; ++i)
	{
		os << wme.get(i);
		if(i < (WME::Field::COUNT - 1))
			os << " ";
	}
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream &os, WME::Field field)
{
	switch(field)
	{
	case WME::Field::NONE:
		os << "none";
		break;
	case WME::Field::ID:
		os << "id";
		break;
	case WME::Field::ATTR:
		os << "attr";
		break;
	case WME::Field::VALUE:
		os << "value";
		break;
	case WME::Field::COUNT:
		os << "count";
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const AlphaMemory &memory)
{
	os << "(alpha memory: ";
	for (auto item : memory.items)
		os << (*item) << " ";
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream &os, const ConstTestNode &node)
{
	if(node.field == WME::Field::NONE)
		return os << "(const-test-dummy)";
	return os << "(const-test " << node.field << " =? " << node.value << ")";
}

std::ostream& operator<<(std::ostream &os, const Token &token)
{
	os << "(";
	os << *token.wme;
	for(Token *t = token.parent; t != nullptr; t = t->parent)
		os << "->" << *t;
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream &os, const BetaMemory &memory)
{
	os << "(beta-memory ";
	for (auto token: memory.items)
		os << *token << " ";
	os <<")";
	return os;
}

std::ostream& operator<<(std::ostream &os, const TestAtJoinNode &test)
{
	os << "(test-at-join ";
	os << test.first_field_arg << " ==  " <<
		test.index_second_token_arg << "[" << test.second_field_arg  << "]";
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream &os, const Rete::JoinNode &node)
{
	os << "(join";
	for (auto test : node.tests)
		os << test;
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream &os, const Rete::ProductionNode &node)
{
	os << "(production " << node.rhs << ")";
	return os;
}
