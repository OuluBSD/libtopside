#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


String RealizeEonFile(String rel_path) {
	if (rel_path.IsEmpty())
		return String();
	
	
	for (int tries = 0; tries < 4; tries++) {
		String path;
		switch (tries) {
			case 0: path = rel_path; break;
			case 1: path = ShareDirFile(rel_path); break;
			case 2: path = ShareDirFile(AppendFileName("eon", rel_path)); break;
			case 3: path = ShareDirFile(AppendFileName("shaders" DIR_SEPS "toys", rel_path)); break;
		}
		
		
		if (DirectoryExists(path)) {
			if (path.Right(1) == DIR_SEPS)
				path = path.Left(path.GetCount()-1);
			String title = GetFileName(path);
			
			String eon_file = AppendFileName(path, title + ".eon");
			if (FileExists(eon_file))
				return eon_file;
			
			String toy_file = AppendFileName(path, title + ".toy");
			if (FileExists(toy_file))
				return toy_file;
		}
		else if (FileExists(path))
			return path;
	}
	
	return rel_path;
}


NAMESPACE_SERIAL_END
