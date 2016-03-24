#ifndef CMRDisplaySettings_h__
#define CMRDisplaySettings_h__

#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRPrerequisites.h"

namespace MR
{
	class CMRDisplaySettings : public CMRRef
	{
	public:
		static SmartPtr<CMRDisplaySettings>& Instance();

		CMRDisplaySettings()
		{
			SetDeFaults();
		}

		CMRDisplaySettings(const CMRDisplaySettings& ds);

		CMRDisplaySettings& operator = (const CMRDisplaySettings& ds);
	protected:
		virtual ~CMRDisplaySettings();
	public:	

		void SetDisplaySettings(const CMRDisplaySettings& ds);

		void Merge(const CMRDisplaySettings& ds);

		void SetScreenWidth(float fWidth) { m_fScreenWidth = fWidth; }
		float GetScreenWidth() const { return m_fScreenWidth; }

		void SetScreenHeight(float fHeight) { m_fScreenHeight = fHeight; }
		float GetScreenHeight() const { return m_fScreenHeight; }

		void SetDoubleBuffer(bool bDoubleBuffer) { m_bDoubleBuffer = bDoubleBuffer; }
		bool GetDoubleBuffer() const { return m_bDoubleBuffer; }

		void SetMinimumNumAlphaBits(unsigned int bits) { m_uiMinimumNumberAlphaBits = bits; }
		unsigned int GetMinimumNumAlphaBits() const { return m_uiMinimumNumberAlphaBits; }
		bool GetAlphaBuffer() const { return m_uiMinimumNumberAlphaBits != 0; }

		void SetMinimumNumStencilBits(unsigned int bits) { m_uiMinimumNumberStencilBits = bits; }
		unsigned int GetMinimumNumStencilBits() const { return m_uiMinimumNumberStencilBits; }
		bool GetStencilBuffer() const { return m_uiMinimumNumberStencilBits != 0; }

		void SetMinimumNumAccumBits(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
		unsigned int GetMinimumNumAccumRedBits() const { return m_uiMinimumNumberAccumRedBits; }
		unsigned int GetMinimumNumAccumGreenBits() const { return m_uiMinimumNumberAccumGreenBits; }
		unsigned int GetMinimumNumAccumBlueBits() const { return m_uiMinimumNumberAccumBlueBits; }
		unsigned int GetMinimumNumAccumAlphaBits() const { return m_uiMinimumNumberAccumAlphaBits; }
		bool GetAccumBuffer() const { return (m_uiMinimumNumberAccumRedBits + m_uiMinimumNumberAccumGreenBits + m_uiMinimumNumberAccumBlueBits + m_uiMinimumNumberAccumAlphaBits) != 0; }

		void SetNumMultiSamples(unsigned int samples) { m_uiNumMultiSamples = samples; }
		unsigned int GetNumMultiSamples() const { return m_uiNumMultiSamples; }
		bool GetMultiSamples() const { return m_uiNumMultiSamples != 0; }

		void SetMaxTexturePoolSize(unsigned int size) { m_nMaxTexturePoolSize = size; }
		unsigned int GetMaxTexturePoolSize() const;

		void SetMaxBufferObjectPoolSize(unsigned int size) { m_nMaxBufferObjectPoolSize = size; }
		unsigned int GetMaxBufferObjectPoolSize() const;

		enum ImplicitBufferAttachment
		{
			IMPLICIT_DEPTH_BUFFER_ATTACHMENT = (1 << 0),
			IMPLICIT_STENCIL_BUFFER_ATTACHMENT = (1 << 1),
			IMPLICIT_COLOR_BUFFER_ATTACHMENT = (1 << 2),
			DEFAULT_IMPLICIT_BUFFER_ATTACHMENT = IMPLICIT_COLOR_BUFFER_ATTACHMENT | IMPLICIT_DEPTH_BUFFER_ATTACHMENT
		};

		typedef int ImplicitBufferAttachmentMask;

		void SetImplicitBufferAttachmentMask(ImplicitBufferAttachmentMask renderMask = CMRDisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT, ImplicitBufferAttachmentMask resolveMask = CMRDisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT)
		{
			m_implicitBufferAttachmentRenderMask = renderMask;
			m_implicitBufferAttachmentResolveMask = resolveMask;
		}

		void SetImplicitBufferAttachmentRenderMask(ImplicitBufferAttachmentMask implicitBufferAttachmentRenderMask)
		{
			m_implicitBufferAttachmentRenderMask = implicitBufferAttachmentRenderMask;
		}

		void SetImplicitBufferAttachmentResolveMask(ImplicitBufferAttachmentMask implicitBufferAttachmentResolveMask)
		{
			m_implicitBufferAttachmentResolveMask = implicitBufferAttachmentResolveMask;
		}

		/** Get mask selecting default implicit buffer attachments for Cameras primary FBOs. */
		ImplicitBufferAttachmentMask GetImplicitBufferAttachmentRenderMask() const { return m_implicitBufferAttachmentRenderMask; }

		/** Get mask selecting default implicit buffer attachments for Cameras secondary MULTISAMPLE FBOs. */
		ImplicitBufferAttachmentMask GetImplicitBufferAttachmentResolveMask() const { return m_implicitBufferAttachmentResolveMask; }

		enum SwapMethod
		{
			SWAP_DEFAULT,   // Leave swap method at default returned by choose Pixel Format.
			SWAP_EXCHANGE,  // Flip front / back buffer.
			SWAP_COPY,      // Copy back to front buffer.
			SWAP_UNDEFINED  // Move back to front buffer leaving contents of back buffer undefined.
		};

		/** Select preferred swap method */
		void SetSwapMethod(SwapMethod swapMethod) { m_swapMethod = swapMethod; }

		/** Get preferred swap method */
		SwapMethod GetSwapMethod(void) { return m_swapMethod; }

		void SetSyncSwapBuffers(unsigned int numFrames = 0) { m_syncSwapBuffers = numFrames; }

		/** Set whether Arb Sync should be used to manage the swaps buffers.*/
		unsigned int GetSyncSwapBuffers() const { return m_syncSwapBuffers; }

		/** Set the hint of which OpenGL version to attempt to create a graphics context for.*/
		void SetGLContextVersion(const string& version) { m_glContextVersion = version; }

		/** Get the hint of which OpenGL version to attempt to create a graphics context for.*/
		const string GetGLContextVersion() const { return m_glContextVersion; }

		/** Set the hint of the flags to use in when creating graphic contexts.*/
		void SetGLContextFlags(unsigned int flags) { m_glContextFlags = flags; }

		/** Get the hint of the flags to use in when creating graphic contexts.*/
		unsigned int GetGLContextFlags() const { return m_glContextFlags; }

		/** Set the hint of the profile mask to use in when creating graphic contexts.*/
		void SetGLContextProfileMask(unsigned int mask) { m_glContextProfileMask = mask; }

		/** Get the hint of the profile mask to use in when creating graphic contexts.*/
		unsigned int GetGLContextProfileMask() const { return m_glContextProfileMask; }

		unsigned int GetMaxNumberOfGraphicsContexts() const;

		void SetDeFaults();

	protected:
		float m_fScreenWidth;
		float m_fScreenHeight;

		bool m_bDoubleBuffer;
		bool m_bRGB;
		bool m_bDepthBuffer;
		unsigned int m_uiMinimumNumberAlphaBits;
		unsigned int m_uiMinimumNumberStencilBits;
		unsigned int m_uiMinimumNumberAccumRedBits;
		unsigned int m_uiMinimumNumberAccumGreenBits;
		unsigned int m_uiMinimumNumberAccumBlueBits;
		unsigned int m_uiMinimumNumberAccumAlphaBits;
		unsigned int m_uiNumMultiSamples;
		unsigned int m_nMaxTexturePoolSize;
		unsigned int m_nMaxBufferObjectPoolSize;
		ImplicitBufferAttachmentMask m_implicitBufferAttachmentRenderMask;
		ImplicitBufferAttachmentMask m_implicitBufferAttachmentResolveMask;
		unsigned int m_syncSwapBuffers;
		SwapMethod m_swapMethod;
		std::string m_glContextVersion;
		unsigned int m_glContextFlags;
		unsigned int m_glContextProfileMask;
		unsigned int m_uiNumberMultiSamples;
		//woshishaji



	};
}
#endif // CMRDisplaySettings_h__
