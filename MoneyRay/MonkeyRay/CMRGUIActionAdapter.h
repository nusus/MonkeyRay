#ifndef CMRGUIACTIONADAPTER
#define CMRGUIACTIONADAPTER 1


namespace MR {
	class CMRGUIEventAdapter;

	class CMRGUIActionAdapter
	{
	public:
		virtual ~CMRGUIActionAdapter() {}
		virtual osg::View* asView() { return 0; }
		virtual void requestRedraw() = 0;
		virtual void requestContinuousUpdate(bool needed = true) = 0;
		virtual void requestWarpPointer(float x, float y) = 0;
		// until º¯Êý
		// until º¯Êý
	};


}
#endif