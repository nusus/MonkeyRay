#pragma once
#ifndef Texture_h__
#define Texture_h__
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
namespace LOGL
{
	template<GLenum Wrapping>
	class Texture
	{
	public:
		Texture()
		{
			glTexParameteri()
		}
	protected:
	private:
	};
}
#endif // Texture_h__