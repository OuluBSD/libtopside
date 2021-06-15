#ifndef _Local_UnitTest_h_
#define _Local_UnitTest_h_

#ifdef flagSTDEXC

NAMESPACE_TOPSIDE_BEGIN


class UnitTest {
	struct UnitExc {};
	
	Vector<String> fails, passes;
	bool cur_fail, cur_pass;
	String fail_msg, pass_msg;
	
public:
	typedef UnitTest CLASSNAME;
	UnitTest();
	
	void Clear() {fails.Clear(); passes.Clear();}
	void Test(String test_title, std::function<void(UnitTest& t)> fn);
	void Pass(String msg);
	void Failed(String msg);
	void End();
	
	void Assert(bool b, String pass_msg) {if (!b) Failed(FailMessage(pass_msg));}
	template <class T> void IsEqual(const T& a, const T& b, String pass_msg) {if (!(a == b)) Failed(FailMessage(pass_msg) /*+ " (" + ToString(a) + " != " + ToString(b) + ")"*/);}
	
	const Vector<String>& GetPasses() const {return passes;}
	const Vector<String>& GetFails() const {return fails;}
	
	String FailMessage(String pass_msg) {return "failed: \"" + pass_msg + "\"";}
	void operator()(String pass_msg, std::function<void(UnitTest& t)> fn) {Test(pass_msg, fn);}
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif
