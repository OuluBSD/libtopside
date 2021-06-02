#include <Local/Local.h>

using namespace UPP;
using namespace TS;

void Print(int lvl, String s) {
	String e, l;
	e.Cat('-', lvl);
	l.Cat(' ', 5-lvl);
	s = l + e + " " + s + " " + e;
	int pad = (80 - s.GetCount()) / 2;
	e.Clear();
	/*if (lvl >= 2) {
		e.Cat(' ', pad);
		s = e + s + e;
	}*/
	COUTLOG(s);
}

CONSOLE_APP_MAIN {
	#define TITLE 4
	#define SUBTITLE 3
	#define NORMAL 1
	#define TEST(x) if (!(x)) {Print(0, "failed"); return;} Print(NORMAL, "ok");
	#define TEST_(x, msg) if (!(x)) {Print(0, msg " failed"); return;} Print(NORMAL, msg " failed");
	
	Print(TITLE, "Testing compression & hashes");
	
	{
		Print(SUBTITLE, "md5");
		String orig = "abc\n";
		String md5 = MD5String(orig);
		String correct = "0bee89b07a248e27c83fc3d5951213c1";
		TEST(md5 == correct);
	}
	{
		Print(SUBTITLE, "bzip2");
		String orig = "test string";
		String bz2 = BZ2Compress(orig);
		String result = BZ2Decompress(bz2);
		TEST(orig == result);
	}
	
	Print(TITLE, "Testing finished");
}
