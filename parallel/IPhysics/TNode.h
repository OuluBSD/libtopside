#ifndef _IPhysics_TNode_h_
#define _IPhysics_TNode_h_

NAMESPACE_PARALLEL_BEGIN

template <class Fys> struct SystemT;


template <class Fys>
struct NodeT : FysNode {
	using Base = NodeT<Fys>;
	using SystemT = Parallel::SystemT<Fys>;
	using Node = typename Fys::Node;
	using Object = typename Fys::Object;
	using Joint = typename Fys::Joint;
	using Space = typename Fys::Space;
	using System = typename Fys::System;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	
	
protected:
	NodeT* owner = NULL;
	Vector<NodeT*> nodes;
	
public:
	RTTI_DECL1(NodeT, FysNode);
	NodeT() {}
	virtual ~NodeT() {}
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(FysNode)}
	
	virtual void Attach(NodeT& node) {
		node.owner = this;
		nodes.Add(&node);
		node.OnAttach();
	}
	
	virtual void Detach(NodeT& node) {
		for(int i = 0; i < nodes.GetCount(); i++) {
			if (nodes[i] == &node) {
				node.OnDetach();
				node.owner = NULL;
				nodes.Remove(i);
				break;
			}
		}
	}
	
	String ToString() const override {return Fys::Id() + "Node";}
	
	System* GetSystem();
	SystemT* GetSystemT();
	Space* GetSpace();
	NativeWorld& GetNativeWorld();
	NativeSpace& GetNativeWorldSpace(bool dbg_chk=true);
	
};


NAMESPACE_PARALLEL_END

#endif
