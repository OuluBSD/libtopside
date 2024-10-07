#include "TextCtrl.h"
#include <TextDataCtrl/TextDataCtrl.h>


BEGIN_TEXTLIB_NAMESPACE


void MetaStartup(bool my_data) {
	MetaDatabase& mdb = MetaDatabase::Single();
	
	if (my_data) {
		// Load Database
		#ifdef flagWIN32
		mdb.dir = AppendFileName(GetHomeDirectory(), "MyTopside");
		#else
		mdb.dir = GetHomeDirFile("MyTopside");
		#endif
	}
	else {
		String dir;
		#ifdef flagDEBUG
		#ifdef flagWIN32
		dir = AppendFileName(GetHomeDirectory(), "Topside");
		#else
		dir = GetHomeDirFile("Topside");
		#endif
		#endif
		
		if (dir.IsEmpty() || !DirectoryExists(dir))
			dir = ConfigFile("");
		
		mdb.dir = dir;
	}
	
	if (!DirectoryExists(mdb.dir)) {
		PromptOK(DeQtf("Default path not found.\nSelect MyTopside directory."));
		mdb.dir = SelectDirectory();
	}
	
	mdb.Load();
	
}

void MetaShutdown() {
	MetaDatabase::Single().Store();
}

void AppModeStartup() {
	MetaDatabase& mdb = MetaDatabase::Single();
	
	TextDatabase& db = GetAppModeDatabase();
	TaskMgrConfig& m = TaskMgrConfig::Single();
	
	db.Load();
	
	//db.src_data.Load();
	db.src_data.a.Load();
	
	if (db.src_data.IsEmpty()) {
		TextDataLoader loader;
		loader.Run();
	}
	
	
	DatabaseBrowser::Single().Load();
}

void AppModeShutdown(bool fast_exit, bool save_songdata) {
	TextDatabase& db = GetAppModeDatabase();
	TaskMgrConfig& m = TaskMgrConfig::Single();
	
	// Deinit storing of files
	SolverBase::StopAll();
	m.Stop();
	
	if (!fast_exit) {
		DatabaseBrowser::Single().Store();
		
		db.Store();
		
		if (save_songdata) {
			db.src_data.a.Store();
			db.src_data.a.StoreJson();
		}
		
		m.Store();
	}
}



END_TEXTLIB_NAMESPACE
