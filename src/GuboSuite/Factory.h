#ifndef _GuboSuite_Factory_h_
#define _GuboSuite_Factory_h_

NAMESPACE_GUBO_BEGIN


class ShopFactory {
	typedef TopWindow* (*NewFn)();
	
public:
	struct Item : Moveable<Item> {
		NewFn newfn;
		String name;
		
		TopWindow* New() {return newfn();}
	};
	
	
	static VectorMap<String, Item>& Items() {static VectorMap<String, Item> items; return items;}
	
public:
	typedef ShopFactory CLASSNAME;
	ShopFactory() {}
	
	
	template <class T> static TopWindow* Create() {return new T();}
	
	template <class T> static void Register(String name) {
		Item& i = Items().GetAdd(name);
		i.name = name;
		i.newfn = &Create<T>;
	}
	
	static Item* Find(String name) {
		VectorMap<String, Item>& items = Items();
		int i = items.Find(name);
		if (i >= 0)
			return &items[i];
		return 0;
	}
	
};


NAMESPACE_GUBO_END

#endif
