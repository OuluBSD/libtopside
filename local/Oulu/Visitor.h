#ifndef _Oulu_Visitor_h_
#define _Oulu_Visitor_h_


NAMESPACE_OULU_BEGIN


class RuntimeVisitor {
	
	
	template <class T>
	void Push(T& o) {
		TODO
	}
	
	void Pop() {
		
	}
	
	template <class T>
	void AddRef(T& o) {
		TODO
	}
	
public:
	
	void StopWhenFound(bool b=true);
	
	template <class T>
	void Visit(T& o) {
		Push(o);
		o.Visit(*this);
		Pop();
	}
	
	template <class T>
	void VisitRef(T& o) {
		AddRef(o);
	}
	
	template <class T>
	void VisitVector(T& o) {
		for (auto iter = o.begin(), end = o.end(); iter != end; ++iter)
			Visit(*iter);
	}
	
	template <class T>
	void VisitVectorRefs(T& o) {
		for (auto iter = o.begin(), end = o.end(); iter != end; ++iter)
			Visit(iter());
	}
	
	template <class T>
	void VisitRefVector(T& o) {
		for (auto iter = o.begin(), end = o.end(); iter != end; ++iter)
			VisitRef(*iter);
	}
	
	template <class T> RuntimeVisitor& operator%(T& o) {Visit(o); return *this;}
	template <class T> RuntimeVisitor& operator&(T& o) {VisitRef(o); return *this;}
	template <class T> RuntimeVisitor& operator|(T& o) {VisitVector(o); return *this;}
	template <class T> RuntimeVisitor& operator||(T& o) {VisitVectorRefs(o); return *this;}
	template <class T> RuntimeVisitor& operator&&(T& o) {VisitRefVector(o); return *this;}
};


NAMESPACE_OULU_END


#endif
