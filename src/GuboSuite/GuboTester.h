#ifndef _GuboSuite_GuboTester_h_
#define _GuboSuite_GuboTester_h_

NAMESPACE_GUBO_BEGIN


class Ground : public Gubo {
	
public:
	RTTI_DECL1(Ground, Gubo)
	typedef Ground CLASSNAME;
	Ground();
	
	Ground& SetSize(float len);
	
	void Paint(Draw3& d) override;
	
};


class Box : public Gubo {
	
public:
	RTTI_DECL1(Box, Gubo)
	typedef Box CLASSNAME;
	Box();
	
	Box& Move(const Point3f& pt);
	
	void Paint(Draw3& d) override;
	
};


struct GuboTester : TopGubo {
	RTTI_DECL1(GuboTester, TopGubo)
	Ground gnd;
	Array<Box> boxes;
	
	
	GuboTester();
	~GuboTester();
	
};


NAMESPACE_GUBO_END

#endif
