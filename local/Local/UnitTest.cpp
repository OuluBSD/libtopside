#include "Local.h"

#ifdef flagSTDEXC

NAMESPACE_TOPSIDE_BEGIN


UnitTest::UnitTest() {
	
}

void UnitTest::Test(String test_title, std::function<void(UnitTest& t)> fn) {
	cur_fail = false;
	cur_pass = false;
	fail_msg.Clear();
	pass_msg.Clear();
	
	String fail_arg;
	try {
		fn(*this);
	}
	catch (Exc e) {
		fail_arg = e;
	}
	catch (UnitExc) {

	}

	
	if (cur_pass || !cur_fail) {
		String msg;
		msg << "passed test: " << test_title;
		if (pass_msg.GetCount())
			msg << " (" << pass_msg << ")";
		passes.Add(msg);
	}
	else {
		String msg;
		msg << "failed test: " << test_title;
		if (fail_msg.GetCount())
			msg << " (" << fail_msg << ")";
		if (fail_arg.GetCount())
			msg << " [" << fail_arg << "]";
		fails.Add(msg);
	}
}

void UnitTest::Pass(String msg) {
	cur_pass = true;
	pass_msg = msg;
	THROW(UnitExc());
}

void UnitTest::Failed(String msg) {
	cur_fail = true;
	fail_msg = msg;
	THROW(UnitExc());
}

void UnitTest::End() {
	THROW(UnitExc());
}


NAMESPACE_TOPSIDE_END

#endif
