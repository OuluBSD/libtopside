#include "ToyHub.h"

#include <Sql/sch_source.h>
#include <Sql/sch_schema.h>

NAMESPACE_TOYHUB_BEGIN

bool has_home_page_connection;
bool HasHomePageConnection() {return has_home_page_connection;}

thread__ Value last_error;
Value GetLastError() {return last_error;}
void SetLastError(Value v) {last_error = v;}



SKYLARK(Css, "hub/css/*") {
	String path = GetDataFile(http[0] + ".css");
	if (FileExists(path))
		http.Content("text/css; charset=UTF-8", LoadFile(path));
}

SKYLARK(JavaScript, "hub/js/*") {
	String path = GetDataFile(http[0] + ".js");
	if (FileExists(path))
		http.Content("text/javascript; charset=utf-8", LoadFile(path));
}

SKYLARK(HubPageMain, "hub/") {
	http.Redirect("hub/Main_Page");
}

SKYLARK(HubPage, "hub/*") {
	if (http.GetParamCount()) {
		String title = http[0];
		title.Replace("_", " ");
		
		Hub hub;
		if (!hub.Load("testing", "en"))
			return;
		
		Page page;
		if (!page.Load(hub, title))
			return;
		
		String content = LoadHtmlFile(page);
		
		http("RawContent", Raw(content))
			.RenderResult("ToyHub/hub");
	}
	else {
		http("RawContent", "")
			.RenderResult("ToyHub/hub");
	}
}

SKYLARK(HomePage, "")
{
	has_home_page_connection = true;
	http.Redirect(HubPageMain);
}



ToyServer::ToyServer()
{
#ifdef _DEBUG
	prefork = 0;
	use_caching = false;
#endif

#ifdef flagSTANDALONE
	threads = 1;
#else
	threads = 10;
#endif
	port = 8001;
}

void ToyServer::WorkThread()
{
	InitMemcachedThread();
	OpenSQL();
	RunThread();
}






#ifdef flagSTANDALONE
inline Array<Sqlite3Session>& GetSessions() {return Single<Array<Sqlite3Session> >();}
#else
inline Array<MySqlSession>& GetSessions() {return Single<Array<MySqlSession> >();}
#endif

void Init() {
	RealizeDirectory(ConfigFile("text"));
	RealizeDirectory(ConfigFile("html"));
	RealizeDirectory(ConfigFile("file"));
	
}

void OpenSQL() {
	#ifdef flagSTANDALONE
	Sqlite3Session& session = GetSessions().Add();
	session.Open(ConfigFile("toyserver.db"));
	#else
	MySqlSession& session = GetSessions().Add();
	if(!session.Connect("root", "Passw0rd", "toyserver")) {
		SKYLARKLOG("Can't create or open database file");
		Exit(1);
	}
	#endif
	
#ifdef _DEBUG
	session.LogErrors();
	session.SetTrace();
#endif
	SQL = session;
}

void InitModel()
{
	#ifndef flagSTANDALONE
	InitMemcachedThread();
	Sql::PerThread();
	#endif
	
	SqlSchema sch(MY_SQL);
	All_Tables(sch);
	OpenSQL();
	
#ifdef _DEBUG
	SqlPerformScript(sch.Upgrade());
	SqlPerformScript(sch.Attributes());
	sch.SaveNormal();
#endif
}

void ServerInit() {
	Init();
	InitModel();
}

void RunToyHub() {
	ServerInit();
	
	LoadDefaultHub();
	
	auto& o = GetToyServer();
	o.Run();
}

void StopToyHub() {
	GetToyServer().Quit();
}










bool SetPage(const Hub& hub, const User& user, String title, String text, String lang, String model, String format) {
	String md5 = MD5String(text);
	
	int i = title.Find(":");
	String nsstr = i >= 0 ? title.Left(i) : "";
	int ns = GetNamespaces().key_to_id.Find(nsstr);
	if (ns < 0)
		return false;
	ns = GetNamespaces().key_to_id[ns];
	
	
	Page dbpage;
	int parent_rev = 0;
	if (dbpage.Load(hub, title)) {
		parent_rev = dbpage.GetLatestRevision();
		Revision prev_rev;
		if (prev_rev.Load(parent_rev)) {
			if (prev_rev.GetMD5() == md5)
				return true;
		}
	} else {
		if (!dbpage.Create(ns, hub, title, "", lang))
			return false;
	}
	
	
	int64 text_id = NewTextId();
	StoreText(text_id, text);
	
	Time now = GetUtcTime();
	
	
	
	Revision rev;
	rev.Create(
		dbpage,
		text_id,
		"Imported",
		user,
		user.GetName(),
		now,
		false,
		text.GetCount(),
		parent_rev,
		md5,
		model,
		format);
	
	dbpage.SetLatestRevision(
		rev,
		false,
		parent_rev == 0,
		text.GetCount(),
		model);
	
	//StoreHtml(dbpage, html);
	
	return true;
}



NAMESPACE_TOYHUB_END

