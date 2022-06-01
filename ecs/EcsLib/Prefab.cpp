#include "EcsLib.h"

NAMESPACE_ECS_BEGIN

namespace KnownModelNames {

String GetPath(String name) {
	String path;
	
	if (name == UnitSphere) {
		path = "sphere.obj";
	}
	else if (name == UnitCube) {
		path = "cube.obj";
	}
	else if (name == UnitQuad) {
		TODO
	}
	else if (name == Baseball) {
		path = "cgtrader/baseball_ball_01/baseball_ball_01.obj";
	}
	else if (name == PaintBrush) {
		path = "cgtrader/IcePick/IcePick.obj";
	}
	else if (name == Gun) {
		path = "cgtrader/Futuristic_pistol/Futuristic_pistol.obj";
	}
	
	path = ShareDirFile(AppendFileName("models", path));
	//LOG(path);
	
	return path;
}

}

NAMESPACE_ECS_END
