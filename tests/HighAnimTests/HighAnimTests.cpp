#include "HighAnimTests.h"

TestApp::TestApp() {
	
    MakeNext();
	
	tc.Set(-1000/60, THISBACK(Iterate));
}

void TestApp::Clear() {
	ctx.Clear();
}

void TestApp::MakeNext() {
	mode = (mode + 1) % 2;
	
	Clear();
	
	ctx.WhenStop = THISBACK(MakeNext);
	
	if (mode == 0)
		Make1();
	else if (mode == 1)
		Make2();
	
	ctx.Init();
}


void TestApp::Iterate() {
	ctx.Iterate();
	Refresh();
}

void TestApp::Make1() {
	AnimScene& s = ctx.a.AddScene("def");
	AnimObject& r = s.GetRoot();
	r.SetPolygon(Color(255, 140, 140));
	
	int kps = ctx.a.GetKeysFromTime(4)+1;
	s.SetLength(kps);
	r.SetLength(kps);
	int kp0 = 0;
	int kp1 = kps / 2;
	int kp2 = kps - 1;
	AnimKeypoint& begin		= r.GetAddKeypoint(0);
	AnimKeypoint& middle	= r.GetAddKeypoint(kp1);
	AnimKeypoint& end		= r.GetAddKeypoint(kp2);
	
	double rot_step =  M_PI*2 / (double)(kps-1);
	begin	.SetAngle(0, TC_SINUSOID_LOWER);
	middle	.SetAngle(kp1 * rot_step, TC_SINUSOID_HIGHER);
	end		.SetAngle(kp2 * rot_step);
	
	r.Points() << Point(0,0) << Point(300,0) << Point(400,500) << Point(200,200) << Point(-100,300);
	r.SetAnchorPointAverage();
	r.SetPosition(Point(300,300));
	
}

void TestApp::Make2() {
	AnimScene& s = ctx.a.AddScene("def");
	AnimObject& r = s.GetRoot();
	
	
	ctx.code.Add("draw clock") =
R"SH4D3R(
to_digit_string(x) {
	if (x >= 0 && x <= 9)
		return "0" + to_string(x);
	else
		return to_string(x);
}

main() {
	for (i = 0; i < 4; i++) {
		x = rand() % 640;
		y = rand() % 480;
		time = GetSysTime();
		str = to_digit_string(time.hour) + ":" + to_digit_string(time.minute) + ":" + to_digit_string(time.second);
		DrawText(x, y, str, 1000);
	}
}
)SH4D3R";
}

void TestApp::Paint(Draw& d) {
	//LOG("TestApp::Paint");
	d.DrawRect(GetSize(), White());
	
	ctx.p.Paint(d);
	
}




GUI_APP_MAIN {
	TestApp().Run();
	
}
