#ifndef _Physics_TNode_h_
#define _Physics_TNode_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
struct NodeT : FysObject {
	using Node = typename Fys::Node;
	using Object = typename Fys::Object;
	using Joint = typename Fys::Joint;
	using Space = typename Fys::Space;
	using System = typename Fys::System;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	
	
protected:
	Node* owner = NULL;
	Vector<Node*> nodes;
	
public:
	NodeT() {}
	virtual ~NodeT() {}
	
	virtual void Attach(Node& node) {
		node.portal = this;
		nodes.Add(&node);
		node.OnAttach();
	}
	
	virtual void Detach(Node& node) {
		for(int i = 0; i < nodes.GetCount(); i++) {
			if (nodes[i] == &node) {
				node.OnDetach();
				node.portal = NULL;
				nodes.Remove(i);
				break;
			}
		}
	}
	
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual String ToString() {return String(Fys::ID) + "Node";}
	
	System& GetWorld();
	Space& GetSpace();
	NativeWorld& GetNativeWorld();
	NativeSpace& GetNativeWorldSpace();
	
};


NAMESPACE_TOPSIDE_END

#endif
