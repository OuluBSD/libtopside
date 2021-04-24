#include "ToyHub.h"

NAMESPACE_TOYHUB_BEGIN


int64 NewTextId() {
	static int64 count;
	static StaticMutex mtx;
	mtx.Enter();
	if (!count) {
		if (SQL * SelectAll().From(TEXT) && SQL.Fetch()) {
			count = SQL[TEXT_COUNT];
		}
		else {
			SQL * Insert(TEXT)(TEXT_COUNT, 0);
		}
		if (!count)
			count++;
	}
	int64 id = count++;
	SQL * Update(TEXT)(TEXT_COUNT, count);
	mtx.Leave();
	return id;
}

String LoadText(int64 text_id) {
	ASSERT(text_id >= 0);
	String s;
	if (GetMemcached("text" + IntStr(text_id), s))
		return s;
	String path = ConfigFile("text") + DIR_SEPS + IntStr64(text_id);
	s = LoadFile(path);
	return s;
}

void StoreText(int64 text_id, String text) {
	ASSERT(text_id >= 0);
	String path = ConfigFile("text") + DIR_SEPS + IntStr64(text_id);
	FileOut fout(path);
	fout << text;
	fout.Close();
	SetMemcached("text" + IntStr(text_id), text);
}


String LoadHtmlFile(int page_id) {
	ASSERT(page_id >= 0);
	String s;
	if (GetMemcached("html" + IntStr(page_id), s))
		return s;
	String path = ConfigFile("html") + DIR_SEPS + IntStr64(page_id);
	s = LoadFile(path);
	return s;
}

void StoreHtmlFile(int page_id, String text) {
	ASSERT(page_id >= 0);
	String path = ConfigFile("html") + DIR_SEPS + IntStr64(page_id);
	FileOut fout(path);
	fout << text;
	fout.Close();
	SetMemcached("html" + IntStr(page_id), text);
}


String LoadFile(int hub, String name) {
	ASSERT(hub >= 0 && !name.IsEmpty());
	String s;
	//if (GetMemcached("file" + IntStr(hub) + "-" + name, s))
	//	return s;
	String path = ConfigFile("file") + DIR_SEPS + IntStr(hub) + "-" + name;
	s = LoadFile(path);
	return s;
}

void StoreFile(int hub, String name, String data) {
	ASSERT(hub >= 0 && !name.IsEmpty());
	String path = ConfigFile("file") + DIR_SEPS + IntStr(hub) + "-" + name;
	FileOut fout(path);
	fout << data;
	fout.Close();
	//SetMemcached("file" + IntStr(hub) + "-" + name, data);
}

String LoadWikipedia(String prefix, String title) {
	ASSERT(!prefix.IsEmpty() && !title.IsEmpty());
	bool update = false;
	if (SQL * SelectAll().From(WIKIPEDIA).Where(WP_PREFIX == prefix && WP_TITLE == title) && SQL.Fetch()) {
		update = true;
		Time expiry = SQL[WP_EXPIRY];
		int64 text_id = SQL[WP_TEXT_ID];
		if (expiry > GetUtcTime()) {
			return LoadText(text_id);
		}
		else StoreText(text_id, ""); // free mem
	}
	String url = "http://" + prefix + ".wikipedia.org/wiki/" + title + "?action=raw";
	//LOG(url);
	String md = HttpRequest().Url(url).Execute();
	//LOG(md);
	
	int64 text_id = NewTextId();
	StoreText(text_id, md);
	
	Time expiry = GetUtcTime() + 24 * 60 * 60;
	if (!update)
		SQL * Insert(WIKIPEDIA)(WP_PREFIX, prefix)(WP_TITLE, title)(WP_EXPIRY, expiry)(WP_TEXT_ID, text_id);
	else
		SQL * Update(WIKIPEDIA)(WP_EXPIRY, expiry)(WP_TEXT_ID, text_id).Where(WP_PREFIX == prefix && WP_TITLE == title);
	
	return md;
}



NAMESPACE_TOYHUB_END
