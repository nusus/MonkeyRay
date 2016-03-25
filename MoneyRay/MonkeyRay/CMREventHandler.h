#ifndef CMREVENTHANDLER
#define CMREVENTHANDLER 1

#include <vector>

//#include <osg/Drawable>
//#include <osg/ApplicationUsage>
#include "CMRGUIEventAdapter.h"
#include "CMRGUIActionAdapter.h"

namespace MR {

	class  CMREventHandler : public osg::NodeCallback, public osg::Drawable::EventCallback
	{
	public:

		CMREventHandler() {}
		CMREventHandler(const CMREventHandler& eh, const CMRCopyPolicy& copyop = CMRCopyPolicy::SHALLOW_COPY) :
			CMRObject(eh, copyop),
			osg::Callback(eh, copyop),
			osg::NodeCallback(eh, copyop),
			osg::Drawable::EventCallback(eh, copyop) {}

		META_OBJECT(io, CMREventHandler);

		virtual bool run(CMRObject* object, CMRObject* data)
		{
			osg::Node* node = dynamic_cast<osg::Node*>(object);
			osg::NodeVisitor* nv = dynamic_cast<osg::NodeVisitor*>(data);
			operator()(node, nv);
			return true;
		}


	}
}

#endif