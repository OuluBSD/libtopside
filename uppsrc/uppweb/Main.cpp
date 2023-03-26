#include "uppweb.h"

uppweb::uppweb()
{
	root = "";
	prefork = 0;
	use_caching = true;
	threads = 1;
	session.format = SESSION_FORMAT_JSON;
	port = 8001;
	basedir = GetFileDirectory(__FILE__);
	srcdir = GetHomeDirFile("upp");
	if(!DirectoryExists(srcdir)) {
		Cerr() << "Please, set 'srcdir' to point to U++ trunk at " __FILE__ ":" << __LINE__-2 << "\n";
		Exit(1);
	}
	path += ";" + basedir + "/static;" + basedir;
	caching = 2;
	
	menu.Add("","uppweb/www.tpp/index_en-us.tpp");
	menu.Add("overview","uppweb/www.tpp/overview_en-us.tpp");
	menu.Add("examples","uppweb/www.tpp/examples_en-us.tpp");
	menu.Add("screenshots","uppweb/www.tpp/ss_en-us.tpp");
	menu.Add("comparisons","uppweb/www.tpp/comparison_en-us.tpp");
	menu.Add("apps","uppweb/www.tpp/apps_en-us.tpp");
	menu.Add("download","uppweb/www.tpp/download_en-us.tpp");
	menu.Add("manual","uppweb/www.tpp/documentation_en-us.tpp");
	menu.Add("bazaar","uppweb/www.tpp/bazaar_en-us.tpp");
	menu.Add("roadmap","uppweb/www.tpp/Roadmap_en-us.tpp");
	menu.Add("faq","uppweb/www.tpp/FAQ_en-us.tpp");
	menu.Add("license","ide/app.tpp/About_en-us.tpp");
	menu.Add("forum","/forum");
	menu.Add("funding","uppweb/www.tpp/Funding_en-us.tpp");
	
	for(int i = 0; i < menu.GetCount(); i++){
		static const char* lng[] = { "en-us", "ca-es", "cs-cz", "de-de", "es-es", "eu-es", "fr-fr", "ro-ro", "ru-ru", "zh-cn", "zh-tw", NULL };
		String s = "topic://"+menu[i];
		menulinks.GetAdd(s) = "/"+menu.GetKey(i);
		for(int j = 1; lng[j]; j++){
			s.Replace(lng[j-1],lng[j]);
			menulinks.GetAdd(s) = "/"+menu.GetKey(i);
		}
	}
}

CONSOLE_APP_MAIN{
#ifdef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);
	Ini::skylark_log = true;
#endif
	uppweb().Run();
}

