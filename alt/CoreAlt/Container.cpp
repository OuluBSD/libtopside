#include "Core.h"



NAMESPACE_UPP_BEGIN


void TestShared() {
	struct Dumber {
		Dumber() {LOG("Dumber ctor +++");}
		virtual ~Dumber() {LOG("Dumber dtor ---");}
	};
	struct Dumb : public Dumber {
		Dumb() {LOG("Dumb ctor ++++++");}
		~Dumb() {LOG("Dumb dtor ------");}
	};
	
	
	#define DUMPDUMB(x, y) LOG(#x ": " #y ": refs " << (y.GetBase() ? (int)y.GetBase()->refs : -1) << ", " << IntStr64((uint64)y.GetBase()));
	
	Shared<Dumb> s0a;
	DUMPDUMB(0, s0a);
	{
		Shared<Dumber> s1a;
		Shared<Dumb> s1b;
		DUMPDUMB(1, s1a);
		DUMPDUMB(2, s1b);
		
		s1b = Shared<Dumb>().WrapObject(new Dumb());
		DUMPDUMB(3, s1b);
		
		s1a = s1b.template As<Dumber>();
		DUMPDUMB(4, s1a);
		
		{
			Shared<Dumber> s2;
			DUMPDUMB(5, s2);
			s2 = s1a;
			DUMPDUMB(6, s2);
			s0a = s2.template As<Dumb>();
			DUMPDUMB(7, s0a);
		}
		DUMPDUMB(8, s0a);
	}
	DUMPDUMB(9, s0a);
	
}


NAMESPACE_UPP_END
