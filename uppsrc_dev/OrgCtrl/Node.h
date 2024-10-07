#ifndef _OrgCtrl_Node_h_
#define _OrgCtrl_Node_h_


BEGIN_TEXTLIB_NAMESPACE


class NodeFactory {
	typedef NodeCtrlBase* (*CtrlFn)();
	typedef NodeViewBase* (*ViewFn)();
	
	struct Factory : Moveable<Factory> {
		String name;
		NodeType type;
		CtrlFn ctrl = 0;
		ViewFn view = 0;
		Image icon;
	};
	
	
public:
	typedef NodeFactory CLASSNAME;
	NodeFactory();
	
	static VectorMap<int, Vector<Factory>>& GetFactories() {static VectorMap<int, Vector<Factory>> m; return m;}
	
	template <class CTRL, class VIEW> static void Register(String name, NodeType type, Image icon=Image()) {
		Factory& f = GetFactories().GetAdd(type).Add();
		f.name = name;
		f.type = type;
		f.icon = icon;
		f.ctrl = &NewCtrl<CTRL>;
		f.view = &NewView<VIEW>;
	}
	
	template <class CTRL> static NodeCtrlBase* NewCtrl() {
		return new CTRL;
	}
	
	template <class VIEW> static NodeViewBase* NewView() {
		return new VIEW;
	}
	
};

Image GetNodeImage(NodeType i);


END_TEXTLIB_NAMESPACE

#endif
