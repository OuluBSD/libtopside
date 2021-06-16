#include <Core/Core.h>
using namespace UPP;


void TestShared() {
	struct Dumber : RTTIBase {
		RTTI_DECL0(Dumber)
		Dumber() {LOG("Dumber ctor +++");}
		virtual ~Dumber() {LOG("Dumber dtor ---");}
	};
	struct Dumb : public Dumber {
		RTTI_DECL1(Dumb, Dumber)
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



CONSOLE_APP_MAIN {
	ASSERT(SignificantBits(0xF) == 4);
	ASSERT(SignificantBits64(0xF) == 4);
	
	CombineHash ch;
	ch.Put(777999777).Put(123).Put64(0xF0F0F0F0F0F0F0F0);
	dword hash = ch;
	ASSERT(hash == 1894504625);
	
	ASSERT(min(1.0f, 2.0f) == 1.0f);
	ASSERT(max(1.0f, 2.0f) == 2.0f);
	ASSERT(fabs(-1.0) == 1.0);
	
	DUMP(Random());
	DUMP(Randomf());
	
	int arr0[10];
	for(int i = 0; i < 10; i++) arr0[i] = i;
	ASSERT(*FindIf(arr0, arr0 + 10, [](int i) -> bool {return i == 6;}) == 6);
	
	// String
	
	
	
	Vector<int> v0;
	for(int i = 0; i < 10; i++) v0.Add(i);
	
	Uuid uuid;
	uuid.New();
	DUMP(uuid);
	
	
	Object value = ParseJSON(
		"{\"menu\": {\n"
		"  \"id\": \"file\",\n"
		"  \"value\": \"File\",\n"
		"  \"popup\": {\n"
		"    \"menuitem\": [\n"
		"      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},\n"
		"      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},\n"
		"      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}\n"
		"    ]\n"
		"  }\n"
		"}}\n");
	LOG(GetObjectTreeString(value));
	
	
	
	TestShared();
}

