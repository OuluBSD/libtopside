#ifndef _GuboLib_StaticGubo_h_
#define _GuboLib_StaticGubo_h_

NAMESPACE_GUBO_BEGIN


class StaticGubo : public Gubo {
	
public:
	RTTI_DECL1(StaticGubo, Gubo)
	StaticGubo();
	
	void Paint(Draw3& d) override;
	
};


NAMESPACE_GUBO_END

#endif
