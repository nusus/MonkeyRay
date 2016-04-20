#ifndef CMRViewport_h__
#define CMRViewport_h__
#include "CMRRef.h"
#include "vmath.h"
#include "CMRObject.h"
namespace MR
{
	class CMRViewport : public CMRRef
	{
	public:
		typedef double value_type;

		CMRViewport();

		CMRViewport(value_type x, value_type y, value_type width, value_type height);

		CMRViewport(const CMRViewport& vp);

		CMRViewport& operator=(const CMRViewport& vp);

		void SetViewport(value_type x, value_type y, value_type width, value_type height);

		void SetX(value_type x);
		value_type GetX() const;

		void SetY(value_type y);
		value_type GetY() const;

		void SetWidth(value_type width);
		value_type GetWidth() const;

		void SetHeight(value_type height);
		value_type GetHeight() const;

		bool IsValid() const;

		double AspectRatio() const;

		const vmath::mat4 ComputeWindowMatrix() const;

		virtual void Apply(CMRObject& state) const;

	protected:

		virtual ~CMRViewport();

		value_type m_x;
		value_type m_y;
		value_type m_width;
		value_type m_height;		
	};
}

#endif // CMRViewport_h__
