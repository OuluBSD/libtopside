#ifndef NO_CONST_V
// Package constants
const dword PKG_NATIVE_V	= 0x1000;
const dword PKG_CORE_V		= 0x2000;
const dword PKG_CTRLCORE_V	= 0x3000;
const dword PKG_CTRLLIB_V	= 0x4000;
const dword PKG_LOCAL_V		= 0x5000;
const dword PKG_LOCALCTRL_V	= 0x6000;
const dword PKG_GEOMETRY_V	= 0x7000;
const dword PKG_PHYSICS_V	= 0x8000;
const dword PKG_HIGH_V		= 0x9000;
const dword PKG_HIGHCTRL_V	= 0xa000;
const dword PKG_PARALLEL_V	= 0xb000;
const dword PKG_SERIAL_V	= 0xc000;
const dword PKG_ECS_V		= 0xd000;

// Core vars
const dword VOID_O    = 0;
const dword UNKNOWN_O = 0xFFFFFFFF;
const dword BOOL_O    = PKG_NATIVE_V  | 1;
const dword UINT8_O   = PKG_NATIVE_V  | 2;
const dword INT8_O    = PKG_NATIVE_V  | 3;
const dword UINT16_O  = PKG_NATIVE_V  | 4;
const dword INT16_O   = PKG_NATIVE_V  | 5;
const dword UINT32_O  = PKG_NATIVE_V  | 6;
const dword INT32_O   = PKG_NATIVE_V  | 7;
const dword UINT64_O  = PKG_NATIVE_V  | 8;
const dword INT64_O   = PKG_NATIVE_V  | 9;
const dword FLOAT_O   = PKG_NATIVE_V | 10;
const dword DOUBLE_O  = PKG_NATIVE_V | 11;

const dword STRING_O  = PKG_CORE_V | 0;
const dword WSTRING_O = PKG_CORE_V | 1;
const dword DATE_O    = PKG_CORE_V | 2;
const dword TIME_O    = PKG_CORE_V | 3;
const dword POINT_O   = PKG_CORE_V | 4;
const dword SIZE_O    = PKG_CORE_V | 5;
const dword RECT_O    = PKG_CORE_V | 6;
const dword COLOR_O   = PKG_CORE_V | 7;
const dword RGBA_O    = PKG_CORE_V | 8;
const dword IMAGE_O   = PKG_CORE_V | 9;
const dword ERROR_O   = PKG_CORE_V | 10;

const dword OBJECTARRAY_O = PKG_CORE_V | 11;
const dword OBJECTMAP_O   = PKG_CORE_V | 12;
const dword OBJECT_ARRAY_AND_MAP_O   = PKG_CORE_V | 13;

#endif


OBJ_TYPE_NO(bool,     BOOL_O )
OBJ_TYPE_NO(uint8,    UINT8_O )
OBJ_TYPE_NO(uint16,   UINT16_O )
OBJ_TYPE_NO(uint32,   UINT32_O )
OBJ_TYPE_NO(uint64,   UINT64_O )
OBJ_TYPE_NO(int8,     INT8_O )
OBJ_TYPE_NO(int16,    INT16_O )
OBJ_TYPE_NO(int32,    INT32_O )
OBJ_TYPE_NO(int64,    INT64_O )
OBJ_TYPE_NO(double,   DOUBLE_O )
OBJ_TYPE_NO(float,    FLOAT_O )

OBJ_TYPE_NO(String,   STRING_O )
OBJ_TYPE_NO(WString,  WSTRING_O )
OBJ_TYPE_NO(Date,     DATE_O )
OBJ_TYPE_NO(Time,     TIME_O )
OBJ_TYPE_NO(Point,    POINT_O )
OBJ_TYPE_NO(Size,     SIZE_O )
OBJ_TYPE_NO(Rect,     RECT_O )
OBJ_TYPE_NO(Color,    COLOR_O )
OBJ_TYPE_NO(RGBA,     RGBA_O )
OBJ_TYPE_NO(Image,    IMAGE_O )
OBJ_TYPE_NO(Exc,      ERROR_O )

