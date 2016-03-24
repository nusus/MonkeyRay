#ifndef CMRView_h__
#define CMRView_h__
#include "CMRScene.h"
#include "CMRCameraManipulator.h"
#include "WeakPtr.h"
#include "CMRDirector.h"
#include "CMRGraphicsThread.h"
#include "CMRViewConfig.h"
#include "CMRDisplaySettings.h"
#include "CMRGUIActionAdapter.h"
#include "CMRViewBase.h"
#include "CMRDevice.h"
#include "CMREventQueue.h"
#include "CMREventHandlers.h"
#include "CMRObject.h"
#include "CMRImagePager.h"
#include "CMRGUIEventAdapter.h"
#include "CMRLineSegmentIntersector.h"
namespace MR
{
	class CMRViewConfig : public CMRObject
	{
	public:
		CMRViewConfig() {}
		CMRViewConfig(const CMRViewConfig&, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY) {}
		META_OBJECT(MonkeyRay, CMRViewConfig);

		virtual void Configure(CMRView&) const {}
		virtual CMRDisplaySettings* GetActiveDisplaySetting(CMRView& view) const;
	protected:
	private:
	};

	struct CMRDepthPartition :public CMRRef
	{
	};


	class CMRView :public CMRViewBase ,public CMRGUIActionAdapter
	{
	public:
		typedef vector<CMRDevice*> Devices;
	public:
		CMRView();
		CMRView(const CMRView& view, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		META_OBJECT(MonkeyRay, CMRView);

	public:
		virtual CMRView* AsView() { return this; }
		CMRDirector* GetDirector() const { return m_wpDirector.Get(); }
		virtual void Take(CMRView& view);

		virtual void SetStartTick(Timer_t startTick);
		Timer_t GetStartTick() const;

		CMRScene* GetScene() { return m_spScene.Get(); }
		const CMRScene* GetScene() const { return m_spScene.Get(); }

		virtual void SetSceneData(CMRScene* pScene);

		template<typename T>
		void SetSceneData(const SmartPtr<T>& spScene) { SetSceneData(spScene.Get()); }

		CMRNode* GetSceneData() { return m_spScene.Valid() ? m_spScene->GetSceneData() : 0; }
		const CMRNode* GetSceneData() const { return m_spScene.Valid() ? m_spScene->GetSceneData() : 0; }

		OBJECT_MEMBER_GET_SET(DatabasePager);

		OBJECT_MEMBER_GET_SET(ImagePager);


		void AddDevice(CMRDevice* dev);
		template<typename T>
		void AddDevice(const SmartPtr<T>& spDev) { AddDevice(spDev.Get()); }

		void RemoveDevice(CMRDevice* dev);
		template<typename T>
		void RemoveDevice(const SmartPtr<T>& spDev) { RemoveDevice(spDev.Get()); }

		Devices& GetDevices();
		const Devices& GetDevices() const;

		OBJECT_MEMBER_GET_SET(CameraManipulator);

		void Home();

		OBJECT_MEMBER_ADD_GET_REMOVE(EventHandlers);

		OBJECT_MEMBER_GET_SET(DisplaySettings);

		void SetCoordinateSystemNodePath(const CMRNodePath& nodePath);

		CMRNodePath GetCoordinateSystemNodePath() const;

		void ComputeActiveCoordinateSystemNodePath();
	
		void ApplyCurrentViewConfig();

		void SetCurrentViewConfig(CMRViewConfig* vc);
		CMRViewConfig* GetCurrentViewConfig();
		const CMRViewConfig* GetCurrentViewConfig() const;

		CMRViewConfig* GetLastAppliedViewConfig();
		const CMRViewConfig* GetLastAppliedViewConfig() const;

		bool SetUpDepthPartition(CMRDepthPartition* dp = 0);

		bool ComputeIntersections(const CMRGUIEventAdapter& ea, CMRLineSegmentIntersector::Intersections & intersections, CMRNode::NodeMask traversalMask = 0xffffffff);

		bool ComputeIntersections(const CMRGUIEventAdapter& ea, const CMRNodePath& nodePath, CMRLineSegmentIntersector::Intersections& intersections, CMRNode::NodeMask traversalMask = 0xffffffff);


		bool ComputeIntersections(const CMRCamera* camera, CMRIntersector::CoordinateFrame cf, float x, float y, CMRLineSegmentIntersector::Intersections& intersections, CMRNode::NodeMask traversalMask = 0xffffffff);

		bool ComputeIntersections(const CMRCamera* camera, CMRIntersector::CoordinateFrame cf, float x, float y, const CMRNodePath& nodePath, CMRLineSegmentIntersector::Intersections& intersections, CMRNode::NodeMask traversalMask = 0xffffffff);

		virtual void RequestRedraw();
		virtual void RequestContinuousUpdate(bool needed = true);
		virtual void RequestWarpPointer(float x, float y);

		void AssignSceneDataToCameras();
		void Init();
	protected:

		virtual ~CMRView();

		virtual CMRGraphicsOperation* CreateRender(CMRCamera* pCamera);

		WeakPtr<CMRDirector> m_wpDirector;
		Timer_t m_startTick;
		Devices m_eventSource;
		SmartPtr<CMRScene> m_spScene;
		SmartPtr<CMREventQueue> m_spEventQueue;
		SmartPtr<CMRCameraManipulator> m_spCameraManipulator;
		CMREventHandlers m_eventHandlers;
		SmartPtr<CMRDisplaySettings> m_spDisplaySetting;
		SmartPtr<CMRViewConfig> m_spLastAppliedViewConfig;
		SmartPtr<CMRViewConfig> m_spCurrentAppliedViewConfig;
	};

	


}
#endif // CMRView_h__
