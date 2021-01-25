#ifndef _RETEVISITOR_H_
#define _RETEVISITOR_H_

#include <Visitor.h>

class AlphaNode;
class TypeNode;
class SelectionNode;
class RootNode;
class AlphaMemoryNode;
class AggregateNode;
class NotNode;
class JoinNode;
class ExistsNode;
class ObjectInputAdapter;
class BindingNode;
class BetaMemoryNode;
class BetaNode;
class RuleNode;
class DummyNode;

#define RETE_VISITOR_CLASSES AlphaNode, TypeNode, SelectionNode, RootNode, AlphaMemoryNode, AggregateNode, NotNode, JoinNode, ExistsNode, ObjectInputAdapter, BindingNode, BetaMemoryNode, BetaNode, RuleNode, DummyNode

typedef Visitable<RETE_VISITOR_CLASSES> ReteVisitable;
typedef Visitor<RETE_VISITOR_CLASSES> ReteVisitor;

template <typename T>
using ReteVisitableImpl = VisitableImpl<T, RETE_VISITOR_CLASSES>;


#endif //_RETEVISITOR_H_
