#ifndef _ToyHub_Defs_h_
#define _ToyHub_Defs_h_


#include <Skylark/Skylark.h>
#ifdef flagMYSQL
	#include <MySql/MySql.h>
#else
	#include <sqlite3/Sqlite3.h>
	#define flagSTANDALONE
#endif
#include <Sql/Sql.h>


#define TINYINT(x)					COLUMN("tinyint", int, x, 0, 0)
#define TINYINT_(x)					COLUMN_("tinyint", int, x, 0, 0)
#define BINARY(x, n)				COLUMN("binary", String, x, n, 0)
#define BINARY_(x, n)				COLUMN_("binary", String, x, n, 0)
#define VARBINARY(x, n)				COLUMN("varbinary", String, x, n, 0)
#define VARBINARY_(x, n)			COLUMN_("varbinary", String, x, n, 0)
#define TINYBLOB(x)					COLUMN("tinyblob", String, x, UINT8_MAX, 0)
#define TINYBLOB_(x)				COLUMN_("tinyblob", String, x, UINT8_MAX, 0)
#define MEDIUMBLOB(x)				COLUMN("mediumblob", String, x, INT_MAX/2, 0)
#define MEDIUMBLOB_(x)				COLUMN_("mediumblob", String, x, INT_MAX/2, 0)

#ifdef flagMYSQL
	#define SCHEMADIALECT <MySql/MySqlSchema.h>
#else
	#define SCHEMADIALECT <sqlite3/Sqlite3Schema.h>
#endif
#define MODEL <ToyHub/Model.sch>
#include <Sql/sch_header.h>


#define TOYHUB						ToyHub
#define NAMESPACE_TOYHUB_BEGIN		namespace  TS { namespace  TOYHUB {
#define NAMESPACE_TOYHUB_END		}}

NAMESPACE_TOYHUB_BEGIN
using namespace UPP;
NAMESPACE_TOYHUB_END


#ifdef flagSTANDALONE
inline void InitMemcachedThread() {}
template <class T> inline bool SetMemcached(String key, T& obj) {return false;}
template <class T> inline bool GetMemcached(String key, T& obj) {return false;}
inline bool ClearMemcached(String key) {return false;}
#endif



#endif
