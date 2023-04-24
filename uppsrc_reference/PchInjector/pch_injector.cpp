#include <Core/Core.h>

using namespace Upp;



CONSOLE_APP_MAIN
{
	
	// Compile Shell PKG and write theide log output to in.txt
	
	String content = LoadFile(GetDataFile("in.txt"));
	ASSERT(!content.IsEmpty());
	
	Vector<String> lines = Split(content, "\n");
	Index<String> pkgs;
	
	for (String line : lines) {
		int a = line.Find("----- ");
		int b = a >= 0 ? line.Find(" (", a) : -1;
		
		if (a == 0 && b >= 0) {
			a += 6;
			String mid = line.Mid(a, b-a);
			LOG(mid);
			pkgs.Add(mid);
		}
		
	}
	
	Vector<String> dirs;
	dirs << "C:/git/libtopside/src";
	dirs << "C:/git/libtopside/alt";
	dirs << "C:/git/libtopside/reference";
	
	for (String pkg : pkgs) {
		String pkg_title = GetFileTitle(pkg);
		
		bool found = false;
		for (String dir : dirs) {
			String path = AppendFileName(dir, pkg);
			
			if (DirectoryExists(path)) {
				LOG(path);
				
				
				String upp = AppendFileName(path, pkg_title + ".upp");
				if (!FileExists(upp)) {
					LOG("not found: " << upp);
					Exit(1);
				}
				
				String upp_content = LoadFile(upp);
				Vector<String> lines = Split(upp_content, "\n", false);
				bool file_found = false;
				int file_i = -1;
				int i = 0;
				for(; i < lines.GetCount(); i++) {
					if (TrimBoth(lines[i]) == "file") {
						file_found = true;
						file_i = i;
						break;
					}
						
				}
				if (!file_found) {
					LOG("'file' line not found");
					Exit(1);
				}
				
				
				if (upp_content.Find("pch.h") < 0) {
					
					i += 1;
					int c = lines.GetCount();
					for(; i < c; i++) {
						int a = lines[i].Find(";");
						if (a > 0) {
							lines[i] = lines[i].Left(a) + ",";
							
							lines.Insert(i+1) = "\tpch.h,";
							lines.Insert(i+2) = "\tpch.cpp;";
							file_found = true;
							break;
						}
							
					}
					
					upp_content = Join(lines, "\n");
					
					LOG(upp_content);
					{
						FileOut fout(upp);
						fout << upp_content;
					}
				}
				
				String pch_h = AppendFileName(path, "pch.h");
				String pch_cpp = AppendFileName(path, "pch.cpp");
				
				if (!FileExists(pch_h)) {
					FileOut fout(pch_h);
					fout << "#include \"" << pkg_title << ".h\"\n";
					fout.Flush();
				}
				
				if (!FileExists(pch_cpp)) {
					FileOut fout(pch_cpp);
					fout << "#include \"pch.h\"\n";
					fout.Flush();
				}
				
				for(int i = file_i+1; i < lines.GetCount(); i++) {
					String line = lines[i];
					String fname = TrimBoth(line);
					fname = fname.Left(fname.GetCount()-1);
					
					String ext = GetFileExt(fname);
					if (fname != "pch.cpp" && (ext == ".cpp" || ext == ".c")) {
						String cpath = AppendFileName(path, fname);
						if (!FileExists(cpath)) {
							Panic("error");
						}
						String c = LoadFile(cpath);
						Vector<String> lines = Split(c, "\n", false);
						String def_inc = "#include \"" + pkg_title + ".h\"";
						String pch_inc = "#include \"pch.h\"";
						if (lines.GetCount() && TrimBoth(lines[0]) == pch_inc) {
							// pass
						}
						else if (lines.GetCount() && TrimBoth(lines[0]) == def_inc) {
							lines[0] = pch_inc;
						}
						else {
							lines.Insert(0, pch_inc);
						}
						String new_c = Join(lines, "\n");
						
						LOG(cpath);
						LOG(new_c.Left(100));
						
						FileOut fout(cpath);
						fout << new_c;
					}
					
					if (line.Find(";") >= 0)
						break;
				}
				
				found = true;
				break;
			}
		}
		
		if (!found) {
			LOG("Pkg dir not found: " << pkg);
			break;
		}
	}
	
}
