#ifndef CMRImage_h__
#define CMRImage_h__

#include "CMRPrerequisites.h"
#include "CMRImageLoader.h"
#include "CMRRef.h"
#include "CMRFile.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRImage : public CMRRef
	{
	public:
		struct ImageEntity : public CMRRef
		{
			GLsizei width;
			GLsizei height;
			GLenum	internal_format;
			GLenum	format;
			GLenum	data_type;
			void*	data;

			~ImageEntity();
		};
	public:
		explicit CMRImage(const string& strName);

		const GLsizei GetWidth();

		const GLsizei GetHeight();

		const void* GetData();

		GLenum GetInternalFormat();

		GLenum GetDataType();

		void LoadImage();

		GLenum GetFormat();

	protected:
		bool m_bLoaded;
		string m_strFullPath;
		SmartPtr<ImageEntity> m_spImageEntity;
	};
}
#endif // CMRImage_h__
