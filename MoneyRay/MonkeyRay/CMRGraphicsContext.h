#ifndef CMRGraphicsContext_h__
#define CMRGraphicsContext_h__
#include "CMRObject.h"
namespace MR
{
	class CMRCamera;

	class CMRGraphicsContext : public CMRObject
	{

	public:
		struct Traits : public CMRRef
		{
			Traits(CMRDisplaySettings* ds = 0);

			int x;
			int y;
			int width;
			int height;

			string windowName;
			bool        windowDecoration;
			bool        supportsResize;

			unsigned int red;
			unsigned int blue;
			unsigned int green;
			unsigned int alpha;
			unsigned int depth;
			unsigned int stencil;

			unsigned int sampleBuffers;
			unsigned int samples;

			// buffer configuration
			bool pbuffer;
			bool doubleBuffer;


			// V-sync
			bool            vsync;

			// Swap Group
			bool            swapGroupEnabled;
			GLuint          swapGroup;
			GLuint          swapBarrier;

			// enable cursor
			bool            useCursor;

			// settings used in set up of graphics context, only presently used by GL3 build of OSG.
			std::string     glContextVersion;
			unsigned int    glContextFlags;
			unsigned int    glContextProfileMask;

			/** return true if glContextVersion is set in the form major.minor, and assign the appropriate major and minor values to the associated parameters.*/
			bool getContextVersion(unsigned int& major, unsigned int& minor) const;

			// shared context
			WeakPtr<CMRGraphicsContext> sharedContext;

			WeakPtr<CMRRef> inheritedWindowData;

			// ask the GraphicsWindow implementation to set the pixel format of an inherited window
			bool setInheritedWindowPixelFormat;

			CMRDisplaySettings::SwapMethod swapMethod;
		};


		class CMRWindowingSystemInterface
		{
		public:
			CMRDisplaySettings* GetDisplaySettings() const;
			void SetDisplaySettings(CMRDisplaySettings* ds);
		protected:
		private:
		};

		class CMRSwapCallback : public CMRRef
		{
		public:

			virtual void SwapBuffersImplemention(CMRGraphicsContext* gc) = 0;
		protected:
		private:
		};

	public:
		void RunOperations()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SwapBuffers()
		{
			//TODO: CMRGraphicsContext is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

			bool IsRealized() const
		{
			return IsRealizedImplemention();
		}

			static CMRGraphicsContext::CMRWindowingSystemInterface* GetWindowingSystemInterface()
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			void SetSwapCallback(const CMRSyncSwapBuffersCallback* ssbc)
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			CMRState* GetState() const
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			void Realize()
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			bool Valid()
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			CMRNode* GetSceneData()
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			virtual bool IsRealizedImplemention() const = 0;










	};

	class CMRSyncSwapBuffersCallback : public CMRGraphicsContext::CMRSwapCallback
	{
	public:
		virtual void SwapBuffersImplemention(CMRGraphicsContext* gc) override
		{
			//TODO: SyncSwapBuffersCallback is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}
	protected:
	private:

	};
}
#endif // CMRGraphicsContext_h__
