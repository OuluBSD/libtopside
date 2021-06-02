#ifndef _Editor_Navigator_h_
#define _Editor_Navigator_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

class IDE;

String GetRelativePath(const String& to, const String& from);

class BlockList : public FileList {
	
	
public:
	typedef BlockList CLASSNAME;
	
	void Exit() {
		
	}
	
	void LocalMenu(Bar& bar) {
		bar.Add("Exit", THISBACK(Exit));
	}

	void RightDown(Point, dword) {
		MenuBar::Execute(THISBACK(LocalMenu));
	}
};

class PackageFileList : public FileList {
	
	
	
public:
	typedef PackageFileList CLASSNAME;
	
	PackageFileList();
	
	void LocalMenu(Bar& bar);

	void RightDown(Point, dword);
	
	Callback WhenAddFiles, WhenRename;
};


class NavigatorCtrl : public ParentCtrl {
	IDE* ide;
	
	BlockList blocks;
	PackageFileList files;
	
	ArrayCtrl references;
	Splitter split;
	int line;
public:
	typedef NavigatorCtrl CLASSNAME;
	NavigatorCtrl(IDE* ide);
	
	//void SetBlock(int bid) { blocks.SetCursor(bid);}
	
	void RefreshFiles();
	String GetCurrentPackageName();
	
	
	void SetFile(const String& path);
	void SetLine(int line);
	
	void ClearBlocks();
	void AddBlock(String name);
	void SetBlock(String name);
	void SelectBlock();
	void LoadBlock(int id);
	void SelectFile();
	void LoadFile(int id);
	void AddFiles();
	void RenameFile();
	
	Callback1<String> WhenSelectFile;
};

#endif
