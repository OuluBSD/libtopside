#include "Editor.h"

using Translation::Cursor;

NodeCache::NodeCache() {
	
}

void NodeCache::LoadFileNode(String path, ClangNode& node) {
	
	// Check file
	if (!FileExists(path)) {
		LOG("ERROR: NodeCache::LoadFileNode: file does not exists: " << path);
		return;
	}
	
	// Check if file is same as previous
	String content = LoadFile(path);
	hash_t hash = content.GetHashValue();
	
	if (node.GetInt() == hash)
		return;
	
	// Headers cannot be "compiled" so make a workaround
	bool is_header = false;
	String real_path = path;
	if (GetFileExt(path) == ".h") {
		path = ConfigFile("tmp.cpp");
		if (FileExists(path)) FileDelete(path);
		FileOut out(path);
		out << content;
		is_header = true;

	}
	
	// Clear previous unit, if exists
	project.RemoveUnit(path);
	
	// Add the unit (file)
	Vector<String> top_paths;
	top_paths <<= this->top_paths;
	top_paths.Add(GetFileDirectory(path));
	project.AddUnit(path, top_paths);

	// Deep-copy the tree. The unit and the file-node are the "same" tree.
	Translation::Unit& unit = project.GetUnit(path);
	Translation::Cursor file_root = unit.GetRootCursor();
	Array<Cursor> file_cursor = file_root.GetCursors(path);
	node.Clear();
	for(int i = 0; i < file_cursor.GetCount(); i++) {
		Cursor& clang_node = file_cursor[i];
		ClangNode& sub = node.Add();
		CopyClangNode(clang_node, sub);
	}
	
	/*if (is_header) {
		LOG(::Dump(node));
	}*/
	
	// Set the hash value and path
	node.SetInt(hash);
	node.SetString(real_path);
	
	StoreThis();
}

ClangNode NodeCache::GetAllBasic() {
	ClangNode out;
	
	//LOG(Dump());
	
	for(int i = 0; i < data.GetCount(); i++) {
		ClangNode& pkg = data[i];
		ASSERT(pkg.GetType() == CI_PKG);
		for(int j = 0; j < pkg.GetCount(); j++) {
			ClangNode& file = pkg[j];
			ASSERT(file.GetType() == CI_FILE);
			String path = file.GetString();
			String file_ext = GetFileExt(path);
			if (file_ext != ".h")
				continue;
			ClangNode& sub = out.Add();
			sub.ClangItem::operator=(file);
			if (file.GetString().Find("TopWindow.h") != -1) {
				LOG(" NODE --------------- " << file.GetString() << " ------------------------------------ ");
				LOG(::Dump(file));
			}
			GetAllBasicR(file, sub, 0);
			/*
			LOG(" Sub --------------------------------------------------- ");
			LOG(::Dump(sub));
			LOG("");
			*/
		}
	}
	
	//LOG(::Dump(out));
	
	return out;
}

void NodeCache::GetAllBasicR(ClangNode& src, ClangNode& dest, int depth) {
	for(int i = 0; i < src.GetCount(); i++) {
		ClangNode& node = src[i];
		int kind = node.GetKind();
		if (kind == CXCursor_Namespace) {
			GetAllBasicR(node, dest, 0);
		}
		else if (depth == 0) {
			if (kind == CXCursor_FunctionDecl) {
				dest.Add(node);
			}
			else if (kind == CXCursor_ClassDecl) {
				ClangNode& sub = dest.Add();
				sub.ClangItem::operator=(node);
				GetAllBasicR(node, sub, 1);
			}
		}
		else if (depth == 1) {
			if (kind == CXCursor_Constructor || kind == CXCursor_CXXMethod) {
				dest.Add(node);
			}
			else if (kind == CXCursor_FieldDecl) {
				dest.Add(node);
			}
		}
		else {
			
		}
	}
}

void CopyClangNode(Translation::Cursor& clang_node, ClangNode& node) {
	int kind = clang_node.GetKind();
	
	node.SetType(CI_AST);
	node.SetKey(clang_node.GetDisplayName());
	node.SetString(clang_node.GetType().GetResultType().GetName());
	node.SetKind(kind);
	
	if (kind == CXCursor_IntegerLiteral) {
		int value = StrInt(clang_node.GetScope());
		node.SetInt(value);
	}
	
	int count = clang_node.GetCount();
	for(int i = 0; i < count; i++) {
		Translation::Cursor clang_sub = clang_node[i];
		ClangNode& node_sub = node.Add();
		CopyClangNode(clang_sub, node_sub);
	}
}