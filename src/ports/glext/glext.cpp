#ifdef flagWIN32

#include "maindef.h"
#include <gl/GL.h>
#include "glext.h"


GLPROC_VOID(glBlendColor,
(GLfloat red ,  GLfloat green ,  GLfloat blue , GLfloat alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glBlendEquation,
(GLenum mode),
(mode)
)

GLPROC_VOID(glDrawRangeElements,
(GLenum mode ,  GLuint start ,  GLuint end ,  GLsizei count ,  GLenum type , const GLvoid *indices),
(mode , start , end , count , type , indices)
)

GLPROC_VOID(glTexImage3D,
(GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , internalformat , width , height , depth , border , format , type , pixels)
)

GLPROC_VOID(glTexSubImage3D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , yoffset , zoffset , width , height , depth , format , type , pixels)
)

GLPROC_VOID(glCopyTexSubImage3D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , level , xoffset , yoffset , zoffset , x , y , width , height)
)





GLPROC_VOID(glActiveTexture,
(GLenum texture),
(texture)
)

GLPROC_VOID(glSampleCoverage,
(GLfloat value , GLboolean invert),
(value , invert)
)

GLPROC_VOID(glCompressedTexImage3D,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , height , depth , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexImage2D,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , height , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexImage1D,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage3D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , yoffset , zoffset , width , height , depth , format , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage2D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , yoffset , width , height , format , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage1D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , width , format , imageSize , data)
)

GLPROC_VOID(glGetCompressedTexImage,
(GLenum target ,  GLint level , GLvoid *img),
(target , level , img)
)

GLPROC_VOID(glClientActiveTexture,
(GLenum texture),
(texture)
)

GLPROC_VOID(glMultiTexCoord1d,
(GLenum target , GLdouble s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1dv,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1f,
(GLenum target , GLfloat s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1fv,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1i,
(GLenum target , GLint s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1iv,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1s,
(GLenum target , GLshort s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1sv,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2d,
(GLenum target ,  GLdouble s , GLdouble t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2dv,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2f,
(GLenum target ,  GLfloat s , GLfloat t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2fv,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2i,
(GLenum target ,  GLint s , GLint t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2iv,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2s,
(GLenum target ,  GLshort s , GLshort t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2sv,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3d,
(GLenum target ,  GLdouble s ,  GLdouble t , GLdouble r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3dv,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3f,
(GLenum target ,  GLfloat s ,  GLfloat t , GLfloat r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3fv,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3i,
(GLenum target ,  GLint s ,  GLint t , GLint r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3iv,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3s,
(GLenum target ,  GLshort s ,  GLshort t , GLshort r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3sv,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4d,
(GLenum target ,  GLdouble s ,  GLdouble t ,  GLdouble r , GLdouble q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4dv,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4f,
(GLenum target ,  GLfloat s ,  GLfloat t ,  GLfloat r , GLfloat q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4fv,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4i,
(GLenum target ,  GLint s ,  GLint t ,  GLint r , GLint q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4iv,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4s,
(GLenum target ,  GLshort s ,  GLshort t ,  GLshort r , GLshort q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4sv,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glLoadTransposeMatrixf,
(const GLfloat *m),
(m)
)

GLPROC_VOID(glLoadTransposeMatrixd,
(const GLdouble *m),
(m)
)

GLPROC_VOID(glMultTransposeMatrixf,
(const GLfloat *m),
(m)
)

GLPROC_VOID(glMultTransposeMatrixd,
(const GLdouble *m),
(m)
)





GLPROC_VOID(glBlendFuncSeparate,
(GLenum sfactorRGB ,  GLenum dfactorRGB ,  GLenum sfactorAlpha , GLenum dfactorAlpha),
(sfactorRGB , dfactorRGB , sfactorAlpha , dfactorAlpha)
)

GLPROC_VOID(glMultiDrawArrays,
(GLenum mode ,  const GLint *first ,  const GLsizei *count , GLsizei drawcount),
(mode , first , count , drawcount)
)

GLPROC_VOID(glMultiDrawElements,
(GLenum mode ,  const GLsizei *count ,  GLenum type ,  const GLvoid *const*indices , GLsizei drawcount),
(mode , count , type , indices , drawcount)
)

GLPROC_VOID(glPointParameterf,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPointParameterfv,
(GLenum pname , const GLfloat *params),
(pname , params)
)

GLPROC_VOID(glPointParameteri,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glPointParameteriv,
(GLenum pname , const GLint *params),
(pname , params)
)

GLPROC_VOID(glFogCoordf,
(GLfloat coord),
(coord)
)

GLPROC_VOID(glFogCoordfv,
(const GLfloat *coord),
(coord)
)

GLPROC_VOID(glFogCoordd,
(GLdouble coord),
(coord)
)

GLPROC_VOID(glFogCoorddv,
(const GLdouble *coord),
(coord)
)

GLPROC_VOID(glFogCoordPointer,
(GLenum type ,  GLsizei stride , const GLvoid *pointer),
(type , stride , pointer)
)

GLPROC_VOID(glSecondaryColor3b,
(GLbyte red ,  GLbyte green , GLbyte blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3bv,
(const GLbyte *v),
(v)
)

GLPROC_VOID(glSecondaryColor3d,
(GLdouble red ,  GLdouble green , GLdouble blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3dv,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glSecondaryColor3f,
(GLfloat red ,  GLfloat green , GLfloat blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3fv,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glSecondaryColor3i,
(GLint red ,  GLint green , GLint blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3iv,
(const GLint *v),
(v)
)

GLPROC_VOID(glSecondaryColor3s,
(GLshort red ,  GLshort green , GLshort blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3sv,
(const GLshort *v),
(v)
)

GLPROC_VOID(glSecondaryColor3ub,
(GLubyte red ,  GLubyte green , GLubyte blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3ubv,
(const GLubyte *v),
(v)
)

GLPROC_VOID(glSecondaryColor3ui,
(GLuint red ,  GLuint green , GLuint blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3uiv,
(const GLuint *v),
(v)
)

GLPROC_VOID(glSecondaryColor3us,
(GLushort red ,  GLushort green , GLushort blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3usv,
(const GLushort *v),
(v)
)

GLPROC_VOID(glSecondaryColorPointer,
(GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(size , type , stride , pointer)
)

GLPROC_VOID(glWindowPos2d,
(GLdouble x , GLdouble y),
(x , y)
)

GLPROC_VOID(glWindowPos2dv,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos2f,
(GLfloat x , GLfloat y),
(x , y)
)

GLPROC_VOID(glWindowPos2fv,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos2i,
(GLint x , GLint y),
(x , y)
)

GLPROC_VOID(glWindowPos2iv,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos2s,
(GLshort x , GLshort y),
(x , y)
)

GLPROC_VOID(glWindowPos2sv,
(const GLshort *v),
(v)
)

GLPROC_VOID(glWindowPos3d,
(GLdouble x ,  GLdouble y , GLdouble z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3dv,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos3f,
(GLfloat x ,  GLfloat y , GLfloat z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3fv,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos3i,
(GLint x ,  GLint y , GLint z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3iv,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos3s,
(GLshort x ,  GLshort y , GLshort z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3sv,
(const GLshort *v),
(v)
)



GLPROC_VOID(glGenQueries,
(GLsizei n , GLuint *ids),
(n , ids)
)

GLPROC_VOID(glDeleteQueries,
(GLsizei n , const GLuint *ids),
(n , ids)
)

GLPROC_RETURN1(GLboolean,
glIsQuery,
(GLuint id),
(id)
)

GLPROC_VOID(glBeginQuery,
(GLenum target , GLuint id),
(target , id)
)

GLPROC_VOID(glEndQuery,
(GLenum target),
(target)
)

GLPROC_VOID(glGetQueryiv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetQueryObjectiv,
(GLuint id ,  GLenum pname , GLint *params),
(id , pname , params)
)

GLPROC_VOID(glGetQueryObjectuiv,
(GLuint id ,  GLenum pname , GLuint *params),
(id , pname , params)
)

GLPROC_VOID(glBindBuffer,
(GLenum target , GLuint buffer),
(target , buffer)
)

GLPROC_VOID(glDeleteBuffers,
(GLsizei n , const GLuint *buffers),
(n , buffers)
)

GLPROC_VOID(glGenBuffers,
(GLsizei n , GLuint *buffers),
(n , buffers)
)

GLPROC_RETURN1(GLboolean,
glIsBuffer,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glBufferData,
(GLenum target ,  GLsizeiptr size ,  const GLvoid *data , GLenum usage),
(target , size , data , usage)
)

GLPROC_VOID(glBufferSubData,
(GLenum target ,  GLintptr offset ,  GLsizeiptr size , const GLvoid *data),
(target , offset , size , data)
)

GLPROC_VOID(glGetBufferSubData,
(GLenum target ,  GLintptr offset ,  GLsizeiptr size , GLvoid *data),
(target , offset , size , data)
)

GLPROC_RETURN1(void *,
glMapBuffer,
(GLenum target , GLenum access),
(target , access)
)

GLPROC_RETURN1(GLboolean,
glUnmapBuffer,
(GLenum target),
(target)
)

GLPROC_VOID(glGetBufferParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetBufferPointerv,
(GLenum target ,  GLenum pname , GLvoid **params),
(target , pname , params)
)



GLPROC_VOID(glBlendEquationSeparate,
(GLenum modeRGB , GLenum modeAlpha),
(modeRGB , modeAlpha)
)

GLPROC_VOID(glDrawBuffers,
(GLsizei n , const GLenum *bufs),
(n , bufs)
)

GLPROC_VOID(glStencilOpSeparate,
(GLenum face ,  GLenum sfail ,  GLenum dpfail , GLenum dppass),
(face , sfail , dpfail , dppass)
)

GLPROC_VOID(glStencilFuncSeparate,
(GLenum face ,  GLenum func ,  GLint ref , GLuint mask),
(face , func , ref , mask)
)

GLPROC_VOID(glStencilMaskSeparate,
(GLenum face , GLuint mask),
(face , mask)
)

GLPROC_VOID(glAttachShader,
(GLuint program , GLuint shader),
(program , shader)
)

GLPROC_VOID(glBindAttribLocation,
(GLuint program ,  GLuint index , const GLchar *name),
(program , index , name)
)

GLPROC_VOID(glCompileShader,
(GLuint shader),
(shader)
)

GLPROC_RETURN1(GLuint,
glCreateProgram,
(void),
()
)

GLPROC_RETURN1(GLuint,
glCreateShader,
(GLenum type),
(type)
)

GLPROC_VOID(glDeleteProgram,
(GLuint program),
(program)
)

GLPROC_VOID(glDeleteShader,
(GLuint shader),
(shader)
)

GLPROC_VOID(glDetachShader,
(GLuint program , GLuint shader),
(program , shader)
)

GLPROC_VOID(glDisableVertexAttribArray,
(GLuint index),
(index)
)

GLPROC_VOID(glEnableVertexAttribArray,
(GLuint index),
(index)
)

GLPROC_VOID(glGetActiveAttrib,
(GLuint program ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length ,  GLint *size ,  GLenum *type , GLchar *name),
(program , index , bufSize , length , size , type , name)
)

GLPROC_VOID(glGetActiveUniform,
(GLuint program ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length ,  GLint *size ,  GLenum *type , GLchar *name),
(program , index , bufSize , length , size , type , name)
)

GLPROC_VOID(glGetAttachedShaders,
(GLuint program ,  GLsizei maxCount ,  GLsizei *count , GLuint *shaders),
(program , maxCount , count , shaders)
)

GLPROC_RETURN1(GLint,
glGetAttribLocation,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glGetProgramiv,
(GLuint program ,  GLenum pname , GLint *params),
(program , pname , params)
)

GLPROC_VOID(glGetProgramInfoLog,
(GLuint program ,  GLsizei bufSize ,  GLsizei *length , GLchar *infoLog),
(program , bufSize , length , infoLog)
)

GLPROC_VOID(glGetShaderiv,
(GLuint shader ,  GLenum pname , GLint *params),
(shader , pname , params)
)

GLPROC_VOID(glGetShaderInfoLog,
(GLuint shader ,  GLsizei bufSize ,  GLsizei *length , GLchar *infoLog),
(shader , bufSize , length , infoLog)
)

GLPROC_VOID(glGetShaderSource,
(GLuint shader ,  GLsizei bufSize ,  GLsizei *length , GLchar *source),
(shader , bufSize , length , source)
)

GLPROC_RETURN1(GLint,
glGetUniformLocation,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glGetUniformfv,
(GLuint program ,  GLint location , GLfloat *params),
(program , location , params)
)

GLPROC_VOID(glGetUniformiv,
(GLuint program ,  GLint location , GLint *params),
(program , location , params)
)

GLPROC_VOID(glGetVertexAttribdv,
(GLuint index ,  GLenum pname , GLdouble *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribfv,
(GLuint index ,  GLenum pname , GLfloat *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribiv,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribPointerv,
(GLuint index ,  GLenum pname , GLvoid **pointer),
(index , pname , pointer)
)

GLPROC_RETURN1(GLboolean,
glIsProgram,
(GLuint program),
(program)
)

GLPROC_RETURN1(GLboolean,
glIsShader,
(GLuint shader),
(shader)
)

GLPROC_VOID(glLinkProgram,
(GLuint program),
(program)
)

GLPROC_VOID(glShaderSource,
(GLuint shader ,  GLsizei count ,  const GLchar *const*string , const GLint *length),
(shader , count , string , length)
)

GLPROC_VOID(glUseProgram,
(GLuint program),
(program)
)

GLPROC_VOID(glUniform1f,
(GLint location , GLfloat v0),
(location , v0)
)

GLPROC_VOID(glUniform2f,
(GLint location ,  GLfloat v0 , GLfloat v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3f,
(GLint location ,  GLfloat v0 ,  GLfloat v1 , GLfloat v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4f,
(GLint location ,  GLfloat v0 ,  GLfloat v1 ,  GLfloat v2 , GLfloat v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1i,
(GLint location , GLint v0),
(location , v0)
)

GLPROC_VOID(glUniform2i,
(GLint location ,  GLint v0 , GLint v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3i,
(GLint location ,  GLint v0 ,  GLint v1 , GLint v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4i,
(GLint location ,  GLint v0 ,  GLint v1 ,  GLint v2 , GLint v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1fv,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform2fv,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform3fv,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform4fv,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform1iv,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform2iv,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform3iv,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform4iv,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniformMatrix2fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glValidateProgram,
(GLuint program),
(program)
)

GLPROC_VOID(glVertexAttrib1d,
(GLuint index , GLdouble x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1f,
(GLuint index , GLfloat x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1fv,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1s,
(GLuint index , GLshort x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1sv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2d,
(GLuint index ,  GLdouble x , GLdouble y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2f,
(GLuint index ,  GLfloat x , GLfloat y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2fv,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2s,
(GLuint index ,  GLshort x , GLshort y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2sv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3d,
(GLuint index ,  GLdouble x ,  GLdouble y , GLdouble z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3f,
(GLuint index ,  GLfloat x ,  GLfloat y , GLfloat z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3fv,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3s,
(GLuint index ,  GLshort x ,  GLshort y , GLshort z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3sv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Nbv,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Niv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Nsv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Nub,
(GLuint index ,  GLubyte x ,  GLubyte y ,  GLubyte z , GLubyte w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4Nubv,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Nuiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4Nusv,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4bv,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4d,
(GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4f,
(GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4fv,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4iv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4s,
(GLuint index ,  GLshort x ,  GLshort y ,  GLshort z , GLshort w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4sv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4ubv,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4uiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4usv,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glVertexAttribPointer,
(GLuint index ,  GLint size ,  GLenum type ,  GLboolean normalized ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , normalized , stride , pointer)
)



GLPROC_VOID(glUniformMatrix2x3fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3x2fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix2x4fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4x2fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3x4fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4x3fv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)



GLPROC_VOID(glColorMaski,
(GLuint index ,  GLboolean r ,  GLboolean g ,  GLboolean b , GLboolean a),
(index , r , g , b , a)
)

GLPROC_VOID(glGetBooleani_v,
(GLenum target ,  GLuint index , GLboolean *data),
(target , index , data)
)

GLPROC_VOID(glGetIntegeri_v,
(GLenum target ,  GLuint index , GLint *data),
(target , index , data)
)

GLPROC_VOID(glEnablei,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_VOID(glDisablei,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_RETURN1(GLboolean,
glIsEnabledi,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_VOID(glBeginTransformFeedback,
(GLenum primitiveMode),
(primitiveMode)
)

GLPROC_VOID(glEndTransformFeedback,
(void),
()
)

GLPROC_VOID(glBindBufferRange,
(GLenum target ,  GLuint index ,  GLuint buffer ,  GLintptr offset , GLsizeiptr size),
(target , index , buffer , offset , size)
)

GLPROC_VOID(glBindBufferBase,
(GLenum target ,  GLuint index , GLuint buffer),
(target , index , buffer)
)

GLPROC_VOID(glTransformFeedbackVaryings,
(GLuint program ,  GLsizei count ,  const GLchar *const*varyings , GLenum bufferMode),
(program , count , varyings , bufferMode)
)

GLPROC_VOID(glGetTransformFeedbackVarying,
(GLuint program ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length ,  GLsizei *size ,  GLenum *type , GLchar *name),
(program , index , bufSize , length , size , type , name)
)

GLPROC_VOID(glClampColor,
(GLenum target , GLenum clamp),
(target , clamp)
)

GLPROC_VOID(glBeginConditionalRender,
(GLuint id , GLenum mode),
(id , mode)
)

GLPROC_VOID(glEndConditionalRender,
(void),
()
)

GLPROC_VOID(glVertexAttribIPointer,
(GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , stride , pointer)
)

GLPROC_VOID(glGetVertexAttribIiv,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribIuiv,
(GLuint index ,  GLenum pname , GLuint *params),
(index , pname , params)
)

GLPROC_VOID(glVertexAttribI1i,
(GLuint index , GLint x),
(index , x)
)

GLPROC_VOID(glVertexAttribI2i,
(GLuint index ,  GLint x , GLint y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribI3i,
(GLuint index ,  GLint x ,  GLint y , GLint z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribI4i,
(GLuint index ,  GLint x ,  GLint y ,  GLint z , GLint w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribI1ui,
(GLuint index , GLuint x),
(index , x)
)

GLPROC_VOID(glVertexAttribI2ui,
(GLuint index ,  GLuint x , GLuint y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribI3ui,
(GLuint index ,  GLuint x ,  GLuint y , GLuint z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribI4ui,
(GLuint index ,  GLuint x ,  GLuint y ,  GLuint z , GLuint w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribI1iv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI2iv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI3iv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4iv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI1uiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI2uiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI3uiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4uiv,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4bv,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4sv,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4ubv,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4usv,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glGetUniformuiv,
(GLuint program ,  GLint location , GLuint *params),
(program , location , params)
)

GLPROC_VOID(glBindFragDataLocation,
(GLuint program ,  GLuint color , const GLchar *name),
(program , color , name)
)

GLPROC_RETURN1(GLint,
glGetFragDataLocation,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glUniform1ui,
(GLint location , GLuint v0),
(location , v0)
)

GLPROC_VOID(glUniform2ui,
(GLint location ,  GLuint v0 , GLuint v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3ui,
(GLint location ,  GLuint v0 ,  GLuint v1 , GLuint v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4ui,
(GLint location ,  GLuint v0 ,  GLuint v1 ,  GLuint v2 , GLuint v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1uiv,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform2uiv,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform3uiv,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform4uiv,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glTexParameterIiv,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glTexParameterIuiv,
(GLenum target ,  GLenum pname , const GLuint *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameterIiv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameterIuiv,
(GLenum target ,  GLenum pname , GLuint *params),
(target , pname , params)
)

GLPROC_VOID(glClearBufferiv,
(GLenum buffer ,  GLint drawbuffer , const GLint *value),
(buffer , drawbuffer , value)
)

GLPROC_VOID(glClearBufferuiv,
(GLenum buffer ,  GLint drawbuffer , const GLuint *value),
(buffer , drawbuffer , value)
)

GLPROC_VOID(glClearBufferfv,
(GLenum buffer ,  GLint drawbuffer , const GLfloat *value),
(buffer , drawbuffer , value)
)

GLPROC_VOID(glClearBufferfi,
(GLenum buffer ,  GLint drawbuffer ,  GLfloat depth , GLint stencil),
(buffer , drawbuffer , depth , stencil)
)

GLPROC_RETURN1(const GLubyte *,
glGetStringi,
(GLenum name , GLuint index),
(name , index)
)

GLPROC_RETURN1(GLboolean,
glIsRenderbuffer,
(GLuint renderbuffer),
(renderbuffer)
)

GLPROC_VOID(glBindRenderbuffer,
(GLenum target , GLuint renderbuffer),
(target , renderbuffer)
)

GLPROC_VOID(glDeleteRenderbuffers,
(GLsizei n , const GLuint *renderbuffers),
(n , renderbuffers)
)

GLPROC_VOID(glGenRenderbuffers,
(GLsizei n , GLuint *renderbuffers),
(n , renderbuffers)
)

GLPROC_VOID(glRenderbufferStorage,
(GLenum target ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , internalformat , width , height)
)

GLPROC_VOID(glGetRenderbufferParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_RETURN1(GLboolean,
glIsFramebuffer,
(GLuint framebuffer),
(framebuffer)
)

GLPROC_VOID(glBindFramebuffer,
(GLenum target , GLuint framebuffer),
(target , framebuffer)
)

GLPROC_VOID(glDeleteFramebuffers,
(GLsizei n , const GLuint *framebuffers),
(n , framebuffers)
)

GLPROC_VOID(glGenFramebuffers,
(GLsizei n , GLuint *framebuffers),
(n , framebuffers)
)

GLPROC_RETURN1(GLenum,
glCheckFramebufferStatus,
(GLenum target),
(target)
)

GLPROC_VOID(glFramebufferTexture1D,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(target , attachment , textarget , texture , level)
)

GLPROC_VOID(glFramebufferTexture2D,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(target , attachment , textarget , texture , level)
)

GLPROC_VOID(glFramebufferTexture3D,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture ,  GLint level , GLint zoffset),
(target , attachment , textarget , texture , level , zoffset)
)

GLPROC_VOID(glFramebufferRenderbuffer,
(GLenum target ,  GLenum attachment ,  GLenum renderbuffertarget , GLuint renderbuffer),
(target , attachment , renderbuffertarget , renderbuffer)
)

GLPROC_VOID(glGetFramebufferAttachmentParameteriv,
(GLenum target ,  GLenum attachment ,  GLenum pname , GLint *params),
(target , attachment , pname , params)
)

GLPROC_VOID(glGenerateMipmap,
(GLenum target),
(target)
)

GLPROC_VOID(glBlitFramebuffer,
(GLint srcX0 ,  GLint srcY0 ,  GLint srcX1 ,  GLint srcY1 ,  GLint dstX0 ,  GLint dstY0 ,  GLint dstX1 ,  GLint dstY1 ,  GLbitfield mask , GLenum filter),
(srcX0 , srcY0 , srcX1 , srcY1 , dstX0 , dstY0 , dstX1 , dstY1 , mask , filter)
)

GLPROC_VOID(glRenderbufferStorageMultisample,
(GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , samples , internalformat , width , height)
)

GLPROC_VOID(glFramebufferTextureLayer,
(GLenum target ,  GLenum attachment ,  GLuint texture ,  GLint level , GLint layer),
(target , attachment , texture , level , layer)
)

GLPROC_RETURN1(void *,
glMapBufferRange,
(GLenum target ,  GLintptr offset ,  GLsizeiptr length , GLbitfield access),
(target , offset , length , access)
)

GLPROC_VOID(glFlushMappedBufferRange,
(GLenum target ,  GLintptr offset , GLsizeiptr length),
(target , offset , length)
)

GLPROC_VOID(glBindVertexArray,
(GLuint array),
(array)
)

GLPROC_VOID(glDeleteVertexArrays,
(GLsizei n , const GLuint *arrays),
(n , arrays)
)

GLPROC_VOID(glGenVertexArrays,
(GLsizei n , GLuint *arrays),
(n , arrays)
)

GLPROC_RETURN1(GLboolean,
glIsVertexArray,
(GLuint array),
(array)
)




GLPROC_VOID(glDrawArraysInstanced,
(GLenum mode ,  GLint first ,  GLsizei count , GLsizei instancecount),
(mode , first , count , instancecount)
)

GLPROC_VOID(glDrawElementsInstanced,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const GLvoid *indices , GLsizei instancecount),
(mode , count , type , indices , instancecount)
)

GLPROC_VOID(glTexBuffer,
(GLenum target ,  GLenum internalformat , GLuint buffer),
(target , internalformat , buffer)
)

GLPROC_VOID(glPrimitiveRestartIndex,
(GLuint index),
(index)
)

GLPROC_VOID(glCopyBufferSubData,
(GLenum readTarget ,  GLenum writeTarget ,  GLintptr readOffset ,  GLintptr writeOffset , GLsizeiptr size),
(readTarget , writeTarget , readOffset , writeOffset , size)
)

GLPROC_VOID(glGetUniformIndices,
(GLuint program ,  GLsizei uniformCount ,  const GLchar *const*uniformNames , GLuint *uniformIndices),
(program , uniformCount , uniformNames , uniformIndices)
)

GLPROC_VOID(glGetActiveUniformsiv,
(GLuint program ,  GLsizei uniformCount ,  const GLuint *uniformIndices ,  GLenum pname , GLint *params),
(program , uniformCount , uniformIndices , pname , params)
)

GLPROC_VOID(glGetActiveUniformName,
(GLuint program ,  GLuint uniformIndex ,  GLsizei bufSize ,  GLsizei *length , GLchar *uniformName),
(program , uniformIndex , bufSize , length , uniformName)
)

GLPROC_RETURN1(GLuint,
glGetUniformBlockIndex,
(GLuint program , const GLchar *uniformBlockName),
(program , uniformBlockName)
)

GLPROC_VOID(glGetActiveUniformBlockiv,
(GLuint program ,  GLuint uniformBlockIndex ,  GLenum pname , GLint *params),
(program , uniformBlockIndex , pname , params)
)

GLPROC_VOID(glGetActiveUniformBlockName,
(GLuint program ,  GLuint uniformBlockIndex ,  GLsizei bufSize ,  GLsizei *length , GLchar *uniformBlockName),
(program , uniformBlockIndex , bufSize , length , uniformBlockName)
)

GLPROC_VOID(glUniformBlockBinding,
(GLuint program ,  GLuint uniformBlockIndex , GLuint uniformBlockBinding),
(program , uniformBlockIndex , uniformBlockBinding)
)



GLPROC_VOID(glDrawElementsBaseVertex,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const GLvoid *indices , GLint basevertex),
(mode , count , type , indices , basevertex)
)

GLPROC_VOID(glDrawRangeElementsBaseVertex,
(GLenum mode ,  GLuint start ,  GLuint end ,  GLsizei count ,  GLenum type ,  const GLvoid *indices , GLint basevertex),
(mode , start , end , count , type , indices , basevertex)
)

GLPROC_VOID(glDrawElementsInstancedBaseVertex,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const GLvoid *indices ,  GLsizei instancecount , GLint basevertex),
(mode , count , type , indices , instancecount , basevertex)
)

GLPROC_VOID(glMultiDrawElementsBaseVertex,
(GLenum mode ,  const GLsizei *count ,  GLenum type ,  const GLvoid *const*indices ,  GLsizei drawcount , const GLint *basevertex),
(mode , count , type , indices , drawcount , basevertex)
)

GLPROC_VOID(glProvokingVertex,
(GLenum mode),
(mode)
)

GLPROC_RETURN1(GLsync,
glFenceSync,
(GLenum condition , GLbitfield flags),
(condition , flags)
)

GLPROC_RETURN1(GLboolean,
glIsSync,
(GLsync sync),
(sync)
)

GLPROC_VOID(glDeleteSync,
(GLsync sync),
(sync)
)

GLPROC_RETURN1(GLenum,
glClientWaitSync,
(GLsync sync ,  GLbitfield flags , GLuint64 timeout),
(sync , flags , timeout)
)

GLPROC_VOID(glWaitSync,
(GLsync sync ,  GLbitfield flags , GLuint64 timeout),
(sync , flags , timeout)
)

GLPROC_VOID(glGetInteger64v,
(GLenum pname , GLint64 *params),
(pname , params)
)

GLPROC_VOID(glGetSynciv,
(GLsync sync ,  GLenum pname ,  GLsizei bufSize ,  GLsizei *length , GLint *values),
(sync , pname , bufSize , length , values)
)

GLPROC_VOID(glGetInteger64i_v,
(GLenum target ,  GLuint index , GLint64 *data),
(target , index , data)
)

GLPROC_VOID(glGetBufferParameteri64v,
(GLenum target ,  GLenum pname , GLint64 *params),
(target , pname , params)
)

GLPROC_VOID(glFramebufferTexture,
(GLenum target ,  GLenum attachment ,  GLuint texture , GLint level),
(target , attachment , texture , level)
)

GLPROC_VOID(glTexImage2DMultisample,
(GLenum target ,  GLsizei samples ,  GLint internalformat ,  GLsizei width ,  GLsizei height , GLboolean fixedsamplelocations),
(target , samples , internalformat , width , height , fixedsamplelocations)
)

GLPROC_VOID(glTexImage3DMultisample,
(GLenum target ,  GLsizei samples ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedsamplelocations),
(target , samples , internalformat , width , height , depth , fixedsamplelocations)
)

GLPROC_VOID(glGetMultisamplefv,
(GLenum pname ,  GLuint index , GLfloat *val),
(pname , index , val)
)

GLPROC_VOID(glSampleMaski,
(GLuint index , GLbitfield mask),
(index , mask)
)



GLPROC_VOID(glBindFragDataLocationIndexed,
(GLuint program ,  GLuint colorNumber ,  GLuint index , const GLchar *name),
(program , colorNumber , index , name)
)

GLPROC_RETURN1(GLint,
glGetFragDataIndex,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glGenSamplers,
(GLsizei count , GLuint *samplers),
(count , samplers)
)

GLPROC_VOID(glDeleteSamplers,
(GLsizei count , const GLuint *samplers),
(count , samplers)
)

GLPROC_RETURN1(GLboolean,
glIsSampler,
(GLuint sampler),
(sampler)
)

GLPROC_VOID(glBindSampler,
(GLuint unit , GLuint sampler),
(unit , sampler)
)

GLPROC_VOID(glSamplerParameteri,
(GLuint sampler ,  GLenum pname , GLint param),
(sampler , pname , param)
)

GLPROC_VOID(glSamplerParameteriv,
(GLuint sampler ,  GLenum pname , const GLint *param),
(sampler , pname , param)
)

GLPROC_VOID(glSamplerParameterf,
(GLuint sampler ,  GLenum pname , GLfloat param),
(sampler , pname , param)
)

GLPROC_VOID(glSamplerParameterfv,
(GLuint sampler ,  GLenum pname , const GLfloat *param),
(sampler , pname , param)
)

GLPROC_VOID(glSamplerParameterIiv,
(GLuint sampler ,  GLenum pname , const GLint *param),
(sampler , pname , param)
)

GLPROC_VOID(glSamplerParameterIuiv,
(GLuint sampler ,  GLenum pname , const GLuint *param),
(sampler , pname , param)
)

GLPROC_VOID(glGetSamplerParameteriv,
(GLuint sampler ,  GLenum pname , GLint *params),
(sampler , pname , params)
)

GLPROC_VOID(glGetSamplerParameterIiv,
(GLuint sampler ,  GLenum pname , GLint *params),
(sampler , pname , params)
)

GLPROC_VOID(glGetSamplerParameterfv,
(GLuint sampler ,  GLenum pname , GLfloat *params),
(sampler , pname , params)
)

GLPROC_VOID(glGetSamplerParameterIuiv,
(GLuint sampler ,  GLenum pname , GLuint *params),
(sampler , pname , params)
)

GLPROC_VOID(glQueryCounter,
(GLuint id , GLenum target),
(id , target)
)

GLPROC_VOID(glGetQueryObjecti64v,
(GLuint id ,  GLenum pname , GLint64 *params),
(id , pname , params)
)

GLPROC_VOID(glGetQueryObjectui64v,
(GLuint id ,  GLenum pname , GLuint64 *params),
(id , pname , params)
)

GLPROC_VOID(glVertexAttribDivisor,
(GLuint index , GLuint divisor),
(index , divisor)
)

GLPROC_VOID(glVertexAttribP1ui,
(GLuint index ,  GLenum type ,  GLboolean normalized , GLuint value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP1uiv,
(GLuint index ,  GLenum type ,  GLboolean normalized , const GLuint *value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP2ui,
(GLuint index ,  GLenum type ,  GLboolean normalized , GLuint value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP2uiv,
(GLuint index ,  GLenum type ,  GLboolean normalized , const GLuint *value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP3ui,
(GLuint index ,  GLenum type ,  GLboolean normalized , GLuint value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP3uiv,
(GLuint index ,  GLenum type ,  GLboolean normalized , const GLuint *value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP4ui,
(GLuint index ,  GLenum type ,  GLboolean normalized , GLuint value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexAttribP4uiv,
(GLuint index ,  GLenum type ,  GLboolean normalized , const GLuint *value),
(index , type , normalized , value)
)

GLPROC_VOID(glVertexP2ui,
(GLenum type , GLuint value),
(type , value)
)

GLPROC_VOID(glVertexP2uiv,
(GLenum type , const GLuint *value),
(type , value)
)

GLPROC_VOID(glVertexP3ui,
(GLenum type , GLuint value),
(type , value)
)

GLPROC_VOID(glVertexP3uiv,
(GLenum type , const GLuint *value),
(type , value)
)

GLPROC_VOID(glVertexP4ui,
(GLenum type , GLuint value),
(type , value)
)

GLPROC_VOID(glVertexP4uiv,
(GLenum type , const GLuint *value),
(type , value)
)

GLPROC_VOID(glTexCoordP1ui,
(GLenum type , GLuint coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP1uiv,
(GLenum type , const GLuint *coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP2ui,
(GLenum type , GLuint coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP2uiv,
(GLenum type , const GLuint *coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP3ui,
(GLenum type , GLuint coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP3uiv,
(GLenum type , const GLuint *coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP4ui,
(GLenum type , GLuint coords),
(type , coords)
)

GLPROC_VOID(glTexCoordP4uiv,
(GLenum type , const GLuint *coords),
(type , coords)
)

GLPROC_VOID(glMultiTexCoordP1ui,
(GLenum texture ,  GLenum type , GLuint coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP1uiv,
(GLenum texture ,  GLenum type , const GLuint *coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP2ui,
(GLenum texture ,  GLenum type , GLuint coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP2uiv,
(GLenum texture ,  GLenum type , const GLuint *coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP3ui,
(GLenum texture ,  GLenum type , GLuint coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP3uiv,
(GLenum texture ,  GLenum type , const GLuint *coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP4ui,
(GLenum texture ,  GLenum type , GLuint coords),
(texture , type , coords)
)

GLPROC_VOID(glMultiTexCoordP4uiv,
(GLenum texture ,  GLenum type , const GLuint *coords),
(texture , type , coords)
)

GLPROC_VOID(glNormalP3ui,
(GLenum type , GLuint coords),
(type , coords)
)

GLPROC_VOID(glNormalP3uiv,
(GLenum type , const GLuint *coords),
(type , coords)
)

GLPROC_VOID(glColorP3ui,
(GLenum type , GLuint color),
(type , color)
)

GLPROC_VOID(glColorP3uiv,
(GLenum type , const GLuint *color),
(type , color)
)

GLPROC_VOID(glColorP4ui,
(GLenum type , GLuint color),
(type , color)
)

GLPROC_VOID(glColorP4uiv,
(GLenum type , const GLuint *color),
(type , color)
)

GLPROC_VOID(glSecondaryColorP3ui,
(GLenum type , GLuint color),
(type , color)
)

GLPROC_VOID(glSecondaryColorP3uiv,
(GLenum type , const GLuint *color),
(type , color)
)



GLPROC_VOID(glMinSampleShading,
(GLfloat value),
(value)
)

GLPROC_VOID(glBlendEquationi,
(GLuint buf , GLenum mode),
(buf , mode)
)

GLPROC_VOID(glBlendEquationSeparatei,
(GLuint buf ,  GLenum modeRGB , GLenum modeAlpha),
(buf , modeRGB , modeAlpha)
)

GLPROC_VOID(glBlendFunci,
(GLuint buf ,  GLenum src , GLenum dst),
(buf , src , dst)
)

GLPROC_VOID(glBlendFuncSeparatei,
(GLuint buf ,  GLenum srcRGB ,  GLenum dstRGB ,  GLenum srcAlpha , GLenum dstAlpha),
(buf , srcRGB , dstRGB , srcAlpha , dstAlpha)
)

GLPROC_VOID(glDrawArraysIndirect,
(GLenum mode , const GLvoid *indirect),
(mode , indirect)
)

GLPROC_VOID(glDrawElementsIndirect,
(GLenum mode ,  GLenum type , const GLvoid *indirect),
(mode , type , indirect)
)

GLPROC_VOID(glUniform1d,
(GLint location , GLdouble x),
(location , x)
)

GLPROC_VOID(glUniform2d,
(GLint location ,  GLdouble x , GLdouble y),
(location , x , y)
)

GLPROC_VOID(glUniform3d,
(GLint location ,  GLdouble x ,  GLdouble y , GLdouble z),
(location , x , y , z)
)

GLPROC_VOID(glUniform4d,
(GLint location ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(location , x , y , z , w)
)

GLPROC_VOID(glUniform1dv,
(GLint location ,  GLsizei count , const GLdouble *value),
(location , count , value)
)

GLPROC_VOID(glUniform2dv,
(GLint location ,  GLsizei count , const GLdouble *value),
(location , count , value)
)

GLPROC_VOID(glUniform3dv,
(GLint location ,  GLsizei count , const GLdouble *value),
(location , count , value)
)

GLPROC_VOID(glUniform4dv,
(GLint location ,  GLsizei count , const GLdouble *value),
(location , count , value)
)

GLPROC_VOID(glUniformMatrix2dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix2x3dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix2x4dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3x2dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3x4dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4x2dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4x3dv,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(location , count , transpose , value)
)

GLPROC_VOID(glGetUniformdv,
(GLuint program ,  GLint location , GLdouble *params),
(program , location , params)
)

GLPROC_RETURN1(GLint,
glGetSubroutineUniformLocation,
(GLuint program ,  GLenum shadertype , const GLchar *name),
(program , shadertype , name)
)

GLPROC_RETURN1(GLuint,
glGetSubroutineIndex,
(GLuint program ,  GLenum shadertype , const GLchar *name),
(program , shadertype , name)
)

GLPROC_VOID(glGetActiveSubroutineUniformiv,
(GLuint program ,  GLenum shadertype ,  GLuint index ,  GLenum pname , GLint *values),
(program , shadertype , index , pname , values)
)

GLPROC_VOID(glGetActiveSubroutineUniformName,
(GLuint program ,  GLenum shadertype ,  GLuint index ,  GLsizei bufsize ,  GLsizei *length , GLchar *name),
(program , shadertype , index , bufsize , length , name)
)

GLPROC_VOID(glGetActiveSubroutineName,
(GLuint program ,  GLenum shadertype ,  GLuint index ,  GLsizei bufsize ,  GLsizei *length , GLchar *name),
(program , shadertype , index , bufsize , length , name)
)

GLPROC_VOID(glUniformSubroutinesuiv,
(GLenum shadertype ,  GLsizei count , const GLuint *indices),
(shadertype , count , indices)
)

GLPROC_VOID(glGetUniformSubroutineuiv,
(GLenum shadertype ,  GLint location , GLuint *params),
(shadertype , location , params)
)

GLPROC_VOID(glGetProgramStageiv,
(GLuint program ,  GLenum shadertype ,  GLenum pname , GLint *values),
(program , shadertype , pname , values)
)

GLPROC_VOID(glPatchParameteri,
(GLenum pname , GLint value),
(pname , value)
)

GLPROC_VOID(glPatchParameterfv,
(GLenum pname , const GLfloat *values),
(pname , values)
)

GLPROC_VOID(glBindTransformFeedback,
(GLenum target , GLuint id),
(target , id)
)

GLPROC_VOID(glDeleteTransformFeedbacks,
(GLsizei n , const GLuint *ids),
(n , ids)
)

GLPROC_VOID(glGenTransformFeedbacks,
(GLsizei n , GLuint *ids),
(n , ids)
)

GLPROC_RETURN1(GLboolean,
glIsTransformFeedback,
(GLuint id),
(id)
)

GLPROC_VOID(glPauseTransformFeedback,
(void),
()
)

GLPROC_VOID(glResumeTransformFeedback,
(void),
()
)

GLPROC_VOID(glDrawTransformFeedback,
(GLenum mode , GLuint id),
(mode , id)
)

GLPROC_VOID(glDrawTransformFeedbackStream,
(GLenum mode ,  GLuint id , GLuint stream),
(mode , id , stream)
)

GLPROC_VOID(glBeginQueryIndexed,
(GLenum target ,  GLuint index , GLuint id),
(target , index , id)
)

GLPROC_VOID(glEndQueryIndexed,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_VOID(glGetQueryIndexediv,
(GLenum target ,  GLuint index ,  GLenum pname , GLint *params),
(target , index , pname , params)
)



GLPROC_VOID(glReleaseShaderCompiler,
(void),
()
)

GLPROC_VOID(glShaderBinary,
(GLsizei count ,  const GLuint *shaders ,  GLenum binaryformat ,  const GLvoid *binary , GLsizei length),
(count , shaders , binaryformat , binary , length)
)

GLPROC_VOID(glGetShaderPrecisionFormat,
(GLenum shadertype ,  GLenum precisiontype ,  GLint *range , GLint *precision),
(shadertype , precisiontype , range , precision)
)

GLPROC_VOID(glDepthRangef,
(GLfloat n , GLfloat f),
(n , f)
)

GLPROC_VOID(glClearDepthf,
(GLfloat d),
(d)
)

GLPROC_VOID(glGetProgramBinary,
(GLuint program ,  GLsizei bufSize ,  GLsizei *length ,  GLenum *binaryFormat , GLvoid *binary),
(program , bufSize , length , binaryFormat , binary)
)

GLPROC_VOID(glProgramBinary,
(GLuint program ,  GLenum binaryFormat ,  const GLvoid *binary , GLsizei length),
(program , binaryFormat , binary , length)
)

GLPROC_VOID(glProgramParameteri,
(GLuint program ,  GLenum pname , GLint value),
(program , pname , value)
)

GLPROC_VOID(glUseProgramStages,
(GLuint pipeline ,  GLbitfield stages , GLuint program),
(pipeline , stages , program)
)

GLPROC_VOID(glActiveShaderProgram,
(GLuint pipeline , GLuint program),
(pipeline , program)
)

GLPROC_RETURN1(GLuint,
glCreateShaderProgramv,
(GLenum type ,  GLsizei count , const GLchar *const*strings),
(type , count , strings)
)

GLPROC_VOID(glBindProgramPipeline,
(GLuint pipeline),
(pipeline)
)

GLPROC_VOID(glDeleteProgramPipelines,
(GLsizei n , const GLuint *pipelines),
(n , pipelines)
)

GLPROC_VOID(glGenProgramPipelines,
(GLsizei n , GLuint *pipelines),
(n , pipelines)
)

GLPROC_RETURN1(GLboolean,
glIsProgramPipeline,
(GLuint pipeline),
(pipeline)
)

GLPROC_VOID(glGetProgramPipelineiv,
(GLuint pipeline ,  GLenum pname , GLint *params),
(pipeline , pname , params)
)

GLPROC_VOID(glProgramUniform1i,
(GLuint program ,  GLint location , GLint v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform1iv,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform1f,
(GLuint program ,  GLint location , GLfloat v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform1fv,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform1d,
(GLuint program ,  GLint location , GLdouble v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform1dv,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform1ui,
(GLuint program ,  GLint location , GLuint v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform1uiv,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2i,
(GLuint program ,  GLint location ,  GLint v0 , GLint v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform2iv,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2f,
(GLuint program ,  GLint location ,  GLfloat v0 , GLfloat v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform2fv,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2d,
(GLuint program ,  GLint location ,  GLdouble v0 , GLdouble v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform2dv,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2ui,
(GLuint program ,  GLint location ,  GLuint v0 , GLuint v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform2uiv,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3i,
(GLuint program ,  GLint location ,  GLint v0 ,  GLint v1 , GLint v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform3iv,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3f,
(GLuint program ,  GLint location ,  GLfloat v0 ,  GLfloat v1 , GLfloat v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform3fv,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3d,
(GLuint program ,  GLint location ,  GLdouble v0 ,  GLdouble v1 , GLdouble v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform3dv,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3ui,
(GLuint program ,  GLint location ,  GLuint v0 ,  GLuint v1 , GLuint v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform3uiv,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4i,
(GLuint program ,  GLint location ,  GLint v0 ,  GLint v1 ,  GLint v2 , GLint v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform4iv,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4f,
(GLuint program ,  GLint location ,  GLfloat v0 ,  GLfloat v1 ,  GLfloat v2 , GLfloat v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform4fv,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4d,
(GLuint program ,  GLint location ,  GLdouble v0 ,  GLdouble v1 ,  GLdouble v2 , GLdouble v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform4dv,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4ui,
(GLuint program ,  GLint location ,  GLuint v0 ,  GLuint v1 ,  GLuint v2 , GLuint v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform4uiv,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniformMatrix2fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x3fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x2fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x4fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x2fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x4fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x3fv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x3dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x2dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x4dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x2dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x4dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x3dv,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glValidateProgramPipeline,
(GLuint pipeline),
(pipeline)
)

GLPROC_VOID(glGetProgramPipelineInfoLog,
(GLuint pipeline ,  GLsizei bufSize ,  GLsizei *length , GLchar *infoLog),
(pipeline , bufSize , length , infoLog)
)

GLPROC_VOID(glVertexAttribL1d,
(GLuint index , GLdouble x),
(index , x)
)

GLPROC_VOID(glVertexAttribL2d,
(GLuint index ,  GLdouble x , GLdouble y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribL3d,
(GLuint index ,  GLdouble x ,  GLdouble y , GLdouble z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribL4d,
(GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribL1dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL2dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL3dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL4dv,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribLPointer,
(GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , stride , pointer)
)

GLPROC_VOID(glGetVertexAttribLdv,
(GLuint index ,  GLenum pname , GLdouble *params),
(index , pname , params)
)

GLPROC_VOID(glViewportArrayv,
(GLuint first ,  GLsizei count , const GLfloat *v),
(first , count , v)
)

GLPROC_VOID(glViewportIndexedf,
(GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat w , GLfloat h),
(index , x , y , w , h)
)

GLPROC_VOID(glViewportIndexedfv,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glScissorArrayv,
(GLuint first ,  GLsizei count , const GLint *v),
(first , count , v)
)

GLPROC_VOID(glScissorIndexed,
(GLuint index ,  GLint left ,  GLint bottom ,  GLsizei width , GLsizei height),
(index , left , bottom , width , height)
)

GLPROC_VOID(glScissorIndexedv,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glDepthRangeArrayv,
(GLuint first ,  GLsizei count , const GLdouble *v),
(first , count , v)
)

GLPROC_VOID(glDepthRangeIndexed,
(GLuint index ,  GLdouble n , GLdouble f),
(index , n , f)
)

GLPROC_VOID(glGetFloati_v,
(GLenum target ,  GLuint index , GLfloat *data),
(target , index , data)
)

GLPROC_VOID(glGetDoublei_v,
(GLenum target ,  GLuint index , GLdouble *data),
(target , index , data)
)



GLPROC_VOID(glDrawArraysInstancedBaseInstance,
(GLenum mode ,  GLint first ,  GLsizei count ,  GLsizei instancecount , GLuint baseinstance),
(mode , first , count , instancecount , baseinstance)
)

GLPROC_VOID(glDrawElementsInstancedBaseInstance,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const void *indices ,  GLsizei instancecount , GLuint baseinstance),
(mode , count , type , indices , instancecount , baseinstance)
)

GLPROC_VOID(glDrawElementsInstancedBaseVertexBaseInstance,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const void *indices ,  GLsizei instancecount ,  GLint basevertex , GLuint baseinstance),
(mode , count , type , indices , instancecount , basevertex , baseinstance)
)

GLPROC_VOID(glGetInternalformati64v,
(GLenum target ,  GLenum internalformat ,  GLenum pname ,  GLsizei bufSize , GLint64 *params),
(target , internalformat , pname , bufSize , params)
)

GLPROC_VOID(glGetActiveAtomicCounterBufferiv,
(GLuint program ,  GLuint bufferIndex ,  GLenum pname , GLint *params),
(program , bufferIndex , pname , params)
)

GLPROC_VOID(glBindImageTexture,
(GLuint unit ,  GLuint texture ,  GLint level ,  GLboolean layered ,  GLint layer ,  GLenum access , GLenum format),
(unit , texture , level , layered , layer , access , format)
)

GLPROC_VOID(glMemoryBarrier,
(GLbitfield barriers),
(barriers)
)

GLPROC_VOID(glTexStorage1D,
(GLenum target ,  GLsizei levels ,  GLenum internalformat , GLsizei width),
(target , levels , internalformat , width)
)

GLPROC_VOID(glTexStorage2D,
(GLenum target ,  GLsizei levels ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , levels , internalformat , width , height)
)

GLPROC_VOID(glTexStorage3D,
(GLenum target ,  GLsizei levels ,  GLenum internalformat ,  GLsizei width ,  GLsizei height , GLsizei depth),
(target , levels , internalformat , width , height , depth)
)

GLPROC_VOID(glDrawTransformFeedbackInstanced,
(GLenum mode ,  GLuint id , GLsizei instancecount),
(mode , id , instancecount)
)

GLPROC_VOID(glDrawTransformFeedbackStreamInstanced,
(GLenum mode ,  GLuint id ,  GLuint stream , GLsizei instancecount),
(mode , id , stream , instancecount)
)



GLPROC_VOID(glClearBufferData,
(GLenum target ,  GLenum internalformat ,  GLenum format ,  GLenum type , const void *data),
(target , internalformat , format , type , data)
)

GLPROC_VOID(glClearBufferSubData,
(GLenum target ,  GLenum internalformat ,  GLintptr offset ,  GLsizeiptr size ,  GLenum format ,  GLenum type , const void *data),
(target , internalformat , offset , size , format , type , data)
)

GLPROC_VOID(glDispatchCompute,
(GLuint num_groups_x ,  GLuint num_groups_y , GLuint num_groups_z),
(num_groups_x , num_groups_y , num_groups_z)
)

GLPROC_VOID(glDispatchComputeIndirect,
(GLintptr indirect),
(indirect)
)

GLPROC_VOID(glCopyImageSubData,
(GLuint srcName ,  GLenum srcTarget ,  GLint srcLevel ,  GLint srcX ,  GLint srcY ,  GLint srcZ ,  GLuint dstName ,  GLenum dstTarget ,  GLint dstLevel ,  GLint dstX ,  GLint dstY ,  GLint dstZ ,  GLsizei srcWidth ,  GLsizei srcHeight , GLsizei srcDepth),
(srcName , srcTarget , srcLevel , srcX , srcY , srcZ , dstName , dstTarget , dstLevel , dstX , dstY , dstZ , srcWidth , srcHeight , srcDepth)
)

GLPROC_VOID(glFramebufferParameteri,
(GLenum target ,  GLenum pname , GLint param),
(target , pname , param)
)

GLPROC_VOID(glGetFramebufferParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glInvalidateTexSubImage,
(GLuint texture ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height , GLsizei depth),
(texture , level , xoffset , yoffset , zoffset , width , height , depth)
)

GLPROC_VOID(glInvalidateTexImage,
(GLuint texture , GLint level),
(texture , level)
)

GLPROC_VOID(glInvalidateBufferSubData,
(GLuint buffer ,  GLintptr offset , GLsizeiptr length),
(buffer , offset , length)
)

GLPROC_VOID(glInvalidateBufferData,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glInvalidateFramebuffer,
(GLenum target ,  GLsizei numAttachments , const GLenum *attachments),
(target , numAttachments , attachments)
)

GLPROC_VOID(glInvalidateSubFramebuffer,
(GLenum target ,  GLsizei numAttachments ,  const GLenum *attachments ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , numAttachments , attachments , x , y , width , height)
)

GLPROC_VOID(glMultiDrawArraysIndirect,
(GLenum mode ,  const void *indirect ,  GLsizei drawcount , GLsizei stride),
(mode , indirect , drawcount , stride)
)

GLPROC_VOID(glMultiDrawElementsIndirect,
(GLenum mode ,  GLenum type ,  const void *indirect ,  GLsizei drawcount , GLsizei stride),
(mode , type , indirect , drawcount , stride)
)

GLPROC_VOID(glGetProgramInterfaceiv,
(GLuint program ,  GLenum programInterface ,  GLenum pname , GLint *params),
(program , programInterface , pname , params)
)

GLPROC_RETURN1(GLuint,
glGetProgramResourceIndex,
(GLuint program ,  GLenum programInterface , const GLchar *name),
(program , programInterface , name)
)

GLPROC_VOID(glGetProgramResourceName,
(GLuint program ,  GLenum programInterface ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length , GLchar *name),
(program , programInterface , index , bufSize , length , name)
)

GLPROC_VOID(glGetProgramResourceiv,
(GLuint program ,  GLenum programInterface ,  GLuint index ,  GLsizei propCount ,  const GLenum *props ,  GLsizei bufSize ,  GLsizei *length , GLint *params),
(program , programInterface , index , propCount , props , bufSize , length , params)
)

GLPROC_RETURN1(GLint,
glGetProgramResourceLocation,
(GLuint program ,  GLenum programInterface , const GLchar *name),
(program , programInterface , name)
)

GLPROC_RETURN1(GLint,
glGetProgramResourceLocationIndex,
(GLuint program ,  GLenum programInterface , const GLchar *name),
(program , programInterface , name)
)

GLPROC_VOID(glShaderStorageBlockBinding,
(GLuint program ,  GLuint storageBlockIndex , GLuint storageBlockBinding),
(program , storageBlockIndex , storageBlockBinding)
)

GLPROC_VOID(glTexBufferRange,
(GLenum target ,  GLenum internalformat ,  GLuint buffer ,  GLintptr offset , GLsizeiptr size),
(target , internalformat , buffer , offset , size)
)

GLPROC_VOID(glTexStorage2DMultisample,
(GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width ,  GLsizei height , GLboolean fixedsamplelocations),
(target , samples , internalformat , width , height , fixedsamplelocations)
)

GLPROC_VOID(glTexStorage3DMultisample,
(GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedsamplelocations),
(target , samples , internalformat , width , height , depth , fixedsamplelocations)
)

GLPROC_VOID(glTextureView,
(GLuint texture ,  GLenum target ,  GLuint origtexture ,  GLenum internalformat ,  GLuint minlevel ,  GLuint numlevels ,  GLuint minlayer , GLuint numlayers),
(texture , target , origtexture , internalformat , minlevel , numlevels , minlayer , numlayers)
)

GLPROC_VOID(glBindVertexBuffer,
(GLuint bindingindex ,  GLuint buffer ,  GLintptr offset , GLsizei stride),
(bindingindex , buffer , offset , stride)
)

GLPROC_VOID(glVertexAttribFormat,
(GLuint attribindex ,  GLint size ,  GLenum type ,  GLboolean normalized , GLuint relativeoffset),
(attribindex , size , type , normalized , relativeoffset)
)

GLPROC_VOID(glVertexAttribIFormat,
(GLuint attribindex ,  GLint size ,  GLenum type , GLuint relativeoffset),
(attribindex , size , type , relativeoffset)
)

GLPROC_VOID(glVertexAttribLFormat,
(GLuint attribindex ,  GLint size ,  GLenum type , GLuint relativeoffset),
(attribindex , size , type , relativeoffset)
)

GLPROC_VOID(glVertexAttribBinding,
(GLuint attribindex , GLuint bindingindex),
(attribindex , bindingindex)
)

GLPROC_VOID(glVertexBindingDivisor,
(GLuint bindingindex , GLuint divisor),
(bindingindex , divisor)
)

GLPROC_VOID(glDebugMessageControl,
(GLenum source ,  GLenum type ,  GLenum severity ,  GLsizei count ,  const GLuint *ids , GLboolean enabled),
(source , type , severity , count , ids , enabled)
)

GLPROC_VOID(glDebugMessageInsert,
(GLenum source ,  GLenum type ,  GLuint id ,  GLenum severity ,  GLsizei length , const GLchar *buf),
(source , type , id , severity , length , buf)
)

GLPROC_VOID(glDebugMessageCallback,
(GLDEBUGPROC callback , const void *userParam),
(callback , userParam)
)

GLPROC_RETURN1(GLuint,
glGetDebugMessageLog,
(GLuint count ,  GLsizei bufsize ,  GLenum *sources ,  GLenum *types ,  GLuint *ids ,  GLenum *severities ,  GLsizei *lengths , GLchar *messageLog),
(count , bufsize , sources , types , ids , severities , lengths , messageLog)
)

GLPROC_VOID(glPushDebugGroup,
(GLenum source ,  GLuint id ,  GLsizei length , const GLchar *message),
(source , id , length , message)
)

GLPROC_VOID(glPopDebugGroup,
(void),
()
)

GLPROC_VOID(glObjectLabel,
(GLenum identifier ,  GLuint name ,  GLsizei length , const GLchar *label),
(identifier , name , length , label)
)

GLPROC_VOID(glGetObjectLabel,
(GLenum identifier ,  GLuint name ,  GLsizei bufSize ,  GLsizei *length , GLchar *label),
(identifier , name , bufSize , length , label)
)

GLPROC_VOID(glObjectPtrLabel,
(const void *ptr ,  GLsizei length , const GLchar *label),
(ptr , length , label)
)

GLPROC_VOID(glGetObjectPtrLabel,
(const void *ptr ,  GLsizei bufSize ,  GLsizei *length , GLchar *label),
(ptr , bufSize , length , label)
)



GLPROC_VOID(glBufferStorage,
(GLenum target ,  GLsizeiptr size ,  const void *data , GLbitfield flags),
(target , size , data , flags)
)

GLPROC_VOID(glClearTexImage,
(GLuint texture ,  GLint level ,  GLenum format ,  GLenum type , const void *data),
(texture , level , format , type , data)
)

GLPROC_VOID(glClearTexSubImage,
(GLuint texture ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLenum type , const void *data),
(texture , level , xoffset , yoffset , zoffset , width , height , depth , format , type , data)
)

GLPROC_VOID(glBindBuffersBase,
(GLenum target ,  GLuint first ,  GLsizei count , const GLuint *buffers),
(target , first , count , buffers)
)

GLPROC_VOID(glBindBuffersRange,
(GLenum target ,  GLuint first ,  GLsizei count ,  const GLuint *buffers ,  const GLintptr *offsets , const GLsizeiptr *sizes),
(target , first , count , buffers , offsets , sizes)
)

GLPROC_VOID(glBindTextures,
(GLuint first ,  GLsizei count , const GLuint *textures),
(first , count , textures)
)

GLPROC_VOID(glBindSamplers,
(GLuint first ,  GLsizei count , const GLuint *samplers),
(first , count , samplers)
)

GLPROC_VOID(glBindImageTextures,
(GLuint first ,  GLsizei count , const GLuint *textures),
(first , count , textures)
)

GLPROC_VOID(glBindVertexBuffers,
(GLuint first ,  GLsizei count ,  const GLuint *buffers ,  const GLintptr *offsets , const GLsizei *strides),
(first , count , buffers , offsets , strides)
)



GLPROC_RETURN1(GLuint64,
glGetTextureHandleARB,
(GLuint texture),
(texture)
)

GLPROC_RETURN1(GLuint64,
glGetTextureSamplerHandleARB,
(GLuint texture , GLuint sampler),
(texture , sampler)
)

GLPROC_VOID(glMakeTextureHandleResidentARB,
(GLuint64 handle),
(handle)
)

GLPROC_VOID(glMakeTextureHandleNonResidentARB,
(GLuint64 handle),
(handle)
)

GLPROC_RETURN1(GLuint64,
glGetImageHandleARB,
(GLuint texture ,  GLint level ,  GLboolean layered ,  GLint layer , GLenum format),
(texture , level , layered , layer , format)
)

GLPROC_VOID(glMakeImageHandleResidentARB,
(GLuint64 handle , GLenum access),
(handle , access)
)

GLPROC_VOID(glMakeImageHandleNonResidentARB,
(GLuint64 handle),
(handle)
)

GLPROC_VOID(glUniformHandleui64ARB,
(GLint location , GLuint64 value),
(location , value)
)

GLPROC_VOID(glUniformHandleui64vARB,
(GLint location ,  GLsizei count , const GLuint64 *value),
(location , count , value)
)

GLPROC_VOID(glProgramUniformHandleui64ARB,
(GLuint program ,  GLint location , GLuint64 value),
(program , location , value)
)

GLPROC_VOID(glProgramUniformHandleui64vARB,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64 *values),
(program , location , count , values)
)

GLPROC_RETURN1(GLboolean,
glIsTextureHandleResidentARB,
(GLuint64 handle),
(handle)
)

GLPROC_RETURN1(GLboolean,
glIsImageHandleResidentARB,
(GLuint64 handle),
(handle)
)

GLPROC_VOID(glVertexAttribL1ui64ARB,
(GLuint index , GLuint64EXT x),
(index , x)
)

GLPROC_VOID(glVertexAttribL1ui64vARB,
(GLuint index , const GLuint64EXT *v),
(index , v)
)

GLPROC_VOID(glGetVertexAttribLui64vARB,
(GLuint index ,  GLenum pname , GLuint64EXT *params),
(index , pname , params)
)





GLPROC_RETURN1(GLsync,
glCreateSyncFromCLeventARB,
(struct _cl_context *context ,  struct _cl_event *event , GLbitfield flags),
(context , event , flags)
)





GLPROC_VOID(glClampColorARB,
(GLenum target , GLenum clamp),
(target , clamp)
)





GLPROC_VOID(glDispatchComputeGroupSizeARB,
(GLuint num_groups_x ,  GLuint num_groups_y ,  GLuint num_groups_z ,  GLuint group_size_x ,  GLuint group_size_y , GLuint group_size_z),
(num_groups_x , num_groups_y , num_groups_z , group_size_x , group_size_y , group_size_z)
)





GLPROC_VOID(glDebugMessageControlARB,
(GLenum source ,  GLenum type ,  GLenum severity ,  GLsizei count ,  const GLuint *ids , GLboolean enabled),
(source , type , severity , count , ids , enabled)
)

GLPROC_VOID(glDebugMessageInsertARB,
(GLenum source ,  GLenum type ,  GLuint id ,  GLenum severity ,  GLsizei length , const GLchar *buf),
(source , type , id , severity , length , buf)
)

GLPROC_VOID(glDebugMessageCallbackARB,
(GLDEBUGPROCARB callback , const void *userParam),
(callback , userParam)
)

GLPROC_RETURN1(GLuint,
glGetDebugMessageLogARB,
(GLuint count ,  GLsizei bufsize ,  GLenum *sources ,  GLenum *types ,  GLuint *ids ,  GLenum *severities ,  GLsizei *lengths , GLchar *messageLog),
(count , bufsize , sources , types , ids , severities , lengths , messageLog)
)





GLPROC_VOID(glDrawBuffersARB,
(GLsizei n , const GLenum *bufs),
(n , bufs)
)





GLPROC_VOID(glBlendEquationiARB,
(GLuint buf , GLenum mode),
(buf , mode)
)

GLPROC_VOID(glBlendEquationSeparateiARB,
(GLuint buf ,  GLenum modeRGB , GLenum modeAlpha),
(buf , modeRGB , modeAlpha)
)

GLPROC_VOID(glBlendFunciARB,
(GLuint buf ,  GLenum src , GLenum dst),
(buf , src , dst)
)

GLPROC_VOID(glBlendFuncSeparateiARB,
(GLuint buf ,  GLenum srcRGB ,  GLenum dstRGB ,  GLenum srcAlpha , GLenum dstAlpha),
(buf , srcRGB , dstRGB , srcAlpha , dstAlpha)
)





GLPROC_VOID(glDrawArraysInstancedARB,
(GLenum mode ,  GLint first ,  GLsizei count , GLsizei primcount),
(mode , first , count , primcount)
)

GLPROC_VOID(glDrawElementsInstancedARB,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const GLvoid *indices , GLsizei primcount),
(mode , count , type , indices , primcount)
)





GLPROC_VOID(glProgramStringARB,
(GLenum target ,  GLenum format ,  GLsizei len , const GLvoid *string),
(target , format , len , string)
)

GLPROC_VOID(glBindProgramARB,
(GLenum target , GLuint program),
(target , program)
)

GLPROC_VOID(glDeleteProgramsARB,
(GLsizei n , const GLuint *programs),
(n , programs)
)

GLPROC_VOID(glGenProgramsARB,
(GLsizei n , GLuint *programs),
(n , programs)
)

GLPROC_VOID(glProgramEnvParameter4dARB,
(GLenum target ,  GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramEnvParameter4dvARB,
(GLenum target ,  GLuint index , const GLdouble *params),
(target , index , params)
)

GLPROC_VOID(glProgramEnvParameter4fARB,
(GLenum target ,  GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramEnvParameter4fvARB,
(GLenum target ,  GLuint index , const GLfloat *params),
(target , index , params)
)

GLPROC_VOID(glProgramLocalParameter4dARB,
(GLenum target ,  GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramLocalParameter4dvARB,
(GLenum target ,  GLuint index , const GLdouble *params),
(target , index , params)
)

GLPROC_VOID(glProgramLocalParameter4fARB,
(GLenum target ,  GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramLocalParameter4fvARB,
(GLenum target ,  GLuint index , const GLfloat *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramEnvParameterdvARB,
(GLenum target ,  GLuint index , GLdouble *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramEnvParameterfvARB,
(GLenum target ,  GLuint index , GLfloat *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramLocalParameterdvARB,
(GLenum target ,  GLuint index , GLdouble *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramLocalParameterfvARB,
(GLenum target ,  GLuint index , GLfloat *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramivARB,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetProgramStringARB,
(GLenum target ,  GLenum pname , GLvoid *string),
(target , pname , string)
)

GLPROC_RETURN1(GLboolean,
glIsProgramARB,
(GLuint program),
(program)
)





GLPROC_VOID(glProgramParameteriARB,
(GLuint program ,  GLenum pname , GLint value),
(program , pname , value)
)

GLPROC_VOID(glFramebufferTextureARB,
(GLenum target ,  GLenum attachment ,  GLuint texture , GLint level),
(target , attachment , texture , level)
)

GLPROC_VOID(glFramebufferTextureLayerARB,
(GLenum target ,  GLenum attachment ,  GLuint texture ,  GLint level , GLint layer),
(target , attachment , texture , level , layer)
)

GLPROC_VOID(glFramebufferTextureFaceARB,
(GLenum target ,  GLenum attachment ,  GLuint texture ,  GLint level , GLenum face),
(target , attachment , texture , level , face)
)





GLPROC_VOID(glColorTable,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *table),
(target , internalformat , width , format , type , table)
)

GLPROC_VOID(glColorTableParameterfv,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glColorTableParameteriv,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glCopyColorTable,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y , GLsizei width),
(target , internalformat , x , y , width)
)

GLPROC_VOID(glGetColorTable,
(GLenum target ,  GLenum format ,  GLenum type , GLvoid *table),
(target , format , type , table)
)

GLPROC_VOID(glGetColorTableParameterfv,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetColorTableParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glColorSubTable,
(GLenum target ,  GLsizei start ,  GLsizei count ,  GLenum format ,  GLenum type , const GLvoid *data),
(target , start , count , format , type , data)
)

GLPROC_VOID(glCopyColorSubTable,
(GLenum target ,  GLsizei start ,  GLint x ,  GLint y , GLsizei width),
(target , start , x , y , width)
)

GLPROC_VOID(glConvolutionFilter1D,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *image),
(target , internalformat , width , format , type , image)
)

GLPROC_VOID(glConvolutionFilter2D,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *image),
(target , internalformat , width , height , format , type , image)
)

GLPROC_VOID(glConvolutionParameterf,
(GLenum target ,  GLenum pname , GLfloat params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameterfv,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameteri,
(GLenum target ,  GLenum pname , GLint params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameteriv,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glCopyConvolutionFilter1D,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y , GLsizei width),
(target , internalformat , x , y , width)
)

GLPROC_VOID(glCopyConvolutionFilter2D,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , internalformat , x , y , width , height)
)

GLPROC_VOID(glGetConvolutionFilter,
(GLenum target ,  GLenum format ,  GLenum type , GLvoid *image),
(target , format , type , image)
)

GLPROC_VOID(glGetConvolutionParameterfv,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetConvolutionParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetSeparableFilter,
(GLenum target ,  GLenum format ,  GLenum type ,  GLvoid *row ,  GLvoid *column , GLvoid *span),
(target , format , type , row , column , span)
)

GLPROC_VOID(glSeparableFilter2D,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type ,  const GLvoid *row , const GLvoid *column),
(target , internalformat , width , height , format , type , row , column)
)

GLPROC_VOID(glGetHistogram,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type , GLvoid *values),
(target , reset , format , type , values)
)

GLPROC_VOID(glGetHistogramParameterfv,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetHistogramParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetMinmax,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type , GLvoid *values),
(target , reset , format , type , values)
)

GLPROC_VOID(glGetMinmaxParameterfv,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetMinmaxParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glHistogram,
(GLenum target ,  GLsizei width ,  GLenum internalformat , GLboolean sink),
(target , width , internalformat , sink)
)

GLPROC_VOID(glMinmax,
(GLenum target ,  GLenum internalformat , GLboolean sink),
(target , internalformat , sink)
)

GLPROC_VOID(glResetHistogram,
(GLenum target),
(target)
)

GLPROC_VOID(glResetMinmax,
(GLenum target),
(target)
)





GLPROC_VOID(glMultiDrawArraysIndirectCountARB,
(GLenum mode ,  GLintptr indirect ,  GLintptr drawcount ,  GLsizei maxdrawcount , GLsizei stride),
(mode , indirect , drawcount , maxdrawcount , stride)
)

GLPROC_VOID(glMultiDrawElementsIndirectCountARB,
(GLenum mode ,  GLenum type ,  GLintptr indirect ,  GLintptr drawcount ,  GLsizei maxdrawcount , GLsizei stride),
(mode , type , indirect , drawcount , maxdrawcount , stride)
)





GLPROC_VOID(glVertexAttribDivisorARB,
(GLuint index , GLuint divisor),
(index , divisor)
)





GLPROC_VOID(glGetInternalformativ,
(GLenum target ,  GLenum internalformat ,  GLenum pname ,  GLsizei bufSize , GLint *params),
(target , internalformat , pname , bufSize , params)
)





GLPROC_VOID(glCurrentPaletteMatrixARB,
(GLint index),
(index)
)

GLPROC_VOID(glMatrixIndexubvARB,
(GLint size , const GLubyte *indices),
(size , indices)
)

GLPROC_VOID(glMatrixIndexusvARB,
(GLint size , const GLushort *indices),
(size , indices)
)

GLPROC_VOID(glMatrixIndexuivARB,
(GLint size , const GLuint *indices),
(size , indices)
)

GLPROC_VOID(glMatrixIndexPointerARB,
(GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(size , type , stride , pointer)
)





GLPROC_VOID(glSampleCoverageARB,
(GLfloat value , GLboolean invert),
(value , invert)
)





GLPROC_VOID(glActiveTextureARB,
(GLenum texture),
(texture)
)

GLPROC_VOID(glClientActiveTextureARB,
(GLenum texture),
(texture)
)

GLPROC_VOID(glMultiTexCoord1dARB,
(GLenum target , GLdouble s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1dvARB,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1fARB,
(GLenum target , GLfloat s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1fvARB,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1iARB,
(GLenum target , GLint s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1ivARB,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord1sARB,
(GLenum target , GLshort s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1svARB,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2dARB,
(GLenum target ,  GLdouble s , GLdouble t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2dvARB,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2fARB,
(GLenum target ,  GLfloat s , GLfloat t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2fvARB,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2iARB,
(GLenum target ,  GLint s , GLint t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2ivARB,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2sARB,
(GLenum target ,  GLshort s , GLshort t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2svARB,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3dARB,
(GLenum target ,  GLdouble s ,  GLdouble t , GLdouble r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3dvARB,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3fARB,
(GLenum target ,  GLfloat s ,  GLfloat t , GLfloat r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3fvARB,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3iARB,
(GLenum target ,  GLint s ,  GLint t , GLint r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3ivARB,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3sARB,
(GLenum target ,  GLshort s ,  GLshort t , GLshort r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3svARB,
(GLenum target , const GLshort *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4dARB,
(GLenum target ,  GLdouble s ,  GLdouble t ,  GLdouble r , GLdouble q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4dvARB,
(GLenum target , const GLdouble *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4fARB,
(GLenum target ,  GLfloat s ,  GLfloat t ,  GLfloat r , GLfloat q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4fvARB,
(GLenum target , const GLfloat *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4iARB,
(GLenum target ,  GLint s ,  GLint t ,  GLint r , GLint q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4ivARB,
(GLenum target , const GLint *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4sARB,
(GLenum target ,  GLshort s ,  GLshort t ,  GLshort r , GLshort q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4svARB,
(GLenum target , const GLshort *v),
(target , v)
)





GLPROC_VOID(glGenQueriesARB,
(GLsizei n , GLuint *ids),
(n , ids)
)

GLPROC_VOID(glDeleteQueriesARB,
(GLsizei n , const GLuint *ids),
(n , ids)
)

GLPROC_RETURN1(GLboolean,
glIsQueryARB,
(GLuint id),
(id)
)

GLPROC_VOID(glBeginQueryARB,
(GLenum target , GLuint id),
(target , id)
)

GLPROC_VOID(glEndQueryARB,
(GLenum target),
(target)
)

GLPROC_VOID(glGetQueryivARB,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetQueryObjectivARB,
(GLuint id ,  GLenum pname , GLint *params),
(id , pname , params)
)

GLPROC_VOID(glGetQueryObjectuivARB,
(GLuint id ,  GLenum pname , GLuint *params),
(id , pname , params)
)





GLPROC_VOID(glPointParameterfARB,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPointParameterfvARB,
(GLenum pname , const GLfloat *params),
(pname , params)
)





GLPROC_RETURN1(GLenum,
glGetGraphicsResetStatusARB,
(void),
()
)

GLPROC_VOID(glGetnTexImageARB,
(GLenum target ,  GLint level ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *img),
(target , level , format , type , bufSize , img)
)

GLPROC_VOID(glReadnPixelsARB,
(GLint x ,  GLint y ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *data),
(x , y , width , height , format , type , bufSize , data)
)

GLPROC_VOID(glGetnCompressedTexImageARB,
(GLenum target ,  GLint lod ,  GLsizei bufSize , GLvoid *img),
(target , lod , bufSize , img)
)

GLPROC_VOID(glGetnUniformfvARB,
(GLuint program ,  GLint location ,  GLsizei bufSize , GLfloat *params),
(program , location , bufSize , params)
)

GLPROC_VOID(glGetnUniformivARB,
(GLuint program ,  GLint location ,  GLsizei bufSize , GLint *params),
(program , location , bufSize , params)
)

GLPROC_VOID(glGetnUniformuivARB,
(GLuint program ,  GLint location ,  GLsizei bufSize , GLuint *params),
(program , location , bufSize , params)
)

GLPROC_VOID(glGetnUniformdvARB,
(GLuint program ,  GLint location ,  GLsizei bufSize , GLdouble *params),
(program , location , bufSize , params)
)

GLPROC_VOID(glGetnMapdvARB,
(GLenum target ,  GLenum query ,  GLsizei bufSize , GLdouble *v),
(target , query , bufSize , v)
)

GLPROC_VOID(glGetnMapfvARB,
(GLenum target ,  GLenum query ,  GLsizei bufSize , GLfloat *v),
(target , query , bufSize , v)
)

GLPROC_VOID(glGetnMapivARB,
(GLenum target ,  GLenum query ,  GLsizei bufSize , GLint *v),
(target , query , bufSize , v)
)

GLPROC_VOID(glGetnPixelMapfvARB,
(GLenum map ,  GLsizei bufSize , GLfloat *values),
(map , bufSize , values)
)

GLPROC_VOID(glGetnPixelMapuivARB,
(GLenum map ,  GLsizei bufSize , GLuint *values),
(map , bufSize , values)
)

GLPROC_VOID(glGetnPixelMapusvARB,
(GLenum map ,  GLsizei bufSize , GLushort *values),
(map , bufSize , values)
)

GLPROC_VOID(glGetnPolygonStippleARB,
(GLsizei bufSize , GLubyte *pattern),
(bufSize , pattern)
)

GLPROC_VOID(glGetnColorTableARB,
(GLenum target ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *table),
(target , format , type , bufSize , table)
)

GLPROC_VOID(glGetnConvolutionFilterARB,
(GLenum target ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *image),
(target , format , type , bufSize , image)
)

GLPROC_VOID(glGetnSeparableFilterARB,
(GLenum target ,  GLenum format ,  GLenum type ,  GLsizei rowBufSize ,  GLvoid *row ,  GLsizei columnBufSize ,  GLvoid *column , GLvoid *span),
(target , format , type , rowBufSize , row , columnBufSize , column , span)
)

GLPROC_VOID(glGetnHistogramARB,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *values),
(target , reset , format , type , bufSize , values)
)

GLPROC_VOID(glGetnMinmaxARB,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type ,  GLsizei bufSize , GLvoid *values),
(target , reset , format , type , bufSize , values)
)





GLPROC_VOID(glMinSampleShadingARB,
(GLfloat value),
(value)
)





GLPROC_VOID(glDeleteObjectARB,
(GLhandleARB obj),
(obj)
)

GLPROC_RETURN1(GLhandleARB,
glGetHandleARB,
(GLenum pname),
(pname)
)

GLPROC_VOID(glDetachObjectARB,
(GLhandleARB containerObj , GLhandleARB attachedObj),
(containerObj , attachedObj)
)

GLPROC_RETURN1(GLhandleARB,
glCreateShaderObjectARB,
(GLenum shaderType),
(shaderType)
)

GLPROC_VOID(glShaderSourceARB,
(GLhandleARB shaderObj ,  GLsizei count ,  const GLcharARB **string , const GLint *length),
(shaderObj , count , string , length)
)

GLPROC_VOID(glCompileShaderARB,
(GLhandleARB shaderObj),
(shaderObj)
)

GLPROC_RETURN1(GLhandleARB,
glCreateProgramObjectARB,
(void),
()
)

GLPROC_VOID(glAttachObjectARB,
(GLhandleARB containerObj , GLhandleARB obj),
(containerObj , obj)
)

GLPROC_VOID(glLinkProgramARB,
(GLhandleARB programObj),
(programObj)
)

GLPROC_VOID(glUseProgramObjectARB,
(GLhandleARB programObj),
(programObj)
)

GLPROC_VOID(glValidateProgramARB,
(GLhandleARB programObj),
(programObj)
)

GLPROC_VOID(glUniform1fARB,
(GLint location , GLfloat v0),
(location , v0)
)

GLPROC_VOID(glUniform2fARB,
(GLint location ,  GLfloat v0 , GLfloat v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3fARB,
(GLint location ,  GLfloat v0 ,  GLfloat v1 , GLfloat v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4fARB,
(GLint location ,  GLfloat v0 ,  GLfloat v1 ,  GLfloat v2 , GLfloat v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1iARB,
(GLint location , GLint v0),
(location , v0)
)

GLPROC_VOID(glUniform2iARB,
(GLint location ,  GLint v0 , GLint v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3iARB,
(GLint location ,  GLint v0 ,  GLint v1 , GLint v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4iARB,
(GLint location ,  GLint v0 ,  GLint v1 ,  GLint v2 , GLint v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1fvARB,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform2fvARB,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform3fvARB,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform4fvARB,
(GLint location ,  GLsizei count , const GLfloat *value),
(location , count , value)
)

GLPROC_VOID(glUniform1ivARB,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform2ivARB,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform3ivARB,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniform4ivARB,
(GLint location ,  GLsizei count , const GLint *value),
(location , count , value)
)

GLPROC_VOID(glUniformMatrix2fvARB,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix3fvARB,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glUniformMatrix4fvARB,
(GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(location , count , transpose , value)
)

GLPROC_VOID(glGetObjectParameterfvARB,
(GLhandleARB obj ,  GLenum pname , GLfloat *params),
(obj , pname , params)
)

GLPROC_VOID(glGetObjectParameterivARB,
(GLhandleARB obj ,  GLenum pname , GLint *params),
(obj , pname , params)
)

GLPROC_VOID(glGetInfoLogARB,
(GLhandleARB obj ,  GLsizei maxLength ,  GLsizei *length , GLcharARB *infoLog),
(obj , maxLength , length , infoLog)
)

GLPROC_VOID(glGetAttachedObjectsARB,
(GLhandleARB containerObj ,  GLsizei maxCount ,  GLsizei *count , GLhandleARB *obj),
(containerObj , maxCount , count , obj)
)

GLPROC_RETURN1(GLint,
glGetUniformLocationARB,
(GLhandleARB programObj , const GLcharARB *name),
(programObj , name)
)

GLPROC_VOID(glGetActiveUniformARB,
(GLhandleARB programObj ,  GLuint index ,  GLsizei maxLength ,  GLsizei *length ,  GLint *size ,  GLenum *type , GLcharARB *name),
(programObj , index , maxLength , length , size , type , name)
)

GLPROC_VOID(glGetUniformfvARB,
(GLhandleARB programObj ,  GLint location , GLfloat *params),
(programObj , location , params)
)

GLPROC_VOID(glGetUniformivARB,
(GLhandleARB programObj ,  GLint location , GLint *params),
(programObj , location , params)
)

GLPROC_VOID(glGetShaderSourceARB,
(GLhandleARB obj ,  GLsizei maxLength ,  GLsizei *length , GLcharARB *source),
(obj , maxLength , length , source)
)





GLPROC_VOID(glNamedStringARB,
(GLenum type ,  GLint namelen ,  const GLchar *name ,  GLint stringlen , const GLchar *string),
(type , namelen , name , stringlen , string)
)

GLPROC_VOID(glDeleteNamedStringARB,
(GLint namelen , const GLchar *name),
(namelen , name)
)

GLPROC_VOID(glCompileShaderIncludeARB,
(GLuint shader ,  GLsizei count ,  const GLchar *const*path , const GLint *length),
(shader , count , path , length)
)

GLPROC_RETURN1(GLboolean,
glIsNamedStringARB,
(GLint namelen , const GLchar *name),
(namelen , name)
)

GLPROC_VOID(glGetNamedStringARB,
(GLint namelen ,  const GLchar *name ,  GLsizei bufSize ,  GLint *stringlen , GLchar *string),
(namelen , name , bufSize , stringlen , string)
)

GLPROC_VOID(glGetNamedStringivARB,
(GLint namelen ,  const GLchar *name ,  GLenum pname , GLint *params),
(namelen , name , pname , params)
)





GLPROC_VOID(glTexPageCommitmentARB,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean resident),
(target , level , xoffset , yoffset , zoffset , width , height , depth , resident)
)





GLPROC_VOID(glTexBufferARB,
(GLenum target ,  GLenum internalformat , GLuint buffer),
(target , internalformat , buffer)
)





GLPROC_VOID(glCompressedTexImage3DARB,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , height , depth , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexImage2DARB,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , height , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexImage1DARB,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLint border ,  GLsizei imageSize , const GLvoid *data),
(target , level , internalformat , width , border , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage3DARB,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , yoffset , zoffset , width , height , depth , format , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage2DARB,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , yoffset , width , height , format , imageSize , data)
)

GLPROC_VOID(glCompressedTexSubImage1DARB,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLsizei imageSize , const GLvoid *data),
(target , level , xoffset , width , format , imageSize , data)
)

GLPROC_VOID(glGetCompressedTexImageARB,
(GLenum target ,  GLint level , GLvoid *img),
(target , level , img)
)





GLPROC_VOID(glLoadTransposeMatrixfARB,
(const GLfloat *m),
(m)
)

GLPROC_VOID(glLoadTransposeMatrixdARB,
(const GLdouble *m),
(m)
)

GLPROC_VOID(glMultTransposeMatrixfARB,
(const GLfloat *m),
(m)
)

GLPROC_VOID(glMultTransposeMatrixdARB,
(const GLdouble *m),
(m)
)





GLPROC_VOID(glWeightbvARB,
(GLint size , const GLbyte *weights),
(size , weights)
)

GLPROC_VOID(glWeightsvARB,
(GLint size , const GLshort *weights),
(size , weights)
)

GLPROC_VOID(glWeightivARB,
(GLint size , const GLint *weights),
(size , weights)
)

GLPROC_VOID(glWeightfvARB,
(GLint size , const GLfloat *weights),
(size , weights)
)

GLPROC_VOID(glWeightdvARB,
(GLint size , const GLdouble *weights),
(size , weights)
)

GLPROC_VOID(glWeightubvARB,
(GLint size , const GLubyte *weights),
(size , weights)
)

GLPROC_VOID(glWeightusvARB,
(GLint size , const GLushort *weights),
(size , weights)
)

GLPROC_VOID(glWeightuivARB,
(GLint size , const GLuint *weights),
(size , weights)
)

GLPROC_VOID(glWeightPointerARB,
(GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(size , type , stride , pointer)
)

GLPROC_VOID(glVertexBlendARB,
(GLint count),
(count)
)





GLPROC_VOID(glBindBufferARB,
(GLenum target , GLuint buffer),
(target , buffer)
)

GLPROC_VOID(glDeleteBuffersARB,
(GLsizei n , const GLuint *buffers),
(n , buffers)
)

GLPROC_VOID(glGenBuffersARB,
(GLsizei n , GLuint *buffers),
(n , buffers)
)

GLPROC_RETURN1(GLboolean,
glIsBufferARB,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glBufferDataARB,
(GLenum target ,  GLsizeiptrARB size ,  const GLvoid *data , GLenum usage),
(target , size , data , usage)
)

GLPROC_VOID(glBufferSubDataARB,
(GLenum target ,  GLintptrARB offset ,  GLsizeiptrARB size , const GLvoid *data),
(target , offset , size , data)
)

GLPROC_VOID(glGetBufferSubDataARB,
(GLenum target ,  GLintptrARB offset ,  GLsizeiptrARB size , GLvoid *data),
(target , offset , size , data)
)

GLPROC_RETURN1(void *,
glMapBufferARB,
(GLenum target , GLenum access),
(target , access)
)

GLPROC_RETURN1(GLboolean,
glUnmapBufferARB,
(GLenum target),
(target)
)

GLPROC_VOID(glGetBufferParameterivARB,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetBufferPointervARB,
(GLenum target ,  GLenum pname , GLvoid **params),
(target , pname , params)
)





GLPROC_VOID(glVertexAttrib1dARB,
(GLuint index , GLdouble x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1dvARB,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1fARB,
(GLuint index , GLfloat x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1fvARB,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1sARB,
(GLuint index , GLshort x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1svARB,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2dARB,
(GLuint index ,  GLdouble x , GLdouble y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2dvARB,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2fARB,
(GLuint index ,  GLfloat x , GLfloat y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2fvARB,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2sARB,
(GLuint index ,  GLshort x , GLshort y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2svARB,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3dARB,
(GLuint index ,  GLdouble x ,  GLdouble y , GLdouble z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3dvARB,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3fARB,
(GLuint index ,  GLfloat x ,  GLfloat y , GLfloat z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3fvARB,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3sARB,
(GLuint index ,  GLshort x ,  GLshort y , GLshort z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3svARB,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NbvARB,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NivARB,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NsvARB,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NubARB,
(GLuint index ,  GLubyte x ,  GLubyte y ,  GLubyte z , GLubyte w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4NubvARB,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NuivARB,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4NusvARB,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4bvARB,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4dARB,
(GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4dvARB,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4fARB,
(GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4fvARB,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4ivARB,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4sARB,
(GLuint index ,  GLshort x ,  GLshort y ,  GLshort z , GLshort w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4svARB,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4ubvARB,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4uivARB,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4usvARB,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glVertexAttribPointerARB,
(GLuint index ,  GLint size ,  GLenum type ,  GLboolean normalized ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , normalized , stride , pointer)
)

GLPROC_VOID(glEnableVertexAttribArrayARB,
(GLuint index),
(index)
)

GLPROC_VOID(glDisableVertexAttribArrayARB,
(GLuint index),
(index)
)

GLPROC_VOID(glGetVertexAttribdvARB,
(GLuint index ,  GLenum pname , GLdouble *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribfvARB,
(GLuint index ,  GLenum pname , GLfloat *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribivARB,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribPointervARB,
(GLuint index ,  GLenum pname , GLvoid **pointer),
(index , pname , pointer)
)





GLPROC_VOID(glBindAttribLocationARB,
(GLhandleARB programObj ,  GLuint index , const GLcharARB *name),
(programObj , index , name)
)

GLPROC_VOID(glGetActiveAttribARB,
(GLhandleARB programObj ,  GLuint index ,  GLsizei maxLength ,  GLsizei *length ,  GLint *size ,  GLenum *type , GLcharARB *name),
(programObj , index , maxLength , length , size , type , name)
)

GLPROC_RETURN1(GLint,
glGetAttribLocationARB,
(GLhandleARB programObj , const GLcharARB *name),
(programObj , name)
)





GLPROC_VOID(glWindowPos2dARB,
(GLdouble x , GLdouble y),
(x , y)
)

GLPROC_VOID(glWindowPos2dvARB,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos2fARB,
(GLfloat x , GLfloat y),
(x , y)
)

GLPROC_VOID(glWindowPos2fvARB,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos2iARB,
(GLint x , GLint y),
(x , y)
)

GLPROC_VOID(glWindowPos2ivARB,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos2sARB,
(GLshort x , GLshort y),
(x , y)
)

GLPROC_VOID(glWindowPos2svARB,
(const GLshort *v),
(v)
)

GLPROC_VOID(glWindowPos3dARB,
(GLdouble x ,  GLdouble y , GLdouble z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3dvARB,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos3fARB,
(GLfloat x ,  GLfloat y , GLfloat z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3fvARB,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos3iARB,
(GLint x ,  GLint y , GLint z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3ivARB,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos3sARB,
(GLshort x ,  GLshort y , GLshort z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3svARB,
(const GLshort *v),
(v)
)





GLPROC_VOID(glMultiTexCoord1bOES,
(GLenum texture , GLbyte s),
(texture , s)
)

GLPROC_VOID(glMultiTexCoord1bvOES,
(GLenum texture , const GLbyte *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord2bOES,
(GLenum texture ,  GLbyte s , GLbyte t),
(texture , s , t)
)

GLPROC_VOID(glMultiTexCoord2bvOES,
(GLenum texture , const GLbyte *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord3bOES,
(GLenum texture ,  GLbyte s ,  GLbyte t , GLbyte r),
(texture , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3bvOES,
(GLenum texture , const GLbyte *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord4bOES,
(GLenum texture ,  GLbyte s ,  GLbyte t ,  GLbyte r , GLbyte q),
(texture , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4bvOES,
(GLenum texture , const GLbyte *coords),
(texture , coords)
)

GLPROC_VOID(glTexCoord1bOES,
(GLbyte s),
(s)
)

GLPROC_VOID(glTexCoord1bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glTexCoord2bOES,
(GLbyte s , GLbyte t),
(s , t)
)

GLPROC_VOID(glTexCoord2bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glTexCoord3bOES,
(GLbyte s ,  GLbyte t , GLbyte r),
(s , t , r)
)

GLPROC_VOID(glTexCoord3bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glTexCoord4bOES,
(GLbyte s ,  GLbyte t ,  GLbyte r , GLbyte q),
(s , t , r , q)
)

GLPROC_VOID(glTexCoord4bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glVertex2bOES,
(GLbyte x),
(x)
)

GLPROC_VOID(glVertex2bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glVertex3bOES,
(GLbyte x , GLbyte y),
(x , y)
)

GLPROC_VOID(glVertex3bvOES,
(const GLbyte *coords),
(coords)
)

GLPROC_VOID(glVertex4bOES,
(GLbyte x ,  GLbyte y , GLbyte z),
(x , y , z)
)

GLPROC_VOID(glVertex4bvOES,
(const GLbyte *coords),
(coords)
)





GLPROC_VOID(glAlphaFuncxOES,
(GLenum func , GLfixed ref),
(func , ref)
)

GLPROC_VOID(glClearColorxOES,
(GLfixed red ,  GLfixed green ,  GLfixed blue , GLfixed alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glClearDepthxOES,
(GLfixed depth),
(depth)
)

GLPROC_VOID(glClipPlanexOES,
(GLenum plane , const GLfixed *equation),
(plane , equation)
)

GLPROC_VOID(glColor4xOES,
(GLfixed red ,  GLfixed green ,  GLfixed blue , GLfixed alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glDepthRangexOES,
(GLfixed n , GLfixed f),
(n , f)
)

GLPROC_VOID(glFogxOES,
(GLenum pname , GLfixed param),
(pname , param)
)

GLPROC_VOID(glFogxvOES,
(GLenum pname , const GLfixed *param),
(pname , param)
)

GLPROC_VOID(glFrustumxOES,
(GLfixed l ,  GLfixed r ,  GLfixed b ,  GLfixed t ,  GLfixed n , GLfixed f),
(l , r , b , t , n , f)
)

GLPROC_VOID(glGetClipPlanexOES,
(GLenum plane , GLfixed *equation),
(plane , equation)
)

GLPROC_VOID(glGetFixedvOES,
(GLenum pname , GLfixed *params),
(pname , params)
)

GLPROC_VOID(glGetTexEnvxvOES,
(GLenum target ,  GLenum pname , GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameterxvOES,
(GLenum target ,  GLenum pname , GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glLightModelxOES,
(GLenum pname , GLfixed param),
(pname , param)
)

GLPROC_VOID(glLightModelxvOES,
(GLenum pname , const GLfixed *param),
(pname , param)
)

GLPROC_VOID(glLightxOES,
(GLenum light ,  GLenum pname , GLfixed param),
(light , pname , param)
)

GLPROC_VOID(glLightxvOES,
(GLenum light ,  GLenum pname , const GLfixed *params),
(light , pname , params)
)

GLPROC_VOID(glLineWidthxOES,
(GLfixed width),
(width)
)

GLPROC_VOID(glLoadMatrixxOES,
(const GLfixed *m),
(m)
)

GLPROC_VOID(glMaterialxOES,
(GLenum face ,  GLenum pname , GLfixed param),
(face , pname , param)
)

GLPROC_VOID(glMaterialxvOES,
(GLenum face ,  GLenum pname , const GLfixed *param),
(face , pname , param)
)

GLPROC_VOID(glMultMatrixxOES,
(const GLfixed *m),
(m)
)

GLPROC_VOID(glMultiTexCoord4xOES,
(GLenum texture ,  GLfixed s ,  GLfixed t ,  GLfixed r , GLfixed q),
(texture , s , t , r , q)
)

GLPROC_VOID(glNormal3xOES,
(GLfixed nx ,  GLfixed ny , GLfixed nz),
(nx , ny , nz)
)

GLPROC_VOID(glOrthoxOES,
(GLfixed l ,  GLfixed r ,  GLfixed b ,  GLfixed t ,  GLfixed n , GLfixed f),
(l , r , b , t , n , f)
)

GLPROC_VOID(glPointParameterxvOES,
(GLenum pname , const GLfixed *params),
(pname , params)
)

GLPROC_VOID(glPointSizexOES,
(GLfixed size),
(size)
)

GLPROC_VOID(glPolygonOffsetxOES,
(GLfixed factor , GLfixed units),
(factor , units)
)

GLPROC_VOID(glRotatexOES,
(GLfixed angle ,  GLfixed x ,  GLfixed y , GLfixed z),
(angle , x , y , z)
)

GLPROC_VOID(glSampleCoverageOES,
(GLfixed value , GLboolean invert),
(value , invert)
)

GLPROC_VOID(glScalexOES,
(GLfixed x ,  GLfixed y , GLfixed z),
(x , y , z)
)

GLPROC_VOID(glTexEnvxOES,
(GLenum target ,  GLenum pname , GLfixed param),
(target , pname , param)
)

GLPROC_VOID(glTexEnvxvOES,
(GLenum target ,  GLenum pname , const GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glTexParameterxOES,
(GLenum target ,  GLenum pname , GLfixed param),
(target , pname , param)
)

GLPROC_VOID(glTexParameterxvOES,
(GLenum target ,  GLenum pname , const GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glTranslatexOES,
(GLfixed x ,  GLfixed y , GLfixed z),
(x , y , z)
)

GLPROC_VOID(glAccumxOES,
(GLenum op , GLfixed value),
(op , value)
)

GLPROC_VOID(glBitmapxOES,
(GLsizei width ,  GLsizei height ,  GLfixed xorig ,  GLfixed yorig ,  GLfixed xmove ,  GLfixed ymove , const GLubyte *bitmap),
(width , height , xorig , yorig , xmove , ymove , bitmap)
)

GLPROC_VOID(glBlendColorxOES,
(GLfixed red ,  GLfixed green ,  GLfixed blue , GLfixed alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glClearAccumxOES,
(GLfixed red ,  GLfixed green ,  GLfixed blue , GLfixed alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glColor3xOES,
(GLfixed red ,  GLfixed green , GLfixed blue),
(red , green , blue)
)

GLPROC_VOID(glColor3xvOES,
(const GLfixed *components),
(components)
)

GLPROC_VOID(glColor4xvOES,
(const GLfixed *components),
(components)
)

GLPROC_VOID(glConvolutionParameterxOES,
(GLenum target ,  GLenum pname , GLfixed param),
(target , pname , param)
)

GLPROC_VOID(glConvolutionParameterxvOES,
(GLenum target ,  GLenum pname , const GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glEvalCoord1xOES,
(GLfixed u),
(u)
)

GLPROC_VOID(glEvalCoord1xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glEvalCoord2xOES,
(GLfixed u , GLfixed v),
(u , v)
)

GLPROC_VOID(glEvalCoord2xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glFeedbackBufferxOES,
(GLsizei n ,  GLenum type , const GLfixed *buffer),
(n , type , buffer)
)

GLPROC_VOID(glGetConvolutionParameterxvOES,
(GLenum target ,  GLenum pname , GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glGetHistogramParameterxvOES,
(GLenum target ,  GLenum pname , GLfixed *params),
(target , pname , params)
)

GLPROC_VOID(glGetLightxOES,
(GLenum light ,  GLenum pname , GLfixed *params),
(light , pname , params)
)

GLPROC_VOID(glGetMapxvOES,
(GLenum target ,  GLenum query , GLfixed *v),
(target , query , v)
)

GLPROC_VOID(glGetMaterialxOES,
(GLenum face ,  GLenum pname , GLfixed param),
(face , pname , param)
)

GLPROC_VOID(glGetPixelMapxv,
(GLenum map ,  GLint size , GLfixed *values),
(map , size , values)
)

GLPROC_VOID(glGetTexGenxvOES,
(GLenum coord ,  GLenum pname , GLfixed *params),
(coord , pname , params)
)

GLPROC_VOID(glGetTexLevelParameterxvOES,
(GLenum target ,  GLint level ,  GLenum pname , GLfixed *params),
(target , level , pname , params)
)

GLPROC_VOID(glIndexxOES,
(GLfixed component),
(component)
)

GLPROC_VOID(glIndexxvOES,
(const GLfixed *component),
(component)
)

GLPROC_VOID(glLoadTransposeMatrixxOES,
(const GLfixed *m),
(m)
)

GLPROC_VOID(glMap1xOES,
(GLenum target ,  GLfixed u1 ,  GLfixed u2 ,  GLint stride ,  GLint order , GLfixed points),
(target , u1 , u2 , stride , order , points)
)

GLPROC_VOID(glMap2xOES,
(GLenum target ,  GLfixed u1 ,  GLfixed u2 ,  GLint ustride ,  GLint uorder ,  GLfixed v1 ,  GLfixed v2 ,  GLint vstride ,  GLint vorder , GLfixed points),
(target , u1 , u2 , ustride , uorder , v1 , v2 , vstride , vorder , points)
)

GLPROC_VOID(glMapGrid1xOES,
(GLint n ,  GLfixed u1 , GLfixed u2),
(n , u1 , u2)
)

GLPROC_VOID(glMapGrid2xOES,
(GLint n ,  GLfixed u1 ,  GLfixed u2 ,  GLfixed v1 , GLfixed v2),
(n , u1 , u2 , v1 , v2)
)

GLPROC_VOID(glMultTransposeMatrixxOES,
(const GLfixed *m),
(m)
)

GLPROC_VOID(glMultiTexCoord1xOES,
(GLenum texture , GLfixed s),
(texture , s)
)

GLPROC_VOID(glMultiTexCoord1xvOES,
(GLenum texture , const GLfixed *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord2xOES,
(GLenum texture ,  GLfixed s , GLfixed t),
(texture , s , t)
)

GLPROC_VOID(glMultiTexCoord2xvOES,
(GLenum texture , const GLfixed *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord3xOES,
(GLenum texture ,  GLfixed s ,  GLfixed t , GLfixed r),
(texture , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3xvOES,
(GLenum texture , const GLfixed *coords),
(texture , coords)
)

GLPROC_VOID(glMultiTexCoord4xvOES,
(GLenum texture , const GLfixed *coords),
(texture , coords)
)

GLPROC_VOID(glNormal3xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glPassThroughxOES,
(GLfixed token),
(token)
)

GLPROC_VOID(glPixelMapx,
(GLenum map ,  GLint size , const GLfixed *values),
(map , size , values)
)

GLPROC_VOID(glPixelStorex,
(GLenum pname , GLfixed param),
(pname , param)
)

GLPROC_VOID(glPixelTransferxOES,
(GLenum pname , GLfixed param),
(pname , param)
)

GLPROC_VOID(glPixelZoomxOES,
(GLfixed xfactor , GLfixed yfactor),
(xfactor , yfactor)
)

GLPROC_VOID(glPrioritizeTexturesxOES,
(GLsizei n ,  const GLuint *textures , const GLfixed *priorities),
(n , textures , priorities)
)

GLPROC_VOID(glRasterPos2xOES,
(GLfixed x , GLfixed y),
(x , y)
)

GLPROC_VOID(glRasterPos2xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glRasterPos3xOES,
(GLfixed x ,  GLfixed y , GLfixed z),
(x , y , z)
)

GLPROC_VOID(glRasterPos3xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glRasterPos4xOES,
(GLfixed x ,  GLfixed y ,  GLfixed z , GLfixed w),
(x , y , z , w)
)

GLPROC_VOID(glRasterPos4xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glRectxOES,
(GLfixed x1 ,  GLfixed y1 ,  GLfixed x2 , GLfixed y2),
(x1 , y1 , x2 , y2)
)

GLPROC_VOID(glRectxvOES,
(const GLfixed *v1 , const GLfixed *v2),
(v1 , v2)
)

GLPROC_VOID(glTexCoord1xOES,
(GLfixed s),
(s)
)

GLPROC_VOID(glTexCoord1xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glTexCoord2xOES,
(GLfixed s , GLfixed t),
(s , t)
)

GLPROC_VOID(glTexCoord2xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glTexCoord3xOES,
(GLfixed s ,  GLfixed t , GLfixed r),
(s , t , r)
)

GLPROC_VOID(glTexCoord3xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glTexCoord4xOES,
(GLfixed s ,  GLfixed t ,  GLfixed r , GLfixed q),
(s , t , r , q)
)

GLPROC_VOID(glTexCoord4xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glTexGenxOES,
(GLenum coord ,  GLenum pname , GLfixed param),
(coord , pname , param)
)

GLPROC_VOID(glTexGenxvOES,
(GLenum coord ,  GLenum pname , const GLfixed *params),
(coord , pname , params)
)

GLPROC_VOID(glVertex2xOES,
(GLfixed x),
(x)
)

GLPROC_VOID(glVertex2xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glVertex3xOES,
(GLfixed x , GLfixed y),
(x , y)
)

GLPROC_VOID(glVertex3xvOES,
(const GLfixed *coords),
(coords)
)

GLPROC_VOID(glVertex4xOES,
(GLfixed x ,  GLfixed y , GLfixed z),
(x , y , z)
)

GLPROC_VOID(glVertex4xvOES,
(const GLfixed *coords),
(coords)
)





GLPROC_RETURN1(GLbitfield,
glQueryMatrixxOES,
(GLfixed *mantissa , GLint *exponent),
(mantissa , exponent)
)





GLPROC_VOID(glClearDepthfOES,
(GLclampf depth),
(depth)
)

GLPROC_VOID(glClipPlanefOES,
(GLenum plane , const GLfloat *equation),
(plane , equation)
)

GLPROC_VOID(glDepthRangefOES,
(GLclampf n , GLclampf f),
(n , f)
)

GLPROC_VOID(glFrustumfOES,
(GLfloat l ,  GLfloat r ,  GLfloat b ,  GLfloat t ,  GLfloat n , GLfloat f),
(l , r , b , t , n , f)
)

GLPROC_VOID(glGetClipPlanefOES,
(GLenum plane , GLfloat *equation),
(plane , equation)
)

GLPROC_VOID(glOrthofOES,
(GLfloat l ,  GLfloat r ,  GLfloat b ,  GLfloat t ,  GLfloat n , GLfloat f),
(l , r , b , t , n , f)
)





GLPROC_VOID(glTbufferMask3DFX,
(GLuint mask),
(mask)
)





GLPROC_VOID(glDebugMessageEnableAMD,
(GLenum category ,  GLenum severity ,  GLsizei count ,  const GLuint *ids , GLboolean enabled),
(category , severity , count , ids , enabled)
)

GLPROC_VOID(glDebugMessageInsertAMD,
(GLenum category ,  GLenum severity ,  GLuint id ,  GLsizei length , const GLchar *buf),
(category , severity , id , length , buf)
)

GLPROC_VOID(glDebugMessageCallbackAMD,
(GLDEBUGPROCAMD callback , void *userParam),
(callback , userParam)
)

GLPROC_RETURN1(GLuint,
glGetDebugMessageLogAMD,
(GLuint count ,  GLsizei bufsize ,  GLenum *categories ,  GLuint *severities ,  GLuint *ids ,  GLsizei *lengths , GLchar *message),
(count , bufsize , categories , severities , ids , lengths , message)
)





GLPROC_VOID(glBlendFuncIndexedAMD,
(GLuint buf ,  GLenum src , GLenum dst),
(buf , src , dst)
)

GLPROC_VOID(glBlendFuncSeparateIndexedAMD,
(GLuint buf ,  GLenum srcRGB ,  GLenum dstRGB ,  GLenum srcAlpha , GLenum dstAlpha),
(buf , srcRGB , dstRGB , srcAlpha , dstAlpha)
)

GLPROC_VOID(glBlendEquationIndexedAMD,
(GLuint buf , GLenum mode),
(buf , mode)
)

GLPROC_VOID(glBlendEquationSeparateIndexedAMD,
(GLuint buf ,  GLenum modeRGB , GLenum modeAlpha),
(buf , modeRGB , modeAlpha)
)





GLPROC_VOID(glVertexAttribParameteriAMD,
(GLuint index ,  GLenum pname , GLint param),
(index , pname , param)
)





GLPROC_VOID(glMultiDrawArraysIndirectAMD,
(GLenum mode ,  const GLvoid *indirect ,  GLsizei primcount , GLsizei stride),
(mode , indirect , primcount , stride)
)

GLPROC_VOID(glMultiDrawElementsIndirectAMD,
(GLenum mode ,  GLenum type ,  const GLvoid *indirect ,  GLsizei primcount , GLsizei stride),
(mode , type , indirect , primcount , stride)
)





GLPROC_VOID(glGenNamesAMD,
(GLenum identifier ,  GLuint num , GLuint *names),
(identifier , num , names)
)

GLPROC_VOID(glDeleteNamesAMD,
(GLenum identifier ,  GLuint num , const GLuint *names),
(identifier , num , names)
)

GLPROC_RETURN1(GLboolean,
glIsNameAMD,
(GLenum identifier , GLuint name),
(identifier , name)
)





GLPROC_VOID(glGetPerfMonitorGroupsAMD,
(GLint *numGroups ,  GLsizei groupsSize , GLuint *groups),
(numGroups , groupsSize , groups)
)

GLPROC_VOID(glGetPerfMonitorCountersAMD,
(GLuint group ,  GLint *numCounters ,  GLint *maxActiveCounters ,  GLsizei counterSize , GLuint *counters),
(group , numCounters , maxActiveCounters , counterSize , counters)
)

GLPROC_VOID(glGetPerfMonitorGroupStringAMD,
(GLuint group ,  GLsizei bufSize ,  GLsizei *length , GLchar *groupString),
(group , bufSize , length , groupString)
)

GLPROC_VOID(glGetPerfMonitorCounterStringAMD,
(GLuint group ,  GLuint counter ,  GLsizei bufSize ,  GLsizei *length , GLchar *counterString),
(group , counter , bufSize , length , counterString)
)

GLPROC_VOID(glGetPerfMonitorCounterInfoAMD,
(GLuint group ,  GLuint counter ,  GLenum pname , GLvoid *data),
(group , counter , pname , data)
)

GLPROC_VOID(glGenPerfMonitorsAMD,
(GLsizei n , GLuint *monitors),
(n , monitors)
)

GLPROC_VOID(glDeletePerfMonitorsAMD,
(GLsizei n , GLuint *monitors),
(n , monitors)
)

GLPROC_VOID(glSelectPerfMonitorCountersAMD,
(GLuint monitor ,  GLboolean enable ,  GLuint group ,  GLint numCounters , GLuint *counterList),
(monitor , enable , group , numCounters , counterList)
)

GLPROC_VOID(glBeginPerfMonitorAMD,
(GLuint monitor),
(monitor)
)

GLPROC_VOID(glEndPerfMonitorAMD,
(GLuint monitor),
(monitor)
)

GLPROC_VOID(glGetPerfMonitorCounterDataAMD,
(GLuint monitor ,  GLenum pname ,  GLsizei dataSize ,  GLuint *data , GLint *bytesWritten),
(monitor , pname , dataSize , data , bytesWritten)
)





GLPROC_VOID(glSetMultisamplefvAMD,
(GLenum pname ,  GLuint index , const GLfloat *val),
(pname , index , val)
)





GLPROC_VOID(glTexStorageSparseAMD,
(GLenum target ,  GLenum internalFormat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLsizei layers , GLbitfield flags),
(target , internalFormat , width , height , depth , layers , flags)
)

GLPROC_VOID(glTextureStorageSparseAMD,
(GLuint texture ,  GLenum target ,  GLenum internalFormat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLsizei layers , GLbitfield flags),
(texture , target , internalFormat , width , height , depth , layers , flags)
)





GLPROC_VOID(glStencilOpValueAMD,
(GLenum face , GLuint value),
(face , value)
)





GLPROC_VOID(glTessellationFactorAMD,
(GLfloat factor),
(factor)
)

GLPROC_VOID(glTessellationModeAMD,
(GLenum mode),
(mode)
)





GLPROC_VOID(glElementPointerAPPLE,
(GLenum type , const GLvoid *pointer),
(type , pointer)
)

GLPROC_VOID(glDrawElementArrayAPPLE,
(GLenum mode ,  GLint first , GLsizei count),
(mode , first , count)
)

GLPROC_VOID(glDrawRangeElementArrayAPPLE,
(GLenum mode ,  GLuint start ,  GLuint end ,  GLint first , GLsizei count),
(mode , start , end , first , count)
)

GLPROC_VOID(glMultiDrawElementArrayAPPLE,
(GLenum mode ,  const GLint *first ,  const GLsizei *count , GLsizei primcount),
(mode , first , count , primcount)
)

GLPROC_VOID(glMultiDrawRangeElementArrayAPPLE,
(GLenum mode ,  GLuint start ,  GLuint end ,  const GLint *first ,  const GLsizei *count , GLsizei primcount),
(mode , start , end , first , count , primcount)
)





GLPROC_VOID(glGenFencesAPPLE,
(GLsizei n , GLuint *fences),
(n , fences)
)

GLPROC_VOID(glDeleteFencesAPPLE,
(GLsizei n , const GLuint *fences),
(n , fences)
)

GLPROC_VOID(glSetFenceAPPLE,
(GLuint fence),
(fence)
)

GLPROC_RETURN1(GLboolean,
glIsFenceAPPLE,
(GLuint fence),
(fence)
)

GLPROC_RETURN1(GLboolean,
glTestFenceAPPLE,
(GLuint fence),
(fence)
)

GLPROC_VOID(glFinishFenceAPPLE,
(GLuint fence),
(fence)
)

GLPROC_RETURN1(GLboolean,
glTestObjectAPPLE,
(GLenum object , GLuint name),
(object , name)
)

GLPROC_VOID(glFinishObjectAPPLE,
(GLenum object , GLint name),
(object , name)
)





GLPROC_VOID(glBufferParameteriAPPLE,
(GLenum target ,  GLenum pname , GLint param),
(target , pname , param)
)

GLPROC_VOID(glFlushMappedBufferRangeAPPLE,
(GLenum target ,  GLintptr offset , GLsizeiptr size),
(target , offset , size)
)





GLPROC_RETURN1(GLenum,
glObjectPurgeableAPPLE,
(GLenum objectType ,  GLuint name , GLenum option),
(objectType , name , option)
)

GLPROC_RETURN1(GLenum,
glObjectUnpurgeableAPPLE,
(GLenum objectType ,  GLuint name , GLenum option),
(objectType , name , option)
)

GLPROC_VOID(glGetObjectParameterivAPPLE,
(GLenum objectType ,  GLuint name ,  GLenum pname , GLint *params),
(objectType , name , pname , params)
)





GLPROC_VOID(glTextureRangeAPPLE,
(GLenum target ,  GLsizei length , const GLvoid *pointer),
(target , length , pointer)
)

GLPROC_VOID(glGetTexParameterPointervAPPLE,
(GLenum target ,  GLenum pname , GLvoid **params),
(target , pname , params)
)





GLPROC_VOID(glBindVertexArrayAPPLE,
(GLuint array),
(array)
)

GLPROC_VOID(glDeleteVertexArraysAPPLE,
(GLsizei n , const GLuint *arrays),
(n , arrays)
)

GLPROC_VOID(glGenVertexArraysAPPLE,
(GLsizei n , GLuint *arrays),
(n , arrays)
)

GLPROC_RETURN1(GLboolean,
glIsVertexArrayAPPLE,
(GLuint array),
(array)
)





GLPROC_VOID(glVertexArrayRangeAPPLE,
(GLsizei length , GLvoid *pointer),
(length , pointer)
)

GLPROC_VOID(glFlushVertexArrayRangeAPPLE,
(GLsizei length , GLvoid *pointer),
(length , pointer)
)

GLPROC_VOID(glVertexArrayParameteriAPPLE,
(GLenum pname , GLint param),
(pname , param)
)





GLPROC_VOID(glEnableVertexAttribAPPLE,
(GLuint index , GLenum pname),
(index , pname)
)

GLPROC_VOID(glDisableVertexAttribAPPLE,
(GLuint index , GLenum pname),
(index , pname)
)

GLPROC_RETURN1(GLboolean,
glIsVertexAttribEnabledAPPLE,
(GLuint index , GLenum pname),
(index , pname)
)

GLPROC_VOID(glMapVertexAttrib1dAPPLE,
(GLuint index ,  GLuint size ,  GLdouble u1 ,  GLdouble u2 ,  GLint stride ,  GLint order , const GLdouble *points),
(index , size , u1 , u2 , stride , order , points)
)

GLPROC_VOID(glMapVertexAttrib1fAPPLE,
(GLuint index ,  GLuint size ,  GLfloat u1 ,  GLfloat u2 ,  GLint stride ,  GLint order , const GLfloat *points),
(index , size , u1 , u2 , stride , order , points)
)

GLPROC_VOID(glMapVertexAttrib2dAPPLE,
(GLuint index ,  GLuint size ,  GLdouble u1 ,  GLdouble u2 ,  GLint ustride ,  GLint uorder ,  GLdouble v1 ,  GLdouble v2 ,  GLint vstride ,  GLint vorder , const GLdouble *points),
(index , size , u1 , u2 , ustride , uorder , v1 , v2 , vstride , vorder , points)
)

GLPROC_VOID(glMapVertexAttrib2fAPPLE,
(GLuint index ,  GLuint size ,  GLfloat u1 ,  GLfloat u2 ,  GLint ustride ,  GLint uorder ,  GLfloat v1 ,  GLfloat v2 ,  GLint vstride ,  GLint vorder , const GLfloat *points),
(index , size , u1 , u2 , ustride , uorder , v1 , v2 , vstride , vorder , points)
)





GLPROC_VOID(glDrawBuffersATI,
(GLsizei n , const GLenum *bufs),
(n , bufs)
)





GLPROC_VOID(glElementPointerATI,
(GLenum type , const GLvoid *pointer),
(type , pointer)
)

GLPROC_VOID(glDrawElementArrayATI,
(GLenum mode , GLsizei count),
(mode , count)
)

GLPROC_VOID(glDrawRangeElementArrayATI,
(GLenum mode ,  GLuint start ,  GLuint end , GLsizei count),
(mode , start , end , count)
)





GLPROC_VOID(glTexBumpParameterivATI,
(GLenum pname , const GLint *param),
(pname , param)
)

GLPROC_VOID(glTexBumpParameterfvATI,
(GLenum pname , const GLfloat *param),
(pname , param)
)

GLPROC_VOID(glGetTexBumpParameterivATI,
(GLenum pname , GLint *param),
(pname , param)
)

GLPROC_VOID(glGetTexBumpParameterfvATI,
(GLenum pname , GLfloat *param),
(pname , param)
)





GLPROC_RETURN1(GLuint,
glGenFragmentShadersATI,
(GLuint range),
(range)
)

GLPROC_VOID(glBindFragmentShaderATI,
(GLuint id),
(id)
)

GLPROC_VOID(glDeleteFragmentShaderATI,
(GLuint id),
(id)
)

GLPROC_VOID(glBeginFragmentShaderATI,
(void),
()
)

GLPROC_VOID(glEndFragmentShaderATI,
(void),
()
)

GLPROC_VOID(glPassTexCoordATI,
(GLuint dst ,  GLuint coord , GLenum swizzle),
(dst , coord , swizzle)
)

GLPROC_VOID(glSampleMapATI,
(GLuint dst ,  GLuint interp , GLenum swizzle),
(dst , interp , swizzle)
)

GLPROC_VOID(glColorFragmentOp1ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMask ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep , GLuint arg1Mod),
(op , dst , dstMask , dstMod , arg1 , arg1Rep , arg1Mod)
)

GLPROC_VOID(glColorFragmentOp2ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMask ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep ,  GLuint arg1Mod ,  GLuint arg2 ,  GLuint arg2Rep , GLuint arg2Mod),
(op , dst , dstMask , dstMod , arg1 , arg1Rep , arg1Mod , arg2 , arg2Rep , arg2Mod)
)

GLPROC_VOID(glColorFragmentOp3ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMask ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep ,  GLuint arg1Mod ,  GLuint arg2 ,  GLuint arg2Rep ,  GLuint arg2Mod ,  GLuint arg3 ,  GLuint arg3Rep , GLuint arg3Mod),
(op , dst , dstMask , dstMod , arg1 , arg1Rep , arg1Mod , arg2 , arg2Rep , arg2Mod , arg3 , arg3Rep , arg3Mod)
)

GLPROC_VOID(glAlphaFragmentOp1ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep , GLuint arg1Mod),
(op , dst , dstMod , arg1 , arg1Rep , arg1Mod)
)

GLPROC_VOID(glAlphaFragmentOp2ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep ,  GLuint arg1Mod ,  GLuint arg2 ,  GLuint arg2Rep , GLuint arg2Mod),
(op , dst , dstMod , arg1 , arg1Rep , arg1Mod , arg2 , arg2Rep , arg2Mod)
)

GLPROC_VOID(glAlphaFragmentOp3ATI,
(GLenum op ,  GLuint dst ,  GLuint dstMod ,  GLuint arg1 ,  GLuint arg1Rep ,  GLuint arg1Mod ,  GLuint arg2 ,  GLuint arg2Rep ,  GLuint arg2Mod ,  GLuint arg3 ,  GLuint arg3Rep , GLuint arg3Mod),
(op , dst , dstMod , arg1 , arg1Rep , arg1Mod , arg2 , arg2Rep , arg2Mod , arg3 , arg3Rep , arg3Mod)
)

GLPROC_VOID(glSetFragmentShaderConstantATI,
(GLuint dst , const GLfloat *value),
(dst , value)
)





GLPROC_RETURN1(void *,
glMapObjectBufferATI,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glUnmapObjectBufferATI,
(GLuint buffer),
(buffer)
)





GLPROC_VOID(glPNTrianglesiATI,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glPNTrianglesfATI,
(GLenum pname , GLfloat param),
(pname , param)
)





GLPROC_VOID(glStencilOpSeparateATI,
(GLenum face ,  GLenum sfail ,  GLenum dpfail , GLenum dppass),
(face , sfail , dpfail , dppass)
)

GLPROC_VOID(glStencilFuncSeparateATI,
(GLenum frontfunc ,  GLenum backfunc ,  GLint ref , GLuint mask),
(frontfunc , backfunc , ref , mask)
)





GLPROC_RETURN1(GLuint,
glNewObjectBufferATI,
(GLsizei size ,  const GLvoid *pointer , GLenum usage),
(size , pointer , usage)
)

GLPROC_RETURN1(GLboolean,
glIsObjectBufferATI,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glUpdateObjectBufferATI,
(GLuint buffer ,  GLuint offset ,  GLsizei size ,  const GLvoid *pointer , GLenum preserve),
(buffer , offset , size , pointer , preserve)
)

GLPROC_VOID(glGetObjectBufferfvATI,
(GLuint buffer ,  GLenum pname , GLfloat *params),
(buffer , pname , params)
)

GLPROC_VOID(glGetObjectBufferivATI,
(GLuint buffer ,  GLenum pname , GLint *params),
(buffer , pname , params)
)

GLPROC_VOID(glFreeObjectBufferATI,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glArrayObjectATI,
(GLenum array ,  GLint size ,  GLenum type ,  GLsizei stride ,  GLuint buffer , GLuint offset),
(array , size , type , stride , buffer , offset)
)

GLPROC_VOID(glGetArrayObjectfvATI,
(GLenum array ,  GLenum pname , GLfloat *params),
(array , pname , params)
)

GLPROC_VOID(glGetArrayObjectivATI,
(GLenum array ,  GLenum pname , GLint *params),
(array , pname , params)
)

GLPROC_VOID(glVariantArrayObjectATI,
(GLuint id ,  GLenum type ,  GLsizei stride ,  GLuint buffer , GLuint offset),
(id , type , stride , buffer , offset)
)

GLPROC_VOID(glGetVariantArrayObjectfvATI,
(GLuint id ,  GLenum pname , GLfloat *params),
(id , pname , params)
)

GLPROC_VOID(glGetVariantArrayObjectivATI,
(GLuint id ,  GLenum pname , GLint *params),
(id , pname , params)
)





GLPROC_VOID(glVertexAttribArrayObjectATI,
(GLuint index ,  GLint size ,  GLenum type ,  GLboolean normalized ,  GLsizei stride ,  GLuint buffer , GLuint offset),
(index , size , type , normalized , stride , buffer , offset)
)

GLPROC_VOID(glGetVertexAttribArrayObjectfvATI,
(GLuint index ,  GLenum pname , GLfloat *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribArrayObjectivATI,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)





GLPROC_VOID(glVertexStream1sATI,
(GLenum stream , GLshort x),
(stream , x)
)

GLPROC_VOID(glVertexStream1svATI,
(GLenum stream , const GLshort *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream1iATI,
(GLenum stream , GLint x),
(stream , x)
)

GLPROC_VOID(glVertexStream1ivATI,
(GLenum stream , const GLint *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream1fATI,
(GLenum stream , GLfloat x),
(stream , x)
)

GLPROC_VOID(glVertexStream1fvATI,
(GLenum stream , const GLfloat *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream1dATI,
(GLenum stream , GLdouble x),
(stream , x)
)

GLPROC_VOID(glVertexStream1dvATI,
(GLenum stream , const GLdouble *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream2sATI,
(GLenum stream ,  GLshort x , GLshort y),
(stream , x , y)
)

GLPROC_VOID(glVertexStream2svATI,
(GLenum stream , const GLshort *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream2iATI,
(GLenum stream ,  GLint x , GLint y),
(stream , x , y)
)

GLPROC_VOID(glVertexStream2ivATI,
(GLenum stream , const GLint *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream2fATI,
(GLenum stream ,  GLfloat x , GLfloat y),
(stream , x , y)
)

GLPROC_VOID(glVertexStream2fvATI,
(GLenum stream , const GLfloat *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream2dATI,
(GLenum stream ,  GLdouble x , GLdouble y),
(stream , x , y)
)

GLPROC_VOID(glVertexStream2dvATI,
(GLenum stream , const GLdouble *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream3sATI,
(GLenum stream ,  GLshort x ,  GLshort y , GLshort z),
(stream , x , y , z)
)

GLPROC_VOID(glVertexStream3svATI,
(GLenum stream , const GLshort *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream3iATI,
(GLenum stream ,  GLint x ,  GLint y , GLint z),
(stream , x , y , z)
)

GLPROC_VOID(glVertexStream3ivATI,
(GLenum stream , const GLint *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream3fATI,
(GLenum stream ,  GLfloat x ,  GLfloat y , GLfloat z),
(stream , x , y , z)
)

GLPROC_VOID(glVertexStream3fvATI,
(GLenum stream , const GLfloat *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream3dATI,
(GLenum stream ,  GLdouble x ,  GLdouble y , GLdouble z),
(stream , x , y , z)
)

GLPROC_VOID(glVertexStream3dvATI,
(GLenum stream , const GLdouble *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream4sATI,
(GLenum stream ,  GLshort x ,  GLshort y ,  GLshort z , GLshort w),
(stream , x , y , z , w)
)

GLPROC_VOID(glVertexStream4svATI,
(GLenum stream , const GLshort *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream4iATI,
(GLenum stream ,  GLint x ,  GLint y ,  GLint z , GLint w),
(stream , x , y , z , w)
)

GLPROC_VOID(glVertexStream4ivATI,
(GLenum stream , const GLint *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream4fATI,
(GLenum stream ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(stream , x , y , z , w)
)

GLPROC_VOID(glVertexStream4fvATI,
(GLenum stream , const GLfloat *coords),
(stream , coords)
)

GLPROC_VOID(glVertexStream4dATI,
(GLenum stream ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(stream , x , y , z , w)
)

GLPROC_VOID(glVertexStream4dvATI,
(GLenum stream , const GLdouble *coords),
(stream , coords)
)

GLPROC_VOID(glNormalStream3bATI,
(GLenum stream ,  GLbyte nx ,  GLbyte ny , GLbyte nz),
(stream , nx , ny , nz)
)

GLPROC_VOID(glNormalStream3bvATI,
(GLenum stream , const GLbyte *coords),
(stream , coords)
)

GLPROC_VOID(glNormalStream3sATI,
(GLenum stream ,  GLshort nx ,  GLshort ny , GLshort nz),
(stream , nx , ny , nz)
)

GLPROC_VOID(glNormalStream3svATI,
(GLenum stream , const GLshort *coords),
(stream , coords)
)

GLPROC_VOID(glNormalStream3iATI,
(GLenum stream ,  GLint nx ,  GLint ny , GLint nz),
(stream , nx , ny , nz)
)

GLPROC_VOID(glNormalStream3ivATI,
(GLenum stream , const GLint *coords),
(stream , coords)
)

GLPROC_VOID(glNormalStream3fATI,
(GLenum stream ,  GLfloat nx ,  GLfloat ny , GLfloat nz),
(stream , nx , ny , nz)
)

GLPROC_VOID(glNormalStream3fvATI,
(GLenum stream , const GLfloat *coords),
(stream , coords)
)

GLPROC_VOID(glNormalStream3dATI,
(GLenum stream ,  GLdouble nx ,  GLdouble ny , GLdouble nz),
(stream , nx , ny , nz)
)

GLPROC_VOID(glNormalStream3dvATI,
(GLenum stream , const GLdouble *coords),
(stream , coords)
)

GLPROC_VOID(glClientActiveVertexStreamATI,
(GLenum stream),
(stream)
)

GLPROC_VOID(glVertexBlendEnviATI,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glVertexBlendEnvfATI,
(GLenum pname , GLfloat param),
(pname , param)
)





GLPROC_VOID(glUniformBufferEXT,
(GLuint program ,  GLint location , GLuint buffer),
(program , location , buffer)
)

GLPROC_RETURN1(GLint,
glGetUniformBufferSizeEXT,
(GLuint program , GLint location),
(program , location)
)

GLPROC_RETURN1(GLintptr,
glGetUniformOffsetEXT,
(GLuint program , GLint location),
(program , location)
)





GLPROC_VOID(glBlendColorEXT,
(GLfloat red ,  GLfloat green ,  GLfloat blue , GLfloat alpha),
(red , green , blue , alpha)
)





GLPROC_VOID(glBlendEquationSeparateEXT,
(GLenum modeRGB , GLenum modeAlpha),
(modeRGB , modeAlpha)
)





GLPROC_VOID(glBlendFuncSeparateEXT,
(GLenum sfactorRGB ,  GLenum dfactorRGB ,  GLenum sfactorAlpha , GLenum dfactorAlpha),
(sfactorRGB , dfactorRGB , sfactorAlpha , dfactorAlpha)
)





GLPROC_VOID(glColorSubTableEXT,
(GLenum target ,  GLsizei start ,  GLsizei count ,  GLenum format ,  GLenum type , const GLvoid *data),
(target , start , count , format , type , data)
)

GLPROC_VOID(glCopyColorSubTableEXT,
(GLenum target ,  GLsizei start ,  GLint x ,  GLint y , GLsizei width),
(target , start , x , y , width)
)





GLPROC_VOID(glLockArraysEXT,
(GLint first , GLsizei count),
(first , count)
)

GLPROC_VOID(glUnlockArraysEXT,
(void),
()
)





GLPROC_VOID(glConvolutionFilter1DEXT,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *image),
(target , internalformat , width , format , type , image)
)

GLPROC_VOID(glConvolutionFilter2DEXT,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *image),
(target , internalformat , width , height , format , type , image)
)

GLPROC_VOID(glConvolutionParameterfEXT,
(GLenum target ,  GLenum pname , GLfloat params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameterfvEXT,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameteriEXT,
(GLenum target ,  GLenum pname , GLint params),
(target , pname , params)
)

GLPROC_VOID(glConvolutionParameterivEXT,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glCopyConvolutionFilter1DEXT,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y , GLsizei width),
(target , internalformat , x , y , width)
)

GLPROC_VOID(glCopyConvolutionFilter2DEXT,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , internalformat , x , y , width , height)
)

GLPROC_VOID(glGetConvolutionFilterEXT,
(GLenum target ,  GLenum format ,  GLenum type , GLvoid *image),
(target , format , type , image)
)

GLPROC_VOID(glGetConvolutionParameterfvEXT,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetConvolutionParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetSeparableFilterEXT,
(GLenum target ,  GLenum format ,  GLenum type ,  GLvoid *row ,  GLvoid *column , GLvoid *span),
(target , format , type , row , column , span)
)

GLPROC_VOID(glSeparableFilter2DEXT,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type ,  const GLvoid *row , const GLvoid *column),
(target , internalformat , width , height , format , type , row , column)
)





GLPROC_VOID(glTangent3bEXT,
(GLbyte tx ,  GLbyte ty , GLbyte tz),
(tx , ty , tz)
)

GLPROC_VOID(glTangent3bvEXT,
(const GLbyte *v),
(v)
)

GLPROC_VOID(glTangent3dEXT,
(GLdouble tx ,  GLdouble ty , GLdouble tz),
(tx , ty , tz)
)

GLPROC_VOID(glTangent3dvEXT,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glTangent3fEXT,
(GLfloat tx ,  GLfloat ty , GLfloat tz),
(tx , ty , tz)
)

GLPROC_VOID(glTangent3fvEXT,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glTangent3iEXT,
(GLint tx ,  GLint ty , GLint tz),
(tx , ty , tz)
)

GLPROC_VOID(glTangent3ivEXT,
(const GLint *v),
(v)
)

GLPROC_VOID(glTangent3sEXT,
(GLshort tx ,  GLshort ty , GLshort tz),
(tx , ty , tz)
)

GLPROC_VOID(glTangent3svEXT,
(const GLshort *v),
(v)
)

GLPROC_VOID(glBinormal3bEXT,
(GLbyte bx ,  GLbyte by , GLbyte bz),
(bx , by , bz)
)

GLPROC_VOID(glBinormal3bvEXT,
(const GLbyte *v),
(v)
)

GLPROC_VOID(glBinormal3dEXT,
(GLdouble bx ,  GLdouble by , GLdouble bz),
(bx , by , bz)
)

GLPROC_VOID(glBinormal3dvEXT,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glBinormal3fEXT,
(GLfloat bx ,  GLfloat by , GLfloat bz),
(bx , by , bz)
)

GLPROC_VOID(glBinormal3fvEXT,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glBinormal3iEXT,
(GLint bx ,  GLint by , GLint bz),
(bx , by , bz)
)

GLPROC_VOID(glBinormal3ivEXT,
(const GLint *v),
(v)
)

GLPROC_VOID(glBinormal3sEXT,
(GLshort bx ,  GLshort by , GLshort bz),
(bx , by , bz)
)

GLPROC_VOID(glBinormal3svEXT,
(const GLshort *v),
(v)
)

GLPROC_VOID(glTangentPointerEXT,
(GLenum type ,  GLsizei stride , const GLvoid *pointer),
(type , stride , pointer)
)

GLPROC_VOID(glBinormalPointerEXT,
(GLenum type ,  GLsizei stride , const GLvoid *pointer),
(type , stride , pointer)
)





GLPROC_VOID(glCopyTexImage1DEXT,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLint border),
(target , level , internalformat , x , y , width , border)
)

GLPROC_VOID(glCopyTexImage2DEXT,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width ,  GLsizei height , GLint border),
(target , level , internalformat , x , y , width , height , border)
)

GLPROC_VOID(glCopyTexSubImage1DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint x ,  GLint y , GLsizei width),
(target , level , xoffset , x , y , width)
)

GLPROC_VOID(glCopyTexSubImage2DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , level , xoffset , yoffset , x , y , width , height)
)

GLPROC_VOID(glCopyTexSubImage3DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , level , xoffset , yoffset , zoffset , x , y , width , height)
)





GLPROC_VOID(glCullParameterdvEXT,
(GLenum pname , GLdouble *params),
(pname , params)
)

GLPROC_VOID(glCullParameterfvEXT,
(GLenum pname , GLfloat *params),
(pname , params)
)





GLPROC_VOID(glDepthBoundsEXT,
(GLclampd zmin , GLclampd zmax),
(zmin , zmax)
)





GLPROC_VOID(glMatrixLoadfEXT,
(GLenum mode , const GLfloat *m),
(mode , m)
)

GLPROC_VOID(glMatrixLoaddEXT,
(GLenum mode , const GLdouble *m),
(mode , m)
)

GLPROC_VOID(glMatrixMultfEXT,
(GLenum mode , const GLfloat *m),
(mode , m)
)

GLPROC_VOID(glMatrixMultdEXT,
(GLenum mode , const GLdouble *m),
(mode , m)
)

GLPROC_VOID(glMatrixLoadIdentityEXT,
(GLenum mode),
(mode)
)

GLPROC_VOID(glMatrixRotatefEXT,
(GLenum mode ,  GLfloat angle ,  GLfloat x ,  GLfloat y , GLfloat z),
(mode , angle , x , y , z)
)

GLPROC_VOID(glMatrixRotatedEXT,
(GLenum mode ,  GLdouble angle ,  GLdouble x ,  GLdouble y , GLdouble z),
(mode , angle , x , y , z)
)

GLPROC_VOID(glMatrixScalefEXT,
(GLenum mode ,  GLfloat x ,  GLfloat y , GLfloat z),
(mode , x , y , z)
)

GLPROC_VOID(glMatrixScaledEXT,
(GLenum mode ,  GLdouble x ,  GLdouble y , GLdouble z),
(mode , x , y , z)
)

GLPROC_VOID(glMatrixTranslatefEXT,
(GLenum mode ,  GLfloat x ,  GLfloat y , GLfloat z),
(mode , x , y , z)
)

GLPROC_VOID(glMatrixTranslatedEXT,
(GLenum mode ,  GLdouble x ,  GLdouble y , GLdouble z),
(mode , x , y , z)
)

GLPROC_VOID(glMatrixFrustumEXT,
(GLenum mode ,  GLdouble left ,  GLdouble right ,  GLdouble bottom ,  GLdouble top ,  GLdouble zNear , GLdouble zFar),
(mode , left , right , bottom , top , zNear , zFar)
)

GLPROC_VOID(glMatrixOrthoEXT,
(GLenum mode ,  GLdouble left ,  GLdouble right ,  GLdouble bottom ,  GLdouble top ,  GLdouble zNear , GLdouble zFar),
(mode , left , right , bottom , top , zNear , zFar)
)

GLPROC_VOID(glMatrixPopEXT,
(GLenum mode),
(mode)
)

GLPROC_VOID(glMatrixPushEXT,
(GLenum mode),
(mode)
)

GLPROC_VOID(glClientAttribDefaultEXT,
(GLbitfield mask),
(mask)
)

GLPROC_VOID(glPushClientAttribDefaultEXT,
(GLbitfield mask),
(mask)
)

GLPROC_VOID(glTextureParameterfEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLfloat param),
(texture , target , pname , param)
)

GLPROC_VOID(glTextureParameterfvEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , const GLfloat *params),
(texture , target , pname , params)
)

GLPROC_VOID(glTextureParameteriEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLint param),
(texture , target , pname , param)
)

GLPROC_VOID(glTextureParameterivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , const GLint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glTextureImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , internalformat , width , border , format , type , pixels)
)

GLPROC_VOID(glTextureImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , internalformat , width , height , border , format , type , pixels)
)

GLPROC_VOID(glTextureSubImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , xoffset , width , format , type , pixels)
)

GLPROC_VOID(glTextureSubImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , xoffset , yoffset , width , height , format , type , pixels)
)

GLPROC_VOID(glCopyTextureImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLint border),
(texture , target , level , internalformat , x , y , width , border)
)

GLPROC_VOID(glCopyTextureImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width ,  GLsizei height , GLint border),
(texture , target , level , internalformat , x , y , width , height , border)
)

GLPROC_VOID(glCopyTextureSubImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint x ,  GLint y , GLsizei width),
(texture , target , level , xoffset , x , y , width)
)

GLPROC_VOID(glCopyTextureSubImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(texture , target , level , xoffset , yoffset , x , y , width , height)
)

GLPROC_VOID(glGetTextureImageEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum format ,  GLenum type , GLvoid *pixels),
(texture , target , level , format , type , pixels)
)

GLPROC_VOID(glGetTextureParameterfvEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLfloat *params),
(texture , target , pname , params)
)

GLPROC_VOID(glGetTextureParameterivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glGetTextureLevelParameterfvEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum pname , GLfloat *params),
(texture , target , level , pname , params)
)

GLPROC_VOID(glGetTextureLevelParameterivEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum pname , GLint *params),
(texture , target , level , pname , params)
)

GLPROC_VOID(glTextureImage3DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , internalformat , width , height , depth , border , format , type , pixels)
)

GLPROC_VOID(glTextureSubImage3DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texture , target , level , xoffset , yoffset , zoffset , width , height , depth , format , type , pixels)
)

GLPROC_VOID(glCopyTextureSubImage3DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(texture , target , level , xoffset , yoffset , zoffset , x , y , width , height)
)

GLPROC_VOID(glBindMultiTextureEXT,
(GLenum texunit ,  GLenum target , GLuint texture),
(texunit , target , texture)
)

GLPROC_VOID(glMultiTexCoordPointerEXT,
(GLenum texunit ,  GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(texunit , size , type , stride , pointer)
)

GLPROC_VOID(glMultiTexEnvfEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLfloat param),
(texunit , target , pname , param)
)

GLPROC_VOID(glMultiTexEnvfvEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLfloat *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glMultiTexEnviEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLint param),
(texunit , target , pname , param)
)

GLPROC_VOID(glMultiTexEnvivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glMultiTexGendEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLdouble param),
(texunit , coord , pname , param)
)

GLPROC_VOID(glMultiTexGendvEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , const GLdouble *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glMultiTexGenfEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLfloat param),
(texunit , coord , pname , param)
)

GLPROC_VOID(glMultiTexGenfvEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , const GLfloat *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glMultiTexGeniEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLint param),
(texunit , coord , pname , param)
)

GLPROC_VOID(glMultiTexGenivEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , const GLint *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glGetMultiTexEnvfvEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLfloat *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexEnvivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexGendvEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLdouble *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glGetMultiTexGenfvEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLfloat *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glGetMultiTexGenivEXT,
(GLenum texunit ,  GLenum coord ,  GLenum pname , GLint *params),
(texunit , coord , pname , params)
)

GLPROC_VOID(glMultiTexParameteriEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLint param),
(texunit , target , pname , param)
)

GLPROC_VOID(glMultiTexParameterivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glMultiTexParameterfEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLfloat param),
(texunit , target , pname , param)
)

GLPROC_VOID(glMultiTexParameterfvEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLfloat *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glMultiTexImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , internalformat , width , border , format , type , pixels)
)

GLPROC_VOID(glMultiTexImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , internalformat , width , height , border , format , type , pixels)
)

GLPROC_VOID(glMultiTexSubImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , xoffset , width , format , type , pixels)
)

GLPROC_VOID(glMultiTexSubImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , xoffset , yoffset , width , height , format , type , pixels)
)

GLPROC_VOID(glCopyMultiTexImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLint border),
(texunit , target , level , internalformat , x , y , width , border)
)

GLPROC_VOID(glCopyMultiTexImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width ,  GLsizei height , GLint border),
(texunit , target , level , internalformat , x , y , width , height , border)
)

GLPROC_VOID(glCopyMultiTexSubImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint x ,  GLint y , GLsizei width),
(texunit , target , level , xoffset , x , y , width)
)

GLPROC_VOID(glCopyMultiTexSubImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(texunit , target , level , xoffset , yoffset , x , y , width , height)
)

GLPROC_VOID(glGetMultiTexImageEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum format ,  GLenum type , GLvoid *pixels),
(texunit , target , level , format , type , pixels)
)

GLPROC_VOID(glGetMultiTexParameterfvEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLfloat *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexParameterivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexLevelParameterfvEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum pname , GLfloat *params),
(texunit , target , level , pname , params)
)

GLPROC_VOID(glGetMultiTexLevelParameterivEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum pname , GLint *params),
(texunit , target , level , pname , params)
)

GLPROC_VOID(glMultiTexImage3DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , internalformat , width , height , depth , border , format , type , pixels)
)

GLPROC_VOID(glMultiTexSubImage3DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(texunit , target , level , xoffset , yoffset , zoffset , width , height , depth , format , type , pixels)
)

GLPROC_VOID(glCopyMultiTexSubImage3DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(texunit , target , level , xoffset , yoffset , zoffset , x , y , width , height)
)

GLPROC_VOID(glEnableClientStateIndexedEXT,
(GLenum array , GLuint index),
(array , index)
)

GLPROC_VOID(glDisableClientStateIndexedEXT,
(GLenum array , GLuint index),
(array , index)
)

GLPROC_VOID(glGetFloatIndexedvEXT,
(GLenum target ,  GLuint index , GLfloat *data),
(target , index , data)
)

GLPROC_VOID(glGetDoubleIndexedvEXT,
(GLenum target ,  GLuint index , GLdouble *data),
(target , index , data)
)

GLPROC_VOID(glGetPointerIndexedvEXT,
(GLenum target ,  GLuint index , GLvoid **data),
(target , index , data)
)

GLPROC_VOID(glEnableIndexedEXT,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_VOID(glDisableIndexedEXT,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_RETURN1(GLboolean,
glIsEnabledIndexedEXT,
(GLenum target , GLuint index),
(target , index)
)

GLPROC_VOID(glGetIntegerIndexedvEXT,
(GLenum target ,  GLuint index , GLint *data),
(target , index , data)
)

GLPROC_VOID(glGetBooleanIndexedvEXT,
(GLenum target ,  GLuint index , GLboolean *data),
(target , index , data)
)

GLPROC_VOID(glCompressedTextureImage3DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , internalformat , width , height , depth , border , imageSize , bits)
)

GLPROC_VOID(glCompressedTextureImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , internalformat , width , height , border , imageSize , bits)
)

GLPROC_VOID(glCompressedTextureImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , internalformat , width , border , imageSize , bits)
)

GLPROC_VOID(glCompressedTextureSubImage3DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , xoffset , yoffset , zoffset , width , height , depth , format , imageSize , bits)
)

GLPROC_VOID(glCompressedTextureSubImage2DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , xoffset , yoffset , width , height , format , imageSize , bits)
)

GLPROC_VOID(glCompressedTextureSubImage1DEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texture , target , level , xoffset , width , format , imageSize , bits)
)

GLPROC_VOID(glGetCompressedTextureImageEXT,
(GLuint texture ,  GLenum target ,  GLint lod , GLvoid *img),
(texture , target , lod , img)
)

GLPROC_VOID(glCompressedMultiTexImage3DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , internalformat , width , height , depth , border , imageSize , bits)
)

GLPROC_VOID(glCompressedMultiTexImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , internalformat , width , height , border , imageSize , bits)
)

GLPROC_VOID(glCompressedMultiTexImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLint border ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , internalformat , width , border , imageSize , bits)
)

GLPROC_VOID(glCompressedMultiTexSubImage3DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , xoffset , yoffset , zoffset , width , height , depth , format , imageSize , bits)
)

GLPROC_VOID(glCompressedMultiTexSubImage2DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , xoffset , yoffset , width , height , format , imageSize , bits)
)

GLPROC_VOID(glCompressedMultiTexSubImage1DEXT,
(GLenum texunit ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLsizei imageSize , const GLvoid *bits),
(texunit , target , level , xoffset , width , format , imageSize , bits)
)

GLPROC_VOID(glGetCompressedMultiTexImageEXT,
(GLenum texunit ,  GLenum target ,  GLint lod , GLvoid *img),
(texunit , target , lod , img)
)

GLPROC_VOID(glMatrixLoadTransposefEXT,
(GLenum mode , const GLfloat *m),
(mode , m)
)

GLPROC_VOID(glMatrixLoadTransposedEXT,
(GLenum mode , const GLdouble *m),
(mode , m)
)

GLPROC_VOID(glMatrixMultTransposefEXT,
(GLenum mode , const GLfloat *m),
(mode , m)
)

GLPROC_VOID(glMatrixMultTransposedEXT,
(GLenum mode , const GLdouble *m),
(mode , m)
)

GLPROC_VOID(glNamedBufferDataEXT,
(GLuint buffer ,  GLsizeiptr size ,  const GLvoid *data , GLenum usage),
(buffer , size , data , usage)
)

GLPROC_VOID(glNamedBufferSubDataEXT,
(GLuint buffer ,  GLintptr offset ,  GLsizeiptr size , const GLvoid *data),
(buffer , offset , size , data)
)

GLPROC_RETURN1(void *,
glMapNamedBufferEXT,
(GLuint buffer , GLenum access),
(buffer , access)
)

GLPROC_RETURN1(GLboolean,
glUnmapNamedBufferEXT,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glGetNamedBufferParameterivEXT,
(GLuint buffer ,  GLenum pname , GLint *params),
(buffer , pname , params)
)

GLPROC_VOID(glGetNamedBufferPointervEXT,
(GLuint buffer ,  GLenum pname , GLvoid **params),
(buffer , pname , params)
)

GLPROC_VOID(glGetNamedBufferSubDataEXT,
(GLuint buffer ,  GLintptr offset ,  GLsizeiptr size , GLvoid *data),
(buffer , offset , size , data)
)

GLPROC_VOID(glProgramUniform1fEXT,
(GLuint program ,  GLint location , GLfloat v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform2fEXT,
(GLuint program ,  GLint location ,  GLfloat v0 , GLfloat v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform3fEXT,
(GLuint program ,  GLint location ,  GLfloat v0 ,  GLfloat v1 , GLfloat v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform4fEXT,
(GLuint program ,  GLint location ,  GLfloat v0 ,  GLfloat v1 ,  GLfloat v2 , GLfloat v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform1iEXT,
(GLuint program ,  GLint location , GLint v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform2iEXT,
(GLuint program ,  GLint location ,  GLint v0 , GLint v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform3iEXT,
(GLuint program ,  GLint location ,  GLint v0 ,  GLint v1 , GLint v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform4iEXT,
(GLuint program ,  GLint location ,  GLint v0 ,  GLint v1 ,  GLint v2 , GLint v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform1fvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2fvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3fvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4fvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLfloat *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform1ivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2ivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3ivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4ivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniformMatrix2fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x3fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x2fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x4fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x2fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x4fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x3fvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLfloat *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glTextureBufferEXT,
(GLuint texture ,  GLenum target ,  GLenum internalformat , GLuint buffer),
(texture , target , internalformat , buffer)
)

GLPROC_VOID(glMultiTexBufferEXT,
(GLenum texunit ,  GLenum target ,  GLenum internalformat , GLuint buffer),
(texunit , target , internalformat , buffer)
)

GLPROC_VOID(glTextureParameterIivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , const GLint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glTextureParameterIuivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , const GLuint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glGetTextureParameterIivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glGetTextureParameterIuivEXT,
(GLuint texture ,  GLenum target ,  GLenum pname , GLuint *params),
(texture , target , pname , params)
)

GLPROC_VOID(glMultiTexParameterIivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glMultiTexParameterIuivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , const GLuint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexParameterIivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glGetMultiTexParameterIuivEXT,
(GLenum texunit ,  GLenum target ,  GLenum pname , GLuint *params),
(texunit , target , pname , params)
)

GLPROC_VOID(glProgramUniform1uiEXT,
(GLuint program ,  GLint location , GLuint v0),
(program , location , v0)
)

GLPROC_VOID(glProgramUniform2uiEXT,
(GLuint program ,  GLint location ,  GLuint v0 , GLuint v1),
(program , location , v0 , v1)
)

GLPROC_VOID(glProgramUniform3uiEXT,
(GLuint program ,  GLint location ,  GLuint v0 ,  GLuint v1 , GLuint v2),
(program , location , v0 , v1 , v2)
)

GLPROC_VOID(glProgramUniform4uiEXT,
(GLuint program ,  GLint location ,  GLuint v0 ,  GLuint v1 ,  GLuint v2 , GLuint v3),
(program , location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glProgramUniform1uivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2uivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3uivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4uivEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint *value),
(program , location , count , value)
)

GLPROC_VOID(glNamedProgramLocalParameters4fvEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLsizei count , const GLfloat *params),
(program , target , index , count , params)
)

GLPROC_VOID(glNamedProgramLocalParameterI4iEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLint x ,  GLint y ,  GLint z , GLint w),
(program , target , index , x , y , z , w)
)

GLPROC_VOID(glNamedProgramLocalParameterI4ivEXT,
(GLuint program ,  GLenum target ,  GLuint index , const GLint *params),
(program , target , index , params)
)

GLPROC_VOID(glNamedProgramLocalParametersI4ivEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLsizei count , const GLint *params),
(program , target , index , count , params)
)

GLPROC_VOID(glNamedProgramLocalParameterI4uiEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLuint x ,  GLuint y ,  GLuint z , GLuint w),
(program , target , index , x , y , z , w)
)

GLPROC_VOID(glNamedProgramLocalParameterI4uivEXT,
(GLuint program ,  GLenum target ,  GLuint index , const GLuint *params),
(program , target , index , params)
)

GLPROC_VOID(glNamedProgramLocalParametersI4uivEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLsizei count , const GLuint *params),
(program , target , index , count , params)
)

GLPROC_VOID(glGetNamedProgramLocalParameterIivEXT,
(GLuint program ,  GLenum target ,  GLuint index , GLint *params),
(program , target , index , params)
)

GLPROC_VOID(glGetNamedProgramLocalParameterIuivEXT,
(GLuint program ,  GLenum target ,  GLuint index , GLuint *params),
(program , target , index , params)
)

GLPROC_VOID(glEnableClientStateiEXT,
(GLenum array , GLuint index),
(array , index)
)

GLPROC_VOID(glDisableClientStateiEXT,
(GLenum array , GLuint index),
(array , index)
)

GLPROC_VOID(glGetFloati_vEXT,
(GLenum pname ,  GLuint index , GLfloat *params),
(pname , index , params)
)

GLPROC_VOID(glGetDoublei_vEXT,
(GLenum pname ,  GLuint index , GLdouble *params),
(pname , index , params)
)

GLPROC_VOID(glGetPointeri_vEXT,
(GLenum pname ,  GLuint index , GLvoid **params),
(pname , index , params)
)

GLPROC_VOID(glNamedProgramStringEXT,
(GLuint program ,  GLenum target ,  GLenum format ,  GLsizei len , const GLvoid *string),
(program , target , format , len , string)
)

GLPROC_VOID(glNamedProgramLocalParameter4dEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(program , target , index , x , y , z , w)
)

GLPROC_VOID(glNamedProgramLocalParameter4dvEXT,
(GLuint program ,  GLenum target ,  GLuint index , const GLdouble *params),
(program , target , index , params)
)

GLPROC_VOID(glNamedProgramLocalParameter4fEXT,
(GLuint program ,  GLenum target ,  GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(program , target , index , x , y , z , w)
)

GLPROC_VOID(glNamedProgramLocalParameter4fvEXT,
(GLuint program ,  GLenum target ,  GLuint index , const GLfloat *params),
(program , target , index , params)
)

GLPROC_VOID(glGetNamedProgramLocalParameterdvEXT,
(GLuint program ,  GLenum target ,  GLuint index , GLdouble *params),
(program , target , index , params)
)

GLPROC_VOID(glGetNamedProgramLocalParameterfvEXT,
(GLuint program ,  GLenum target ,  GLuint index , GLfloat *params),
(program , target , index , params)
)

GLPROC_VOID(glGetNamedProgramivEXT,
(GLuint program ,  GLenum target ,  GLenum pname , GLint *params),
(program , target , pname , params)
)

GLPROC_VOID(glGetNamedProgramStringEXT,
(GLuint program ,  GLenum target ,  GLenum pname , GLvoid *string),
(program , target , pname , string)
)

GLPROC_VOID(glNamedRenderbufferStorageEXT,
(GLuint renderbuffer ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(renderbuffer , internalformat , width , height)
)

GLPROC_VOID(glGetNamedRenderbufferParameterivEXT,
(GLuint renderbuffer ,  GLenum pname , GLint *params),
(renderbuffer , pname , params)
)

GLPROC_VOID(glNamedRenderbufferStorageMultisampleEXT,
(GLuint renderbuffer ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(renderbuffer , samples , internalformat , width , height)
)

GLPROC_VOID(glNamedRenderbufferStorageMultisampleCoverageEXT,
(GLuint renderbuffer ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(renderbuffer , coverageSamples , colorSamples , internalformat , width , height)
)

GLPROC_RETURN1(GLenum,
glCheckNamedFramebufferStatusEXT,
(GLuint framebuffer , GLenum target),
(framebuffer , target)
)

GLPROC_VOID(glNamedFramebufferTexture1DEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(framebuffer , attachment , textarget , texture , level)
)

GLPROC_VOID(glNamedFramebufferTexture2DEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(framebuffer , attachment , textarget , texture , level)
)

GLPROC_VOID(glNamedFramebufferTexture3DEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLenum textarget ,  GLuint texture ,  GLint level , GLint zoffset),
(framebuffer , attachment , textarget , texture , level , zoffset)
)

GLPROC_VOID(glNamedFramebufferRenderbufferEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLenum renderbuffertarget , GLuint renderbuffer),
(framebuffer , attachment , renderbuffertarget , renderbuffer)
)

GLPROC_VOID(glGetNamedFramebufferAttachmentParameterivEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLenum pname , GLint *params),
(framebuffer , attachment , pname , params)
)

GLPROC_VOID(glGenerateTextureMipmapEXT,
(GLuint texture , GLenum target),
(texture , target)
)

GLPROC_VOID(glGenerateMultiTexMipmapEXT,
(GLenum texunit , GLenum target),
(texunit , target)
)

GLPROC_VOID(glFramebufferDrawBufferEXT,
(GLuint framebuffer , GLenum mode),
(framebuffer , mode)
)

GLPROC_VOID(glFramebufferDrawBuffersEXT,
(GLuint framebuffer ,  GLsizei n , const GLenum *bufs),
(framebuffer , n , bufs)
)

GLPROC_VOID(glFramebufferReadBufferEXT,
(GLuint framebuffer , GLenum mode),
(framebuffer , mode)
)

GLPROC_VOID(glGetFramebufferParameterivEXT,
(GLuint framebuffer ,  GLenum pname , GLint *params),
(framebuffer , pname , params)
)

GLPROC_VOID(glNamedCopyBufferSubDataEXT,
(GLuint readBuffer ,  GLuint writeBuffer ,  GLintptr readOffset ,  GLintptr writeOffset , GLsizeiptr size),
(readBuffer , writeBuffer , readOffset , writeOffset , size)
)

GLPROC_VOID(glNamedFramebufferTextureEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLuint texture , GLint level),
(framebuffer , attachment , texture , level)
)

GLPROC_VOID(glNamedFramebufferTextureLayerEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLuint texture ,  GLint level , GLint layer),
(framebuffer , attachment , texture , level , layer)
)

GLPROC_VOID(glNamedFramebufferTextureFaceEXT,
(GLuint framebuffer ,  GLenum attachment ,  GLuint texture ,  GLint level , GLenum face),
(framebuffer , attachment , texture , level , face)
)

GLPROC_VOID(glTextureRenderbufferEXT,
(GLuint texture ,  GLenum target , GLuint renderbuffer),
(texture , target , renderbuffer)
)

GLPROC_VOID(glMultiTexRenderbufferEXT,
(GLenum texunit ,  GLenum target , GLuint renderbuffer),
(texunit , target , renderbuffer)
)

GLPROC_VOID(glVertexArrayVertexOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , size , type , stride , offset)
)

GLPROC_VOID(glVertexArrayColorOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , size , type , stride , offset)
)

GLPROC_VOID(glVertexArrayEdgeFlagOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , stride , offset)
)

GLPROC_VOID(glVertexArrayIndexOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , type , stride , offset)
)

GLPROC_VOID(glVertexArrayNormalOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , type , stride , offset)
)

GLPROC_VOID(glVertexArrayTexCoordOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , size , type , stride , offset)
)

GLPROC_VOID(glVertexArrayMultiTexCoordOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLenum texunit ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , texunit , size , type , stride , offset)
)

GLPROC_VOID(glVertexArrayFogCoordOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , type , stride , offset)
)

GLPROC_VOID(glVertexArraySecondaryColorOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , size , type , stride , offset)
)

GLPROC_VOID(glVertexArrayVertexAttribOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLuint index ,  GLint size ,  GLenum type ,  GLboolean normalized ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , index , size , type , normalized , stride , offset)
)

GLPROC_VOID(glVertexArrayVertexAttribIOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , index , size , type , stride , offset)
)

GLPROC_VOID(glEnableVertexArrayEXT,
(GLuint vaobj , GLenum array),
(vaobj , array)
)

GLPROC_VOID(glDisableVertexArrayEXT,
(GLuint vaobj , GLenum array),
(vaobj , array)
)

GLPROC_VOID(glEnableVertexArrayAttribEXT,
(GLuint vaobj , GLuint index),
(vaobj , index)
)

GLPROC_VOID(glDisableVertexArrayAttribEXT,
(GLuint vaobj , GLuint index),
(vaobj , index)
)

GLPROC_VOID(glGetVertexArrayIntegervEXT,
(GLuint vaobj ,  GLenum pname , GLint *param),
(vaobj , pname , param)
)

GLPROC_VOID(glGetVertexArrayPointervEXT,
(GLuint vaobj ,  GLenum pname , GLvoid **param),
(vaobj , pname , param)
)

GLPROC_VOID(glGetVertexArrayIntegeri_vEXT,
(GLuint vaobj ,  GLuint index ,  GLenum pname , GLint *param),
(vaobj , index , pname , param)
)

GLPROC_VOID(glGetVertexArrayPointeri_vEXT,
(GLuint vaobj ,  GLuint index ,  GLenum pname , GLvoid **param),
(vaobj , index , pname , param)
)

GLPROC_RETURN1(void *,
glMapNamedBufferRangeEXT,
(GLuint buffer ,  GLintptr offset ,  GLsizeiptr length , GLbitfield access),
(buffer , offset , length , access)
)

GLPROC_VOID(glFlushMappedNamedBufferRangeEXT,
(GLuint buffer ,  GLintptr offset , GLsizeiptr length),
(buffer , offset , length)
)

GLPROC_VOID(glClearNamedBufferDataEXT,
(GLuint buffer ,  GLenum internalformat ,  GLenum format ,  GLenum type , const void *data),
(buffer , internalformat , format , type , data)
)

GLPROC_VOID(glClearNamedBufferSubDataEXT,
(GLuint buffer ,  GLenum internalformat ,  GLenum format ,  GLenum type ,  GLsizeiptr offset ,  GLsizeiptr size , const void *data),
(buffer , internalformat , format , type , offset , size , data)
)

GLPROC_VOID(glNamedFramebufferParameteriEXT,
(GLuint framebuffer ,  GLenum pname , GLint param),
(framebuffer , pname , param)
)

GLPROC_VOID(glGetNamedFramebufferParameterivEXT,
(GLuint framebuffer ,  GLenum pname , GLint *params),
(framebuffer , pname , params)
)

GLPROC_VOID(glProgramUniform1dEXT,
(GLuint program ,  GLint location , GLdouble x),
(program , location , x)
)

GLPROC_VOID(glProgramUniform2dEXT,
(GLuint program ,  GLint location ,  GLdouble x , GLdouble y),
(program , location , x , y)
)

GLPROC_VOID(glProgramUniform3dEXT,
(GLuint program ,  GLint location ,  GLdouble x ,  GLdouble y , GLdouble z),
(program , location , x , y , z)
)

GLPROC_VOID(glProgramUniform4dEXT,
(GLuint program ,  GLint location ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(program , location , x , y , z , w)
)

GLPROC_VOID(glProgramUniform1dvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2dvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3dvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4dvEXT,
(GLuint program ,  GLint location ,  GLsizei count , const GLdouble *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniformMatrix2dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x3dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix2x4dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x2dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix3x4dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x2dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glProgramUniformMatrix4x3dvEXT,
(GLuint program ,  GLint location ,  GLsizei count ,  GLboolean transpose , const GLdouble *value),
(program , location , count , transpose , value)
)

GLPROC_VOID(glTextureBufferRangeEXT,
(GLuint texture ,  GLenum target ,  GLenum internalformat ,  GLuint buffer ,  GLintptr offset , GLsizeiptr size),
(texture , target , internalformat , buffer , offset , size)
)

GLPROC_VOID(glTextureStorage1DEXT,
(GLuint texture ,  GLenum target ,  GLsizei levels ,  GLenum internalformat , GLsizei width),
(texture , target , levels , internalformat , width)
)

GLPROC_VOID(glTextureStorage2DEXT,
(GLuint texture ,  GLenum target ,  GLsizei levels ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(texture , target , levels , internalformat , width , height)
)

GLPROC_VOID(glTextureStorage3DEXT,
(GLuint texture ,  GLenum target ,  GLsizei levels ,  GLenum internalformat ,  GLsizei width ,  GLsizei height , GLsizei depth),
(texture , target , levels , internalformat , width , height , depth)
)

GLPROC_VOID(glTextureStorage2DMultisampleEXT,
(GLuint texture ,  GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width ,  GLsizei height , GLboolean fixedsamplelocations),
(texture , target , samples , internalformat , width , height , fixedsamplelocations)
)

GLPROC_VOID(glTextureStorage3DMultisampleEXT,
(GLuint texture ,  GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedsamplelocations),
(texture , target , samples , internalformat , width , height , depth , fixedsamplelocations)
)

GLPROC_VOID(glVertexArrayBindVertexBufferEXT,
(GLuint vaobj ,  GLuint bindingindex ,  GLuint buffer ,  GLintptr offset , GLsizei stride),
(vaobj , bindingindex , buffer , offset , stride)
)

GLPROC_VOID(glVertexArrayVertexAttribFormatEXT,
(GLuint vaobj ,  GLuint attribindex ,  GLint size ,  GLenum type ,  GLboolean normalized , GLuint relativeoffset),
(vaobj , attribindex , size , type , normalized , relativeoffset)
)

GLPROC_VOID(glVertexArrayVertexAttribIFormatEXT,
(GLuint vaobj ,  GLuint attribindex ,  GLint size ,  GLenum type , GLuint relativeoffset),
(vaobj , attribindex , size , type , relativeoffset)
)

GLPROC_VOID(glVertexArrayVertexAttribLFormatEXT,
(GLuint vaobj ,  GLuint attribindex ,  GLint size ,  GLenum type , GLuint relativeoffset),
(vaobj , attribindex , size , type , relativeoffset)
)

GLPROC_VOID(glVertexArrayVertexAttribBindingEXT,
(GLuint vaobj ,  GLuint attribindex , GLuint bindingindex),
(vaobj , attribindex , bindingindex)
)

GLPROC_VOID(glVertexArrayVertexBindingDivisorEXT,
(GLuint vaobj ,  GLuint bindingindex , GLuint divisor),
(vaobj , bindingindex , divisor)
)

GLPROC_VOID(glVertexArrayVertexAttribLOffsetEXT,
(GLuint vaobj ,  GLuint buffer ,  GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , GLintptr offset),
(vaobj , buffer , index , size , type , stride , offset)
)

GLPROC_VOID(glTexturePageCommitmentEXT,
(GLuint texture ,  GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean resident),
(texture , target , level , xoffset , yoffset , zoffset , width , height , depth , resident)
)





GLPROC_VOID(glColorMaskIndexedEXT,
(GLuint index ,  GLboolean r ,  GLboolean g ,  GLboolean b , GLboolean a),
(index , r , g , b , a)
)





GLPROC_VOID(glDrawArraysInstancedEXT,
(GLenum mode ,  GLint start ,  GLsizei count , GLsizei primcount),
(mode , start , count , primcount)
)

GLPROC_VOID(glDrawElementsInstancedEXT,
(GLenum mode ,  GLsizei count ,  GLenum type ,  const GLvoid *indices , GLsizei primcount),
(mode , count , type , indices , primcount)
)





GLPROC_VOID(glDrawRangeElementsEXT,
(GLenum mode ,  GLuint start ,  GLuint end ,  GLsizei count ,  GLenum type , const GLvoid *indices),
(mode , start , end , count , type , indices)
)





GLPROC_VOID(glFogCoordfEXT,
(GLfloat coord),
(coord)
)

GLPROC_VOID(glFogCoordfvEXT,
(const GLfloat *coord),
(coord)
)

GLPROC_VOID(glFogCoorddEXT,
(GLdouble coord),
(coord)
)

GLPROC_VOID(glFogCoorddvEXT,
(const GLdouble *coord),
(coord)
)

GLPROC_VOID(glFogCoordPointerEXT,
(GLenum type ,  GLsizei stride , const GLvoid *pointer),
(type , stride , pointer)
)





GLPROC_VOID(glBlitFramebufferEXT,
(GLint srcX0 ,  GLint srcY0 ,  GLint srcX1 ,  GLint srcY1 ,  GLint dstX0 ,  GLint dstY0 ,  GLint dstX1 ,  GLint dstY1 ,  GLbitfield mask , GLenum filter),
(srcX0 , srcY0 , srcX1 , srcY1 , dstX0 , dstY0 , dstX1 , dstY1 , mask , filter)
)





GLPROC_VOID(glRenderbufferStorageMultisampleEXT,
(GLenum target ,  GLsizei samples ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , samples , internalformat , width , height)
)





GLPROC_RETURN1(GLboolean,
glIsRenderbufferEXT,
(GLuint renderbuffer),
(renderbuffer)
)

GLPROC_VOID(glBindRenderbufferEXT,
(GLenum target , GLuint renderbuffer),
(target , renderbuffer)
)

GLPROC_VOID(glDeleteRenderbuffersEXT,
(GLsizei n , const GLuint *renderbuffers),
(n , renderbuffers)
)

GLPROC_VOID(glGenRenderbuffersEXT,
(GLsizei n , GLuint *renderbuffers),
(n , renderbuffers)
)

GLPROC_VOID(glRenderbufferStorageEXT,
(GLenum target ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , internalformat , width , height)
)

GLPROC_VOID(glGetRenderbufferParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_RETURN1(GLboolean,
glIsFramebufferEXT,
(GLuint framebuffer),
(framebuffer)
)

GLPROC_VOID(glBindFramebufferEXT,
(GLenum target , GLuint framebuffer),
(target , framebuffer)
)

GLPROC_VOID(glDeleteFramebuffersEXT,
(GLsizei n , const GLuint *framebuffers),
(n , framebuffers)
)

GLPROC_VOID(glGenFramebuffersEXT,
(GLsizei n , GLuint *framebuffers),
(n , framebuffers)
)

GLPROC_RETURN1(GLenum,
glCheckFramebufferStatusEXT,
(GLenum target),
(target)
)

GLPROC_VOID(glFramebufferTexture1DEXT,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(target , attachment , textarget , texture , level)
)

GLPROC_VOID(glFramebufferTexture2DEXT,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture , GLint level),
(target , attachment , textarget , texture , level)
)

GLPROC_VOID(glFramebufferTexture3DEXT,
(GLenum target ,  GLenum attachment ,  GLenum textarget ,  GLuint texture ,  GLint level , GLint zoffset),
(target , attachment , textarget , texture , level , zoffset)
)

GLPROC_VOID(glFramebufferRenderbufferEXT,
(GLenum target ,  GLenum attachment ,  GLenum renderbuffertarget , GLuint renderbuffer),
(target , attachment , renderbuffertarget , renderbuffer)
)

GLPROC_VOID(glGetFramebufferAttachmentParameterivEXT,
(GLenum target ,  GLenum attachment ,  GLenum pname , GLint *params),
(target , attachment , pname , params)
)

GLPROC_VOID(glGenerateMipmapEXT,
(GLenum target),
(target)
)





GLPROC_VOID(glProgramParameteriEXT,
(GLuint program ,  GLenum pname , GLint value),
(program , pname , value)
)





GLPROC_VOID(glProgramEnvParameters4fvEXT,
(GLenum target ,  GLuint index ,  GLsizei count , const GLfloat *params),
(target , index , count , params)
)

GLPROC_VOID(glProgramLocalParameters4fvEXT,
(GLenum target ,  GLuint index ,  GLsizei count , const GLfloat *params),
(target , index , count , params)
)





GLPROC_VOID(glGetUniformuivEXT,
(GLuint program ,  GLint location , GLuint *params),
(program , location , params)
)

GLPROC_VOID(glBindFragDataLocationEXT,
(GLuint program ,  GLuint color , const GLchar *name),
(program , color , name)
)

GLPROC_RETURN1(GLint,
glGetFragDataLocationEXT,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glUniform1uiEXT,
(GLint location , GLuint v0),
(location , v0)
)

GLPROC_VOID(glUniform2uiEXT,
(GLint location ,  GLuint v0 , GLuint v1),
(location , v0 , v1)
)

GLPROC_VOID(glUniform3uiEXT,
(GLint location ,  GLuint v0 ,  GLuint v1 , GLuint v2),
(location , v0 , v1 , v2)
)

GLPROC_VOID(glUniform4uiEXT,
(GLint location ,  GLuint v0 ,  GLuint v1 ,  GLuint v2 , GLuint v3),
(location , v0 , v1 , v2 , v3)
)

GLPROC_VOID(glUniform1uivEXT,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform2uivEXT,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform3uivEXT,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)

GLPROC_VOID(glUniform4uivEXT,
(GLint location ,  GLsizei count , const GLuint *value),
(location , count , value)
)





GLPROC_VOID(glGetHistogramEXT,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type , GLvoid *values),
(target , reset , format , type , values)
)

GLPROC_VOID(glGetHistogramParameterfvEXT,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetHistogramParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetMinmaxEXT,
(GLenum target ,  GLboolean reset ,  GLenum format ,  GLenum type , GLvoid *values),
(target , reset , format , type , values)
)

GLPROC_VOID(glGetMinmaxParameterfvEXT,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetMinmaxParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glHistogramEXT,
(GLenum target ,  GLsizei width ,  GLenum internalformat , GLboolean sink),
(target , width , internalformat , sink)
)

GLPROC_VOID(glMinmaxEXT,
(GLenum target ,  GLenum internalformat , GLboolean sink),
(target , internalformat , sink)
)

GLPROC_VOID(glResetHistogramEXT,
(GLenum target),
(target)
)

GLPROC_VOID(glResetMinmaxEXT,
(GLenum target),
(target)
)





GLPROC_VOID(glIndexFuncEXT,
(GLenum func , GLclampf ref),
(func , ref)
)





GLPROC_VOID(glIndexMaterialEXT,
(GLenum face , GLenum mode),
(face , mode)
)





GLPROC_VOID(glApplyTextureEXT,
(GLenum mode),
(mode)
)

GLPROC_VOID(glTextureLightEXT,
(GLenum pname),
(pname)
)

GLPROC_VOID(glTextureMaterialEXT,
(GLenum face , GLenum mode),
(face , mode)
)





GLPROC_VOID(glMultiDrawArraysEXT,
(GLenum mode ,  const GLint *first ,  const GLsizei *count , GLsizei primcount),
(mode , first , count , primcount)
)

GLPROC_VOID(glMultiDrawElementsEXT,
(GLenum mode ,  const GLsizei *count ,  GLenum type ,  const GLvoid *const*indices , GLsizei primcount),
(mode , count , type , indices , primcount)
)





GLPROC_VOID(glSampleMaskEXT,
(GLclampf value , GLboolean invert),
(value , invert)
)

GLPROC_VOID(glSamplePatternEXT,
(GLenum pattern),
(pattern)
)





GLPROC_VOID(glColorTableEXT,
(GLenum target ,  GLenum internalFormat ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *table),
(target , internalFormat , width , format , type , table)
)

GLPROC_VOID(glGetColorTableEXT,
(GLenum target ,  GLenum format ,  GLenum type , GLvoid *data),
(target , format , type , data)
)

GLPROC_VOID(glGetColorTableParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetColorTableParameterfvEXT,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)





GLPROC_VOID(glPixelTransformParameteriEXT,
(GLenum target ,  GLenum pname , GLint param),
(target , pname , param)
)

GLPROC_VOID(glPixelTransformParameterfEXT,
(GLenum target ,  GLenum pname , GLfloat param),
(target , pname , param)
)

GLPROC_VOID(glPixelTransformParameterivEXT,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glPixelTransformParameterfvEXT,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetPixelTransformParameterivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetPixelTransformParameterfvEXT,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)





GLPROC_VOID(glPointParameterfEXT,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPointParameterfvEXT,
(GLenum pname , const GLfloat *params),
(pname , params)
)





GLPROC_VOID(glPolygonOffsetEXT,
(GLfloat factor , GLfloat bias),
(factor , bias)
)





GLPROC_VOID(glProvokingVertexEXT,
(GLenum mode),
(mode)
)





GLPROC_VOID(glSecondaryColor3bEXT,
(GLbyte red ,  GLbyte green , GLbyte blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3bvEXT,
(const GLbyte *v),
(v)
)

GLPROC_VOID(glSecondaryColor3dEXT,
(GLdouble red ,  GLdouble green , GLdouble blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3dvEXT,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glSecondaryColor3fEXT,
(GLfloat red ,  GLfloat green , GLfloat blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3fvEXT,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glSecondaryColor3iEXT,
(GLint red ,  GLint green , GLint blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3ivEXT,
(const GLint *v),
(v)
)

GLPROC_VOID(glSecondaryColor3sEXT,
(GLshort red ,  GLshort green , GLshort blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3svEXT,
(const GLshort *v),
(v)
)

GLPROC_VOID(glSecondaryColor3ubEXT,
(GLubyte red ,  GLubyte green , GLubyte blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3ubvEXT,
(const GLubyte *v),
(v)
)

GLPROC_VOID(glSecondaryColor3uiEXT,
(GLuint red ,  GLuint green , GLuint blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3uivEXT,
(const GLuint *v),
(v)
)

GLPROC_VOID(glSecondaryColor3usEXT,
(GLushort red ,  GLushort green , GLushort blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3usvEXT,
(const GLushort *v),
(v)
)

GLPROC_VOID(glSecondaryColorPointerEXT,
(GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(size , type , stride , pointer)
)





GLPROC_VOID(glUseShaderProgramEXT,
(GLenum type , GLuint program),
(type , program)
)

GLPROC_VOID(glActiveProgramEXT,
(GLuint program),
(program)
)

GLPROC_RETURN1(GLuint,
glCreateShaderProgramEXT,
(GLenum type , const GLchar *string),
(type , string)
)





GLPROC_VOID(glBindImageTextureEXT,
(GLuint index ,  GLuint texture ,  GLint level ,  GLboolean layered ,  GLint layer ,  GLenum access , GLint format),
(index , texture , level , layered , layer , access , format)
)

GLPROC_VOID(glMemoryBarrierEXT,
(GLbitfield barriers),
(barriers)
)





GLPROC_VOID(glStencilClearTagEXT,
(GLsizei stencilTagBits , GLuint stencilClearTag),
(stencilTagBits , stencilClearTag)
)





GLPROC_VOID(glActiveStencilFaceEXT,
(GLenum face),
(face)
)





GLPROC_VOID(glTexSubImage1DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , width , format , type , pixels)
)

GLPROC_VOID(glTexSubImage2DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , yoffset , width , height , format , type , pixels)
)





GLPROC_VOID(glTexImage3DEXT,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , internalformat , width , height , depth , border , format , type , pixels)
)

GLPROC_VOID(glTexSubImage3DEXT,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , yoffset , zoffset , width , height , depth , format , type , pixels)
)





GLPROC_VOID(glTexBufferEXT,
(GLenum target ,  GLenum internalformat , GLuint buffer),
(target , internalformat , buffer)
)





GLPROC_VOID(glTexParameterIivEXT,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glTexParameterIuivEXT,
(GLenum target ,  GLenum pname , const GLuint *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameterIivEXT,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameterIuivEXT,
(GLenum target ,  GLenum pname , GLuint *params),
(target , pname , params)
)

GLPROC_VOID(glClearColorIiEXT,
(GLint red ,  GLint green ,  GLint blue , GLint alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glClearColorIuiEXT,
(GLuint red ,  GLuint green ,  GLuint blue , GLuint alpha),
(red , green , blue , alpha)
)





GLPROC_RETURN1(GLboolean,
glAreTexturesResidentEXT,
(GLsizei n ,  const GLuint *textures , GLboolean *residences),
(n , textures , residences)
)

GLPROC_VOID(glBindTextureEXT,
(GLenum target , GLuint texture),
(target , texture)
)

GLPROC_VOID(glDeleteTexturesEXT,
(GLsizei n , const GLuint *textures),
(n , textures)
)

GLPROC_VOID(glGenTexturesEXT,
(GLsizei n , GLuint *textures),
(n , textures)
)

GLPROC_RETURN1(GLboolean,
glIsTextureEXT,
(GLuint texture),
(texture)
)

GLPROC_VOID(glPrioritizeTexturesEXT,
(GLsizei n ,  const GLuint *textures , const GLclampf *priorities),
(n , textures , priorities)
)





GLPROC_VOID(glTextureNormalEXT,
(GLenum mode),
(mode)
)





GLPROC_VOID(glGetQueryObjecti64vEXT,
(GLuint id ,  GLenum pname , GLint64 *params),
(id , pname , params)
)

GLPROC_VOID(glGetQueryObjectui64vEXT,
(GLuint id ,  GLenum pname , GLuint64 *params),
(id , pname , params)
)





GLPROC_VOID(glBeginTransformFeedbackEXT,
(GLenum primitiveMode),
(primitiveMode)
)

GLPROC_VOID(glEndTransformFeedbackEXT,
(void),
()
)

GLPROC_VOID(glBindBufferRangeEXT,
(GLenum target ,  GLuint index ,  GLuint buffer ,  GLintptr offset , GLsizeiptr size),
(target , index , buffer , offset , size)
)

GLPROC_VOID(glBindBufferOffsetEXT,
(GLenum target ,  GLuint index ,  GLuint buffer , GLintptr offset),
(target , index , buffer , offset)
)

GLPROC_VOID(glBindBufferBaseEXT,
(GLenum target ,  GLuint index , GLuint buffer),
(target , index , buffer)
)

GLPROC_VOID(glTransformFeedbackVaryingsEXT,
(GLuint program ,  GLsizei count ,  const GLchar *const*varyings , GLenum bufferMode),
(program , count , varyings , bufferMode)
)

GLPROC_VOID(glGetTransformFeedbackVaryingEXT,
(GLuint program ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length ,  GLsizei *size ,  GLenum *type , GLchar *name),
(program , index , bufSize , length , size , type , name)
)





GLPROC_VOID(glArrayElementEXT,
(GLint i),
(i)
)

GLPROC_VOID(glColorPointerEXT,
(GLint size ,  GLenum type ,  GLsizei stride ,  GLsizei count , const GLvoid *pointer),
(size , type , stride , count , pointer)
)

GLPROC_VOID(glDrawArraysEXT,
(GLenum mode ,  GLint first , GLsizei count),
(mode , first , count)
)

GLPROC_VOID(glEdgeFlagPointerEXT,
(GLsizei stride ,  GLsizei count , const GLboolean *pointer),
(stride , count , pointer)
)

GLPROC_VOID(glGetPointervEXT,
(GLenum pname , GLvoid **params),
(pname , params)
)

GLPROC_VOID(glIndexPointerEXT,
(GLenum type ,  GLsizei stride ,  GLsizei count , const GLvoid *pointer),
(type , stride , count , pointer)
)

GLPROC_VOID(glNormalPointerEXT,
(GLenum type ,  GLsizei stride ,  GLsizei count , const GLvoid *pointer),
(type , stride , count , pointer)
)

GLPROC_VOID(glTexCoordPointerEXT,
(GLint size ,  GLenum type ,  GLsizei stride ,  GLsizei count , const GLvoid *pointer),
(size , type , stride , count , pointer)
)

GLPROC_VOID(glVertexPointerEXT,
(GLint size ,  GLenum type ,  GLsizei stride ,  GLsizei count , const GLvoid *pointer),
(size , type , stride , count , pointer)
)





GLPROC_VOID(glVertexAttribL1dEXT,
(GLuint index , GLdouble x),
(index , x)
)

GLPROC_VOID(glVertexAttribL2dEXT,
(GLuint index ,  GLdouble x , GLdouble y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribL3dEXT,
(GLuint index ,  GLdouble x ,  GLdouble y , GLdouble z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribL4dEXT,
(GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribL1dvEXT,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL2dvEXT,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL3dvEXT,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL4dvEXT,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttribLPointerEXT,
(GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , stride , pointer)
)

GLPROC_VOID(glGetVertexAttribLdvEXT,
(GLuint index ,  GLenum pname , GLdouble *params),
(index , pname , params)
)





GLPROC_VOID(glBeginVertexShaderEXT,
(void),
()
)

GLPROC_VOID(glEndVertexShaderEXT,
(void),
()
)

GLPROC_VOID(glBindVertexShaderEXT,
(GLuint id),
(id)
)

GLPROC_RETURN1(GLuint,
glGenVertexShadersEXT,
(GLuint range),
(range)
)

GLPROC_VOID(glDeleteVertexShaderEXT,
(GLuint id),
(id)
)

GLPROC_VOID(glShaderOp1EXT,
(GLenum op ,  GLuint res , GLuint arg1),
(op , res , arg1)
)

GLPROC_VOID(glShaderOp2EXT,
(GLenum op ,  GLuint res ,  GLuint arg1 , GLuint arg2),
(op , res , arg1 , arg2)
)

GLPROC_VOID(glShaderOp3EXT,
(GLenum op ,  GLuint res ,  GLuint arg1 ,  GLuint arg2 , GLuint arg3),
(op , res , arg1 , arg2 , arg3)
)

GLPROC_VOID(glSwizzleEXT,
(GLuint res ,  GLuint in ,  GLenum outX ,  GLenum outY ,  GLenum outZ , GLenum outW),
(res , in , outX , outY , outZ , outW)
)

GLPROC_VOID(glWriteMaskEXT,
(GLuint res ,  GLuint in ,  GLenum outX ,  GLenum outY ,  GLenum outZ , GLenum outW),
(res , in , outX , outY , outZ , outW)
)

GLPROC_VOID(glInsertComponentEXT,
(GLuint res ,  GLuint src , GLuint num),
(res , src , num)
)

GLPROC_VOID(glExtractComponentEXT,
(GLuint res ,  GLuint src , GLuint num),
(res , src , num)
)

GLPROC_RETURN1(GLuint,
glGenSymbolsEXT,
(GLenum datatype ,  GLenum storagetype ,  GLenum range , GLuint components),
(datatype , storagetype , range , components)
)

GLPROC_VOID(glSetInvariantEXT,
(GLuint id ,  GLenum type , const GLvoid *addr),
(id , type , addr)
)

GLPROC_VOID(glSetLocalConstantEXT,
(GLuint id ,  GLenum type , const GLvoid *addr),
(id , type , addr)
)

GLPROC_VOID(glVariantbvEXT,
(GLuint id , const GLbyte *addr),
(id , addr)
)

GLPROC_VOID(glVariantsvEXT,
(GLuint id , const GLshort *addr),
(id , addr)
)

GLPROC_VOID(glVariantivEXT,
(GLuint id , const GLint *addr),
(id , addr)
)

GLPROC_VOID(glVariantfvEXT,
(GLuint id , const GLfloat *addr),
(id , addr)
)

GLPROC_VOID(glVariantdvEXT,
(GLuint id , const GLdouble *addr),
(id , addr)
)

GLPROC_VOID(glVariantubvEXT,
(GLuint id , const GLubyte *addr),
(id , addr)
)

GLPROC_VOID(glVariantusvEXT,
(GLuint id , const GLushort *addr),
(id , addr)
)

GLPROC_VOID(glVariantuivEXT,
(GLuint id , const GLuint *addr),
(id , addr)
)

GLPROC_VOID(glVariantPointerEXT,
(GLuint id ,  GLenum type ,  GLuint stride , const GLvoid *addr),
(id , type , stride , addr)
)

GLPROC_VOID(glEnableVariantClientStateEXT,
(GLuint id),
(id)
)

GLPROC_VOID(glDisableVariantClientStateEXT,
(GLuint id),
(id)
)

GLPROC_RETURN1(GLuint,
glBindLightParameterEXT,
(GLenum light , GLenum value),
(light , value)
)

GLPROC_RETURN1(GLuint,
glBindMaterialParameterEXT,
(GLenum face , GLenum value),
(face , value)
)

GLPROC_RETURN1(GLuint,
glBindTexGenParameterEXT,
(GLenum unit ,  GLenum coord , GLenum value),
(unit , coord , value)
)

GLPROC_RETURN1(GLuint,
glBindTextureUnitParameterEXT,
(GLenum unit , GLenum value),
(unit , value)
)

GLPROC_RETURN1(GLuint,
glBindParameterEXT,
(GLenum value),
(value)
)

GLPROC_RETURN1(GLboolean,
glIsVariantEnabledEXT,
(GLuint id , GLenum cap),
(id , cap)
)

GLPROC_VOID(glGetVariantBooleanvEXT,
(GLuint id ,  GLenum value , GLboolean *data),
(id , value , data)
)

GLPROC_VOID(glGetVariantIntegervEXT,
(GLuint id ,  GLenum value , GLint *data),
(id , value , data)
)

GLPROC_VOID(glGetVariantFloatvEXT,
(GLuint id ,  GLenum value , GLfloat *data),
(id , value , data)
)

GLPROC_VOID(glGetVariantPointervEXT,
(GLuint id ,  GLenum value , GLvoid **data),
(id , value , data)
)

GLPROC_VOID(glGetInvariantBooleanvEXT,
(GLuint id ,  GLenum value , GLboolean *data),
(id , value , data)
)

GLPROC_VOID(glGetInvariantIntegervEXT,
(GLuint id ,  GLenum value , GLint *data),
(id , value , data)
)

GLPROC_VOID(glGetInvariantFloatvEXT,
(GLuint id ,  GLenum value , GLfloat *data),
(id , value , data)
)

GLPROC_VOID(glGetLocalConstantBooleanvEXT,
(GLuint id ,  GLenum value , GLboolean *data),
(id , value , data)
)

GLPROC_VOID(glGetLocalConstantIntegervEXT,
(GLuint id ,  GLenum value , GLint *data),
(id , value , data)
)

GLPROC_VOID(glGetLocalConstantFloatvEXT,
(GLuint id ,  GLenum value , GLfloat *data),
(id , value , data)
)





GLPROC_VOID(glVertexWeightfEXT,
(GLfloat weight),
(weight)
)

GLPROC_VOID(glVertexWeightfvEXT,
(const GLfloat *weight),
(weight)
)

GLPROC_VOID(glVertexWeightPointerEXT,
(GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(size , type , stride , pointer)
)





GLPROC_RETURN1(GLsync,
glImportSyncEXT,
(GLenum external_sync_type ,  GLintptr external_sync , GLbitfield flags),
(external_sync_type , external_sync , flags)
)





GLPROC_VOID(glFrameTerminatorGREMEDY,
(void),
()
)





GLPROC_VOID(glStringMarkerGREMEDY,
(GLsizei len , const GLvoid *string),
(len , string)
)





GLPROC_VOID(glImageTransformParameteriHP,
(GLenum target ,  GLenum pname , GLint param),
(target , pname , param)
)

GLPROC_VOID(glImageTransformParameterfHP,
(GLenum target ,  GLenum pname , GLfloat param),
(target , pname , param)
)

GLPROC_VOID(glImageTransformParameterivHP,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glImageTransformParameterfvHP,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetImageTransformParameterivHP,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetImageTransformParameterfvHP,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)





GLPROC_VOID(glMultiModeDrawArraysIBM,
(const GLenum *mode ,  const GLint *first ,  const GLsizei *count ,  GLsizei primcount , GLint modestride),
(mode , first , count , primcount , modestride)
)

GLPROC_VOID(glMultiModeDrawElementsIBM,
(const GLenum *mode ,  const GLsizei *count ,  GLenum type ,  const GLvoid *const*indices ,  GLsizei primcount , GLint modestride),
(mode , count , type , indices , primcount , modestride)
)





GLPROC_VOID(glFlushStaticDataIBM,
(GLenum target),
(target)
)





GLPROC_VOID(glColorPointerListIBM,
(GLint size ,  GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(size , type , stride , pointer , ptrstride)
)

GLPROC_VOID(glSecondaryColorPointerListIBM,
(GLint size ,  GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(size , type , stride , pointer , ptrstride)
)

GLPROC_VOID(glEdgeFlagPointerListIBM,
(GLint stride ,  const GLboolean **pointer , GLint ptrstride),
(stride , pointer , ptrstride)
)

GLPROC_VOID(glFogCoordPointerListIBM,
(GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(type , stride , pointer , ptrstride)
)

GLPROC_VOID(glIndexPointerListIBM,
(GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(type , stride , pointer , ptrstride)
)

GLPROC_VOID(glNormalPointerListIBM,
(GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(type , stride , pointer , ptrstride)
)

GLPROC_VOID(glTexCoordPointerListIBM,
(GLint size ,  GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(size , type , stride , pointer , ptrstride)
)

GLPROC_VOID(glVertexPointerListIBM,
(GLint size ,  GLenum type ,  GLint stride ,  const GLvoid **pointer , GLint ptrstride),
(size , type , stride , pointer , ptrstride)
)





GLPROC_VOID(glBlendFuncSeparateINGR,
(GLenum sfactorRGB ,  GLenum dfactorRGB ,  GLenum sfactorAlpha , GLenum dfactorAlpha),
(sfactorRGB , dfactorRGB , sfactorAlpha , dfactorAlpha)
)





GLPROC_VOID(glSyncTextureINTEL,
(GLuint texture),
(texture)
)

GLPROC_VOID(glUnmapTexture2DINTEL,
(GLuint texture , GLint level),
(texture , level)
)

GLPROC_RETURN1(void *,
glMapTexture2DINTEL,
(GLuint texture ,  GLint level ,  GLbitfield access ,  const GLint *stride , const GLenum *layout),
(texture , level , access , stride , layout)
)





GLPROC_VOID(glVertexPointervINTEL,
(GLint size ,  GLenum type , const GLvoid **pointer),
(size , type , pointer)
)

GLPROC_VOID(glNormalPointervINTEL,
(GLenum type , const GLvoid **pointer),
(type , pointer)
)

GLPROC_VOID(glColorPointervINTEL,
(GLint size ,  GLenum type , const GLvoid **pointer),
(size , type , pointer)
)

GLPROC_VOID(glTexCoordPointervINTEL,
(GLint size ,  GLenum type , const GLvoid **pointer),
(size , type , pointer)
)





GLPROC_VOID(glResizeBuffersMESA,
(void),
()
)





GLPROC_VOID(glWindowPos2dMESA,
(GLdouble x , GLdouble y),
(x , y)
)

GLPROC_VOID(glWindowPos2dvMESA,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos2fMESA,
(GLfloat x , GLfloat y),
(x , y)
)

GLPROC_VOID(glWindowPos2fvMESA,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos2iMESA,
(GLint x , GLint y),
(x , y)
)

GLPROC_VOID(glWindowPos2ivMESA,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos2sMESA,
(GLshort x , GLshort y),
(x , y)
)

GLPROC_VOID(glWindowPos2svMESA,
(const GLshort *v),
(v)
)

GLPROC_VOID(glWindowPos3dMESA,
(GLdouble x ,  GLdouble y , GLdouble z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3dvMESA,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos3fMESA,
(GLfloat x ,  GLfloat y , GLfloat z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3fvMESA,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos3iMESA,
(GLint x ,  GLint y , GLint z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3ivMESA,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos3sMESA,
(GLshort x ,  GLshort y , GLshort z),
(x , y , z)
)

GLPROC_VOID(glWindowPos3svMESA,
(const GLshort *v),
(v)
)

GLPROC_VOID(glWindowPos4dMESA,
(GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(x , y , z , w)
)

GLPROC_VOID(glWindowPos4dvMESA,
(const GLdouble *v),
(v)
)

GLPROC_VOID(glWindowPos4fMESA,
(GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(x , y , z , w)
)

GLPROC_VOID(glWindowPos4fvMESA,
(const GLfloat *v),
(v)
)

GLPROC_VOID(glWindowPos4iMESA,
(GLint x ,  GLint y ,  GLint z , GLint w),
(x , y , z , w)
)

GLPROC_VOID(glWindowPos4ivMESA,
(const GLint *v),
(v)
)

GLPROC_VOID(glWindowPos4sMESA,
(GLshort x ,  GLshort y ,  GLshort z , GLshort w),
(x , y , z , w)
)

GLPROC_VOID(glWindowPos4svMESA,
(const GLshort *v),
(v)
)





GLPROC_VOID(glBeginConditionalRenderNVX,
(GLuint id),
(id)
)

GLPROC_VOID(glEndConditionalRenderNVX,
(void),
()
)





GLPROC_VOID(glMultiDrawArraysIndirectBindlessNV,
(GLenum mode ,  const GLvoid *indirect ,  GLsizei drawCount ,  GLsizei stride , GLint vertexBufferCount),
(mode , indirect , drawCount , stride , vertexBufferCount)
)

GLPROC_VOID(glMultiDrawElementsIndirectBindlessNV,
(GLenum mode ,  GLenum type ,  const GLvoid *indirect ,  GLsizei drawCount ,  GLsizei stride , GLint vertexBufferCount),
(mode , type , indirect , drawCount , stride , vertexBufferCount)
)





GLPROC_RETURN1(GLuint64,
glGetTextureHandleNV,
(GLuint texture),
(texture)
)

GLPROC_RETURN1(GLuint64,
glGetTextureSamplerHandleNV,
(GLuint texture , GLuint sampler),
(texture , sampler)
)

GLPROC_VOID(glMakeTextureHandleResidentNV,
(GLuint64 handle),
(handle)
)

GLPROC_VOID(glMakeTextureHandleNonResidentNV,
(GLuint64 handle),
(handle)
)

GLPROC_RETURN1(GLuint64,
glGetImageHandleNV,
(GLuint texture ,  GLint level ,  GLboolean layered ,  GLint layer , GLenum format),
(texture , level , layered , layer , format)
)

GLPROC_VOID(glMakeImageHandleResidentNV,
(GLuint64 handle , GLenum access),
(handle , access)
)

GLPROC_VOID(glMakeImageHandleNonResidentNV,
(GLuint64 handle),
(handle)
)

GLPROC_VOID(glUniformHandleui64NV,
(GLint location , GLuint64 value),
(location , value)
)

GLPROC_VOID(glUniformHandleui64vNV,
(GLint location ,  GLsizei count , const GLuint64 *value),
(location , count , value)
)

GLPROC_VOID(glProgramUniformHandleui64NV,
(GLuint program ,  GLint location , GLuint64 value),
(program , location , value)
)

GLPROC_VOID(glProgramUniformHandleui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64 *values),
(program , location , count , values)
)

GLPROC_RETURN1(GLboolean,
glIsTextureHandleResidentNV,
(GLuint64 handle),
(handle)
)

GLPROC_RETURN1(GLboolean,
glIsImageHandleResidentNV,
(GLuint64 handle),
(handle)
)





GLPROC_VOID(glBlendParameteriNV,
(GLenum pname , GLint value),
(pname , value)
)

GLPROC_VOID(glBlendBarrierNV,
(void),
()
)





GLPROC_VOID(glBeginConditionalRenderNV,
(GLuint id , GLenum mode),
(id , mode)
)

GLPROC_VOID(glEndConditionalRenderNV,
(void),
()
)





GLPROC_VOID(glCopyImageSubDataNV,
(GLuint srcName ,  GLenum srcTarget ,  GLint srcLevel ,  GLint srcX ,  GLint srcY ,  GLint srcZ ,  GLuint dstName ,  GLenum dstTarget ,  GLint dstLevel ,  GLint dstX ,  GLint dstY ,  GLint dstZ ,  GLsizei width ,  GLsizei height , GLsizei depth),
(srcName , srcTarget , srcLevel , srcX , srcY , srcZ , dstName , dstTarget , dstLevel , dstX , dstY , dstZ , width , height , depth)
)





GLPROC_VOID(glDepthRangedNV,
(GLdouble zNear , GLdouble zFar),
(zNear , zFar)
)

GLPROC_VOID(glClearDepthdNV,
(GLdouble depth),
(depth)
)

GLPROC_VOID(glDepthBoundsdNV,
(GLdouble zmin , GLdouble zmax),
(zmin , zmax)
)





GLPROC_VOID(glDrawTextureNV,
(GLuint texture ,  GLuint sampler ,  GLfloat x0 ,  GLfloat y0 ,  GLfloat x1 ,  GLfloat y1 ,  GLfloat z ,  GLfloat s0 ,  GLfloat t0 ,  GLfloat s1 , GLfloat t1),
(texture , sampler , x0 , y0 , x1 , y1 , z , s0 , t0 , s1 , t1)
)





GLPROC_VOID(glMapControlPointsNV,
(GLenum target ,  GLuint index ,  GLenum type ,  GLsizei ustride ,  GLsizei vstride ,  GLint uorder ,  GLint vorder ,  GLboolean packed , const GLvoid *points),
(target , index , type , ustride , vstride , uorder , vorder , packed , points)
)

GLPROC_VOID(glMapParameterivNV,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glMapParameterfvNV,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetMapControlPointsNV,
(GLenum target ,  GLuint index ,  GLenum type ,  GLsizei ustride ,  GLsizei vstride ,  GLboolean packed , GLvoid *points),
(target , index , type , ustride , vstride , packed , points)
)

GLPROC_VOID(glGetMapParameterivNV,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetMapParameterfvNV,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetMapAttribParameterivNV,
(GLenum target ,  GLuint index ,  GLenum pname , GLint *params),
(target , index , pname , params)
)

GLPROC_VOID(glGetMapAttribParameterfvNV,
(GLenum target ,  GLuint index ,  GLenum pname , GLfloat *params),
(target , index , pname , params)
)

GLPROC_VOID(glEvalMapsNV,
(GLenum target , GLenum mode),
(target , mode)
)





GLPROC_VOID(glGetMultisamplefvNV,
(GLenum pname ,  GLuint index , GLfloat *val),
(pname , index , val)
)

GLPROC_VOID(glSampleMaskIndexedNV,
(GLuint index , GLbitfield mask),
(index , mask)
)

GLPROC_VOID(glTexRenderbufferNV,
(GLenum target , GLuint renderbuffer),
(target , renderbuffer)
)





GLPROC_VOID(glDeleteFencesNV,
(GLsizei n , const GLuint *fences),
(n , fences)
)

GLPROC_VOID(glGenFencesNV,
(GLsizei n , GLuint *fences),
(n , fences)
)

GLPROC_RETURN1(GLboolean,
glIsFenceNV,
(GLuint fence),
(fence)
)

GLPROC_RETURN1(GLboolean,
glTestFenceNV,
(GLuint fence),
(fence)
)

GLPROC_VOID(glGetFenceivNV,
(GLuint fence ,  GLenum pname , GLint *params),
(fence , pname , params)
)

GLPROC_VOID(glFinishFenceNV,
(GLuint fence),
(fence)
)

GLPROC_VOID(glSetFenceNV,
(GLuint fence , GLenum condition),
(fence , condition)
)





GLPROC_VOID(glProgramNamedParameter4fNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(id , len , name , x , y , z , w)
)

GLPROC_VOID(glProgramNamedParameter4fvNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name , const GLfloat *v),
(id , len , name , v)
)

GLPROC_VOID(glProgramNamedParameter4dNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(id , len , name , x , y , z , w)
)

GLPROC_VOID(glProgramNamedParameter4dvNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name , const GLdouble *v),
(id , len , name , v)
)

GLPROC_VOID(glGetProgramNamedParameterfvNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name , GLfloat *params),
(id , len , name , params)
)

GLPROC_VOID(glGetProgramNamedParameterdvNV,
(GLuint id ,  GLsizei len ,  const GLubyte *name , GLdouble *params),
(id , len , name , params)
)





GLPROC_VOID(glRenderbufferStorageMultisampleCoverageNV,
(GLenum target ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLenum internalformat ,  GLsizei width , GLsizei height),
(target , coverageSamples , colorSamples , internalformat , width , height)
)





GLPROC_VOID(glProgramVertexLimitNV,
(GLenum target , GLint limit),
(target , limit)
)

GLPROC_VOID(glFramebufferTextureEXT,
(GLenum target ,  GLenum attachment ,  GLuint texture , GLint level),
(target , attachment , texture , level)
)

GLPROC_VOID(glFramebufferTextureLayerEXT,
(GLenum target ,  GLenum attachment ,  GLuint texture ,  GLint level , GLint layer),
(target , attachment , texture , level , layer)
)

GLPROC_VOID(glFramebufferTextureFaceEXT,
(GLenum target ,  GLenum attachment ,  GLuint texture ,  GLint level , GLenum face),
(target , attachment , texture , level , face)
)





GLPROC_VOID(glProgramLocalParameterI4iNV,
(GLenum target ,  GLuint index ,  GLint x ,  GLint y ,  GLint z , GLint w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramLocalParameterI4ivNV,
(GLenum target ,  GLuint index , const GLint *params),
(target , index , params)
)

GLPROC_VOID(glProgramLocalParametersI4ivNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLint *params),
(target , index , count , params)
)

GLPROC_VOID(glProgramLocalParameterI4uiNV,
(GLenum target ,  GLuint index ,  GLuint x ,  GLuint y ,  GLuint z , GLuint w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramLocalParameterI4uivNV,
(GLenum target ,  GLuint index , const GLuint *params),
(target , index , params)
)

GLPROC_VOID(glProgramLocalParametersI4uivNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLuint *params),
(target , index , count , params)
)

GLPROC_VOID(glProgramEnvParameterI4iNV,
(GLenum target ,  GLuint index ,  GLint x ,  GLint y ,  GLint z , GLint w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramEnvParameterI4ivNV,
(GLenum target ,  GLuint index , const GLint *params),
(target , index , params)
)

GLPROC_VOID(glProgramEnvParametersI4ivNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLint *params),
(target , index , count , params)
)

GLPROC_VOID(glProgramEnvParameterI4uiNV,
(GLenum target ,  GLuint index ,  GLuint x ,  GLuint y ,  GLuint z , GLuint w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramEnvParameterI4uivNV,
(GLenum target ,  GLuint index , const GLuint *params),
(target , index , params)
)

GLPROC_VOID(glProgramEnvParametersI4uivNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLuint *params),
(target , index , count , params)
)

GLPROC_VOID(glGetProgramLocalParameterIivNV,
(GLenum target ,  GLuint index , GLint *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramLocalParameterIuivNV,
(GLenum target ,  GLuint index , GLuint *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramEnvParameterIivNV,
(GLenum target ,  GLuint index , GLint *params),
(target , index , params)
)

GLPROC_VOID(glGetProgramEnvParameterIuivNV,
(GLenum target ,  GLuint index , GLuint *params),
(target , index , params)
)





GLPROC_VOID(glProgramSubroutineParametersuivNV,
(GLenum target ,  GLsizei count , const GLuint *params),
(target , count , params)
)

GLPROC_VOID(glGetProgramSubroutineParameteruivNV,
(GLenum target ,  GLuint index , GLuint *param),
(target , index , param)
)





GLPROC_VOID(glUniform1i64NV,
(GLint location , GLint64EXT x),
(location , x)
)

GLPROC_VOID(glUniform2i64NV,
(GLint location ,  GLint64EXT x , GLint64EXT y),
(location , x , y)
)

GLPROC_VOID(glUniform3i64NV,
(GLint location ,  GLint64EXT x ,  GLint64EXT y , GLint64EXT z),
(location , x , y , z)
)

GLPROC_VOID(glUniform4i64NV,
(GLint location ,  GLint64EXT x ,  GLint64EXT y ,  GLint64EXT z , GLint64EXT w),
(location , x , y , z , w)
)

GLPROC_VOID(glUniform1i64vNV,
(GLint location ,  GLsizei count , const GLint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform2i64vNV,
(GLint location ,  GLsizei count , const GLint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform3i64vNV,
(GLint location ,  GLsizei count , const GLint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform4i64vNV,
(GLint location ,  GLsizei count , const GLint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform1ui64NV,
(GLint location , GLuint64EXT x),
(location , x)
)

GLPROC_VOID(glUniform2ui64NV,
(GLint location ,  GLuint64EXT x , GLuint64EXT y),
(location , x , y)
)

GLPROC_VOID(glUniform3ui64NV,
(GLint location ,  GLuint64EXT x ,  GLuint64EXT y , GLuint64EXT z),
(location , x , y , z)
)

GLPROC_VOID(glUniform4ui64NV,
(GLint location ,  GLuint64EXT x ,  GLuint64EXT y ,  GLuint64EXT z , GLuint64EXT w),
(location , x , y , z , w)
)

GLPROC_VOID(glUniform1ui64vNV,
(GLint location ,  GLsizei count , const GLuint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform2ui64vNV,
(GLint location ,  GLsizei count , const GLuint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform3ui64vNV,
(GLint location ,  GLsizei count , const GLuint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glUniform4ui64vNV,
(GLint location ,  GLsizei count , const GLuint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glGetUniformi64vNV,
(GLuint program ,  GLint location , GLint64EXT *params),
(program , location , params)
)

GLPROC_VOID(glProgramUniform1i64NV,
(GLuint program ,  GLint location , GLint64EXT x),
(program , location , x)
)

GLPROC_VOID(glProgramUniform2i64NV,
(GLuint program ,  GLint location ,  GLint64EXT x , GLint64EXT y),
(program , location , x , y)
)

GLPROC_VOID(glProgramUniform3i64NV,
(GLuint program ,  GLint location ,  GLint64EXT x ,  GLint64EXT y , GLint64EXT z),
(program , location , x , y , z)
)

GLPROC_VOID(glProgramUniform4i64NV,
(GLuint program ,  GLint location ,  GLint64EXT x ,  GLint64EXT y ,  GLint64EXT z , GLint64EXT w),
(program , location , x , y , z , w)
)

GLPROC_VOID(glProgramUniform1i64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2i64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3i64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4i64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform1ui64NV,
(GLuint program ,  GLint location , GLuint64EXT x),
(program , location , x)
)

GLPROC_VOID(glProgramUniform2ui64NV,
(GLuint program ,  GLint location ,  GLuint64EXT x , GLuint64EXT y),
(program , location , x , y)
)

GLPROC_VOID(glProgramUniform3ui64NV,
(GLuint program ,  GLint location ,  GLuint64EXT x ,  GLuint64EXT y , GLuint64EXT z),
(program , location , x , y , z)
)

GLPROC_VOID(glProgramUniform4ui64NV,
(GLuint program ,  GLint location ,  GLuint64EXT x ,  GLuint64EXT y ,  GLuint64EXT z , GLuint64EXT w),
(program , location , x , y , z , w)
)

GLPROC_VOID(glProgramUniform1ui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform2ui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform3ui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64EXT *value),
(program , location , count , value)
)

GLPROC_VOID(glProgramUniform4ui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64EXT *value),
(program , location , count , value)
)





GLPROC_VOID(glVertex2hNV,
(GLhalfNV x , GLhalfNV y),
(x , y)
)

GLPROC_VOID(glVertex2hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glVertex3hNV,
(GLhalfNV x ,  GLhalfNV y , GLhalfNV z),
(x , y , z)
)

GLPROC_VOID(glVertex3hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glVertex4hNV,
(GLhalfNV x ,  GLhalfNV y ,  GLhalfNV z , GLhalfNV w),
(x , y , z , w)
)

GLPROC_VOID(glVertex4hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glNormal3hNV,
(GLhalfNV nx ,  GLhalfNV ny , GLhalfNV nz),
(nx , ny , nz)
)

GLPROC_VOID(glNormal3hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glColor3hNV,
(GLhalfNV red ,  GLhalfNV green , GLhalfNV blue),
(red , green , blue)
)

GLPROC_VOID(glColor3hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glColor4hNV,
(GLhalfNV red ,  GLhalfNV green ,  GLhalfNV blue , GLhalfNV alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glColor4hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glTexCoord1hNV,
(GLhalfNV s),
(s)
)

GLPROC_VOID(glTexCoord1hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glTexCoord2hNV,
(GLhalfNV s , GLhalfNV t),
(s , t)
)

GLPROC_VOID(glTexCoord2hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glTexCoord3hNV,
(GLhalfNV s ,  GLhalfNV t , GLhalfNV r),
(s , t , r)
)

GLPROC_VOID(glTexCoord3hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glTexCoord4hNV,
(GLhalfNV s ,  GLhalfNV t ,  GLhalfNV r , GLhalfNV q),
(s , t , r , q)
)

GLPROC_VOID(glTexCoord4hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glMultiTexCoord1hNV,
(GLenum target , GLhalfNV s),
(target , s)
)

GLPROC_VOID(glMultiTexCoord1hvNV,
(GLenum target , const GLhalfNV *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord2hNV,
(GLenum target ,  GLhalfNV s , GLhalfNV t),
(target , s , t)
)

GLPROC_VOID(glMultiTexCoord2hvNV,
(GLenum target , const GLhalfNV *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord3hNV,
(GLenum target ,  GLhalfNV s ,  GLhalfNV t , GLhalfNV r),
(target , s , t , r)
)

GLPROC_VOID(glMultiTexCoord3hvNV,
(GLenum target , const GLhalfNV *v),
(target , v)
)

GLPROC_VOID(glMultiTexCoord4hNV,
(GLenum target ,  GLhalfNV s ,  GLhalfNV t ,  GLhalfNV r , GLhalfNV q),
(target , s , t , r , q)
)

GLPROC_VOID(glMultiTexCoord4hvNV,
(GLenum target , const GLhalfNV *v),
(target , v)
)

GLPROC_VOID(glFogCoordhNV,
(GLhalfNV fog),
(fog)
)

GLPROC_VOID(glFogCoordhvNV,
(const GLhalfNV *fog),
(fog)
)

GLPROC_VOID(glSecondaryColor3hNV,
(GLhalfNV red ,  GLhalfNV green , GLhalfNV blue),
(red , green , blue)
)

GLPROC_VOID(glSecondaryColor3hvNV,
(const GLhalfNV *v),
(v)
)

GLPROC_VOID(glVertexWeighthNV,
(GLhalfNV weight),
(weight)
)

GLPROC_VOID(glVertexWeighthvNV,
(const GLhalfNV *weight),
(weight)
)

GLPROC_VOID(glVertexAttrib1hNV,
(GLuint index , GLhalfNV x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1hvNV,
(GLuint index , const GLhalfNV *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2hNV,
(GLuint index ,  GLhalfNV x , GLhalfNV y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2hvNV,
(GLuint index , const GLhalfNV *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3hNV,
(GLuint index ,  GLhalfNV x ,  GLhalfNV y , GLhalfNV z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3hvNV,
(GLuint index , const GLhalfNV *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4hNV,
(GLuint index ,  GLhalfNV x ,  GLhalfNV y ,  GLhalfNV z , GLhalfNV w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4hvNV,
(GLuint index , const GLhalfNV *v),
(index , v)
)

GLPROC_VOID(glVertexAttribs1hvNV,
(GLuint index ,  GLsizei n , const GLhalfNV *v),
(index , n , v)
)

GLPROC_VOID(glVertexAttribs2hvNV,
(GLuint index ,  GLsizei n , const GLhalfNV *v),
(index , n , v)
)

GLPROC_VOID(glVertexAttribs3hvNV,
(GLuint index ,  GLsizei n , const GLhalfNV *v),
(index , n , v)
)

GLPROC_VOID(glVertexAttribs4hvNV,
(GLuint index ,  GLsizei n , const GLhalfNV *v),
(index , n , v)
)





GLPROC_VOID(glGenOcclusionQueriesNV,
(GLsizei n , GLuint *ids),
(n , ids)
)

GLPROC_VOID(glDeleteOcclusionQueriesNV,
(GLsizei n , const GLuint *ids),
(n , ids)
)

GLPROC_RETURN1(GLboolean,
glIsOcclusionQueryNV,
(GLuint id),
(id)
)

GLPROC_VOID(glBeginOcclusionQueryNV,
(GLuint id),
(id)
)

GLPROC_VOID(glEndOcclusionQueryNV,
(void),
()
)

GLPROC_VOID(glGetOcclusionQueryivNV,
(GLuint id ,  GLenum pname , GLint *params),
(id , pname , params)
)

GLPROC_VOID(glGetOcclusionQueryuivNV,
(GLuint id ,  GLenum pname , GLuint *params),
(id , pname , params)
)





GLPROC_VOID(glProgramBufferParametersfvNV,
(GLenum target ,  GLuint bindingIndex ,  GLuint wordIndex ,  GLsizei count , const GLfloat *params),
(target , bindingIndex , wordIndex , count , params)
)

GLPROC_VOID(glProgramBufferParametersIivNV,
(GLenum target ,  GLuint bindingIndex ,  GLuint wordIndex ,  GLsizei count , const GLint *params),
(target , bindingIndex , wordIndex , count , params)
)

GLPROC_VOID(glProgramBufferParametersIuivNV,
(GLenum target ,  GLuint bindingIndex ,  GLuint wordIndex ,  GLsizei count , const GLuint *params),
(target , bindingIndex , wordIndex , count , params)
)





GLPROC_RETURN1(GLuint,
glGenPathsNV,
(GLsizei range),
(range)
)

GLPROC_VOID(glDeletePathsNV,
(GLuint path , GLsizei range),
(path , range)
)

GLPROC_RETURN1(GLboolean,
glIsPathNV,
(GLuint path),
(path)
)

GLPROC_VOID(glPathCommandsNV,
(GLuint path ,  GLsizei numCommands ,  const GLubyte *commands ,  GLsizei numCoords ,  GLenum coordType , const GLvoid *coords),
(path , numCommands , commands , numCoords , coordType , coords)
)

GLPROC_VOID(glPathCoordsNV,
(GLuint path ,  GLsizei numCoords ,  GLenum coordType , const GLvoid *coords),
(path , numCoords , coordType , coords)
)

GLPROC_VOID(glPathSubCommandsNV,
(GLuint path ,  GLsizei commandStart ,  GLsizei commandsToDelete ,  GLsizei numCommands ,  const GLubyte *commands ,  GLsizei numCoords ,  GLenum coordType , const GLvoid *coords),
(path , commandStart , commandsToDelete , numCommands , commands , numCoords , coordType , coords)
)

GLPROC_VOID(glPathSubCoordsNV,
(GLuint path ,  GLsizei coordStart ,  GLsizei numCoords ,  GLenum coordType , const GLvoid *coords),
(path , coordStart , numCoords , coordType , coords)
)

GLPROC_VOID(glPathStringNV,
(GLuint path ,  GLenum format ,  GLsizei length , const GLvoid *pathString),
(path , format , length , pathString)
)

GLPROC_VOID(glPathGlyphsNV,
(GLuint firstPathName ,  GLenum fontTarget ,  const GLvoid *fontName ,  GLbitfield fontStyle ,  GLsizei numGlyphs ,  GLenum type ,  const GLvoid *charcodes ,  GLenum handleMissingGlyphs ,  GLuint pathParameterTemplate , GLfloat emScale),
(firstPathName , fontTarget , fontName , fontStyle , numGlyphs , type , charcodes , handleMissingGlyphs , pathParameterTemplate , emScale)
)

GLPROC_VOID(glPathGlyphRangeNV,
(GLuint firstPathName ,  GLenum fontTarget ,  const GLvoid *fontName ,  GLbitfield fontStyle ,  GLuint firstGlyph ,  GLsizei numGlyphs ,  GLenum handleMissingGlyphs ,  GLuint pathParameterTemplate , GLfloat emScale),
(firstPathName , fontTarget , fontName , fontStyle , firstGlyph , numGlyphs , handleMissingGlyphs , pathParameterTemplate , emScale)
)

GLPROC_VOID(glWeightPathsNV,
(GLuint resultPath ,  GLsizei numPaths ,  const GLuint *paths , const GLfloat *weights),
(resultPath , numPaths , paths , weights)
)

GLPROC_VOID(glCopyPathNV,
(GLuint resultPath , GLuint srcPath),
(resultPath , srcPath)
)

GLPROC_VOID(glInterpolatePathsNV,
(GLuint resultPath ,  GLuint pathA ,  GLuint pathB , GLfloat weight),
(resultPath , pathA , pathB , weight)
)

GLPROC_VOID(glTransformPathNV,
(GLuint resultPath ,  GLuint srcPath ,  GLenum transformType , const GLfloat *transformValues),
(resultPath , srcPath , transformType , transformValues)
)

GLPROC_VOID(glPathParameterivNV,
(GLuint path ,  GLenum pname , const GLint *value),
(path , pname , value)
)

GLPROC_VOID(glPathParameteriNV,
(GLuint path ,  GLenum pname , GLint value),
(path , pname , value)
)

GLPROC_VOID(glPathParameterfvNV,
(GLuint path ,  GLenum pname , const GLfloat *value),
(path , pname , value)
)

GLPROC_VOID(glPathParameterfNV,
(GLuint path ,  GLenum pname , GLfloat value),
(path , pname , value)
)

GLPROC_VOID(glPathDashArrayNV,
(GLuint path ,  GLsizei dashCount , const GLfloat *dashArray),
(path , dashCount , dashArray)
)

GLPROC_VOID(glPathStencilFuncNV,
(GLenum func ,  GLint ref , GLuint mask),
(func , ref , mask)
)

GLPROC_VOID(glPathStencilDepthOffsetNV,
(GLfloat factor , GLfloat units),
(factor , units)
)

GLPROC_VOID(glStencilFillPathNV,
(GLuint path ,  GLenum fillMode , GLuint mask),
(path , fillMode , mask)
)

GLPROC_VOID(glStencilStrokePathNV,
(GLuint path ,  GLint reference , GLuint mask),
(path , reference , mask)
)

GLPROC_VOID(glStencilFillPathInstancedNV,
(GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLenum fillMode ,  GLuint mask ,  GLenum transformType , const GLfloat *transformValues),
(numPaths , pathNameType , paths , pathBase , fillMode , mask , transformType , transformValues)
)

GLPROC_VOID(glStencilStrokePathInstancedNV,
(GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLint reference ,  GLuint mask ,  GLenum transformType , const GLfloat *transformValues),
(numPaths , pathNameType , paths , pathBase , reference , mask , transformType , transformValues)
)

GLPROC_VOID(glPathCoverDepthFuncNV,
(GLenum func),
(func)
)

GLPROC_VOID(glPathColorGenNV,
(GLenum color ,  GLenum genMode ,  GLenum colorFormat , const GLfloat *coeffs),
(color , genMode , colorFormat , coeffs)
)

GLPROC_VOID(glPathTexGenNV,
(GLenum texCoordSet ,  GLenum genMode ,  GLint components , const GLfloat *coeffs),
(texCoordSet , genMode , components , coeffs)
)

GLPROC_VOID(glPathFogGenNV,
(GLenum genMode),
(genMode)
)

GLPROC_VOID(glCoverFillPathNV,
(GLuint path , GLenum coverMode),
(path , coverMode)
)

GLPROC_VOID(glCoverStrokePathNV,
(GLuint path , GLenum coverMode),
(path , coverMode)
)

GLPROC_VOID(glCoverFillPathInstancedNV,
(GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLenum coverMode ,  GLenum transformType , const GLfloat *transformValues),
(numPaths , pathNameType , paths , pathBase , coverMode , transformType , transformValues)
)

GLPROC_VOID(glCoverStrokePathInstancedNV,
(GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLenum coverMode ,  GLenum transformType , const GLfloat *transformValues),
(numPaths , pathNameType , paths , pathBase , coverMode , transformType , transformValues)
)

GLPROC_VOID(glGetPathParameterivNV,
(GLuint path ,  GLenum pname , GLint *value),
(path , pname , value)
)

GLPROC_VOID(glGetPathParameterfvNV,
(GLuint path ,  GLenum pname , GLfloat *value),
(path , pname , value)
)

GLPROC_VOID(glGetPathCommandsNV,
(GLuint path , GLubyte *commands),
(path , commands)
)

GLPROC_VOID(glGetPathCoordsNV,
(GLuint path , GLfloat *coords),
(path , coords)
)

GLPROC_VOID(glGetPathDashArrayNV,
(GLuint path , GLfloat *dashArray),
(path , dashArray)
)

GLPROC_VOID(glGetPathMetricsNV,
(GLbitfield metricQueryMask ,  GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLsizei stride , GLfloat *metrics),
(metricQueryMask , numPaths , pathNameType , paths , pathBase , stride , metrics)
)

GLPROC_VOID(glGetPathMetricRangeNV,
(GLbitfield metricQueryMask ,  GLuint firstPathName ,  GLsizei numPaths ,  GLsizei stride , GLfloat *metrics),
(metricQueryMask , firstPathName , numPaths , stride , metrics)
)

GLPROC_VOID(glGetPathSpacingNV,
(GLenum pathListMode ,  GLsizei numPaths ,  GLenum pathNameType ,  const GLvoid *paths ,  GLuint pathBase ,  GLfloat advanceScale ,  GLfloat kerningScale ,  GLenum transformType , GLfloat *returnedSpacing),
(pathListMode , numPaths , pathNameType , paths , pathBase , advanceScale , kerningScale , transformType , returnedSpacing)
)

GLPROC_VOID(glGetPathColorGenivNV,
(GLenum color ,  GLenum pname , GLint *value),
(color , pname , value)
)

GLPROC_VOID(glGetPathColorGenfvNV,
(GLenum color ,  GLenum pname , GLfloat *value),
(color , pname , value)
)

GLPROC_VOID(glGetPathTexGenivNV,
(GLenum texCoordSet ,  GLenum pname , GLint *value),
(texCoordSet , pname , value)
)

GLPROC_VOID(glGetPathTexGenfvNV,
(GLenum texCoordSet ,  GLenum pname , GLfloat *value),
(texCoordSet , pname , value)
)

GLPROC_RETURN1(GLboolean,
glIsPointInFillPathNV,
(GLuint path ,  GLuint mask ,  GLfloat x , GLfloat y),
(path , mask , x , y)
)

GLPROC_RETURN1(GLboolean,
glIsPointInStrokePathNV,
(GLuint path ,  GLfloat x , GLfloat y),
(path , x , y)
)

GLPROC_RETURN1(GLfloat,
glGetPathLengthNV,
(GLuint path ,  GLsizei startSegment , GLsizei numSegments),
(path , startSegment , numSegments)
)

GLPROC_RETURN1(GLboolean,
glPointAlongPathNV,
(GLuint path ,  GLsizei startSegment ,  GLsizei numSegments ,  GLfloat distance ,  GLfloat *x ,  GLfloat *y ,  GLfloat *tangentX , GLfloat *tangentY),
(path , startSegment , numSegments , distance , x , y , tangentX , tangentY)
)





GLPROC_VOID(glPixelDataRangeNV,
(GLenum target ,  GLsizei length , const GLvoid *pointer),
(target , length , pointer)
)

GLPROC_VOID(glFlushPixelDataRangeNV,
(GLenum target),
(target)
)





GLPROC_VOID(glPointParameteriNV,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glPointParameterivNV,
(GLenum pname , const GLint *params),
(pname , params)
)





GLPROC_VOID(glPresentFrameKeyedNV,
(GLuint video_slot ,  GLuint64EXT minPresentTime ,  GLuint beginPresentTimeId ,  GLuint presentDurationId ,  GLenum type ,  GLenum target0 ,  GLuint fill0 ,  GLuint key0 ,  GLenum target1 ,  GLuint fill1 , GLuint key1),
(video_slot , minPresentTime , beginPresentTimeId , presentDurationId , type , target0 , fill0 , key0 , target1 , fill1 , key1)
)

GLPROC_VOID(glPresentFrameDualFillNV,
(GLuint video_slot ,  GLuint64EXT minPresentTime ,  GLuint beginPresentTimeId ,  GLuint presentDurationId ,  GLenum type ,  GLenum target0 ,  GLuint fill0 ,  GLenum target1 ,  GLuint fill1 ,  GLenum target2 ,  GLuint fill2 ,  GLenum target3 , GLuint fill3),
(video_slot , minPresentTime , beginPresentTimeId , presentDurationId , type , target0 , fill0 , target1 , fill1 , target2 , fill2 , target3 , fill3)
)

GLPROC_VOID(glGetVideoivNV,
(GLuint video_slot ,  GLenum pname , GLint *params),
(video_slot , pname , params)
)

GLPROC_VOID(glGetVideouivNV,
(GLuint video_slot ,  GLenum pname , GLuint *params),
(video_slot , pname , params)
)

GLPROC_VOID(glGetVideoi64vNV,
(GLuint video_slot ,  GLenum pname , GLint64EXT *params),
(video_slot , pname , params)
)

GLPROC_VOID(glGetVideoui64vNV,
(GLuint video_slot ,  GLenum pname , GLuint64EXT *params),
(video_slot , pname , params)
)





GLPROC_VOID(glPrimitiveRestartNV,
(void),
()
)

GLPROC_VOID(glPrimitiveRestartIndexNV,
(GLuint index),
(index)
)





GLPROC_VOID(glCombinerParameterfvNV,
(GLenum pname , const GLfloat *params),
(pname , params)
)

GLPROC_VOID(glCombinerParameterfNV,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glCombinerParameterivNV,
(GLenum pname , const GLint *params),
(pname , params)
)

GLPROC_VOID(glCombinerParameteriNV,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glCombinerInputNV,
(GLenum stage ,  GLenum portion ,  GLenum variable ,  GLenum input ,  GLenum mapping , GLenum componentUsage),
(stage , portion , variable , input , mapping , componentUsage)
)

GLPROC_VOID(glCombinerOutputNV,
(GLenum stage ,  GLenum portion ,  GLenum abOutput ,  GLenum cdOutput ,  GLenum sumOutput ,  GLenum scale ,  GLenum bias ,  GLboolean abDotProduct ,  GLboolean cdDotProduct , GLboolean muxSum),
(stage , portion , abOutput , cdOutput , sumOutput , scale , bias , abDotProduct , cdDotProduct , muxSum)
)

GLPROC_VOID(glFinalCombinerInputNV,
(GLenum variable ,  GLenum input ,  GLenum mapping , GLenum componentUsage),
(variable , input , mapping , componentUsage)
)

GLPROC_VOID(glGetCombinerInputParameterfvNV,
(GLenum stage ,  GLenum portion ,  GLenum variable ,  GLenum pname , GLfloat *params),
(stage , portion , variable , pname , params)
)

GLPROC_VOID(glGetCombinerInputParameterivNV,
(GLenum stage ,  GLenum portion ,  GLenum variable ,  GLenum pname , GLint *params),
(stage , portion , variable , pname , params)
)

GLPROC_VOID(glGetCombinerOutputParameterfvNV,
(GLenum stage ,  GLenum portion ,  GLenum pname , GLfloat *params),
(stage , portion , pname , params)
)

GLPROC_VOID(glGetCombinerOutputParameterivNV,
(GLenum stage ,  GLenum portion ,  GLenum pname , GLint *params),
(stage , portion , pname , params)
)

GLPROC_VOID(glGetFinalCombinerInputParameterfvNV,
(GLenum variable ,  GLenum pname , GLfloat *params),
(variable , pname , params)
)

GLPROC_VOID(glGetFinalCombinerInputParameterivNV,
(GLenum variable ,  GLenum pname , GLint *params),
(variable , pname , params)
)





GLPROC_VOID(glCombinerStageParameterfvNV,
(GLenum stage ,  GLenum pname , const GLfloat *params),
(stage , pname , params)
)

GLPROC_VOID(glGetCombinerStageParameterfvNV,
(GLenum stage ,  GLenum pname , GLfloat *params),
(stage , pname , params)
)





GLPROC_VOID(glMakeBufferResidentNV,
(GLenum target , GLenum access),
(target , access)
)

GLPROC_VOID(glMakeBufferNonResidentNV,
(GLenum target),
(target)
)

GLPROC_RETURN1(GLboolean,
glIsBufferResidentNV,
(GLenum target),
(target)
)

GLPROC_VOID(glMakeNamedBufferResidentNV,
(GLuint buffer , GLenum access),
(buffer , access)
)

GLPROC_VOID(glMakeNamedBufferNonResidentNV,
(GLuint buffer),
(buffer)
)

GLPROC_RETURN1(GLboolean,
glIsNamedBufferResidentNV,
(GLuint buffer),
(buffer)
)

GLPROC_VOID(glGetBufferParameterui64vNV,
(GLenum target ,  GLenum pname , GLuint64EXT *params),
(target , pname , params)
)

GLPROC_VOID(glGetNamedBufferParameterui64vNV,
(GLuint buffer ,  GLenum pname , GLuint64EXT *params),
(buffer , pname , params)
)

GLPROC_VOID(glGetIntegerui64vNV,
(GLenum value , GLuint64EXT *result),
(value , result)
)

GLPROC_VOID(glUniformui64NV,
(GLint location , GLuint64EXT value),
(location , value)
)

GLPROC_VOID(glUniformui64vNV,
(GLint location ,  GLsizei count , const GLuint64EXT *value),
(location , count , value)
)

GLPROC_VOID(glGetUniformui64vNV,
(GLuint program ,  GLint location , GLuint64EXT *params),
(program , location , params)
)

GLPROC_VOID(glProgramUniformui64NV,
(GLuint program ,  GLint location , GLuint64EXT value),
(program , location , value)
)

GLPROC_VOID(glProgramUniformui64vNV,
(GLuint program ,  GLint location ,  GLsizei count , const GLuint64EXT *value),
(program , location , count , value)
)





GLPROC_VOID(glTextureBarrierNV,
(void),
()
)





GLPROC_VOID(glTexImage2DMultisampleCoverageNV,
(GLenum target ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height , GLboolean fixedSampleLocations),
(target , coverageSamples , colorSamples , internalFormat , width , height , fixedSampleLocations)
)

GLPROC_VOID(glTexImage3DMultisampleCoverageNV,
(GLenum target ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedSampleLocations),
(target , coverageSamples , colorSamples , internalFormat , width , height , depth , fixedSampleLocations)
)

GLPROC_VOID(glTextureImage2DMultisampleNV,
(GLuint texture ,  GLenum target ,  GLsizei samples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height , GLboolean fixedSampleLocations),
(texture , target , samples , internalFormat , width , height , fixedSampleLocations)
)

GLPROC_VOID(glTextureImage3DMultisampleNV,
(GLuint texture ,  GLenum target ,  GLsizei samples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedSampleLocations),
(texture , target , samples , internalFormat , width , height , depth , fixedSampleLocations)
)

GLPROC_VOID(glTextureImage2DMultisampleCoverageNV,
(GLuint texture ,  GLenum target ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height , GLboolean fixedSampleLocations),
(texture , target , coverageSamples , colorSamples , internalFormat , width , height , fixedSampleLocations)
)

GLPROC_VOID(glTextureImage3DMultisampleCoverageNV,
(GLuint texture ,  GLenum target ,  GLsizei coverageSamples ,  GLsizei colorSamples ,  GLint internalFormat ,  GLsizei width ,  GLsizei height ,  GLsizei depth , GLboolean fixedSampleLocations),
(texture , target , coverageSamples , colorSamples , internalFormat , width , height , depth , fixedSampleLocations)
)





GLPROC_VOID(glBeginTransformFeedbackNV,
(GLenum primitiveMode),
(primitiveMode)
)

GLPROC_VOID(glEndTransformFeedbackNV,
(void),
()
)

GLPROC_VOID(glTransformFeedbackAttribsNV,
(GLuint count ,  const GLint *attribs , GLenum bufferMode),
(count , attribs , bufferMode)
)

GLPROC_VOID(glBindBufferRangeNV,
(GLenum target ,  GLuint index ,  GLuint buffer ,  GLintptr offset , GLsizeiptr size),
(target , index , buffer , offset , size)
)

GLPROC_VOID(glBindBufferOffsetNV,
(GLenum target ,  GLuint index ,  GLuint buffer , GLintptr offset),
(target , index , buffer , offset)
)

GLPROC_VOID(glBindBufferBaseNV,
(GLenum target ,  GLuint index , GLuint buffer),
(target , index , buffer)
)

GLPROC_VOID(glTransformFeedbackVaryingsNV,
(GLuint program ,  GLsizei count ,  const GLint *locations , GLenum bufferMode),
(program , count , locations , bufferMode)
)

GLPROC_VOID(glActiveVaryingNV,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_RETURN1(GLint,
glGetVaryingLocationNV,
(GLuint program , const GLchar *name),
(program , name)
)

GLPROC_VOID(glGetActiveVaryingNV,
(GLuint program ,  GLuint index ,  GLsizei bufSize ,  GLsizei *length ,  GLsizei *size ,  GLenum *type , GLchar *name),
(program , index , bufSize , length , size , type , name)
)

GLPROC_VOID(glGetTransformFeedbackVaryingNV,
(GLuint program ,  GLuint index , GLint *location),
(program , index , location)
)

GLPROC_VOID(glTransformFeedbackStreamAttribsNV,
(GLsizei count ,  const GLint *attribs ,  GLsizei nbuffers ,  const GLint *bufstreams , GLenum bufferMode),
(count , attribs , nbuffers , bufstreams , bufferMode)
)





GLPROC_VOID(glBindTransformFeedbackNV,
(GLenum target , GLuint id),
(target , id)
)

GLPROC_VOID(glDeleteTransformFeedbacksNV,
(GLsizei n , const GLuint *ids),
(n , ids)
)

GLPROC_VOID(glGenTransformFeedbacksNV,
(GLsizei n , GLuint *ids),
(n , ids)
)

GLPROC_RETURN1(GLboolean,
glIsTransformFeedbackNV,
(GLuint id),
(id)
)

GLPROC_VOID(glPauseTransformFeedbackNV,
(void),
()
)

GLPROC_VOID(glResumeTransformFeedbackNV,
(void),
()
)

GLPROC_VOID(glDrawTransformFeedbackNV,
(GLenum mode , GLuint id),
(mode , id)
)





GLPROC_VOID(glVDPAUInitNV,
(const GLvoid *vdpDevice , const GLvoid *getProcAddress),
(vdpDevice , getProcAddress)
)

GLPROC_VOID(glVDPAUFiniNV,
(void),
()
)

GLPROC_RETURN1(GLvdpauSurfaceNV,
glVDPAURegisterVideoSurfaceNV,
(const GLvoid *vdpSurface ,  GLenum target ,  GLsizei numTextureNames , const GLuint *textureNames),
(vdpSurface , target , numTextureNames , textureNames)
)

GLPROC_RETURN1(GLvdpauSurfaceNV,
glVDPAURegisterOutputSurfaceNV,
(const GLvoid *vdpSurface ,  GLenum target ,  GLsizei numTextureNames , const GLuint *textureNames),
(vdpSurface , target , numTextureNames , textureNames)
)

GLPROC_VOID(glVDPAUIsSurfaceNV,
(GLvdpauSurfaceNV surface),
(surface)
)

GLPROC_VOID(glVDPAUUnregisterSurfaceNV,
(GLvdpauSurfaceNV surface),
(surface)
)

GLPROC_VOID(glVDPAUGetSurfaceivNV,
(GLvdpauSurfaceNV surface ,  GLenum pname ,  GLsizei bufSize ,  GLsizei *length , GLint *values),
(surface , pname , bufSize , length , values)
)

GLPROC_VOID(glVDPAUSurfaceAccessNV,
(GLvdpauSurfaceNV surface , GLenum access),
(surface , access)
)

GLPROC_VOID(glVDPAUMapSurfacesNV,
(GLsizei numSurfaces , const GLvdpauSurfaceNV *surfaces),
(numSurfaces , surfaces)
)

GLPROC_VOID(glVDPAUUnmapSurfacesNV,
(GLsizei numSurface , const GLvdpauSurfaceNV *surfaces),
(numSurface , surfaces)
)





GLPROC_VOID(glFlushVertexArrayRangeNV,
(void),
()
)

GLPROC_VOID(glVertexArrayRangeNV,
(GLsizei length , const GLvoid *pointer),
(length , pointer)
)





GLPROC_VOID(glVertexAttribL1i64NV,
(GLuint index , GLint64EXT x),
(index , x)
)

GLPROC_VOID(glVertexAttribL2i64NV,
(GLuint index ,  GLint64EXT x , GLint64EXT y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribL3i64NV,
(GLuint index ,  GLint64EXT x ,  GLint64EXT y , GLint64EXT z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribL4i64NV,
(GLuint index ,  GLint64EXT x ,  GLint64EXT y ,  GLint64EXT z , GLint64EXT w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribL1i64vNV,
(GLuint index , const GLint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL2i64vNV,
(GLuint index , const GLint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL3i64vNV,
(GLuint index , const GLint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL4i64vNV,
(GLuint index , const GLint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL1ui64NV,
(GLuint index , GLuint64EXT x),
(index , x)
)

GLPROC_VOID(glVertexAttribL2ui64NV,
(GLuint index ,  GLuint64EXT x , GLuint64EXT y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribL3ui64NV,
(GLuint index ,  GLuint64EXT x ,  GLuint64EXT y , GLuint64EXT z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribL4ui64NV,
(GLuint index ,  GLuint64EXT x ,  GLuint64EXT y ,  GLuint64EXT z , GLuint64EXT w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribL1ui64vNV,
(GLuint index , const GLuint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL2ui64vNV,
(GLuint index , const GLuint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL3ui64vNV,
(GLuint index , const GLuint64EXT *v),
(index , v)
)

GLPROC_VOID(glVertexAttribL4ui64vNV,
(GLuint index , const GLuint64EXT *v),
(index , v)
)

GLPROC_VOID(glGetVertexAttribLi64vNV,
(GLuint index ,  GLenum pname , GLint64EXT *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribLui64vNV,
(GLuint index ,  GLenum pname , GLuint64EXT *params),
(index , pname , params)
)

GLPROC_VOID(glVertexAttribLFormatNV,
(GLuint index ,  GLint size ,  GLenum type , GLsizei stride),
(index , size , type , stride)
)





GLPROC_VOID(glBufferAddressRangeNV,
(GLenum pname ,  GLuint index ,  GLuint64EXT address , GLsizeiptr length),
(pname , index , address , length)
)

GLPROC_VOID(glVertexFormatNV,
(GLint size ,  GLenum type , GLsizei stride),
(size , type , stride)
)

GLPROC_VOID(glNormalFormatNV,
(GLenum type , GLsizei stride),
(type , stride)
)

GLPROC_VOID(glColorFormatNV,
(GLint size ,  GLenum type , GLsizei stride),
(size , type , stride)
)

GLPROC_VOID(glIndexFormatNV,
(GLenum type , GLsizei stride),
(type , stride)
)

GLPROC_VOID(glTexCoordFormatNV,
(GLint size ,  GLenum type , GLsizei stride),
(size , type , stride)
)

GLPROC_VOID(glEdgeFlagFormatNV,
(GLsizei stride),
(stride)
)

GLPROC_VOID(glSecondaryColorFormatNV,
(GLint size ,  GLenum type , GLsizei stride),
(size , type , stride)
)

GLPROC_VOID(glFogCoordFormatNV,
(GLenum type , GLsizei stride),
(type , stride)
)

GLPROC_VOID(glVertexAttribFormatNV,
(GLuint index ,  GLint size ,  GLenum type ,  GLboolean normalized , GLsizei stride),
(index , size , type , normalized , stride)
)

GLPROC_VOID(glVertexAttribIFormatNV,
(GLuint index ,  GLint size ,  GLenum type , GLsizei stride),
(index , size , type , stride)
)

GLPROC_VOID(glGetIntegerui64i_vNV,
(GLenum value ,  GLuint index , GLuint64EXT *result),
(value , index , result)
)





GLPROC_RETURN1(GLboolean,
glAreProgramsResidentNV,
(GLsizei n ,  const GLuint *programs , GLboolean *residences),
(n , programs , residences)
)

GLPROC_VOID(glBindProgramNV,
(GLenum target , GLuint id),
(target , id)
)

GLPROC_VOID(glDeleteProgramsNV,
(GLsizei n , const GLuint *programs),
(n , programs)
)

GLPROC_VOID(glExecuteProgramNV,
(GLenum target ,  GLuint id , const GLfloat *params),
(target , id , params)
)

GLPROC_VOID(glGenProgramsNV,
(GLsizei n , GLuint *programs),
(n , programs)
)

GLPROC_VOID(glGetProgramParameterdvNV,
(GLenum target ,  GLuint index ,  GLenum pname , GLdouble *params),
(target , index , pname , params)
)

GLPROC_VOID(glGetProgramParameterfvNV,
(GLenum target ,  GLuint index ,  GLenum pname , GLfloat *params),
(target , index , pname , params)
)

GLPROC_VOID(glGetProgramivNV,
(GLuint id ,  GLenum pname , GLint *params),
(id , pname , params)
)

GLPROC_VOID(glGetProgramStringNV,
(GLuint id ,  GLenum pname , GLubyte *program),
(id , pname , program)
)

GLPROC_VOID(glGetTrackMatrixivNV,
(GLenum target ,  GLuint address ,  GLenum pname , GLint *params),
(target , address , pname , params)
)

GLPROC_VOID(glGetVertexAttribdvNV,
(GLuint index ,  GLenum pname , GLdouble *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribfvNV,
(GLuint index ,  GLenum pname , GLfloat *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribivNV,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribPointervNV,
(GLuint index ,  GLenum pname , GLvoid **pointer),
(index , pname , pointer)
)

GLPROC_RETURN1(GLboolean,
glIsProgramNV,
(GLuint id),
(id)
)

GLPROC_VOID(glLoadProgramNV,
(GLenum target ,  GLuint id ,  GLsizei len , const GLubyte *program),
(target , id , len , program)
)

GLPROC_VOID(glProgramParameter4dNV,
(GLenum target ,  GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramParameter4dvNV,
(GLenum target ,  GLuint index , const GLdouble *v),
(target , index , v)
)

GLPROC_VOID(glProgramParameter4fNV,
(GLenum target ,  GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(target , index , x , y , z , w)
)

GLPROC_VOID(glProgramParameter4fvNV,
(GLenum target ,  GLuint index , const GLfloat *v),
(target , index , v)
)

GLPROC_VOID(glProgramParameters4dvNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLdouble *v),
(target , index , count , v)
)

GLPROC_VOID(glProgramParameters4fvNV,
(GLenum target ,  GLuint index ,  GLsizei count , const GLfloat *v),
(target , index , count , v)
)

GLPROC_VOID(glRequestResidentProgramsNV,
(GLsizei n , const GLuint *programs),
(n , programs)
)

GLPROC_VOID(glTrackMatrixNV,
(GLenum target ,  GLuint address ,  GLenum matrix , GLenum transform),
(target , address , matrix , transform)
)

GLPROC_VOID(glVertexAttribPointerNV,
(GLuint index ,  GLint fsize ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(index , fsize , type , stride , pointer)
)

GLPROC_VOID(glVertexAttrib1dNV,
(GLuint index , GLdouble x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1dvNV,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1fNV,
(GLuint index , GLfloat x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1fvNV,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib1sNV,
(GLuint index , GLshort x),
(index , x)
)

GLPROC_VOID(glVertexAttrib1svNV,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2dNV,
(GLuint index ,  GLdouble x , GLdouble y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2dvNV,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2fNV,
(GLuint index ,  GLfloat x , GLfloat y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2fvNV,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib2sNV,
(GLuint index ,  GLshort x , GLshort y),
(index , x , y)
)

GLPROC_VOID(glVertexAttrib2svNV,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3dNV,
(GLuint index ,  GLdouble x ,  GLdouble y , GLdouble z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3dvNV,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3fNV,
(GLuint index ,  GLfloat x ,  GLfloat y , GLfloat z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3fvNV,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib3sNV,
(GLuint index ,  GLshort x ,  GLshort y , GLshort z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttrib3svNV,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4dNV,
(GLuint index ,  GLdouble x ,  GLdouble y ,  GLdouble z , GLdouble w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4dvNV,
(GLuint index , const GLdouble *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4fNV,
(GLuint index ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4fvNV,
(GLuint index , const GLfloat *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4sNV,
(GLuint index ,  GLshort x ,  GLshort y ,  GLshort z , GLshort w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4svNV,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttrib4ubNV,
(GLuint index ,  GLubyte x ,  GLubyte y ,  GLubyte z , GLubyte w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttrib4ubvNV,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttribs1dvNV,
(GLuint index ,  GLsizei count , const GLdouble *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs1fvNV,
(GLuint index ,  GLsizei count , const GLfloat *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs1svNV,
(GLuint index ,  GLsizei count , const GLshort *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs2dvNV,
(GLuint index ,  GLsizei count , const GLdouble *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs2fvNV,
(GLuint index ,  GLsizei count , const GLfloat *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs2svNV,
(GLuint index ,  GLsizei count , const GLshort *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs3dvNV,
(GLuint index ,  GLsizei count , const GLdouble *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs3fvNV,
(GLuint index ,  GLsizei count , const GLfloat *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs3svNV,
(GLuint index ,  GLsizei count , const GLshort *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs4dvNV,
(GLuint index ,  GLsizei count , const GLdouble *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs4fvNV,
(GLuint index ,  GLsizei count , const GLfloat *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs4svNV,
(GLuint index ,  GLsizei count , const GLshort *v),
(index , count , v)
)

GLPROC_VOID(glVertexAttribs4ubvNV,
(GLuint index ,  GLsizei count , const GLubyte *v),
(index , count , v)
)





GLPROC_VOID(glVertexAttribI1iEXT,
(GLuint index , GLint x),
(index , x)
)

GLPROC_VOID(glVertexAttribI2iEXT,
(GLuint index ,  GLint x , GLint y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribI3iEXT,
(GLuint index ,  GLint x ,  GLint y , GLint z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribI4iEXT,
(GLuint index ,  GLint x ,  GLint y ,  GLint z , GLint w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribI1uiEXT,
(GLuint index , GLuint x),
(index , x)
)

GLPROC_VOID(glVertexAttribI2uiEXT,
(GLuint index ,  GLuint x , GLuint y),
(index , x , y)
)

GLPROC_VOID(glVertexAttribI3uiEXT,
(GLuint index ,  GLuint x ,  GLuint y , GLuint z),
(index , x , y , z)
)

GLPROC_VOID(glVertexAttribI4uiEXT,
(GLuint index ,  GLuint x ,  GLuint y ,  GLuint z , GLuint w),
(index , x , y , z , w)
)

GLPROC_VOID(glVertexAttribI1ivEXT,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI2ivEXT,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI3ivEXT,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4ivEXT,
(GLuint index , const GLint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI1uivEXT,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI2uivEXT,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI3uivEXT,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4uivEXT,
(GLuint index , const GLuint *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4bvEXT,
(GLuint index , const GLbyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4svEXT,
(GLuint index , const GLshort *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4ubvEXT,
(GLuint index , const GLubyte *v),
(index , v)
)

GLPROC_VOID(glVertexAttribI4usvEXT,
(GLuint index , const GLushort *v),
(index , v)
)

GLPROC_VOID(glVertexAttribIPointerEXT,
(GLuint index ,  GLint size ,  GLenum type ,  GLsizei stride , const GLvoid *pointer),
(index , size , type , stride , pointer)
)

GLPROC_VOID(glGetVertexAttribIivEXT,
(GLuint index ,  GLenum pname , GLint *params),
(index , pname , params)
)

GLPROC_VOID(glGetVertexAttribIuivEXT,
(GLuint index ,  GLenum pname , GLuint *params),
(index , pname , params)
)





GLPROC_VOID(glBeginVideoCaptureNV,
(GLuint video_capture_slot),
(video_capture_slot)
)

GLPROC_VOID(glBindVideoCaptureStreamBufferNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum frame_region , GLintptrARB offset),
(video_capture_slot , stream , frame_region , offset)
)

GLPROC_VOID(glBindVideoCaptureStreamTextureNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum frame_region ,  GLenum target , GLuint texture),
(video_capture_slot , stream , frame_region , target , texture)
)

GLPROC_VOID(glEndVideoCaptureNV,
(GLuint video_capture_slot),
(video_capture_slot)
)

GLPROC_VOID(glGetVideoCaptureivNV,
(GLuint video_capture_slot ,  GLenum pname , GLint *params),
(video_capture_slot , pname , params)
)

GLPROC_VOID(glGetVideoCaptureStreamivNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , GLint *params),
(video_capture_slot , stream , pname , params)
)

GLPROC_VOID(glGetVideoCaptureStreamfvNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , GLfloat *params),
(video_capture_slot , stream , pname , params)
)

GLPROC_VOID(glGetVideoCaptureStreamdvNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , GLdouble *params),
(video_capture_slot , stream , pname , params)
)

GLPROC_RETURN1(GLenum,
glVideoCaptureNV,
(GLuint video_capture_slot ,  GLuint *sequence_num , GLuint64EXT *capture_time),
(video_capture_slot , sequence_num , capture_time)
)

GLPROC_VOID(glVideoCaptureStreamParameterivNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , const GLint *params),
(video_capture_slot , stream , pname , params)
)

GLPROC_VOID(glVideoCaptureStreamParameterfvNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , const GLfloat *params),
(video_capture_slot , stream , pname , params)
)

GLPROC_VOID(glVideoCaptureStreamParameterdvNV,
(GLuint video_capture_slot ,  GLuint stream ,  GLenum pname , const GLdouble *params),
(video_capture_slot , stream , pname , params)
)





GLPROC_VOID(glHintPGI,
(GLenum target , GLint mode),
(target , mode)
)





GLPROC_VOID(glDetailTexFuncSGIS,
(GLenum target ,  GLsizei n , const GLfloat *points),
(target , n , points)
)

GLPROC_VOID(glGetDetailTexFuncSGIS,
(GLenum target , GLfloat *points),
(target , points)
)





GLPROC_VOID(glFogFuncSGIS,
(GLsizei n , const GLfloat *points),
(n , points)
)

GLPROC_VOID(glGetFogFuncSGIS,
(GLfloat *points),
(points)
)





GLPROC_VOID(glSampleMaskSGIS,
(GLclampf value , GLboolean invert),
(value , invert)
)

GLPROC_VOID(glSamplePatternSGIS,
(GLenum pattern),
(pattern)
)





GLPROC_VOID(glPixelTexGenParameteriSGIS,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glPixelTexGenParameterivSGIS,
(GLenum pname , const GLint *params),
(pname , params)
)

GLPROC_VOID(glPixelTexGenParameterfSGIS,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPixelTexGenParameterfvSGIS,
(GLenum pname , const GLfloat *params),
(pname , params)
)

GLPROC_VOID(glGetPixelTexGenParameterivSGIS,
(GLenum pname , GLint *params),
(pname , params)
)

GLPROC_VOID(glGetPixelTexGenParameterfvSGIS,
(GLenum pname , GLfloat *params),
(pname , params)
)





GLPROC_VOID(glPointParameterfSGIS,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPointParameterfvSGIS,
(GLenum pname , const GLfloat *params),
(pname , params)
)





GLPROC_VOID(glSharpenTexFuncSGIS,
(GLenum target ,  GLsizei n , const GLfloat *points),
(target , n , points)
)

GLPROC_VOID(glGetSharpenTexFuncSGIS,
(GLenum target , GLfloat *points),
(target , points)
)





GLPROC_VOID(glTexImage4DSGIS,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLsizei size4d ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , internalformat , width , height , depth , size4d , border , format , type , pixels)
)

GLPROC_VOID(glTexSubImage4DSGIS,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint zoffset ,  GLint woffset ,  GLsizei width ,  GLsizei height ,  GLsizei depth ,  GLsizei size4d ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , yoffset , zoffset , woffset , width , height , depth , size4d , format , type , pixels)
)





GLPROC_VOID(glTextureColorMaskSGIS,
(GLboolean red ,  GLboolean green ,  GLboolean blue , GLboolean alpha),
(red , green , blue , alpha)
)





GLPROC_VOID(glGetTexFilterFuncSGIS,
(GLenum target ,  GLenum filter , GLfloat *weights),
(target , filter , weights)
)

GLPROC_VOID(glTexFilterFuncSGIS,
(GLenum target ,  GLenum filter ,  GLsizei n , const GLfloat *weights),
(target , filter , n , weights)
)





GLPROC_VOID(glAsyncMarkerSGIX,
(GLuint marker),
(marker)
)

GLPROC_RETURN1(GLint,
glFinishAsyncSGIX,
(GLuint *markerp),
(markerp)
)

GLPROC_RETURN1(GLint,
glPollAsyncSGIX,
(GLuint *markerp),
(markerp)
)

GLPROC_RETURN1(GLuint,
glGenAsyncMarkersSGIX,
(GLsizei range),
(range)
)

GLPROC_VOID(glDeleteAsyncMarkersSGIX,
(GLuint marker , GLsizei range),
(marker , range)
)

GLPROC_RETURN1(GLboolean,
glIsAsyncMarkerSGIX,
(GLuint marker),
(marker)
)





GLPROC_VOID(glFlushRasterSGIX,
(void),
()
)





GLPROC_VOID(glFragmentColorMaterialSGIX,
(GLenum face , GLenum mode),
(face , mode)
)

GLPROC_VOID(glFragmentLightfSGIX,
(GLenum light ,  GLenum pname , GLfloat param),
(light , pname , param)
)

GLPROC_VOID(glFragmentLightfvSGIX,
(GLenum light ,  GLenum pname , const GLfloat *params),
(light , pname , params)
)

GLPROC_VOID(glFragmentLightiSGIX,
(GLenum light ,  GLenum pname , GLint param),
(light , pname , param)
)

GLPROC_VOID(glFragmentLightivSGIX,
(GLenum light ,  GLenum pname , const GLint *params),
(light , pname , params)
)

GLPROC_VOID(glFragmentLightModelfSGIX,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glFragmentLightModelfvSGIX,
(GLenum pname , const GLfloat *params),
(pname , params)
)

GLPROC_VOID(glFragmentLightModeliSGIX,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glFragmentLightModelivSGIX,
(GLenum pname , const GLint *params),
(pname , params)
)

GLPROC_VOID(glFragmentMaterialfSGIX,
(GLenum face ,  GLenum pname , GLfloat param),
(face , pname , param)
)

GLPROC_VOID(glFragmentMaterialfvSGIX,
(GLenum face ,  GLenum pname , const GLfloat *params),
(face , pname , params)
)

GLPROC_VOID(glFragmentMaterialiSGIX,
(GLenum face ,  GLenum pname , GLint param),
(face , pname , param)
)

GLPROC_VOID(glFragmentMaterialivSGIX,
(GLenum face ,  GLenum pname , const GLint *params),
(face , pname , params)
)

GLPROC_VOID(glGetFragmentLightfvSGIX,
(GLenum light ,  GLenum pname , GLfloat *params),
(light , pname , params)
)

GLPROC_VOID(glGetFragmentLightivSGIX,
(GLenum light ,  GLenum pname , GLint *params),
(light , pname , params)
)

GLPROC_VOID(glGetFragmentMaterialfvSGIX,
(GLenum face ,  GLenum pname , GLfloat *params),
(face , pname , params)
)

GLPROC_VOID(glGetFragmentMaterialivSGIX,
(GLenum face ,  GLenum pname , GLint *params),
(face , pname , params)
)

GLPROC_VOID(glLightEnviSGIX,
(GLenum pname , GLint param),
(pname , param)
)





GLPROC_VOID(glFrameZoomSGIX,
(GLint factor),
(factor)
)





GLPROC_VOID(glIglooInterfaceSGIX,
(GLenum pname , const GLvoid *params),
(pname , params)
)





GLPROC_RETURN1(GLint,
glGetInstrumentsSGIX,
(void),
()
)

GLPROC_VOID(glInstrumentsBufferSGIX,
(GLsizei size , GLint *buffer),
(size , buffer)
)

GLPROC_RETURN1(GLint,
glPollInstrumentsSGIX,
(GLint *marker_p),
(marker_p)
)

GLPROC_VOID(glReadInstrumentsSGIX,
(GLint marker),
(marker)
)

GLPROC_VOID(glStartInstrumentsSGIX,
(void),
()
)

GLPROC_VOID(glStopInstrumentsSGIX,
(GLint marker),
(marker)
)





GLPROC_VOID(glGetListParameterfvSGIX,
(GLuint list ,  GLenum pname , GLfloat *params),
(list , pname , params)
)

GLPROC_VOID(glGetListParameterivSGIX,
(GLuint list ,  GLenum pname , GLint *params),
(list , pname , params)
)

GLPROC_VOID(glListParameterfSGIX,
(GLuint list ,  GLenum pname , GLfloat param),
(list , pname , param)
)

GLPROC_VOID(glListParameterfvSGIX,
(GLuint list ,  GLenum pname , const GLfloat *params),
(list , pname , params)
)

GLPROC_VOID(glListParameteriSGIX,
(GLuint list ,  GLenum pname , GLint param),
(list , pname , param)
)

GLPROC_VOID(glListParameterivSGIX,
(GLuint list ,  GLenum pname , const GLint *params),
(list , pname , params)
)





GLPROC_VOID(glPixelTexGenSGIX,
(GLenum mode),
(mode)
)





GLPROC_VOID(glDeformationMap3dSGIX,
(GLenum target ,  GLdouble u1 ,  GLdouble u2 ,  GLint ustride ,  GLint uorder ,  GLdouble v1 ,  GLdouble v2 ,  GLint vstride ,  GLint vorder ,  GLdouble w1 ,  GLdouble w2 ,  GLint wstride ,  GLint worder , const GLdouble *points),
(target , u1 , u2 , ustride , uorder , v1 , v2 , vstride , vorder , w1 , w2 , wstride , worder , points)
)

GLPROC_VOID(glDeformationMap3fSGIX,
(GLenum target ,  GLfloat u1 ,  GLfloat u2 ,  GLint ustride ,  GLint uorder ,  GLfloat v1 ,  GLfloat v2 ,  GLint vstride ,  GLint vorder ,  GLfloat w1 ,  GLfloat w2 ,  GLint wstride ,  GLint worder , const GLfloat *points),
(target , u1 , u2 , ustride , uorder , v1 , v2 , vstride , vorder , w1 , w2 , wstride , worder , points)
)

GLPROC_VOID(glDeformSGIX,
(GLbitfield mask),
(mask)
)

GLPROC_VOID(glLoadIdentityDeformationMapSGIX,
(GLbitfield mask),
(mask)
)





GLPROC_VOID(glSpriteParameterfSGIX,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glSpriteParameterfvSGIX,
(GLenum pname , const GLfloat *params),
(pname , params)
)

GLPROC_VOID(glSpriteParameteriSGIX,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glSpriteParameterivSGIX,
(GLenum pname , const GLint *params),
(pname , params)
)





GLPROC_VOID(glTagSampleBufferSGIX,
(void),
()
)





GLPROC_VOID(glColorTableSGI,
(GLenum target ,  GLenum internalformat ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *table),
(target , internalformat , width , format , type , table)
)

GLPROC_VOID(glColorTableParameterfvSGI,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glColorTableParameterivSGI,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glCopyColorTableSGI,
(GLenum target ,  GLenum internalformat ,  GLint x ,  GLint y , GLsizei width),
(target , internalformat , x , y , width)
)

GLPROC_VOID(glGetColorTableSGI,
(GLenum target ,  GLenum format ,  GLenum type , GLvoid *table),
(target , format , type , table)
)

GLPROC_VOID(glGetColorTableParameterfvSGI,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetColorTableParameterivSGI,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)





GLPROC_VOID(glFinishTextureSUNX,
(void),
()
)





GLPROC_VOID(glGlobalAlphaFactorbSUN,
(GLbyte factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactorsSUN,
(GLshort factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactoriSUN,
(GLint factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactorfSUN,
(GLfloat factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactordSUN,
(GLdouble factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactorubSUN,
(GLubyte factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactorusSUN,
(GLushort factor),
(factor)
)

GLPROC_VOID(glGlobalAlphaFactoruiSUN,
(GLuint factor),
(factor)
)





GLPROC_VOID(glDrawMeshArraysSUN,
(GLenum mode ,  GLint first ,  GLsizei count , GLsizei width),
(mode , first , count , width)
)





GLPROC_VOID(glReplacementCodeuiSUN,
(GLuint code),
(code)
)

GLPROC_VOID(glReplacementCodeusSUN,
(GLushort code),
(code)
)

GLPROC_VOID(glReplacementCodeubSUN,
(GLubyte code),
(code)
)

GLPROC_VOID(glReplacementCodeuivSUN,
(const GLuint *code),
(code)
)

GLPROC_VOID(glReplacementCodeusvSUN,
(const GLushort *code),
(code)
)

GLPROC_VOID(glReplacementCodeubvSUN,
(const GLubyte *code),
(code)
)

GLPROC_VOID(glReplacementCodePointerSUN,
(GLenum type ,  GLsizei stride , const GLvoid **pointer),
(type , stride , pointer)
)





GLPROC_VOID(glColor4ubVertex2fSUN,
(GLubyte r ,  GLubyte g ,  GLubyte b ,  GLubyte a ,  GLfloat x , GLfloat y),
(r , g , b , a , x , y)
)

GLPROC_VOID(glColor4ubVertex2fvSUN,
(const GLubyte *c , const GLfloat *v),
(c , v)
)

GLPROC_VOID(glColor4ubVertex3fSUN,
(GLubyte r ,  GLubyte g ,  GLubyte b ,  GLubyte a ,  GLfloat x ,  GLfloat y , GLfloat z),
(r , g , b , a , x , y , z)
)

GLPROC_VOID(glColor4ubVertex3fvSUN,
(const GLubyte *c , const GLfloat *v),
(c , v)
)

GLPROC_VOID(glColor3fVertex3fSUN,
(GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat x ,  GLfloat y , GLfloat z),
(r , g , b , x , y , z)
)

GLPROC_VOID(glColor3fVertex3fvSUN,
(const GLfloat *c , const GLfloat *v),
(c , v)
)

GLPROC_VOID(glNormal3fVertex3fSUN,
(GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(nx , ny , nz , x , y , z)
)

GLPROC_VOID(glNormal3fVertex3fvSUN,
(const GLfloat *n , const GLfloat *v),
(n , v)
)

GLPROC_VOID(glColor4fNormal3fVertex3fSUN,
(GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat a ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(r , g , b , a , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glColor4fNormal3fVertex3fvSUN,
(const GLfloat *c ,  const GLfloat *n , const GLfloat *v),
(c , n , v)
)

GLPROC_VOID(glTexCoord2fVertex3fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat x ,  GLfloat y , GLfloat z),
(s , t , x , y , z)
)

GLPROC_VOID(glTexCoord2fVertex3fvSUN,
(const GLfloat *tc , const GLfloat *v),
(tc , v)
)

GLPROC_VOID(glTexCoord4fVertex4fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat p ,  GLfloat q ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(s , t , p , q , x , y , z , w)
)

GLPROC_VOID(glTexCoord4fVertex4fvSUN,
(const GLfloat *tc , const GLfloat *v),
(tc , v)
)

GLPROC_VOID(glTexCoord2fColor4ubVertex3fSUN,
(GLfloat s ,  GLfloat t ,  GLubyte r ,  GLubyte g ,  GLubyte b ,  GLubyte a ,  GLfloat x ,  GLfloat y , GLfloat z),
(s , t , r , g , b , a , x , y , z)
)

GLPROC_VOID(glTexCoord2fColor4ubVertex3fvSUN,
(const GLfloat *tc ,  const GLubyte *c , const GLfloat *v),
(tc , c , v)
)

GLPROC_VOID(glTexCoord2fColor3fVertex3fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat x ,  GLfloat y , GLfloat z),
(s , t , r , g , b , x , y , z)
)

GLPROC_VOID(glTexCoord2fColor3fVertex3fvSUN,
(const GLfloat *tc ,  const GLfloat *c , const GLfloat *v),
(tc , c , v)
)

GLPROC_VOID(glTexCoord2fNormal3fVertex3fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(s , t , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glTexCoord2fNormal3fVertex3fvSUN,
(const GLfloat *tc ,  const GLfloat *n , const GLfloat *v),
(tc , n , v)
)

GLPROC_VOID(glTexCoord2fColor4fNormal3fVertex3fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat a ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(s , t , r , g , b , a , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glTexCoord2fColor4fNormal3fVertex3fvSUN,
(const GLfloat *tc ,  const GLfloat *c ,  const GLfloat *n , const GLfloat *v),
(tc , c , n , v)
)

GLPROC_VOID(glTexCoord4fColor4fNormal3fVertex4fSUN,
(GLfloat s ,  GLfloat t ,  GLfloat p ,  GLfloat q ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat a ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y ,  GLfloat z , GLfloat w),
(s , t , p , q , r , g , b , a , nx , ny , nz , x , y , z , w)
)

GLPROC_VOID(glTexCoord4fColor4fNormal3fVertex4fvSUN,
(const GLfloat *tc ,  const GLfloat *c ,  const GLfloat *n , const GLfloat *v),
(tc , c , n , v)
)

GLPROC_VOID(glReplacementCodeuiVertex3fSUN,
(GLuint rc ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiVertex3fvSUN,
(const GLuint *rc , const GLfloat *v),
(rc , v)
)

GLPROC_VOID(glReplacementCodeuiColor4ubVertex3fSUN,
(GLuint rc ,  GLubyte r ,  GLubyte g ,  GLubyte b ,  GLubyte a ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , r , g , b , a , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiColor4ubVertex3fvSUN,
(const GLuint *rc ,  const GLubyte *c , const GLfloat *v),
(rc , c , v)
)

GLPROC_VOID(glReplacementCodeuiColor3fVertex3fSUN,
(GLuint rc ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , r , g , b , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiColor3fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *c , const GLfloat *v),
(rc , c , v)
)

GLPROC_VOID(glReplacementCodeuiNormal3fVertex3fSUN,
(GLuint rc ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiNormal3fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *n , const GLfloat *v),
(rc , n , v)
)

GLPROC_VOID(glReplacementCodeuiColor4fNormal3fVertex3fSUN,
(GLuint rc ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat a ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , r , g , b , a , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiColor4fNormal3fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *c ,  const GLfloat *n , const GLfloat *v),
(rc , c , n , v)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fVertex3fSUN,
(GLuint rc ,  GLfloat s ,  GLfloat t ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , s , t , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *tc , const GLfloat *v),
(rc , tc , v)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN,
(GLuint rc ,  GLfloat s ,  GLfloat t ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , s , t , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *tc ,  const GLfloat *n , const GLfloat *v),
(rc , tc , n , v)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN,
(GLuint rc ,  GLfloat s ,  GLfloat t ,  GLfloat r ,  GLfloat g ,  GLfloat b ,  GLfloat a ,  GLfloat nx ,  GLfloat ny ,  GLfloat nz ,  GLfloat x ,  GLfloat y , GLfloat z),
(rc , s , t , r , g , b , a , nx , ny , nz , x , y , z)
)

GLPROC_VOID(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN,
(const GLuint *rc ,  const GLfloat *tc ,  const GLfloat *c ,  const GLfloat *n , const GLfloat *v),
(rc , tc , c , n , v)
)



#endif
