#ifndef _LayoutCtrl_Object_h_
#define _LayoutCtrl_Object_h_


NAMESPACE_LAYOUT_BEGIN

class Object :
	RTTIBase
{
	Array<Object> sub;
	Object* parent = NULL;
	
public:
	RTTI_DECL0(Object)
	typedef const Object ConstObject;
	
	Object();
	virtual ~Object() {}
	
	template <class T> bool Is() {return CastPtr<T>(this);}
	template <class T> T* As() {return CastPtr<T>(this);}
	template <class T> const T* As() const {return CastConstPtr<T>(this);}
	
	void Clear() {sub.Clear();}
	Object& Add() {Object& o = sub.Add(); o.parent = this; return o;}
	Object& Add(Object* o) {ASSERT(!o->GetParent()); o->parent = this; return sub.Add(o);}
	Object& Insert(int i, Object* o) {ASSERT(!o->GetParent()); o->parent = this; return sub.Insert(i, o);}
	Object* GetParent() const {return parent;}
	ConstObject* GetTopParent() const {ConstObject* o = this; while (o->GetParent()) o = o->GetParent(); return o;}
	Object* GetTopParent() {Object* o = this; while (o->GetParent()) o = o->GetParent(); return o;}
	const Object& At(int i) const {return sub[i];}
	Object& At(int i) {return sub[i];}
	int GetCount() const {return sub.GetCount();}
	void Remove(int i, int count=1) {sub.Remove(i, count);}
	void Remove(Object* o) {
		for(int i = 0; i < sub.GetCount(); i++)
			if (&sub[i] == o)
				{sub.Remove(i); i--;}
	}
	template <class T> T* Find() {
		for(int i = 0; i < sub.GetCount(); i++) {
			T* o = CastPtr<T>(&sub[i]);
			if (o) return o;
		}
		return NULL;
	}
	template <class T> T* ReverseFind() {
		for(int i = sub.GetCount()-1; i >= 0; i--) {
			T* o = CastPtr<T>(&sub[i]);
			if (o) return o;
		}
		return NULL;
	}
	int FindPos(Object* o) {
		for(int i = 0; i < sub.GetCount(); i++)
			if (&sub[i] == o)
				return i;
		return -1;
	}
	Object* DetachChild(Object* o) {
		for(int i = 0; i < sub.GetCount(); i++)
			if (&sub[i] == o)
				return sub.Detach(i);
		return NULL;
	}
	void MoveTo(Object& node) {
		if (parent)
			parent->DetachChild(this);
		parent = NULL;
		node.Add(this);
	}
};


NAMESPACE_LAYOUT_END

#endif
