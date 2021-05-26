#ifndef _RETE_H_
#define _RETE_H_

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "StringManip.h"

namespace Rete
{
class JoinNode;
class AlphaMemory;
class Token;
class BetaMemory;
struct AlphaMemoryItem;

class WME {
public:
	enum Field { NONE = -1, ID = 0, ATTR = 1, VALUE = 2, COUNT = 3 };

	std::string id;
	std::string attr;
	std::string value;
	std::vector<AlphaMemoryItem *> alpha_memories;
	std::vector<Token *> tokens;

	WME(const std::string &id, const std::string &attr, const std::string &value) : id(id), attr(attr), value(value)
	{
	}

	std::string get(int i) const
	{
		switch (i) {
		case Field::ID:
			return id;
		case Field::ATTR:
			return attr;
		case Field::VALUE:
			return value;
		}
		return "";
	}
};

class AlphaMemory {
public:
	std::vector<AlphaMemoryItem *> items;
	std::vector<JoinNode *> successors;

	void activate(WME *wme);
};

struct AlphaMemoryItem {
	WME *wme;
	AlphaMemory *alpha_memory;
	AlphaMemoryItem *next;
	AlphaMemoryItem *previous;
};

class ConstTestNode {
public:
	WME::Field field;
	std::string value;
	AlphaMemory *output;
	ConstTestNode *parent;
	std::vector<ConstTestNode *> children;

	ConstTestNode(WME::Field field, const std::string &value, AlphaMemory *output);
	static ConstTestNode *dummy();
	bool activate(WME *wme);
};

class Token {
public:
	Token *parent;
	int token_index;
	WME *wme;
	std::vector<Token *> children;
	BetaMemory *node;

	Token(BetaMemory *node, WME *wme, Token *parent);
	WME *index(int index) const;
	void remove_child(Token *token);
};

class BetaMemory {
public:
	JoinNode *parent;
	std::list<std::unique_ptr<Token> > items;
	std::vector<JoinNode *> children;

	virtual void join_activation(Token *token, WME *wme);
	void update_new();
	void remove(Token *token);
};

struct TestAtJoinNode {
	WME::Field first_field_arg;
	WME::Field second_field_arg;
	int index_second_token_arg;

	bool operator==(const TestAtJoinNode &rhs) const;
};

class JoinNode {
public:
	AlphaMemory *alpha_src;
	BetaMemory *beta_src;
	std::vector<BetaMemory *> children;
	std::vector<TestAtJoinNode> tests;

	JoinNode();
	void alpha_activation(WME *wme);
	void beta_activation(Token *token);
	bool test(Token *token, WME *wme) const;
};

class ProductionNode : public BetaMemory {
public:
	std::string rhs;

	void join_activation(Token *token, WME *wme) override;
};

struct CField {
	enum Type { CONSTANT, VARIABLE };
	Type type;
	std::string value;
	static CField var(const std::string &value);
	static CField cons(const std::string &value);
};

class Condition {
public:
	CField fields[WME::Field::COUNT];
	Condition(CField id, CField attr, CField value);
	Condition(const std::string &id, const std::string &attr, const std::string &value);

	bool is_satisfied(const WME *wme) const;
};

class Net {
public:
	Net();
	void add(WME *wme);
	void remove(WME *wme);
	ProductionNode *add(const std::vector<Condition> &conditions, const std::string &rhs);
	void remove(ProductionNode *node);

	friend std::ostream &operator<<(std::ostream &os, const Net &net);

private:
	BetaMemory *build_beta_memory(JoinNode *parent);
	JoinNode *build_join_node(BetaMemory *beta_memory, AlphaMemory *alpha_memory,
							  const std::vector<TestAtJoinNode> &tests);
	ConstTestNode *build_const_node(ConstTestNode *parent, WME::Field field, const std::string &symbol);
	AlphaMemory *build_alpha(const Condition &condition);

	void delete_token(Token *token);
	void delete_node(JoinNode *node);
	void delete_node(BetaMemory *node);
	void delete_node(AlphaMemory *node);

	template <typename T> void remove_node_from_list(std::vector<std::unique_ptr<T> > &vector, T *node)
	{
		vector.erase(std::remove_if(vector.begin(), vector.end(),
									[&](std::unique_ptr<T> const &n) { return n.get() == node; }),
					 vector.end());
	}

	void lookup_conditions(const std::vector<Condition> &conditions, const std::string value, int *index, int *field);
	std::vector<TestAtJoinNode> get_tests(const Condition &condition, const std::vector<Condition> &prev_conditions);

	ConstTestNode *dummy;
	std::vector<std::unique_ptr<AlphaMemory> > alpha_memories;
	std::vector<std::unique_ptr<BetaMemory> > beta_memories;
	std::vector<std::unique_ptr<ConstTestNode> > const_test_nodes;
	std::vector<std::unique_ptr<JoinNode> > join_nodes;
	std::vector<std::unique_ptr<ProductionNode> > production_nodes;
	std::vector<std::unique_ptr<WME> > working_memory;
};

std::ostream &operator<<(std::ostream &os, const BetaMemory &memory);
std::ostream &operator<<(std::ostream &os, const Token &token);
std::ostream &operator<<(std::ostream &os, const ConstTestNode &node);
std::ostream &operator<<(std::ostream &os, const WME &wme);
std::ostream &operator<<(std::ostream &os, WME::Field field);
std::ostream &operator<<(std::ostream &os, const AlphaMemory &memory);
std::ostream &operator<<(std::ostream &os, const TestAtJoinNode &test);
std::ostream &operator<<(std::ostream &os, const JoinNode &node);
std::ostream &operator<<(std::ostream &os, const ProductionNode &node);
std::ostream &operator<<(std::ostream &os, const Net &net);
} // namespace Rete

#endif //_RETE_H_
