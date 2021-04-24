#ifndef _ToyHub_Database_h_
#define _ToyHub_Database_h_

NAMESPACE_TOYHUB_BEGIN

#define DUMPVAR(x) s << #x "=" << x << ", ";
#define DUMPVAR_(x) s << #x "=" << x;

class User : Moveable<User> {
	int id = -1;
	String name;
	String real_name;
	String password;
	String newpassword;
	Time newpass_time;
	String email;
	Time touched;
	String token;
	Time email_authenticated;
	String email_token;
	Time email_token_expires;
	Time registration;
	int editcount = 0;
	Time password_expires;
	
	void Load(Sql& sql);
	void StoreMem() {ASSERT(id >= 0); SetMemcached("user" + IntStr(id), *this);}
public:
	
	void Serialize(Stream& s);
	String ToString() const {
		String s;
		DUMPVAR(id);
		DUMPVAR(name);
		DUMPVAR(real_name);
		DUMPVAR(password);
		DUMPVAR(newpassword);
		DUMPVAR(newpass_time);
		DUMPVAR(email);
		DUMPVAR(touched);
		DUMPVAR(token);
		DUMPVAR(email_authenticated);
		DUMPVAR(email_token);
		DUMPVAR(email_token_expires);
		DUMPVAR(registration);
		DUMPVAR(editcount);
		DUMPVAR_(password_expires);
		return s;
	}
	
	bool Create(String name, String password, String email);
	bool Load(int user);
	bool Load(String username);
	
	bool SetRealName(String real_name);
	bool SetPassword(String password);
	bool SetNewPassword(String password);
	bool SetEmail(String email);
	bool LogIn(String password);
	bool Authenticate();
	bool IncEdits();
	
	String GetName() const {return name;}
	String GetRealName() const {return real_name;}
	String GetPassword() const {return password;}
	String GetNewPassword() const {return newpassword;}
	Time GetNewPasswordTime() const {return newpass_time;}
	String GetEmail() const {return email;}
	Time GetTouched() const {return touched;}
	String GetToken() const {return token;}
	Time GetEmailAuthenticated() const {return email_authenticated;}
	String GetEmailToken() const {return email_token;}
	Time GetEmailTokenExpires() const {return email_token_expires;}
	Time GetRegistered() const {return registration;}
	int GetEditCount() const {return editcount;}
	Time GetPasswordExpires() const {return password_expires;}
	
	operator int() const {return id;}
	operator String() const {return name;}
	
	static int GetCount();
	static Vector<User> GetRange(int begin, int end);
};

class UserProperty : Moveable<UserProperty> {
	int user_id = -1;
	String property;
	String value;
	
	void Load(Sql& sql);
public:
	
	bool Load(int user_id, String property);
	bool Set(String value) {ASSERT(user_id >= 0 && !property.IsEmpty()); return Set(user_id, property, value);}
	bool Set(int user_id, String property, String value);
	
	int GetUser() const {return user_id;}
	String GetProperty() const {return property;}
	String GetValue() const {return value;}
	
	operator int() const {return user_id;}
	operator String() const {return value;}
	
	static int GetCount();
	static Vector<UserProperty> GetRange(int begin, int end);
	
};

class UserGroup : Moveable<UserGroup> {
	int user_id = -1;
	String group;
	
public:
	int GetUser() const {return user_id;}
	String GetGroup() const {return group;}
	
	operator int() const {return user_id;}
	operator String() const {return group;}
	
	static bool Add(int user_id, String group);
	static bool Remove(int user_id, String group);
	static Vector<String> GetUserGroups(int user_id);
	static Vector<String> GetUserFormerGroups(int user_id);
	
};

class UserNewTalk : Moveable<UserNewTalk> {
	int user_id = -1;
	Time last_timestamp;
	
	void Load(Sql& sql);
	
public:
	int GetUser() const {return user_id;}
	Time GetTime() const {return last_timestamp;}
	
	operator int() const {return user_id;}
	operator Time() const {return last_timestamp;}
	
	static bool Add(int user_id);
	static bool RemoveAll(int user_id);
	static Vector<UserNewTalk> Get(int user_id);
	
};

class LogItem : Moveable<LogItem> {
	int id = -1;
	String type;
	String action;
	Time timestamp;
	int user_id;
	String user_text;
	int namespace_;
	int hub;
	String title;
	int page;
	String comment;
	String params;
	bool deleted;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int id);
	
	bool Delete();
	
	int GetId() const {return id;}
	String GetType() const {return type;}
	String GetAction() const {return action;}
	Time GetTime() const {return timestamp;}
	int GetUser() const {return user_id;}
	String GetUserText() const {return user_text;}
	int GetNamespace() const {return namespace_;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	int GetPage() const {return page;}
	String GetComment() const {return comment;}
	String GetParams() const {return params;}
	bool IsDeleted() const {return deleted;}
	
	operator int() const {return id;}
	
	static const bool Add(
		String type,
		String action,
		int user_id,
		String user_text,
		int namespace_,
		int hub,
		String title,
		int page,
		String comment,
		String params);
		
	static int GetCount();
	static Vector<LogItem> GetRange(int begin, int end);
	static Vector<LogItem> GetUser(int user_id, int limit=1000);
	static Vector<LogItem> GetUserLastHours(int user_id, int hours);
	static Vector<LogItem> GetLast(int limit=1000);
	static Vector<LogItem> GetLastHours(int hours);
	static Vector<LogItem> GetPage(int page, int limit=1000);
	
};

class ValidTag : Moveable<ValidTag> {
	
public:
	static bool Add(String tag);
	static bool Remove(String tag);
	static Index<String> GetAll();
};

class RecentChange : Moveable<RecentChange> {
	int id = -1;
	Time timestamp;
	int user;
	String user_text;
	int namespace_;
	int hub;
	String title;
	String comment;
	bool minor;
	bool bot;
	bool new_;
	int cur_id;
	int this_revid;
	int last_revid;
	String source;
	bool patrolled;
	String ip;
	int old_len;
	int new_len;
	bool deleted;
	int logid;
	String log_type;
	String log_action;
	String log_params;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int id);
	
	bool Delete();
	bool SetPatrolled();
	
	Time GetTime() const {return timestamp;}
	int GetUser() const {return user;}
	String GetUserText() const {return user_text;}
	int GetNamespace() const {return namespace_;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	String GetComment() const {return comment;}
	bool IsMinor() const {return minor;}
	bool IsBot() const {return bot;}
	bool IsNew() const {return new_;}
	int GetPage() const {return cur_id;}
	int GetCurrentRevision() const {return this_revid;}
	int GetPreviousRevision() const {return last_revid;}
	String GetSource() const {return source;}
	bool IsPatrolled() const {return patrolled;}
	String GetIpAddress() const {return ip;}
	int GetOldLength() const {return old_len;}
	int GetNewLength() const {return new_len;}
	bool IsDeleted() const {return deleted;}
	int GetLogItem() const {return logid;}
	String GetLogItemType() const {return log_type;}
	String GetLogItemAction() const {return log_action;}
	String GetLogItemParams() const {return log_params;}
	
	operator int() const {return id;}
	
	static bool Add(
		int user,
		String user_text,
		int namespace_,
		int hub,
		String title,
		String comment,
		bool minor,
		bool bot,
		bool new_,
		int cur_page_id,
		int this_revid,
		int last_revid,
		String source,
		String ip,
		int old_len,
		int new_len,
		int logid,
		String log_type,
		String log_action,
		String log_params);
	static int GetCount();
	static Vector<RecentChange> GetRange(int begin, int end);
	static Vector<RecentChange> GetUser(int user_id, int limit=1000);
	static Vector<RecentChange> GetUserLastHours(int user_id, int hours);
	static Vector<RecentChange> GetLast(int limit=1000);
	static Vector<RecentChange> GetLastHours(int hours);
	static Vector<RecentChange> GetPage(int page, int limit=1000);
	
};

class WatchItem : Moveable<WatchItem> {
	int id = -1;
	int user;
	int page;
	int namespace_;
	int hub;
	String title;
	Time notification_timestamp;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int user, int page);
	bool Remove();
	bool ResetNotification();
	
	int GetId() const {return id;}
	int GetUser() const {return user;}
	int GetPage() const {return page;}
	int GetNamespace() const {return namespace_;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	Time GetNotificationTime() const {return notification_timestamp;}
	
	static bool Add(
		int user,
		int page,
		int namespace_,
		int hub,
		String title);
	static Vector<WatchItem> GetUserAll(int user);
	static Vector<WatchItem> GetUserNotifications(int user);
	static Vector<WatchItem> GetPage(int page);
	static Vector<WatchItem> GetHub(int hub);
};

class Hub : Moveable<Hub> {
	int id = -1;
	String title;
	Time created;
	int created_user;
	String lang;
	bool deleted;
	Time deleted_time;
	int deleted_user;
	String deleted_reason;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(String title, String lang);
	bool Load(int hub);
	bool Create(int user, String title, String language);
	bool Delete(int user, String reason);
	
	operator int() const {return id;}
	
	static int GetCount();
	static Vector<Hub> GetHubs();
};

class ArchiveItem : Moveable<ArchiveItem> {
	int id = -1;
	int ns;
	int hub;
	String title;
	String comment;
	int user;
	String user_text;
	Time rev_timestamp;
	int rev_id;
	int text_id;
	bool deleted;
	int len;
	int page_id;
	String md5;
	String content_model;
	String content_format;
	
	void Load(Sql& sql);
	
public:
	
	bool LoadPage(int page);
	bool Delete();
	
	int GetId() const {return id;}
	int GetNamespace() const {return ns;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	String GetComment() const {return comment;}
	int GetUser() const {return user;}
	String GetUserText() const {return user_text;}
	Time GetTime() const {return rev_timestamp;}
	int GetRevision() const {return rev_id;}
	int GetText() const {return text_id;}
	bool IsDeleted() const {return deleted;}
	int GetLength() const {return len;}
	int GetPage() const {return page_id;}
	String GetMD5() const {return md5;}
	String GetContentModel() const {return content_model;}
	String GetContentFormat() const {return content_format;}
	
	static bool Add(
		int ns,
		int hub,
		String title,
		String comment,
		int user,
		String user_text,
		Time rev_timestamp,
		int rev_id,
		int text_id,
		int len,
		int page_id,
		String md5,
		String content_model,
		String content_format);
	static int GetCount();
	static Vector<ArchiveItem> GetRange(int begin, int end);
};

class Revision : Moveable<Revision> {
	int id = -1;
	int page;
	int64 text_id;
	String comment;
	int user;
	String user_text;
	Time timestamp;
	bool minor_edit;
	bool deleted;
	int len;
	int parent_id;
	String md5;
	String content_model;
	String content_format;
	
	void Load(Sql& sql);
	void StoreMem() {ASSERT(id >= 0); SetMemcached("rev" + IntStr(id), *this);}
public:
	
	void Serialize(Stream& s);
	String ToString() const {
		String s;
		DUMPVAR(id);
		DUMPVAR(page);
		DUMPVAR(text_id);
		DUMPVAR(comment);
		DUMPVAR(user);
		DUMPVAR(user_text);
		DUMPVAR(timestamp);
		DUMPVAR(minor_edit);
		DUMPVAR(deleted);
		DUMPVAR(len);
		DUMPVAR(parent_id);
		DUMPVAR(md5);
		DUMPVAR(content_model);
		DUMPVAR(content_format);
		return s;
	}
	
	bool Create(
		int page,
		int64 text_id,
		String comment,
		int user,
		String user_text,
		Time timestamp,
		bool minor_edit,
		int len,
		int parent_id,
		String md5,
		String content_model,
		String content_format);
	bool Load(int id);
	
	bool Delete();
	
	int GetId() const {return id;}
	int GetPage() const {return page;}
	int64 GetText() const {return text_id;}
	String GetComment() const {return comment;}
	int GetUser() const {return user;}
	String GetUserText() const {return user_text;}
	Time GetTime() const {return timestamp;}
	bool IsMinorEdit() const {return minor_edit;}
	bool IsDeleted() const {return deleted;}
	int GetLength() const {return len;}
	int GetParent() const {return parent_id;}
	String GetMD5() const {return md5;}
	String GetContentModel() const {return content_model;}
	String GetContentFormat() const {return content_format;}
	
	operator int() const {return id;}
	
	static Vector<Revision> GetPage(int page);
};

class Page : Moveable<Page> {
	int id = -1;
	int ns;
	int hub;
	String title;
	String restrictions;
	bool is_redirect;
	bool is_new;
	double random;
	Time touched;
	Time links_updated;
	int latest_rev;
	int len;
	String content_model;
	String lang;
	
	void StoreMem() {ASSERT(id >= 0); SetMemcached("page" + IntStr(id), *this);}
public:
	
	void Load(Sql& sql);
	void Serialize(Stream& s);
	String ToString() const {
		String s;
		DUMPVAR(id);
		DUMPVAR(ns);
		DUMPVAR(hub);
		DUMPVAR(title);
		DUMPVAR(restrictions);
		DUMPVAR(is_redirect);
		DUMPVAR(is_new);
		DUMPVAR(random);
		DUMPVAR(touched);
		DUMPVAR(links_updated);
		DUMPVAR(latest_rev);
		DUMPVAR(len);
		DUMPVAR(content_model);
		DUMPVAR(lang);
		return s;
	}
	
	bool Load(int id);
	bool Load(int hub, String title);
	bool Create(
		int ns,
		int hub,
		String title,
		String restrictions,
		/*bool is_redirect,
		bool is_new,
		int latest_rev,
		int len,
		String content_model,*/
		String lang);
	bool Remove(int user, String user_text, String comment);
	
	bool SetRestrictions(String restrictions);
	bool SetRedirect(bool b);
	bool Touch();
	bool SetLinksUpdated();
	bool SetLatestRevision(int rev, bool is_redirect, bool is_new, int len, String content_model);
	
	int GetId() const {return id;}
	int GetNamespace() const {return ns;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	String GetRestrictions() const {return restrictions;}
	bool IsRedirect() const {return is_redirect;}
	bool IsNew() const {return is_new;}
	double GetRandom() const {return random;}
	Time GetTouched() const {return touched;}
	Time GetLinksUpdated() const {return links_updated;}
	int GetLatestRevision() const {return latest_rev;}
	int GetLength() const {return len;}
	String GetContentModel() const {return content_model;}
	String GetLanguage() const {return lang;}
	
	operator int () const {return id;}
	
};

class Redirection : Moveable<Redirection> {
	int from;
	int ns;
	int hub;
	String title;
	String interhub;
	String fragment;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() {return from;}
	int GetNamespace() {return ns;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	String GetInterhub() const {return interhub;}
	String GetFragment() const {return fragment;}
	
	static bool Add(
		int from,
		int ns,
		int hub,
		String title,
		String interhub,
		String fragment);
	static bool RemoveAll(int page);
	static Vector<Redirection> GetPage(int page);
};

class Category : Moveable<Category> {
	int id = -1;
	String title;
	int hub;
	int pages;
	int subcats;
	int files;

	void Load(Sql& sql);
	
public:
	
	bool Load(int id);
	bool Load(int hub, String title);
	bool Create(int hub, String title);
	
	bool SetStats(int pages, int subcats, int files);
	
	int GetId() const {return id;}
	String GetTitle() const {return title;}
	int GetHub() const {return hub;}
	int GetPages() const {return pages;}
	int GetSubCategories() const {return subcats;}
	int GetFiles() const {return files;}
	
	operator int () const {return id;}
	
	static Vector<Category> GetHub(int hub);
};

class PageProp : Moveable<PageProp> {
	int page = -1;
	String propname;
	String value;
	double sortkey;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int page, String propname);
	bool Set(String value) {ASSERT(page >= 0 && !propname.IsEmpty()); return Set(page, propname, value);}
	bool Remove();
	
	int GetPage() const {return page;}
	String GetKey() const {return propname;}
	String GetValue() const {return value;}
	double GetSortKey() const {return sortkey;}
	
	static bool Set(int page, String propname, String value);
	static Vector<PageProp> GetPage(int page);
	
};

class PageRestriction : Moveable<PageRestriction> {
	int id = -1;
	int page;
	String type;
	String level;
	bool cascade;
	Time expiry;
	
	void Load(Sql& sql);
	
public:
	
	bool Remove();
	
	int GetId() const {return id;}
	int GetPage() const {return page;}
	String GetType() const {return type;}
	String GetLevel() const {return level;}
	bool IsCascade() const {return cascade;}
	Time GetExpiry() const {return expiry;}
	
	operator int () const {return id;}
	
	static bool Add(
		int page,
		String type,
		String level,
		bool cascade,
		Time expiry);
	static Vector<PageRestriction> GetPage(int page);
	
};

class ProtectedTitle : Moveable<ProtectedTitle> {
	int ns;
	int hub;
	String title;
	int user;
	String reason;
	Time timestamp;
	Time expiry;
	String create_perm;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int hub, String title);
	bool Remove();
	
	int GetNamespace() const {return ns;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	int GetUser() const {return user;}
	String GetReason() const {return reason;}
	Time GetTime() const {return timestamp;}
	Time GetExpiry() const {return expiry;}
	String GetCreatePermission() const {return create_perm;}
	
	static bool Add(
		int ns,
		int hub,
		String title,
		int user,
		String reason,
		Time expiry,
		String create_perm);
	static Vector<ProtectedTitle> GetHub(int hub);
};

class PageLink : Moveable<PageLink> {
	int from = -1;
	int from_ns;
	int hub;
	int ns;
	String title;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from;}
	int GetFromNamespace() const {return from_ns;}
	int GetHub() const {return hub;}
	int GetNamespace() const {return ns;}
	String GetTitle() const {return title;}
	
	static bool Add(
		int from,
		int from_ns,
		int hub,
		int ns,
		String title);
	static bool RemoveAll(int page);
	static Vector<PageLink> GetFrom(int page);
	static Vector<PageLink> GetTo(int hub, String title);
};

class InterhubLink : Moveable<InterhubLink> {
	int from_page = -1;
	int from_hub;
	int to_hub;
	String title;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from_page;}
	int GetFromHub() const {return from_hub;}
	int GetToHub() const {return to_hub;}
	String GetToTitle() const {return title;}
	
	static bool Add(
		int from_page,
		int from_hub,
		int to_hub,
		String title);
	static bool RemoveAll(int page);
	static Vector<InterhubLink> GetFrom(int page);
	static Vector<InterhubLink> GetTo(int hub, String title);
	
};

class ExternalLink : Moveable<ExternalLink> {
	int id = -1;
	int from;
	int hub;
	String to;
	String index;
	
	void Load(Sql& sql);
	
public:
	
	int GetId() const {return id;}
	int GetFromPage() const {return from;}
	int GetHub() const {return hub;}
	String GetTo() const {return to;}
	String GetIndex() const {return index;}
	
	operator int () const {return id;}
	
	static bool Add(
		int id,
		int from,
		int hub,
		String to,
		String index);
	static bool RemoveAll(int page);
	static Vector<ExternalLink> GetFrom(int page);
	static Vector<ExternalLink> GetTo(String url);
	static Vector<ExternalLink> GetToIndex(String idx);
};

class LanguageLink : Moveable<LanguageLink> {
	int from = -1;
	int hub;
	String lang;
	String title;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from;}
	int GetHub() const {return hub;}
	String GetLanguage() const {return lang;}
	String GetTitle() const {return title;}
	
	static bool Add(
		int from,
		int hub,
		String lang,
		String title);
	static bool RemoveAll(int page);
	static Vector<LanguageLink> GetFrom(int page);
	static Vector<LanguageLink> GetTo(String lang, String title);
};

class FileLink : Moveable<FileLink> {
	int from;
	int from_ns;
	int from_hub;
	String to;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from;}
	int GetFromNamespace() const {return from_ns;}
	int GetFromHub() const {return from_hub;}
	String GetTo() const {return to;}
	
	static bool Add(
		int from,
		int from_ns,
		int from_hub,
		String to);
	static bool RemoveAll(int page);
	static Vector<FileLink> GetFrom(int page);
	static Vector<FileLink> GetTo(String file);
};

class TemplateLink : Moveable<TemplateLink> {
	int from;
	int from_ns;
	int from_hub;
	int ns;
	String title;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from;}
	int GetFromNamespace() const {return from_ns;}
	int GetFromHub() const {return from_hub;}
	int GetNamespace() const {return ns;}
	String GetTitle() const {return title;}
	
	static bool Add(
		int from,
		int from_ns,
		int from_hub,
		int ns,
		String title);
	static bool RemoveAll(int page);
	static Vector<TemplateLink> GetFrom(int page);
	static Vector<TemplateLink> GetTo(String title);
};

class CategoryLink : Moveable<CategoryLink> {
	int from;
	int hub;
	String to;
	String sortkey;
	String sortkey_prefix;
	Time timestamp;
	String collation;
	uint8 type;
	
	void Load(Sql& sql);
	
public:
	
	int GetFromPage() const {return from;}
	int GetFromHub() const {return hub;}
	String GetTo() const {return to;}
	String GetSortkey() const {return sortkey;}
	String GetSortkeyPrefix() const {return sortkey_prefix;}
	Time GetTime() const {return timestamp;}
	String GetCollation() const {return collation;}
	uint8 GetType() const {return type;}
	
	static bool Add(
		int from,
		int hub,
		String to,
		String sortkey,
		String sortkey_prefix,
		String collation,
		uint8 type);
	static Vector<CategoryLink> GetFrom(int page);
	static Vector<CategoryLink> GetTo(int hub, String title);
};

class File : Moveable<File> {
	int hub = -1;
	String name;
	int size;
	int width;
	int height;
	String metadata;
	int bits;
	int media_type;
	int major_mime;
	String minor_mime;
	String description;
	int user;
	String user_text;
	Time timestamp;
	String md5;
	
	void Load(Sql& sql);
	void StoreMem() {ASSERT(hub >= 0 && !name.IsEmpty()); SetMemcached("file-" + IntStr(hub) + "-" + name, *this);}
public:
	
	void Serialize(Stream& s);
	String ToString() const {
		String s;
		DUMPVAR(hub);
		DUMPVAR(name);
		DUMPVAR(size);
		DUMPVAR(width);
		DUMPVAR(height);
		DUMPVAR(metadata);
		DUMPVAR(bits);
		DUMPVAR(media_type);
		DUMPVAR(major_mime);
		DUMPVAR(minor_mime);
		DUMPVAR(description);
		DUMPVAR(user);
		DUMPVAR(user_text);
		DUMPVAR(timestamp);
		DUMPVAR(md5);
		return s;
	}
	
	bool Load(int hub, String name);
	bool Create(int hub, String title);
	bool Update(
		int size,
		int width,
		int height,
		String metadata,
		int bits,
		int media_type,
		int major_mime,
		String minor_mime,
		String description,
		int user,
		String user_text,
		String md5);
	
	String GetName() const {return name;}
	int GetSize() const {return size;}
	int GetWidth() const {return width;}
	int GetHeight() const {return height;}
	String GetMetadata() const {return metadata;}
	int GetBits() const {return bits;}
	int GetMediaType() const {return media_type;}
	int GetMajorMime() const {return major_mime;}
	String GetMinorMime() const {return minor_mime;}
	String GetDescription() const {return description;}
	int GetUser() const {return user;}
	String GetUserText() const {return user_text;}
	Time GetTime() const {return timestamp;}
	String GetMD5() const {return md5;}
	
	static Vector<File> GetUser(int user);
	static Vector<File> GetHub(int hub);
	
};

class ArchiveFile : Moveable<ArchiveFile> {
	int id = -1;
	int hub;
	String name;
	String archive_name;
	String storage_group;
	String storage_key;
	int deleted_user;
	Time deleted_timestamp;
	String deleted_reason;
	int size;
	int width;
	int height;
	String metadata;
	int bits;
	int media_type;
	int major_mime;
	String minor_mime;
	String description;
	int user;
	String user_text;
	Time timestamp;
	bool deleted;
	String md5;
	
	void Load(Sql& sql);
	
public:
	
	bool Delete();
	
	int GetHub() const {return hub;}
	int GetId() const {return id;}
	String GetName() const {return name;}
	String GetArchiveName() const {return archive_name;}
	String GetStorageGroup() const {return storage_group;}
	String GetStorageKey() const {return storage_key;}
	int GetDeletedUser() const {return deleted_user;}
	Time GetDeletedTimestamp() const {return deleted_timestamp;}
	String GetDeletedReason() const {return deleted_reason;}
	int GetSize() const {return size;}
	int GetWidth() const {return width;}
	int GetHeight() const {return height;}
	String GetMetadata() const {return metadata;}
	int GetBits() const {return bits;}
	int GetMediaType() const {return media_type;}
	int GetMajorMime() const {return major_mime;}
	String GetMinorMime() const {return minor_mime;}
	String GetDescription() const {return description;}
	int GetUser() const {return user;}
	String GetUserText() const {return user_text;}
	Time GetTime() const {return timestamp;}
	bool IsDeleted() const {return deleted;}
	String GetMD5() const {return md5;}
	
	static bool Add(
		String name,
		String archive_name,
		String storage_group,
		String storage_key,
		int deleted_user,
		Time deleted_timestamp,
		String deleted_reason,
		int size,
		int width,
		int height,
		String metadata,
		int bits,
		int media_type,
		int major_mime,
		String minor_mime,
		String description,
		int user,
		String user_text,
		Time timestamp,
		String md5);
	static Vector<ArchiveFile> GetName(int hub, String name);
	
};

class UploadStash : Moveable<UploadStash> {
	int id = -1;
	int user;
	String key;
	String orig_path;
	String path;
	String source_type;
	Time timestamp;
	String status;
	int chunk_inx;
	String props;
	int size;
	String md5;
	String mime;
	int media_type;
	int image_width;
	int image_height;
	int image_bits;
	
	void Load(Sql& sql);
	
public:
	
	bool Create(String key);
	bool Load(String key);
	bool Remove();
	bool Set(
		String orig_path,
		String path,
		String source_type,
		Time timestamp,
		String status,
		int chunk_inx,
		String props,
		int size,
		String md5,
		String mime,
		int media_type,
		int image_width,
		int image_height,
		int image_bits);
	
	int GetId() const {return id;}
	int GetUser() const {return user;}
	String GetKey() const {return key;}
	String GetOrigPath() const {return orig_path;}
	String GetPath() const {return path;}
	String GetSourceType() const {return source_type;}
	Time GetTime() const {return timestamp;}
	String GetStatus() const {return status;}
	int GetChunkInx() const {return chunk_inx;}
	String GetProps() const {return props;}
	int GetSize() const {return size;}
	String GetMD5() const {return md5;}
	String GetMIME() const {return mime;}
	int GetMediaType() const {return media_type;}
	int GetImageWidth() const {return image_width;}
	int GetImageHeight() const {return image_height;}
	int GetImageBits() const {return image_bits;}
	
};

class Job : Moveable<Job> {
	int id = -1;
	String cmd;
	int ns;
	int hub;
	String title;
	Time timestamp;
	String params;
	int random;
	int attempts;
	String token;
	Time token_timestamp;
	String md5;
	
	void Load(Sql& sql);
	
public:
	
	int GetId() const {return id;}
	String GetCommand() const {return cmd;}
	int GetNamespace() const {return ns;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	Time GetTime() const {return timestamp;}
	String GetParams() const {return params;}
	int GetRandom() const {return random;}
	int GetAttempts() const {return attempts;}
	String GetToken() const {return token;}
	Time GetTokenTime() const {return token_timestamp;}
	String GetMD5() const {return md5;}
	
	static bool Add(
		String cmd,
		int ns,
		int hub,
		String title,
		Time timestamp,
		String params,
		int random,
		int attempts,
		String token,
		Time token_timestamp,
		String md5);
	static Vector<Job> GetRange(int begin, int end);
	static int GetCount();
};

class SiteStat : Moveable<SiteStat> {
	int id = -1;
	int64 total_edits;
	int64 good_articles;
	int64 total_pages;
	int64 users;
	int64 active_users;
	int64 files;
	int hubs;
	Time timestamp;
	
	void Load(Sql& sql);
	
public:
	
	int64 GetTotalEdits() const {return total_edits;}
	int64 GetGoodArticles() const {return good_articles;}
	int64 GetTotalPages() const {return total_pages;}
	int64 GetUsers() const {return users;}
	int64 GetActiveUsers() const {return active_users;}
	int64 GetFiles() const {return files;}
	int GetHubs() const {return hubs;}
	Time GetTime() const {return timestamp;}
	
	static bool Add(
		int64 total_edits,
		int64 good_articles,
		int64 total_pages,
		int64 users,
		int64 active_users,
		int64 files,
		int hubs);
	static Vector<SiteStat> GetRange(int begin, int end);
	static int GetCount();
};

class SearchIndexItem : Moveable<SearchIndexItem> {
	int page;
	int hub;
	String title;
	String text;
	
	void Load(Sql& sql);
	
public:
	
	bool Load(int page);
	
	int GetPage() const {return page;}
	int GetHub() const {return hub;}
	String GetTitle() const {return title;}
	String GetText() const {return text;}
	
	static Vector<SearchIndexItem> GetHub(int hub);
	static int GetCount();
	
};

struct Namespaces {
	VectorMap<int, String> id_to_key;
	VectorMap<String, int> key_to_id;
	void Add(int id, String key) {id_to_key.Add(id, key); key_to_id.Add(key, id);}
};

inline Namespaces& GetNamespaces() {return Single<Namespaces>();}

NAMESPACE_TOYHUB_END

#endif
