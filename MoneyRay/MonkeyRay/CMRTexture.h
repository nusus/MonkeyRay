#ifndef CMRTexture_h__
#define CMRTexture_h__

#include "CMRRef.h"
#include "CMRImage.h"
namespace MR
{
	class CMRTexture : public CMRRef
	{
	public:
		explicit CMRTexture(const std::string& name);

		~CMRTexture();

		bool LoadTexture();

		void Bind(GLenum eTextureUnit);

		const GLuint GetTextureObject() const;

		void SetTarget(GLenum target);
		const GLenum GetTarget() const;

		void SetLevel(GLint level);
		const GLint GetLevel() const;
		
		void SetBorder(GLint border);
		const GLint GetBorder() const;
		const GLsizei GetWidth() const;
		const GLsizei GetHeight() const;
		const GLint GetInternalFormat() const;
		const GLenum GetFormat() const;
		const GLenum GetType() const;
		const void* GetData() const;

		void SetMagFilter(GLint magFilter);
		const GLint GetMagFilter() const;

		void SetMinFilter(GLint minFilter);
		const GLint GetMinFilter() const;

		void SetWrapS(GLint wrap_s);
		void SetWrapT(GLint wrap_t);

		const GLint GetWrapS() const;
		const GLint GetWrapT() const;
	protected:
		std::string m_strFullPath;
		SmartPtr<CMRImage> m_spImage;
		GLenum m_target;
		GLint m_level;
		GLint m_border;
		GLint m_magFilter;
		GLint m_minFilter;
		GLint m_wrapS;
		GLint m_wrapT;
		GLuint m_textureObject;
	};
}
#endif // CMRTexture_h__
