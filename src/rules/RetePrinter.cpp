#include "Rete.h"

using namespace Rete;

std::ostream &Rete::operator<<(std::ostream &os, const WME &wme)
{
	os << "(";
	for (int i = 0; i < WME::Field::COUNT; ++i) {
		os << wme.get(i);
		if (i < (WME::Field::COUNT - 1))
			os << " ";
	}
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, WME::Field field)
{
	switch (field) {
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

std::ostream &Rete::operator<<(std::ostream &os, const AlphaMemory &memory)
{
	os << "(alpha memory: ";
	for (auto item : memory.items)
		os << (*item->wme) << " ";
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const ConstTestNode &node)
{
	if (node.field == WME::Field::NONE)
		return os << "(const-test-dummy)";
	return os << "(const-test " << node.field << " =? " << node.value << ")";
}

std::ostream &Rete::operator<<(std::ostream &os, const Token &token)
{
	os << "(";
	os << *token.wme;
	for (Token *t = token.parent; t != nullptr; t = t->parent)
		os << "->" << *t;
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const BetaMemory &memory)
{
	os << "(beta-memory ";
	for (auto &token : memory.items)
		os << *token << " ";
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const TestAtJoinNode &test)
{
	os << "(test-at-join ";
	os << test.first_field_arg << " ==  " << test.index_second_token_arg << "[" << test.second_field_arg << "]";
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const JoinNode &node)
{
	os << "(join ";
	for (auto test : node.tests)
		os << test;
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const ProductionNode &node)
{
	os << "(production " << node.rhs << " " << std::endl;
	for (auto &item : node.items)
		os << "\t" << *item << std::endl;
	os << ")";
	return os;
}

std::ostream &Rete::operator<<(std::ostream &os, const Net &net)
{
	os << "(net " << std::endl;

	os << "\t(alpha " << std::endl;
	for (auto &alpha : net.alpha_memories)
		os << "\t\t" << *(alpha.get()) << std::endl;
	os << ")";

	os << "\t(wme " << std::endl;
	for (auto &wme : net.working_memory)
		os << "\t\t" << *(wme.get()) << std::endl;
	os << ")";

	os << "\t(beta " << std::endl;
	for (auto &beta : net.beta_memories)
		os << "\t\t" << *(beta.get()) << std::endl;
	os << ")";

	os << "\t(joins " << std::endl;
	for (auto &join : net.join_nodes)
		os << "\t\t" << *(join.get()) << std::endl;
	os << ")";

	os << "\t(production " << std::endl;
	for (auto &prod : net.production_nodes)
		os << "\t\t" << *(prod.get()) << std::endl;
	os << ")";

	os << "\t(const tests " << std::endl;
	for (auto &tests : net.const_test_nodes)
		os << "\t\t" << *(tests.get()) << std::endl;
	os << ")";

	os << ")";
	return os;
}
