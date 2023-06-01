#ifndef NO_CONST_V

const dword VEC2_O     = PKG_GEOMETRY_V  | 0;
const dword VEC3_O     = PKG_GEOMETRY_V  | 1;
const dword VEC4_O     = PKG_GEOMETRY_V  | 2;
const dword IVEC2_O    = PKG_GEOMETRY_V  | 3;
const dword IVEC3_O    = PKG_GEOMETRY_V  | 4;
const dword IVEC4_O    = PKG_GEOMETRY_V  | 5;
const dword QUAT_O     = PKG_GEOMETRY_V  | 6;
const dword MAT2_O     = PKG_GEOMETRY_V  | 7;
const dword MAT3_O     = PKG_GEOMETRY_V  | 8;
const dword MAT34_O    = PKG_GEOMETRY_V  | 9;
const dword MAT43_O    = PKG_GEOMETRY_V  | 10;
const dword MAT4_O     = PKG_GEOMETRY_V  | 11;
const dword MODEL_O    = PKG_GEOMETRY_V  | 12;
const dword TRANSMAT_O = PKG_GEOMETRY_V  | 13;
const dword AXES2_O    = PKG_GEOMETRY_V  | 14;
const dword AXES3_O    = PKG_GEOMETRY_V  | 15;
const dword AXES2S_O   = PKG_GEOMETRY_V  | 16;
const dword AXES3S_O   = PKG_GEOMETRY_V  | 17;
const dword CTRLMAT_O  = PKG_GEOMETRY_V  | 18;

#endif

OBJ_TYPE_NO(vec2,   VEC2_O)
OBJ_TYPE_NO(vec3,   VEC3_O)
OBJ_TYPE_NO(vec4,   VEC3_O)
OBJ_TYPE_NO(ivec2,  IVEC2_O)
OBJ_TYPE_NO(ivec3,  IVEC3_O)
OBJ_TYPE_NO(ivec4,  IVEC3_O)
OBJ_TYPE_NO(quat,   QUAT_O)
OBJ_TYPE_NO(mat2,   MAT2_O)
OBJ_TYPE_NO(mat3,   MAT3_O)
//OBJ_TYPE_NO(mat34, MAT34_O)
OBJ_TYPE_NO(mat43,  MAT43_O)
OBJ_TYPE_NO(mat4,   MAT4_O)
OBJ_TYPE_NO(Model,  MODEL_O)
OBJ_TYPE_NO(TransformMatrix,  TRANSMAT_O)
OBJ_TYPE_NO(axes2,  AXES2_O)
OBJ_TYPE_NO(axes3,  AXES3_O)
OBJ_TYPE_NO(axes2s, AXES2S_O)
OBJ_TYPE_NO(axes3s, AXES3S_O)
OBJ_TYPE_NO(ControllerMatrix,  CTRLMAT_O)
