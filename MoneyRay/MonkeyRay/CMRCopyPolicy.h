#ifndef CMRCopyPolicy_h__
#define CMRCopyPolicy_h__
#include "CMRObject.h"
namespace MR
{

	class CMRRef;
	class CMRObject;
	class CMRImage;
	class CMRTexture;
	class CMRStateSet;
	class CMRStateAttribute;
	class CMRStateAttributeCallback;
	class CMRUniform;
	class CMRUniformCallback;
	class CMRNode;
	class CMRDrawable;
	class CMRArray;
	class CMRPrimitiveSet;
	class CMRShape;
	class CMRCallback;

	class CMRCopyPolicy
	{

	public:

		enum Options
		{
			SHALLOW_COPY = 0,
			DEEP_COPY_OBJECTS = 1 << 0,
			DEEP_COPY_NODES = 1 << 1,
			DEEP_COPY_DRAWABLES = 1 << 2,
			DEEP_COPY_STATESETS = 1 << 3,
			DEEP_COPY_STATEATTRIBUTES = 1 << 4,
			DEEP_COPY_TEXTURES = 1 << 5,
			DEEP_COPY_IMAGES = 1 << 6,
			DEEP_COPY_ARRAYS = 1 << 7,
			DEEP_COPY_PRIMITIVES = 1 << 8,
			DEEP_COPY_SHAPES = 1 << 9,
			DEEP_COPY_UNIFORMS = 1 << 10,
			DEEP_COPY_CALLBACKS = 1 << 11,
			DEEP_COPY_USERDATA = 1 << 12,
			DEEP_COPY_ALL = 0x7FFFFFFF
		};

		typedef unsigned int CopyFlags;

		inline CMRCopyPolicy(CopyFlags flags = SHALLOW_COPY) :m_flags(flags) {}
		virtual ~CMRCopyPolicy() {}

		void SetCopyFlags(CopyFlags flags) { m_flags = flags; }
		CopyFlags GetCopyFlags() const { return m_flags; }

		virtual CMRRef*     Copy (const CMRRef* ref) const;
		virtual CMRObject*         Copy (const CMRObject* obj) const;
		virtual CMRNode*           Copy (const CMRNode* node) const;
		virtual CMRDrawable*       Copy (const CMRDrawable* drawable) const;
		virtual CMRStateSet*       Copy (const CMRStateSet* stateset) const;
		virtual CMRStateAttribute* Copy (const CMRStateAttribute* attr) const;
		virtual CMRTexture*        Copy (const CMRTexture* text) const;
		virtual CMRImage*          Copy (const CMRImage* image) const;
		virtual CMRArray*          Copy (const CMRArray* array) const;
		virtual CMRPrimitiveSet*   Copy (const CMRPrimitiveSet* primitives) const;
		virtual CMRShape*          Copy (const CMRShape* shape) const;
		virtual CMRUniform*        Copy (const CMRUniform* shape) const;
		virtual CMRCallback*       Copy (const CMRCallback* nodecallback) const;
		virtual CMRStateAttributeCallback* Copy (const CMRStateAttributeCallback* stateattributecallback) const;
		virtual CMRUniformCallback*        Copy (const CMRUniformCallback* uniformcallback) const;

	protected:

		CopyFlags m_flags;
	};
}
#endif // CMRCopyPolicy_h__
