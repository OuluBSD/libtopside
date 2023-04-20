#include "EcsLib.h"

NAMESPACE_ECS_BEGIN

namespace KnownModelNames {

	
const char* UnitSphere = "UnitSphere_LowPoly";
const char* UnitCube = "UnitCube";
const char* UnitQuad = "UnitQuad";
const char* Baseball = "Baseball";
const char* PaintBrush = "PaintBrush";
const char* Gun = "Gun";



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
		path = "ms/Baseball.obj";
	}
	else if (name == PaintBrush) {
		path = "ms/Paintbrush.obj";
	}
	else if (name == Gun) {
		path = "ms/Gun.obj";
	}
	
	path = ShareDirFile(AppendFileName("models", path));
	
	return path;
}

}

NAMESPACE_ECS_END
