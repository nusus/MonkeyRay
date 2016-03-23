#ifndef CMRGL_h__
#define CMRGL_h__
#include <stdint.h>

#define GLUT_APIENTRY_DEFINED
#define WINAPI __stdcall
#define APIENTRY WINAPI
#define CALLBACK __stdcall

#define GLUT_WINGDIAPI_DEFINED
#define DECLSPEC_IMPORT __declspec(dllimport)
#define WINGDIAPI DECLSPEC_IMPORT

#define GL3_PROTOTYPES 1
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>

#define GL_APIENTRY APIENTRY

typedef int64_t GLint64;

typedef uint64_t GLuint64;

inline void glLoadMatrix(const float* mat) { glLoadMatrixf(static_cast<const GLfloat*>(mat)); }
inline void glMultMatrix(const float* mat) { glMultMatrixf(static_cast<const GLfloat*>(mat)); }
inline void glLoadMatrix(const double* mat) { glLoadMatrixd(static_cast<const GLdouble*>(mat)); }
inline void glMultMatrix(const double* mat) { glMultMatrixd(static_cast<const GLdouble*>(mat)); }

#define GL_POLYGON                         0x0009
#define GL_QUADS                           0x0007
#define GL_QUAD_STRIP                      0x0008

#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A
#endif // CMRGL_h__
