#include "Core.h"

NAMESPACE_UPP_BEGIN

static int s_month[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int s_month_off[] = {
	  0,  31,  59,  90, 120, 151,
	181, 212, 243, 273, 304, 334
};

bool Date::IsLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int Date::GetDaysOfMonth(int m, int y) {
	ASSERT(m >= 1 && m <= 12);
	return s_month[m - 1] + (m == 2) * IsLeapYear(y);
}

int64 Date::Get() const {
	int64 y400 = (year / 400 ) - 2;
	int64 ym = year - y400 * 400;
	return y400 * (400 * 365 + 100 - 3) +
	        ym * 365 + s_month_off[month - 1] + (day - 1) +
	       (ym - 1) / 4 - (ym - 1) / 100 + (ym - 1) / 400 + 1 +
	       (month > 2) * IsLeapYear(ym);
}

String Date::ToString() const {
	return	IntStr(day) + "." + IntStr(month) + "." + IntStr(day);
}

void Date::Set(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

void Date::Set(int64 d) {
	if(d == 0) {
		day = 0; month = 0; year = 0;
		return;
	}
	int q;
	int leap;
	year = 0;
	q = d / (400 * 365 + 100 - 3);
	year += 400 * q;
	d -= q * (400 * 365 + 100 - 3);
	if(d < 0) {
		year -= 400;
		d += 400 * 365 + 100 - 3;
	}
	leap = 1;
	if(d >= 100 * 365 + 24 + 1) {
		d--;
		q = d / (100 * 365 + 24);
		year += 100 * q;
		d -= q * (100 * 365 + 24);
		leap = 0;
	}
	if(d >= 365 * 4 + leap) {
		q = (d + 1 - leap) / (365 * 4 + 1);
		year += 4 * q;
		d -= q * (365 * 4 + 1) - 1 + leap;
		leap = 1;
	}
	if(d >= 365 + leap) {
		q = (d - leap) / 365;
		year += q;
		d -= q * 365 + leap;
		leap = 0;
	}
	int i;
	for(i = 0; i < 12; i++) {
		int q = s_month[i] + (i == 1) * leap;
		if(q > d) break;
		d -= q;
	}
	month = i + 1;
	day = d + 1;
}


void Time::Set(int y, int mon, int d, int h, int m, int s) {
	Date::Set(y, mon, d);
	hour = h;
	min = m;
	sec = s;
}

void Time::Set(int64 scalar) {
	int q = (int)(scalar / (24 * 3600));
	Date::Set(q);
	int n = int(scalar - (int64)q * 24 * 3600);
	hour = n / 3600;
	n %= 3600;
	min = n / 60;
	sec = n % 60;
}

String Time::ToString() const {
	char m[3];
	m[0] = '0' + min / 10;
	m[1] = '0' + min / 10;
	m[2] = 0;
	char s[3];
	s[0] = '0' + sec / 10;
	s[1] = '0' + sec / 10;
	s[2] = 0;
	return	IntStr(year) + "." + IntStr(month) + "." + IntStr(day) +
			" " + IntStr(hour) + ":" + String(m) + ":" + String(s);
	//return Format("%s.%s.%s %s:%s", (int)t.day(), (int)t.month(), (int)t.year(), (int)t.hour(), min);
}


String Time::ToDiffString() const {
	#define DIV(x, y) {x = seconds / (y); seconds = seconds % (y);};
	#define PRINT(x) {if (x) {out.Cat(' '); out += IntStr64(x) + " " #x;};}
	String out;
	int64 seconds = Get();
	
	if (seconds > -60 && seconds < 60) return "Now";
	
	if (seconds < 0)		{out += "-"; seconds *= -1;}
	else if (seconds > 0)	out += "+";
	
	int64 years;
	int64 months;
	int64 days;
	int64 hours;
	int64 minutes;
	
	DIV(years, 365*24*60*60);
	DIV(months, 30*24*60*60);
	DIV(days,    24*60*60);
	DIV(hours,      60*60);
	DIV(minutes,       60);
	PRINT(years);
	PRINT(months);
	PRINT(days);
	PRINT(hours);
	PRINT(minutes);
	return out;
	#undef DIV
	#undef PRINT
}

Time Time::GetSys() {
	Time t;
	t.Set(CurrentTime());
	return t;
}

void Time::SetFromStamp(int seconds) {
	static int64 begin = Time(1970,1,1).Get();
	Set(begin + (int64)seconds);
}

int Time::GetStamp() const {
	static int64 begin = Time(1970,1,1).Get();
	return Get() - begin;
}

Time& Time::operator+=(int seconds) {
	TODO
}

bool Time::operator>=(const Time& t) const {
	TODO
}

bool Time::operator<=(const Time& t) const {
	TODO
}

bool Time::operator>(const Time& t) const {
	TODO
}

bool Time::operator<(const Time& t) const {
	TODO
}















String GetTimeString(Time t) {
	String s;
	s << (int)t.day << "." << (int)t.month << "." << (int)t.year << " "
	  << (int)t.hour << ":" << (int)t.min << ":" << (int)t.sec;
	return s;
}


dword Timestamp(const Time& t) {
	return (dword)(t.Get() - Time(1970,1,1).Get());
}

dword TimestampNow() {
	return (dword)(GetSysTime().Get() - Time(1970,1,1).Get());
}

Time TimeFromTimestamp(int64 seconds) {
	return Time(1970, 1, 1) + seconds;
}

String TimeDiffString(int64 seconds) {
	String out;
	
	if (seconds > -60 && seconds < 60) return "Now";
	
	if (seconds < 0)		{out += "-"; seconds *= -1;}
	else if (seconds > 0)	out += "+";
	
	int64 years, months, days, hours, minutes;
	#define DIV(x, y) x = seconds / (y); seconds = seconds % (y);
	DIV(years, 365*24*60*60);
	DIV(months, 30*24*60*60);
	DIV(days,    24*60*60);
	DIV(hours,      60*60);
	DIV(minutes,       60);
	#undef DIV
	#undef PRINT
	#define PRINT(x) if (x) out += " " + IntStr64(x) + " " #x;
	PRINT(years);
	PRINT(months);
	PRINT(days);
	PRINT(hours);
	PRINT(minutes);
	#undef PRINT
	return out;
}











uint32 global_ticks;

struct TimeCallbackItem : Moveable<TimeCallbackItem> {
	void* id;
	Callback cb;
	uint32 ticks;
	uint32 delay;
	bool is_periodical;
	byte epoch;
};

Array<TimeCallbackItem> __time_cbs;
Mutex __time_cbs_lock;

void SetTimeCallback(int delay_ms, Callback cb, void *id) {
	bool is_periodical = false;
	if (delay_ms < 0) {
		delay_ms *= -1;
		is_periodical = true;
	}
	
	for(int i = 0; i < __time_cbs.GetCount(); i++) {
		TimeCallbackItem& it = __time_cbs[i];
		if (it.id == id) {
			it.cb = cb;
			it.ticks = global_ticks + delay_ms;
			it.delay = delay_ms;
			it.is_periodical = is_periodical;
			it.epoch = it.ticks < global_ticks ? 1 : 0;
			return;
		}
	}
	
	
	__time_cbs_lock.Enter();
	
	TimeCallbackItem& it = __time_cbs.Add();
	it.id = id;
	it.cb = cb;
	it.ticks = global_ticks + delay_ms;
	it.delay = delay_ms;
	it.is_periodical = is_periodical;
	it.epoch = it.ticks < global_ticks ? 1 : 0;
	
	__time_cbs_lock.Leave();
}

void KillTimeCallback(void *id) {
	for(int i = 0; i < __time_cbs.GetCount(); i++) {
		TimeCallbackItem& it = __time_cbs[i];
		if (it.id == id) {
			__time_cbs_lock.Enter();
			__time_cbs.Remove(i);
			__time_cbs_lock.Leave();
			break;
		}
	}
}

bool ExistsTimeCallback(void *id) {
	for(int i = 0; i < __time_cbs.GetCount(); i++) {
		TimeCallbackItem& it = __time_cbs[i];
		if (it.id == id) {
			return true;
		}
	}
	return false;
}

void ExecuteTimeCallback() {
	Vector<int> remlist;
	
	for(int i = 0; i < __time_cbs.GetCount(); i++) {
		TimeCallbackItem& it = __time_cbs[i];
		if (it.epoch == 0 && it.ticks <= global_ticks) {
			it.cb.Execute();
			if (it.is_periodical) {
				it.ticks = global_ticks + it.delay;
				it.epoch = it.ticks < global_ticks ? 1 : 0;
			}
			else
				remlist.Add(i);
		}
	}
	// TODO remove vector of positions
	
	
	__time_cbs_lock.Enter();
	__time_cbs.Remove(remlist);
	__time_cbs_lock.Leave();
}

void DecreaseTimeCallbackEpoch() {
	__time_cbs_lock.Enter();
	
	for(int i = 0; i < __time_cbs.GetCount(); i++) {
		TimeCallbackItem& it = __time_cbs[i];
		if (it.epoch > 0)
			it.epoch--;
		else
			__time_cbs.Remove(i--);
	}
	
	__time_cbs_lock.Leave();
}

void AddGlobalTicks(uint32 diff) {
	uint32 prev_global_ticks = global_ticks;
	global_ticks += diff;
	
	// overflow
	if (global_ticks < prev_global_ticks)
		DecreaseTimeCallbackEpoch();
	
	ExecuteTimeCallback();
}

uint32 GetGlobalTicks() {return global_ticks;}
void SetGlobalTicks(uint32 ticks) {global_ticks = ticks;}




bool IsLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int  GetDaysOfMonth(int m, int y) {
	ASSERT(m >= 1 && m <= 12);
	return s_month[m - 1] + (m == 2) * IsLeapYear(y);
}

int64 DateSeconds(uint64 year, uint64 month, uint64 day) {
	int64 y400 = (year / 400 ) - 2;
	int64 ym = year - y400 * 400;
	return y400 * (400 * 365 + 100 - 3) +
	        ym * 365 + s_month_off[month - 1] + (day - 1) +
	       (ym - 1) / 4 - (ym - 1) / 100 + (ym - 1) / 400 + 1 +
	       (month > 2) * IsLeapYear(ym);
}

int64 TimeSeconds(uint64 year, uint64 month, uint64 day, uint64 hour, uint64 minute, uint64 second) {
	int64 date = DateSeconds(year, month, day);
	return date * (int64)24 * 3600 + hour * 3600 + minute * 60 + second;
}

int64 CurrentTime() {
	time_t rawtime;
	time(&rawtime);
	
	struct tm t;
	#ifdef flagWIN32
	localtime_s(&t, &rawtime);
	#else
	t = *localtime(&rawtime);
	#endif
	
	return TimeSeconds(
		t.tm_year + 1900, t.tm_mon, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);
}

uint64 GetNanoSeconds() {
	auto p2 = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(p2.time_since_epoch()).count();
}

uint64 GetMilliSeconds() {
	auto p2 = std::chrono::steady_clock::now();
	return (int)std::chrono::duration_cast<std::chrono::milliseconds>(p2.time_since_epoch()).count();
}

void GetSysSeedValues(int64* a, int64* b, int64* c) {
	if (a) *a = CurrentTime();
	if (b) *b = GetNanoSeconds();
	if (c) *c = GetMilliSeconds();
}












void GetSysTimeObject(short& year, uint8& mon, uint8& day, uint8& hour, uint8& min, uint8& sec) {
	time_t rawtime;
	
	time(&rawtime);
	
	struct tm tmp;
	#ifdef flagWIN32
	localtime_s(&tmp, &rawtime);
	#else
	tmp = *localtime(&rawtime);
	#endif
	
	year	= 1900 + tmp.tm_year;
	mon		= 1 + tmp.tm_mon;
	day		= tmp.tm_mday;
	hour	= tmp.tm_hour;
	min		= tmp.tm_min;
	sec		= tmp.tm_sec;
}

Time GetSysTime() {
	Time t;
	GetSysTimeObject(t.year, t.month, t.day, t.hour, t.min, t.sec);
	return t;
}

Time GetUtcTime() {
	TODO
}






void TimeStop::Reset() {
	start = high_resolution_clock::now();
}

double TimeStop::Elapsed() const {
	return Seconds() * 1000.0;
}

double TimeStop::Seconds() const {
	std::chrono::high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double> >(stop - start);
	return time_span.count();
}

double TimeStop::ResetElapsed() {
	return ResetSeconds() * 1000.0;
}

double TimeStop::ResetSeconds() {
	std::chrono::high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double> >(stop - start);
	start = stop;
	return time_span.count();
}

String TimeStop::ToString() const {
	double d = Seconds();
	int sec = d;
	int ms = (d - (double)sec) * 1000;
	String s;
	if (!sec && !ms) return "0 ms";
	if (sec)	{s << IntStr(sec) << " seconds";}
	if (ms)		{if (sec) {s.Cat(' ');} s << IntStr(ms) << " ms";}
	return s;
}

NAMESPACE_UPP_END
