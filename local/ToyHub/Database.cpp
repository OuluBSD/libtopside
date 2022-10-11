#include "ToyHub.h"

NAMESPACE_TOYHUB_BEGIN

void User::Serialize(Stream& s) {
	s % (id);
	s % (name);
	s % (real_name);
	s % (password);
	s % (newpassword);
	s % (newpass_time);
	s % (email);
	s % (touched);
	s % (token);
	s % (email_authenticated);
	s % (email_token);
	s % (email_token_expires);
	s % (registration);
	s % (editcount);
	s % (password_expires);
}

void User::Load(Sql& sql) {
	id = sql[USER_ID];
	name = sql[USER_NAME];
	real_name = sql[USER_REAL_NAME];
	password = sql[USER_PASSWORD];
	newpassword = sql[USER_NEWPASSWORD];
	newpass_time = sql[USER_NEWPASS_TIME];
	email = sql[USER_EMAIL];
	touched = sql[USER_TOUCHED];
	token = sql[USER_TOKEN];
	email_authenticated = sql[USER_EMAIL_AUTHENTICATED];
	email_token = sql[USER_EMAIL_TOKEN];
	email_token_expires = sql[USER_EMAIL_TOKEN_EXPIRES];
	registration = sql[USER_REGISTRATION];
	editcount = sql[USER_EDITCOUNT];
	password_expires = sql[USER_PASSWORD_EXPIRES];
}

bool User::Create(String name, String password, String email) {
	if (SQL * Insert(USER)
		(USER_NAME, name)
		(USER_PASSWORD, password)
		(USER_EMAIL, email)
		(USER_REGISTRATION, GetUtcTime())
		(USER_EDITCOUNT, 0)) {
		return Load(name);
	}
	return false;
}

bool User::Load(int user) {
	if (GetMemcached("user" + IntStr(user), *this))
		return true;
	if (SQL * SelectAll().From(USER).Where(USER_ID == user) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool User::Load(String username) {
	if (SQL * SelectAll().From(USER).Where(USER_NAME == username) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool User::SetRealName(String real_name) {
	ASSERT(id >= 0);
	if (SQL * Update(USER)(USER_REAL_NAME, real_name).Where(USER_ID == id)) {
		this->real_name = real_name;
		StoreMem();
		return true;
	}
	return false;
}

bool User::SetPassword(String password) {
	ASSERT(id >= 0);
	if (SQL * Update(USER)(USER_PASSWORD, password).Where(USER_ID == id)) {
		this->password = password;
		StoreMem();
		return true;
	}
	return false;
}

bool User::SetNewPassword(String password) {
	ASSERT(id >= 0);
	if (SQL * Update(USER)(USER_NEWPASSWORD, password).Where(USER_ID == id)) {
		this->newpassword = newpassword;
		StoreMem();
		return true;
	}
	return false;
}

bool User::SetEmail(String email) {
	ASSERT(id >= 0);
	if (SQL * Update(USER)(USER_EMAIL, email).Where(USER_ID == id)) {
		this->email = email;
		StoreMem();
		return true;
	}
	return false;
}

bool User::LogIn(String password) {
	ASSERT(id >= 0);
	if (password.IsEmpty() || this->password != password)
		return false;
	Time now = GetUtcTime();
	if (SQL * Update(USER)(USER_TOUCHED, now).Where(USER_ID == id)) {
		this->touched = now;
		StoreMem();
		return true;
	}
	return false;
}

bool User::Authenticate() {
	ASSERT(id >= 0);
	if (!IsNull(email_authenticated))
		return false;
	Time now = GetUtcTime();
	if (SQL * Update(USER)(USER_EMAIL_AUTHENTICATED, now).Where(USER_ID == id)) {
		this->email_authenticated = now;
		StoreMem();
		return true;
	}
	return false;
}

bool User::IncEdits() {
	ASSERT(id >= 0);
	if (SQL * Update(USER)(USER_EDITCOUNT, USER_EDITCOUNT+1).Where(USER_ID == id)) {
		this->editcount++;
		StoreMem();
		return true;
	}
	return false;
}

int User::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(USER) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<User> User::GetRange(int begin, int end) {
	Vector<User> v;
	if (SQL * SelectAll().From(USER).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void UserProperty::Load(Sql& sql) {
	user_id = sql[UP_USER];
	property = sql[UP_PROPERTY];
	value = sql[UP_VALUE];
}

bool UserProperty::Load(int user_id, String property) {
	if (SQL * SelectAll().From(USER_PROPERTIES).Where(UP_USER == user_id && UP_PROPERTY == property) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

int UserProperty::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(USER_PROPERTIES) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<UserProperty> UserProperty::GetRange(int begin, int end) {
	Vector<UserProperty> v;
	if (SQL * SelectAll().From(USER_PROPERTIES).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

bool UserProperty::Set(int user_id, String property, String value) {
	if (SQL * Update(USER_PROPERTIES)(UP_VALUE, value).Where(UP_USER == user_id && UP_PROPERTY == property)) {
		this->user_id = user_id;
		this->property = property;
		this->value = value;
		return true;
	}
	if (SQL * Insert(USER_PROPERTIES)(UP_USER, user_id)(UP_PROPERTY, property)(UP_VALUE, value)) {
		this->user_id = user_id;
		this->property = property;
		this->value = value;
		return true;
	}
	return false;
}



bool UserGroup::Add(int user_id, String group) {
	if (SQL * Insert(USER_GROUPS)(UG_USER, user_id)(UG_GROUP, group)) {
		return true;
	}
	// return true if failed on duplicate
	if (SQL * SelectAll().From(USER_GROUPS).Where(UG_USER == user_id && UG_GROUP == group) && SQL.Fetch()) {
		return true;
	}
	return false;
}

bool UserGroup::Remove(int user_id, String group) {
	// If was in the group
	if (SQL * SelectAll().From(USER_GROUPS).Where(UG_USER == user_id && UG_GROUP == group) && SQL.Fetch()) {
		// Add to former groups (fails on duplicate and it's ok)
		SQL * Insert(USER_FORMER_GROUPS)(UFG_USER, user_id)(UFG_GROUP, group);
		
		return SQL * Delete(USER_GROUPS).Where(UG_USER == user_id && UG_GROUP == group);
	}
	return false;
}

Vector<String> UserGroup::GetUserGroups(int user_id) {
	Vector<String> v;
	if (SQL * Select(UG_GROUP).From(USER_GROUPS).Where(UG_USER == user_id)) {
		while (SQL.Fetch())
			v.Add(SQL[0]);
	}
	return v;
}

Vector<String> UserGroup::GetUserFormerGroups(int user_id) {
	Vector<String> v;
	if (SQL * Select(UFG_GROUP).From(USER_FORMER_GROUPS).Where(UFG_USER == user_id)) {
		while (SQL.Fetch())
			v.Add(SQL[0]);
	}
	return v;
}





void UserNewTalk::Load(Sql& sql) {
	user_id = sql[UNT_ID];
	last_timestamp = sql[UNT_LAST_TIMESTAMP];
}

bool UserNewTalk::Add(int user_id) {
	return SQL * Insert(USER_NEWTALK)(UNT_ID, user_id)(UNT_LAST_TIMESTAMP, GetUtcTime());
}

bool UserNewTalk::RemoveAll(int user_id) {
	return SQL * Delete(USER_NEWTALK).Where(UNT_ID == user_id);
}

Vector<UserNewTalk> UserNewTalk::Get(int user_id) {
	Vector<UserNewTalk> v;
	if (SQL * SelectAll().From(USER_NEWTALK).Where(UNT_ID == user_id)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void LogItem::Load(Sql& sql) {
	id = sql[LOG_ID];
	type = sql[LOG_TYPE];
	action = sql[LOG_ACTION];
	timestamp = sql[LOG_TIMESTAMP_];
	user_id = sql[LOG_USER];
	user_text = sql[LOG_USER_TEXT];
	namespace_ = sql[LOG_NAMESPACE];
	hub = sql[LOG_HUB];
	title = sql[LOG_TITLE];
	page = sql[LOG_PAGE];
	comment = sql[LOG_COMMENT];
	params = sql[LOG_PARAMS];
	deleted = sql[LOG_DELETED];
}

bool LogItem::Load(int id) {
	if (SQL * SelectAll().From(LOGGING).Where(LOG_ID == id) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool LogItem::Delete() {
	ASSERT(id >= 0);
	return SQL * ::Delete(LOGGING).Where(LOG_ID == id);
}

const bool LogItem::Add(
	String type,
	String action,
	int user_id,
	String user_text,
	int namespace_,
	int hub,
	String title,
	int page,
	String comment,
	String params) {
	return SQL * Insert(LOGGING)
		(LOG_TYPE, type)
		(LOG_ACTION, action)
		(LOG_USER_, user_id)
		(LOG_USER_TEXT, user_text)
		(LOG_NAMESPACE, namespace_)
		(LOG_HUB, hub)
		(LOG_TITLE, title)
		(LOG_PAGE, page)
		(LOG_COMMENT, comment)
		(LOG_PARAMS, params)
		(LOG_DELETED, false);
}

int LogItem::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(LOGGING) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<LogItem> LogItem::GetRange(int begin, int end) {
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LogItem> LogItem::GetUser(int user_id, int limit) {
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Where(LOG_USER_ == user_id).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LogItem> LogItem::GetUserLastHours(int user_id, int hours) {
	Time begin = GetUtcTime() - 60 * 60 * hours;
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Where(LOG_USER_ == user_id && LOG_TIMESTAMP_ >= begin)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LogItem> LogItem::GetLast(int limit) {
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LogItem> LogItem::GetLastHours(int hours) {
	Time begin = GetUtcTime() - 60 * 60 * hours;
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Where(LOG_TIMESTAMP_ >= begin)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LogItem> LogItem::GetPage(int page, int limit) {
	Vector<LogItem> v;
	if (SQL * SelectAll().From(LOGGING).Where(LOG_PAGE == page).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





bool ValidTag::Add(String tag) {
	return SQL * Insert(VALID_TAG)(VT_TAG, tag);
}

bool ValidTag::Remove(String tag) {
	return SQL * Delete(VALID_TAG).Where(VT_TAG == tag);
}

Index<String> ValidTag::GetAll() {
	Index<String> idx;
	if (SQL * Select(VT_TAG).From(VALID_TAG)) {
		while (SQL.Fetch())
			idx.Add(SQL[0]);
	}
	return idx;
}





void RecentChange::Load(Sql& sql) {
	id = sql[RC_ID];
	timestamp = sql[RC_TIMESTAMP];
	user = sql[RC_USER];
	user_text = sql[RC_USER_TEXT];
	namespace_ = sql[RC_NAMESPACE];
	hub = sql[RC_HUB];
	title = sql[RC_TITLE];
	comment = sql[RC_COMMENT];
	minor = sql[RC_MINOR];
	bot = sql[RC_BOT];
	new_ = sql[RC_NEW];
	cur_id = sql[RC_CUR_ID];
	this_revid = sql[RC_THIS_REVID];
	last_revid = sql[RC_LAST_REVID];
	source = sql[RC_SOURCE];
	patrolled = sql[RC_PATROLLED];
	ip = sql[RC_IP];
	old_len = sql[RC_OLD_LEN];
	new_len = sql[RC_NEW_LEN];
	deleted = sql[RC_DELETED];
	logid = sql[RC_LOGID];
	log_type = sql[RC_LOG_TYPE];
	log_action = sql[RC_LOG_ACTION];
	log_params = sql[RC_LOG_PARAMS];
}

bool RecentChange::Load(int id) {
	if (SQL * SelectAll().From(RECENTCHANGES).Where(RC_ID == id) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool RecentChange::Delete() {
	ASSERT(id >= 0);
	return SQL * ::Delete(RECENTCHANGES).Where(RC_ID == id);
}

bool RecentChange::SetPatrolled() {
	ASSERT(id >= 0);
	return SQL * Update(RECENTCHANGES)(RC_PATROLLED, true).Where(id >= 0);
}

bool RecentChange::Add(
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
	String log_params) {
	return SQL * Insert(RECENTCHANGES)
		(RC_TIMESTAMP, GetUtcTime())
		(RC_USER, user)
		(RC_USER_TEXT, user_text)
		(RC_NAMESPACE, namespace_)
		(RC_HUB, hub)
		(RC_TITLE, title)
		(RC_COMMENT, comment)
		(RC_MINOR, minor)
		(RC_BOT, bot)
		(RC_NEW, new_)
		(RC_CUR_ID, cur_page_id)
		(RC_THIS_REVID, this_revid)
		(RC_LAST_REVID, last_revid)
		(RC_SOURCE, source)
		(RC_IP, ip)
		(RC_OLD_LEN, old_len)
		(RC_NEW_LEN, new_len)
		(RC_DELETED, false)
		(RC_LOGID, logid)
		(RC_LOG_TYPE, log_type)
		(RC_LOG_ACTION, log_action)
		(RC_LOG_PARAMS, log_params);
}

int RecentChange::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(RECENTCHANGES) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<RecentChange> RecentChange::GetRange(int begin, int end) {
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<RecentChange> RecentChange::GetUser(int user_id, int limit) {
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Where(RC_USER == user_id).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<RecentChange> RecentChange::GetUserLastHours(int user_id, int hours) {
	Time begin = GetUtcTime() - 60 * 60 * hours;
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Where(RC_USER == user_id && RC_TIMESTAMP >= begin)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<RecentChange> RecentChange::GetLast(int limit) {
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<RecentChange> RecentChange::GetLastHours(int hours) {
	Time begin = GetUtcTime() - 60 * 60 * hours;
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Where(RC_TIMESTAMP >= begin)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<RecentChange> RecentChange::GetPage(int page, int limit) {
	Vector<RecentChange> v;
	if (SQL * SelectAll().From(RECENTCHANGES).Where(RC_CUR_ID == page).Limit(limit)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void WatchItem::Load(Sql& sql) {
	id = sql[WL_ID];
	user = sql[WL_USER];
	page = sql[WL_PAGE];
	namespace_ = sql[WL_NAMESPACE];
	hub = sql[WL_HUB];
	title = sql[WL_TITLE];
	notification_timestamp = sql[WL_NOTIFICATION_TIMESTAMP];
}

bool WatchItem::Load(int user, int page) {
	if (SQL * SelectAll().From(WATCHLIST).Where(WL_USER == user && WL_PAGE == page) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool WatchItem::Remove() {
	ASSERT(id >= 0);
	return SQL * Delete(WATCHLIST).Where(id == WL_ID);
}

bool WatchItem::ResetNotification() {
	ASSERT(id >= 0);
	return SQL * Update(WATCHLIST)(WL_NOTIFICATION_TIMESTAMP, Null).Where(WL_ID == id);
}

bool Add(
		int user,
		int page,
		int namespace_,
		int hub,
		String title) {
	return SQL * Insert(WATCHLIST)
		(WL_USER, user)
		(WL_PAGE, page)
		(WL_NAMESPACE, namespace_)
		(WL_HUB, hub)
		(WL_TITLE, title);
}

Vector<WatchItem> WatchItem::GetUserAll(int user) {
	Vector<WatchItem> v;
	if (SQL * SelectAll().From(WATCHLIST).Where(WL_USER == user)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<WatchItem> WatchItem::GetUserNotifications(int user) {
	Vector<WatchItem> v;
	if (SQL * SelectAll().From(WATCHLIST).Where(WL_USER == user && WL_NOTIFICATION_TIMESTAMP != Null)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<WatchItem> WatchItem::GetPage(int page) {
	Vector<WatchItem> v;
	if (SQL * SelectAll().From(WATCHLIST).Where(WL_PAGE == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<WatchItem> WatchItem::GetHub(int hub) {
	Vector<WatchItem> v;
	if (SQL * SelectAll().From(WATCHLIST).Where(WL_HUB == hub)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void Hub::Load(Sql& sql) {
	id = sql[HUB_ID];
	title = sql[HUB_TITLE];
	created =  sql[HUB_CREATED];
	created_user = sql[HUB_CREATED_USER];
	lang = sql[HUB_LANG];
	deleted = sql[HUB_DELETED];
	deleted_time = sql[HUB_DELETED_TIMESTAMP];
	deleted_user = sql[HUB_DELETED_USER];
	deleted_reason = sql[HUB_DELETED_REASON];
}

bool Hub::Load(String title, String lang) {
	if (SQL * SelectAll().From(HUB).Where(HUB_TITLE == title && HUB_LANG == lang) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool Hub::Load(int hub) {
	if (SQL * SelectAll().From(HUB).Where(HUB_ID == hub) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool Hub::Create(int user, String title, String language) {
	if (SQL * Insert(HUB)
		(HUB_TITLE, title)
		(HUB_CREATED, GetUtcTime())
		(HUB_CREATED_USER, user)
		(HUB_LANG, language)
		(HUB_DELETED, false)) {
		if (SQL * SelectAll().From(HUB).Where(HUB_TITLE == title && HUB_LANG == language) && SQL.Fetch()) {
			Load(SQL);
			return true;
		}
	}
	return false;
}

bool Hub::Delete(int user, String reason) {
	ASSERT(id >= 0);
	if (deleted)
		return false;
	Time now = GetUtcTime();
	if (SQL * Update(HUB)
		(HUB_DELETED, true)
		(HUB_DELETED_TIMESTAMP, now)
		(HUB_DELETED_USER, user)
		(HUB_DELETED_REASON, reason).Where(HUB_ID == id)) {
		deleted = true;
		deleted_time = now;
		deleted_user = user;
		deleted_reason = reason;
		return true;
	}
	return false;
}

int Hub::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(HUB) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<Hub> Hub::GetHubs() {
	Vector<Hub> v;
	if (SQL * SelectAll().From(HUB)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void ArchiveItem::Load(Sql& sql) {
	id = sql[AR_ID];
	ns = sql[AR_NAMESPACE];
	hub = sql[AR_HUB];
	title = sql[AR_TITLE];
	comment = sql[AR_COMMENT];
	user = sql[AR_USER];
	user_text = sql[AR_USER_TEXT];
	rev_timestamp = sql[AR_REV_TIMESTAMP];
	rev_id = sql[AR_REV_ID];
	text_id = sql[AR_TEXT_ID];
	deleted = sql[AR_DELETED];
	len = sql[AR_LEN];
	page_id = sql[AR_PAGE_ID];
	md5 = sql[AR_MD5];
	content_model = sql[AR_CONTENT_MODEL];
	content_format = sql[AR_CONTENT_FORMAT];
}

bool ArchiveItem::LoadPage(int page) {
	if (SQL * SelectAll().From(ARCHIVE).Where(AR_PAGE_ID == page) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool ArchiveItem::Delete() {
	ASSERT(id >= 0);
	return SQL * Update(ARCHIVE)(AR_DELETED, true).Where(AR_ID == id);
}

bool ArchiveItem::Add(
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
	String content_format) {
	return SQL * Insert(ARCHIVE)
		(AR_NAMESPACE, ns)
		(AR_HUB, hub)
		(AR_TITLE, title)
		(AR_COMMENT, comment)
		(AR_USER, user)
		(AR_USER_TEXT, user_text)
		(AR_REV_TIMESTAMP, rev_timestamp)
		(AR_REV_ID, rev_id)
		(AR_TEXT_ID, text_id)
		(AR_LEN, len)
		(AR_PAGE_ID, page_id)
		(AR_MD5, md5)
		(AR_CONTENT_MODEL, content_model)
		(AR_CONTENT_FORMAT, content_format);
}

int ArchiveItem::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(ARCHIVE) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}

Vector<ArchiveItem> ArchiveItem::GetRange(int begin, int end) {
	Vector<ArchiveItem> v;
	if (SQL * SelectAll().From(ARCHIVE).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}






void Revision::Serialize(Stream& s) {
	s % (id);
	s % (page);
	s % (text_id);
	s % (comment);
	s % (user);
	s % (user_text);
	s % (timestamp);
	s % (minor_edit);
	s % (deleted);
	s % (len);
	s % (parent_id);
	s % (md5);
	s % (content_model);
	s % (content_format);
}

void Revision::Load(Sql& sql) {
	id = sql[REV_ID];
	page = sql[REV_PAGE];
	text_id = sql[REV_TEXT_ID];
	comment = sql[REV_COMMENT];
	user = sql[REV_USER];
	user_text = sql[REV_USER_TEXT];
	timestamp = sql[REV_TIMESTAMP];
	minor_edit = sql[REV_MINOR_EDIT];
	deleted = sql[REV_DELETED];
	len = sql[REV_LEN];
	parent_id = sql[REV_PARENT_ID];
	md5 = sql[REV_MD5];
	content_model = sql[REV_CONTENT_MODEL];
	content_format = sql[REV_CONTENT_FORMAT];
}

bool Revision::Create(
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
	String content_format) {
	if (SQL * Insert(REVISION)
		(REV_PAGE, page)
		(REV_TEXT_ID, text_id)
		(REV_COMMENT, comment)
		(REV_USER, user)
		(REV_USER_TEXT, user_text)
		(REV_TIMESTAMP, timestamp)
		(REV_MINOR_EDIT, minor_edit)
		(REV_LEN, len)
		(REV_PARENT_ID, parent_id)
		(REV_MD5, md5)
		(REV_CONTENT_MODEL, content_model)
		(REV_CONTENT_FORMAT, content_format)) {
		if (SQL * SelectAll().From(REVISION)
			.Where(REV_PAGE == page && REV_TEXT_ID == text_id) && SQL.Fetch()) {
			Load(SQL);
			return true;
		}
	}
	return false;
}

bool Revision::Load(int id) {
	if (GetMemcached("rev" + IntStr(id), *this))
		return true;
	if (SQL * SelectAll().From(REVISION).Where(REV_ID == id) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool Revision::Delete() {
	ASSERT(id >= 0);
	if (SQL * Update(REVISION)(REV_DELETED, true).Where(REV_ID == id)) {
		deleted = true;
		StoreMem();
		return true;
	}
	return false;
}

Vector<Revision> Revision::GetPage(int page) {
	Vector<Revision> v;
	if (SQL * SelectAll().From(REVISION).Where(REV_PAGE == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}







void Page::Serialize(Stream& s) {
	s % (id);
	s % (ns);
	s % (hub);
	s % (title);
	s % (restrictions);
	s % (is_redirect);
	s % (is_new);
	s % (random);
	s % (touched);
	s % (links_updated);
	s % (latest_rev);
	s % (len);
	s % (content_model);
	s % (lang);
}

void Page::Load(Sql& sql) {
	id = sql[PAGE_ID];
	ns = sql[PAGE_NAMESPACE];
	hub = sql[PAGE_HUB];
	title = sql[PAGE_TITLE];
	restrictions = sql[PAGE_RESTRICTIONS_ITEM];
	is_redirect = sql[PAGE_IS_REDIRECT];
	is_new = sql[PAGE_IS_NEW];
	random = sql[PAGE_RANDOM];
	touched = sql[PAGE_TOUCHED];
	links_updated = sql[PAGE_LINKS_UPDATED];
	latest_rev = sql[PAGE_LATEST];
	len = sql[PAGE_LEN];
	content_model = sql[PAGE_CONTENT_MODEL];
	lang = sql[PAGE_LANG];
}

bool Page::Load(int id) {
	if (GetMemcached("page" + IntStr(id), *this))
		return true;
	if (SQL * SelectAll().From(PAGE).Where(PAGE_ID == id) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool Page::Load(int hub, String title) {
	if (SQL * SelectAll().From(PAGE).Where(PAGE_HUB == hub && PAGE_TITLE == title) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool Page::Create(
	int ns,
	int hub,
	String title,
	String restrictions,
	String lang) {
	Time now = GetUtcTime();
	if (SQL * Insert(PAGE)
		(PAGE_NAMESPACE, ns)
		(PAGE_HUB, hub)
		(PAGE_TITLE, title)
		(PAGE_RESTRICTIONS_ITEM, restrictions)
		(PAGE_IS_REDIRECT, false)
		(PAGE_IS_NEW, true)
		(PAGE_RANDOM, Randomf())
		(PAGE_TOUCHED, now)
		(PAGE_LINKS_UPDATED, now)
		(PAGE_LATEST, 0)
		(PAGE_LEN, 0)
		(PAGE_CONTENT_MODEL, "")
		(PAGE_LANG, lang)) {
		if (SQL * SelectAll().From(PAGE).Where(PAGE_HUB == hub && PAGE_TITLE == title) && SQL.Fetch()) {
			Load(SQL);
			StoreMem();
			return true;
		}
	}
	return false;
}

bool Page::Remove(int user, String user_text, String comment) {
	ASSERT(id >= 0);
	
	Revision r;
	if (!r.Load(latest_rev))
		return false;
	
	if (ArchiveItem::Add(
		ns,
		hub,
		title,
		comment,
		user,
		user_text,
		r.GetTime(),
		r.GetId(),
		r.GetText(),
		r.GetLength(),
		id,
		r.GetMD5(),
		r.GetContentModel(),
		r.GetContentFormat())) {
		
		// Clear page references
		SQL * Delete(REDIRECT).Where(RD_FROM == id);
		SQL * Delete(PAGE_PROPS).Where(PP_PAGE == id);
		SQL * Delete(PAGELINKS).Where(PL_FROM == id);
		SQL * Delete(IWLINKS).Where(IWL_FROM == id);
		SQL * Delete(EXTERNALLINKS).Where(EL_FROM == id);
		SQL * Delete(LANGLINKS).Where(LL_FROM == id);
		SQL * Delete(FILELINKS).Where(IL_FROM == id);
		SQL * Delete(TEMPLATELINKS).Where(TL_FROM == id);
		SQL * Delete(CATEGORYLINKS).Where(CL_FROM == id);
		SQL * Delete(SEARCHINDEX).Where(SI_PAGE == id);
		
		bool r = SQL * Delete(PAGE).Where(PAGE_ID == id);
		ClearMemcached("page" + IntStr(id));
		return r;
	}
	return false;
}

bool Page::SetRestrictions(String restrictions) {
	ASSERT(id >= 0);
	if (SQL * Update(PAGE)(PAGE_RESTRICTIONS_ITEM, restrictions).Where(PAGE_ID == id)) {
		this->restrictions = restrictions;
		StoreMem();
		return true;
	}
	return false;
}

bool Page::SetRedirect(bool b) {
	ASSERT(id >= 0);
	if (SQL * Update(PAGE)(PAGE_IS_REDIRECT, (int)b).Where(PAGE_ID == id)) {
		this->is_redirect = b;
		StoreMem();
		return true;
	}
	return false;
}

bool Page::Touch() {
	ASSERT(id >= 0);
	Time now = GetUtcTime();
	if (SQL * Update(PAGE)(PAGE_TOUCHED, now).Where(PAGE_ID == id)) {
		this->touched = now;
		StoreMem();
		return true;
	}
	return false;
}

bool Page::SetLinksUpdated() {
	ASSERT(id >= 0);
	Time now = GetUtcTime();
	if (SQL * Update(PAGE)(PAGE_LINKS_UPDATED, now).Where(PAGE_ID == id)) {
		this->links_updated = now;
		StoreMem();
		return true;
	}
	return false;
}

bool Page::SetLatestRevision(int rev, bool is_redirect, bool is_new, int len, String content_model) {
	ASSERT(id >= 0);
	Time now = GetUtcTime();
	if (SQL * Update(PAGE)
		(PAGE_LATEST, rev)
		(PAGE_IS_REDIRECT, is_redirect)
		(PAGE_IS_NEW, is_new)
		(PAGE_LEN, len)
		(PAGE_CONTENT_MODEL, content_model)
		(PAGE_TOUCHED, now)
		(PAGE_LINKS_UPDATED, now)
		.Where(PAGE_ID == id)) {
		this->latest_rev = rev;
		this->is_redirect = is_redirect;
		this->is_new = is_new;
		this->len = len;
		this->content_model = content_model;
		touched = now;
		links_updated = now;
		StoreMem();
		return true;
	}
	return false;
}





void Redirection::Load(Sql& sql) {
	from = sql[RD_FROM];
	ns = sql[RD_NAMESPACE];
	hub = sql[RD_HUB];
	title = sql[RD_TITLE];
	interhub = sql[RD_INTERHUB];
	fragment = sql[RD_FRAGMENT];
}

bool Redirection::Add(
	int from,
	int ns,
	int hub,
	String title,
	String interhub,
	String fragment) {
	return SQL * Insert(REDIRECT)
		(RD_FROM, from)
		(RD_NAMESPACE, ns)
		(RD_HUB, hub)
		(RD_TITLE, title)
		(RD_INTERHUB, interhub)
		(RD_FRAGMENT, fragment);
}

bool Redirection::RemoveAll(int page) {
	return SQL * Delete(REDIRECT).Where(RD_FROM == page);
}

Vector<Redirection> Redirection::GetPage(int page) {
	Vector<Redirection> v;
	if (SQL * SelectAll().From(REDIRECT).Where(RD_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void Category::Load(Sql& sql) {
	id = sql[CAT_ID];
	title = sql[CAT_TITLE];
	hub = sql[CAT_HUB];
	pages = sql[CAT_PAGES];
	subcats = sql[CAT_SUBCATS];
	files = sql[CAT_FILES];
}

bool Category::Load(int id) {
	if (SQL * SelectAll().From(CATEGORY).Where(CAT_ID == id) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool Category::Load(int hub, String title) {
	if (SQL * SelectAll().From(CATEGORY).Where(CAT_HUB == hub && CAT_TITLE == title) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool Category::Create(int hub, String title) {
	if (SQL * Insert(CATEGORY)
		(CAT_TITLE, title)
		(CAT_HUB, hub)
		(CAT_PAGES, 0)
		(CAT_SUBCATS, 0)
		(CAT_FILES, 0)) {
		return Load(hub, title);
	}
	return false;
}

bool Category::SetStats(int pages, int subcats, int files) {
	ASSERT(id >= 0);
	if (SQL * Update(CATEGORY)(CAT_PAGES, pages)(CAT_SUBCATS, subcats)(CAT_FILES, files).Where(id == CAT_ID)) {
		this->pages = pages;
		this->subcats = subcats;
		this->files = files;
		return true;
	}
	return false;
}

Vector<Category> Category::GetHub(int hub) {
	Vector<Category> v;
	if (SQL * SelectAll().From(CATEGORY).Where(CAT_HUB == hub)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void PageProp::Load(Sql& sql) {
	page = sql[PP_PAGE];
	propname = sql[PP_PROPNAME];
	value = sql[PP_VALUE];
	sortkey = sql[PP_SORTKEY];
}

bool PageProp::Load(int page, String propname) {
	if (SQL * SelectAll().From(PAGE_PROPS).Where(PP_PAGE == page && PP_PROPNAME == propname) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool PageProp::Remove() {
	ASSERT(page >= 0);
	return SQL * Delete(PAGE_PROPS).Where(PP_PAGE == page && PP_PROPNAME == propname);
}

bool PageProp::Set(int page, String propname, String value) {
	if (SQL * Insert(PAGE_PROPS)(PP_PAGE, page)(PP_PROPNAME, propname)(PP_VALUE, value))
		return true;
	return
		SQL * Update(PAGE_PROPS)(PP_VALUE, value).Where(PP_PAGE == page && PP_PROPNAME == propname);
}

Vector<PageProp> PageProp::GetPage(int page) {
	Vector<PageProp> v;
	if (SQL * SelectAll().From(PAGE_PROPS).Where(PP_PAGE == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void PageRestriction::Load(Sql& sql) {
	id = sql[PR_ID];
	page = sql[PR_PAGE];
	type = sql[PR_TYPE];
	level = sql[PR_LEVEL];
	cascade = sql[PR_CASCADE];
	expiry = sql[PR_EXPIRY];
}

bool PageRestriction::Remove() {
	ASSERT(id >= 0);
	return SQL * Delete(PAGE_RESTRICTIONS).Where(PR_ID == id);
}

bool PageRestriction::Add(
	int page,
	String type,
	String level,
	bool cascade,
	Time expiry) {
	return SQL * Insert(PAGE_RESTRICTIONS)
		(PR_PAGE, page)
		(PR_TYPE, type)
		(PR_LEVEL, level)
		(PR_CASCADE, cascade)
		(PR_EXPIRY, expiry);
}

Vector<PageRestriction> PageRestriction::GetPage(int page) {
	Vector<PageRestriction> v;
	if (SQL * SelectAll().From(PAGE_RESTRICTIONS).Where(PR_PAGE == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void ProtectedTitle::Load(Sql& sql) {
	ns = sql[PT_NAMESPACE];
	hub = sql[PT_HUB];
	title = sql[PT_TITLE];
	user = sql[PT_USER];
	reason = sql[PT_REASON];
	timestamp = sql[PT_TIMESTAMP];
	expiry = sql[PT_EXPIRY];
	create_perm = sql[PT_CREATE_PERM];
}

bool ProtectedTitle::Load(int hub, String title) {
	if (SQL * SelectAll().From(PROTECTED_TITLES).Where(PT_HUB == hub && PT_TITLE == title) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool ProtectedTitle::Remove() {
	return SQL * Delete(PROTECTED_TITLES).Where(PT_HUB == hub && PT_TITLE == title);
}

bool ProtectedTitle::Add(
	int ns,
	int hub,
	String title,
	int user,
	String reason,
	Time expiry,
	String create_perm) {
	return SQL * Insert(PROTECTED_TITLES)
		(PT_NAMESPACE, ns)
		(PT_HUB, hub)
		(PT_TITLE, title)
		(PT_USER, user)
		(PT_REASON, reason)
		(PT_TIMESTAMP, GetUtcTime())
		(PT_EXPIRY, expiry)
		(PT_CREATE_PERM, create_perm);
}

Vector<ProtectedTitle> ProtectedTitle::GetHub(int hub) {
	Vector<ProtectedTitle> v;
	if (SQL * SelectAll().From(PROTECTED_TITLES).Where(PT_HUB == hub)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void PageLink::Load(Sql& sql) {
	from = sql[PL_FROM];
	from_ns = sql[PL_FROM_NAMESPACE];
	hub = sql[PL_HUB];
	ns = sql[PL_NAMESPACE];
	title = sql[PL_TITLE];
}

bool PageLink::Add(
	int from,
	int from_ns,
	int hub,
	int ns,
	String title) {
	return SQL * Insert(PAGELINKS)
		(PL_FROM, from)
		(PL_FROM_NAMESPACE, from_ns)
		(PL_HUB, hub)
		(PL_NAMESPACE, ns)
		(PL_TITLE, title);
}

bool PageLink::RemoveAll(int page) {
	return SQL * Delete(PAGELINKS).Where(PL_FROM == page);
}

Vector<PageLink> PageLink::GetFrom(int page) {
	Vector<PageLink> v;
	if (SQL * SelectAll().From(PAGELINKS).Where(PL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<PageLink> PageLink::GetTo(int hub, String title) {
	Vector<PageLink> v;
	if (SQL * SelectAll().From(PAGELINKS).Where(PL_HUB == hub && PL_TITLE == title)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void InterhubLink::Load(Sql& sql) {
	from_page = sql[IWL_FROM];
	from_hub = sql[IWL_FROM_HUB];
	to_hub = sql[IWL_TO_HUB];
	title = sql[IWL_TITLE];
}

bool InterhubLink::Add(
	int from_page,
	int from_hub,
	int to_hub,
	String title) {
	return SQL * Insert(IWLINKS)
		(IWL_FROM, from_page)
		(IWL_FROM_HUB, from_hub)
		(IWL_TO_HUB, to_hub)
		(IWL_TITLE, title);
}

bool InterhubLink::RemoveAll(int page) {
	return SQL * Delete(IWLINKS).Where(IWL_FROM == page);
}

Vector<InterhubLink> InterhubLink::GetFrom(int page) {
	Vector<InterhubLink> v;
	if (SQL * SelectAll().From(IWLINKS).Where(IWL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<InterhubLink> InterhubLink::GetTo(int hub, String title) {
	Vector<InterhubLink> v;
	if (SQL * SelectAll().From(IWLINKS).Where(IWL_TO_HUB == hub && IWL_TITLE == title)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void ExternalLink::Load(Sql& sql) {
	id = sql[EL_ID];
	from = sql[EL_FROM];
	hub = sql[EL_HUB];
	to = sql[EL_TO];
	index = sql[EL_INDEX];
}

bool ExternalLink::Add(
	int id,
	int from,
	int hub,
	String to,
	String index) {
	return SQL * Insert(EXTERNALLINKS)
		(EL_ID, id)
		(EL_FROM, from)
		(EL_HUB, hub)
		(EL_TO, to)
		(EL_INDEX, index);
}

bool ExternalLink::RemoveAll(int page) {
	return SQL * Delete(EXTERNALLINKS).Where(EL_FROM == page);
}

Vector<ExternalLink> ExternalLink::GetFrom(int page) {
	Vector<ExternalLink> v;
	if (SQL * SelectAll().From(EXTERNALLINKS).Where(EL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<ExternalLink> ExternalLink::GetTo(String url) {
	Vector<ExternalLink> v;
	if (SQL * SelectAll().From(EXTERNALLINKS).Where(EL_TO == url)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<ExternalLink> ExternalLink::GetToIndex(String idx) {
	Vector<ExternalLink> v;
	if (SQL * SelectAll().From(EXTERNALLINKS).Where(EL_INDEX == idx)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void LanguageLink::Load(Sql& sql) {
	from = sql[LL_FROM];
	hub = sql[LL_HUB];
	lang = sql[LL_LANG];
	title = sql[LL_TITLE];
}

bool LanguageLink::Add(
	int from,
	int hub,
	String lang,
	String title) {
	return SQL * Insert(LANGLINKS)
		(LL_FROM, from)
		(LL_HUB, hub)
		(LL_LANG, lang)
		(LL_TITLE, title);
}

bool LanguageLink::RemoveAll(int page) {
	return SQL * Delete(LANGLINKS).Where(LL_FROM == page);
}

Vector<LanguageLink> LanguageLink::GetFrom(int page) {
	Vector<LanguageLink> v;
	if (SQL * SelectAll().From(LANGLINKS).Where(LL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<LanguageLink> LanguageLink::GetTo(String lang, String title) {
	Vector<LanguageLink> v;
	if (SQL * SelectAll().From(LANGLINKS).Where(LL_LANG == lang && LL_TITLE == title)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void FileLink::Load(Sql& sql) {
	from = sql[IL_FROM];
	from_ns = sql[IL_FROM_NAMESPACE];
	from_hub = sql[IL_FROM_HUB];
	to = sql[IL_TO];
}

bool FileLink::Add(
	int from,
	int from_ns,
	int from_hub,
	String to) {
	return SQL * Insert(FILELINKS)
		(IL_FROM, from)
		(IL_FROM_NAMESPACE, from_ns)
		(IL_FROM_HUB, from_hub)
		(IL_TO, to);
}

bool FileLink::RemoveAll(int page) {
	return SQL * Delete(FILELINKS).Where(IL_FROM == page);
}

Vector<FileLink> FileLink::GetFrom(int page) {
	Vector<FileLink> v;
	if (SQL * SelectAll().From(FILELINKS).Where(IL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<FileLink> FileLink::GetTo(String file) {
	Vector<FileLink> v;
	if (SQL * SelectAll().From(FILELINKS).Where(IL_TO == file)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void TemplateLink::Load(Sql& sql) {
	from = sql[TL_FROM];
	from_ns = sql[TL_FROM_NAMESPACE];
	from_hub = sql[TL_FROM_HUB];
	ns = sql[TL_NAMESPACE];
	title = sql[TL_TITLE];
}

bool TemplateLink::Add(
	int from,
	int from_ns,
	int from_hub,
	int ns,
	String title) {
	return SQL * Insert(TEMPLATELINKS)
		(TL_FROM, from)
		(TL_FROM_NAMESPACE, from_ns)
		(TL_FROM_HUB, from_hub)
		(TL_NAMESPACE, ns)
		(TL_TITLE, title);
}

bool TemplateLink::RemoveAll(int page) {
	return SQL * Delete(TEMPLATELINKS).Where(TL_FROM == page);
}

Vector<TemplateLink> TemplateLink::GetFrom(int page) {
	Vector<TemplateLink> v;
	if (SQL * SelectAll().From(TEMPLATELINKS).Where(TL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<TemplateLink> TemplateLink::GetTo(String title) {
	Vector<TemplateLink> v;
	if (SQL * SelectAll().From(TEMPLATELINKS).Where(TL_TITLE == title)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void CategoryLink::Load(Sql& sql) {
	from = sql[CL_FROM];
	hub = sql[CL_HUB];
	to = sql[CL_TO];
	sortkey = sql[CL_SORTKEY];
	sortkey_prefix = sql[CL_SORTKEY_PREFIX];
	timestamp = sql[CL_TIMESTAMP];
	collation = sql[CL_COLLATION];
	type = (int)sql[CL_TYPE];
}

bool CategoryLink::Add(
	int from,
	int hub,
	String to,
	String sortkey,
	String sortkey_prefix,
	String collation,
	uint8 type) {
	return SQL * Insert(CATEGORYLINKS)
		(CL_FROM, from)
		(CL_HUB, hub)
		(CL_TO, to)
		(CL_SORTKEY, sortkey)
		(CL_SORTKEY_PREFIX, sortkey_prefix)
		(CL_TIMESTAMP, GetUtcTime())
		(CL_COLLATION, collation)
		(CL_TYPE, type);
}

Vector<CategoryLink> CategoryLink::GetFrom(int page) {
	Vector<CategoryLink> v;
	if (SQL * SelectAll().From(CATEGORYLINKS).Where(CL_FROM == page)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<CategoryLink> CategoryLink::GetTo(int hub, String title) {
	Vector<CategoryLink> v;
	if (SQL * SelectAll().From(CATEGORYLINKS).Where(CL_HUB == hub && CL_TO == title)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}







void File::Serialize(Stream& s) {
	s % (hub);
	s % (name);
	s % (size);
	s % (width);
	s % (height);
	s % (metadata);
	s % (bits);
	s % (media_type);
	s % (major_mime);
	s % (minor_mime);
	s % (description);
	s % (user);
	s % (user_text);
	s % (timestamp);
	s % (md5);
}

void File::Load(Sql& sql) {
	hub = sql[FILE_HUB];
	name = sql[FILE_NAME];
	size = sql[FILE_SIZE];
	width = sql[FILE_WIDTH];
	height = sql[FILE_HEIGHT];
	metadata = sql[FILE_METADATA];
	bits = sql[FILE_BITS];
	media_type = sql[FILE_MEDIA_TYPE];
	major_mime = sql[FILE_MAJOR_MIME];
	minor_mime = sql[FILE_MINOR_MIME];
	description = sql[FILE_DESCRIPTION];
	user = sql[FILE_USER];
	user_text = sql[FILE_USER_TEXT];
	timestamp = sql[FILE_TIMESTAMP];
	md5 = sql[FILE_MD5];
}

bool File::Load(int hub, String name) {
	if (GetMemcached("file-" + IntStr(hub) + "-" + name, *this))
		return true;
	if (SQL * SelectAll().From(FILE_).Where(FILE_HUB == hub && FILE_NAME == name) && SQL.Fetch()) {
		Load(SQL);
		StoreMem();
		return true;
	}
	return false;
}

bool File::Create(int hub, String title) {
	if (SQL * Insert(FILE_)
		(FILE_HUB, hub)
		(FILE_NAME, title)
		(FILE_SIZE, 0)
		(FILE_WIDTH, 0)
		(FILE_HEIGHT, 0)
		(FILE_BITS, 0)
		(FILE_MEDIA_TYPE, 0)
		(FILE_MAJOR_MIME, 0)
		(FILE_USER, 0)
		(FILE_TIMESTAMP, GetUtcTime())) {
		return Load(hub, title);
	}
	return false;
}

bool File::Update(
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
	String md5) {
	ASSERT(hub >= 0 && !name.IsEmpty());
	Time now = GetUtcTime();
	if (SQL * ::Update(FILE_)
		(FILE_SIZE, size)
		(FILE_WIDTH, width)
		(FILE_HEIGHT, height)
		(FILE_METADATA, metadata)
		(FILE_BITS, bits)
		(FILE_MEDIA_TYPE, media_type)
		(FILE_MAJOR_MIME, major_mime)
		(FILE_MINOR_MIME, minor_mime)
		(FILE_DESCRIPTION, description)
		(FILE_USER, user)
		(FILE_USER_TEXT, user_text)
		(FILE_TIMESTAMP, now)
		(FILE_MD5, md5).Where(FILE_HUB == hub && FILE_NAME == name)) {
		this->size = size;
		this->width = width;
		this->height = height;
		this->metadata = metadata;
		this->bits = bits;
		this->media_type = media_type;
		this->major_mime = major_mime;
		this->minor_mime = minor_mime;
		this->description = description;
		this->user = user;
		this->user_text = user_text;
		this->timestamp = now;
		this->md5 = md5;
		StoreMem();
		return true;
	}
	return false;
}

Vector<File> File::GetUser(int user) {
	Vector<File> v;
	if (SQL * SelectAll().From(FILE_).Where(FILE_USER == user)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

Vector<File> File::GetHub(int hub) {
	Vector<File> v;
	if (SQL * SelectAll().From(FILE_).Where(FILE_HUB == hub)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void ArchiveFile::Load(Sql& sql) {
	id = sql[FA_ID];
	hub = sql[FA_HUB];
	name = sql[FA_NAME];
	archive_name = sql[FA_ARCHIVE_NAME];
	storage_group = sql[FA_STORAGE_GROUP];
	storage_key = sql[FA_STORAGE_KEY];
	deleted_user = sql[FA_DELETED_USER];
	deleted_timestamp = sql[FA_DELETED_TIMESTAMP];
	deleted_reason = sql[FA_DELETED_REASON];
	size = sql[FA_SIZE];
	width = sql[FA_WIDTH];
	height = sql[FA_HEIGHT];
	metadata = sql[FA_METADATA];
	bits = sql[FA_BITS];
	media_type = sql[FA_MEDIA_TYPE];
	major_mime = sql[FA_MAJOR_MIME];
	minor_mime = sql[FA_MINOR_MIME];
	description = sql[FA_DESCRIPTION];
	user = sql[FA_USER];
	user_text = sql[FA_USER_TEXT];
	timestamp = sql[FA_TIMESTAMP];
	deleted = sql[FA_DELETED];
	md5 = sql[FA_MD5];
}

bool ArchiveFile::Delete() {
	ASSERT(id >= 0);
	return SQL * Update(ARCHIVE)(FA_DELETED, true).Where(FA_ID == id);
}

bool ArchiveFile::Add(
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
	String md5) {
	return SQL * Insert(ARCHIVE)
		(FA_NAME, name)
		(FA_ARCHIVE_NAME, archive_name)
		(FA_STORAGE_GROUP, storage_group)
		(FA_STORAGE_KEY, storage_key)
		(FA_DELETED_USER, deleted_user)
		(FA_DELETED_TIMESTAMP, deleted_timestamp)
		(FA_DELETED_REASON, deleted_reason)
		(FA_SIZE, size)
		(FA_WIDTH, width)
		(FA_HEIGHT, height)
		(FA_METADATA, metadata)
		(FA_BITS, bits)
		(FA_MEDIA_TYPE, media_type)
		(FA_MAJOR_MIME, major_mime)
		(FA_MINOR_MIME, minor_mime)
		(FA_DESCRIPTION, description)
		(FA_USER, user)
		(FA_USER_TEXT, user_text)
		(FA_TIMESTAMP, timestamp)
		(FA_DELETED, true)
		(FA_MD5, md5);
}

Vector<ArchiveFile> ArchiveFile::GetName(int hub, String name) {
	Vector<ArchiveFile> v;
	if (SQL * SelectAll().From(ARCHIVE).Where(FA_HUB == hub && FA_NAME == name)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}





void UploadStash::Load(Sql& sql) {
	id = sql[US_ID];
	user = sql[US_USER];
	key = sql[US_KEY];
	orig_path = sql[US_ORIG_PATH];
	path = sql[US_PATH];
	source_type = sql[US_SOURCE_TYPE];
	timestamp = sql[US_TIMESTAMP];
	status = sql[US_STATUS];
	chunk_inx = sql[US_CHUNK_INX];
	props = sql[US_PROPS];
	size = sql[US_SIZE];
	md5 = sql[US_MD5];
	mime = sql[US_MIME];
	media_type = sql[US_MEDIA_TYPE];
	image_width = sql[US_IMAGE_WIDTH];
	image_height =  sql[US_IMAGE_HEIGHT];
	image_bits = sql[US_IMAGE_BITS];
}

bool UploadStash::Create(String key) {
	if (SQL * Insert(UPLOADSTASH)
		(US_USER, 0)
		(US_KEY, key)
		(US_CHUNK_INX, 0)
		(US_SIZE, 0)
		(US_MEDIA_TYPE, 0)
		(US_IMAGE_WIDTH, 0)
		(US_IMAGE_HEIGHT, 0)
		(US_IMAGE_BITS, 0)) {
		Load(key);
		return true;
	}
	return false;
}

bool UploadStash::Load(String key) {
	if (SQL * SelectAll().From(UPLOADSTASH).Where(US_KEY == key) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

bool UploadStash::Remove() {
	ASSERT(id >= 0);
	return SQL * Delete(UPLOADSTASH).Where(US_ID == id);
}

bool UploadStash::Set(
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
	int image_bits) {
	ASSERT(id >= 0);
	return SQL * Update(UPLOADSTASH)
		(US_ORIG_PATH, orig_path)
		(US_PATH, path)
		(US_SOURCE_TYPE, source_type)
		(US_TIMESTAMP, timestamp)
		(US_STATUS, status)
		(US_CHUNK_INX, chunk_inx)
		(US_PROPS, props)
		(US_SIZE, size)
		(US_MD5, md5)
		(US_MIME, mime)
		(US_MEDIA_TYPE, media_type)
		(US_IMAGE_WIDTH, image_width)
		(US_IMAGE_HEIGHT, image_height)
		(US_IMAGE_BITS, image_bits)
		.Where(US_ID == id);
}





void Job::Load(Sql& sql) {
	id = sql[JOB_ID];
	cmd = sql[JOB_CMD];
	ns = sql[JOB_NAMESPACE];
	hub = sql[JOB_HUB];
	title = sql[JOB_TITLE];
	timestamp = sql[JOB_TIMESTAMP];
	params = sql[JOB_PARAMS];
	random = sql[JOB_RANDOM];
	attempts = sql[JOB_ATTEMPTS];
	token = sql[JOB_TOKEN];
	token_timestamp = sql[JOB_TOKEN_TIMESTAMP];
	md5 = sql[JOB_MD5];
}

bool Job::Add(
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
	String md5) {
	return SQL * Insert(JOB)
		(JOB_CMD, cmd)
		(JOB_NAMESPACE, ns)
		(JOB_HUB, hub)
		(JOB_TITLE, title)
		(JOB_TIMESTAMP, timestamp)
		(JOB_PARAMS, params)
		(JOB_RANDOM, random)
		(JOB_ATTEMPTS, attempts)
		(JOB_TOKEN, token)
		(JOB_TOKEN_TIMESTAMP, token_timestamp)
		(JOB_MD5, md5);
}

Vector<Job> Job::GetRange(int begin, int end) {
	Vector<Job> v;
	if (SQL * SelectAll().From(JOB).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

int Job::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(JOB) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}





void SiteStat::Load(Sql& sql) {
	id = sql[SS_ID];
	total_edits = sql[SS_TOTAL_EDITS];
	good_articles = sql[SS_GOOD_ARTICLES];
	total_pages = sql[SS_TOTAL_PAGES];
	users = sql[SS_USERS];
	active_users = sql[SS_ACTIVE_USERS];
	files = sql[SS_FILES];
	hubs = sql[SS_HUBS];
	timestamp = sql[SS_TIMESTAMP];
}

bool SiteStat::Add(
	int64 total_edits,
	int64 good_articles,
	int64 total_pages,
	int64 users,
	int64 active_users,
	int64 files,
	int hubs) {
	return SQL * Insert(SITE_STATS)
		(SS_TOTAL_EDITS, total_edits)
		(SS_GOOD_ARTICLES, good_articles)
		(SS_TOTAL_PAGES, total_pages)
		(SS_USERS, users)
		(SS_ACTIVE_USERS, active_users)
		(SS_FILES, files)
		(SS_HUBS, hubs);
}

Vector<SiteStat> SiteStat::GetRange(int begin, int end) {
	Vector<SiteStat> v;
	if (SQL * SelectAll().From(SITE_STATS).Limit(begin, end)) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

int SiteStat::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(SITE_STATS) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}





void SearchIndexItem::Load(Sql& sql) {
	page = sql[SI_PAGE];
	hub = sql[SI_HUB];
	title = sql[SI_TITLE];
	text = sql[SI_TEXT];
}

bool SearchIndexItem::Load(int page) {
	if (SQL * SelectAll().From(SEARCHINDEX).Where(SI_PAGE == page) && SQL.Fetch()) {
		Load(SQL);
		return true;
	}
	return false;
}

Vector<SearchIndexItem> SearchIndexItem::GetHub(int hub) {
	Vector<SearchIndexItem> v;
	if (SQL * SelectAll().From(SEARCHINDEX).Where(SI_HUB == hub) && SQL.Fetch()) {
		while (SQL.Fetch())
			v.Add().Load(SQL);
	}
	return v;
}

int SearchIndexItem::GetCount() {
	if (SQL * Select(Count(SqlAll())).From(SEARCHINDEX) && SQL.Fetch()) {
		int count = SQL[0];
		return count;
	}
	return -1;
}


NAMESPACE_TOYHUB_END
