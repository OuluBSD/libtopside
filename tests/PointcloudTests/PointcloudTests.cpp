#include <Pointcloud/Pointcloud.h>
using namespace TS;


int CalcLens();


CONSOLE_APP_MAIN {
	//MemoryBreakpoint(17450);
	
	SetCoutLog();
	
	CalcLens();
	
	Octree o0;
	o0.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
	
	int points = 500;
	float radius = 3;
	bool random_points = 0;
	
	for(int i = 0; i < points; i++) {
		float yaw, pitch;
		if (random_points) {
			yaw = Randomf() * M_PI * 2;
			pitch = (Randomf() * 2 - 1) * (M_PI / 2);
		}
		else {
			float f = ((float)i / (float)points);
			yaw = f * M_PI * 2;
			pitch = fmodf(f * M_PI * 40, M_PI) - M_PI/2;
		}
		//pitch = 0;
		vec3 pos = AxesDir(yaw, pitch) * radius;
		OctreeNode* n = o0.GetAddNode(pos, 0);
		Pointcloud::Point& p = n->Add<Pointcloud::Point>();
		p.SetPosition(pos);
		
		//LOG(pos.ToString() + ": " + HexStr(n));
	}
	
	VirtualStereoCamera cam;
	cam.SetResolution(3040 / 2, 1080);
	
	// Fisheye lens camera with ~150 degrees from bottom left to top right
	float fov = 150;
	cam.SetPixelAngle(-0.0200947f, 0.00136151f, -1.22183e-07f, 1.86459e-10f);
	
	vec3 pos(0, 0, 0);
	quat orient = AxesQuat(0,0,0);
	cam.SetWorld(pos, orient);
	cam.SetPerspective(fov, 1.0, 0.1, 10.0);
	
	VectorImage img;
	cam.Render(o0, img);
	
	
	
	
}
