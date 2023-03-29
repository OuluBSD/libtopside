#if defined flagWIN32 && !defined flagMSC

#include "maindef.h"
#include "glcorearb.h"


GLPROC_VOID(glCullFace,
(GLenum mode),
(mode)
)

GLPROC_VOID(glFrontFace,
(GLenum mode),
(mode)
)

GLPROC_VOID(glHint,
(GLenum target , GLenum mode),
(target , mode)
)

GLPROC_VOID(glLineWidth,
(GLfloat width),
(width)
)

GLPROC_VOID(glPointSize,
(GLfloat size),
(size)
)

GLPROC_VOID(glPolygonMode,
(GLenum face , GLenum mode),
(face , mode)
)

GLPROC_VOID(glScissor,
(GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(x , y , width , height)
)

GLPROC_VOID(glTexParameterf,
(GLenum target ,  GLenum pname , GLfloat param),
(target , pname , param)
)

GLPROC_VOID(glTexParameterfv,
(GLenum target ,  GLenum pname , const GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glTexParameteri,
(GLenum target ,  GLenum pname , GLint param),
(target , pname , param)
)

GLPROC_VOID(glTexParameteriv,
(GLenum target ,  GLenum pname , const GLint *params),
(target , pname , params)
)

GLPROC_VOID(glTexImage1D,
(GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , internalformat , width , border , format , type , pixels)
)

GLPROC_VOID(glTexImage2D,
(GLenum target ,  GLint level ,  GLint internalformat ,  GLsizei width ,  GLsizei height ,  GLint border ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , internalformat , width , height , border , format , type , pixels)
)

GLPROC_VOID(glDrawBuffer,
(GLenum mode),
(mode)
)

GLPROC_VOID(glClear,
(GLbitfield mask),
(mask)
)

GLPROC_VOID(glClearColor,
(GLfloat red ,  GLfloat green ,  GLfloat blue , GLfloat alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glClearStencil,
(GLint s),
(s)
)

GLPROC_VOID(glClearDepth,
(GLdouble depth),
(depth)
)

GLPROC_VOID(glStencilMask,
(GLuint mask),
(mask)
)

GLPROC_VOID(glColorMask,
(GLboolean red ,  GLboolean green ,  GLboolean blue , GLboolean alpha),
(red , green , blue , alpha)
)

GLPROC_VOID(glDepthMask,
(GLboolean flag),
(flag)
)

GLPROC_VOID(glDisable,
(GLenum cap),
(cap)
)

GLPROC_VOID(glEnable,
(GLenum cap),
(cap)
)

GLPROC_VOID(glFinish,
(void),
()
)

GLPROC_VOID(glFlush,
(void),
()
)

GLPROC_VOID(glBlendFunc,
(GLenum sfactor , GLenum dfactor),
(sfactor , dfactor)
)

GLPROC_VOID(glLogicOp,
(GLenum opcode),
(opcode)
)

GLPROC_VOID(glStencilFunc,
(GLenum func ,  GLint ref , GLuint mask),
(func , ref , mask)
)

GLPROC_VOID(glStencilOp,
(GLenum fail ,  GLenum zfail , GLenum zpass),
(fail , zfail , zpass)
)

GLPROC_VOID(glDepthFunc,
(GLenum func),
(func)
)

GLPROC_VOID(glPixelStoref,
(GLenum pname , GLfloat param),
(pname , param)
)

GLPROC_VOID(glPixelStorei,
(GLenum pname , GLint param),
(pname , param)
)

GLPROC_VOID(glReadBuffer,
(GLenum mode),
(mode)
)

GLPROC_VOID(glReadPixels,
(GLint x ,  GLint y ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , GLvoid *pixels),
(x , y , width , height , format , type , pixels)
)

GLPROC_VOID(glGetBooleanv,
(GLenum pname , GLboolean *params),
(pname , params)
)

GLPROC_VOID(glGetDoublev,
(GLenum pname , GLdouble *params),
(pname , params)
)

GLPROC_RETURN1(GLenum,
glGetError,
(void),
()
)

GLPROC_VOID(glGetFloatv,
(GLenum pname , GLfloat *params),
(pname , params)
)

GLPROC_VOID(glGetIntegerv,
(GLenum pname , GLint *params),
(pname , params)
)

GLPROC_RETURN1(const GLubyte *,
glGetString,
(GLenum name),
(name)
)

GLPROC_VOID(glGetTexImage,
(GLenum target ,  GLint level ,  GLenum format ,  GLenum type , GLvoid *pixels),
(target , level , format , type , pixels)
)

GLPROC_VOID(glGetTexParameterfv,
(GLenum target ,  GLenum pname , GLfloat *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexParameteriv,
(GLenum target ,  GLenum pname , GLint *params),
(target , pname , params)
)

GLPROC_VOID(glGetTexLevelParameterfv,
(GLenum target ,  GLint level ,  GLenum pname , GLfloat *params),
(target , level , pname , params)
)

GLPROC_VOID(glGetTexLevelParameteriv,
(GLenum target ,  GLint level ,  GLenum pname , GLint *params),
(target , level , pname , params)
)

GLPROC_RETURN1(GLboolean,
glIsEnabled,
(GLenum cap),
(cap)
)

GLPROC_VOID(glDepthRange,
(GLdouble pnear , GLdouble pfar),
(pnear , pfar)
)

GLPROC_VOID(glViewport,
(GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(x , y , width , height)
)

GLPROC_VOID(glDrawArrays,
(GLenum mode ,  GLint first , GLsizei count),
(mode , first , count)
)

GLPROC_VOID(glDrawElements,
(GLenum mode ,  GLsizei count ,  GLenum type , const GLvoid *indices),
(mode , count , type , indices)
)

GLPROC_VOID(glGetPointerv,
(GLenum pname , GLvoid **params),
(pname , params)
)

GLPROC_VOID(glPolygonOffset,
(GLfloat factor , GLfloat units),
(factor , units)
)

GLPROC_VOID(glCopyTexImage1D,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width , GLint border),
(target , level , internalformat , x , y , width , border)
)

GLPROC_VOID(glCopyTexImage2D,
(GLenum target ,  GLint level ,  GLenum internalformat ,  GLint x ,  GLint y ,  GLsizei width ,  GLsizei height , GLint border),
(target , level , internalformat , x , y , width , height , border)
)

GLPROC_VOID(glCopyTexSubImage1D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint x ,  GLint y , GLsizei width),
(target , level , xoffset , x , y , width)
)

GLPROC_VOID(glCopyTexSubImage2D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLint x ,  GLint y ,  GLsizei width , GLsizei height),
(target , level , xoffset , yoffset , x , y , width , height)
)

GLPROC_VOID(glTexSubImage1D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLsizei width ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , width , format , type , pixels)
)

GLPROC_VOID(glTexSubImage2D,
(GLenum target ,  GLint level ,  GLint xoffset ,  GLint yoffset ,  GLsizei width ,  GLsizei height ,  GLenum format ,  GLenum type , const GLvoid *pixels),
(target , level , xoffset , yoffset , width , height , format , type , pixels)
)

GLPROC_VOID(glBindTexture,
(GLenum target , GLuint texture),
(target , texture)
)

GLPROC_VOID(glDeleteTextures,
(GLsizei n , const GLuint *textures),
(n , textures)
)

GLPROC_VOID(glGenTextures,
(GLsizei n , GLuint *textures),
(n , textures)
)

GLPROC_RETURN1(GLboolean,
glIsTexture,
(GLuint texture),
(texture)
)


#endif
