#include "MonkeyRay.h"


using namespace MR;
int main(int argc, char* arg[])
{
	SmartPtr<CMRView> spView = new CMRView;
	CMRCamera* pCamera = spView->GetCamera();
	vmath::vec3 eye(-5.0, -5.0, 5.0);
	vmath::vec3 center(0.0, 0.0, 0.0);
	vmath::vec3 up(1.0, 1.0, 1.0);
	pCamera->SetViewport()
	pCamera->SetViewMatrixAsLookAt(eye, center, up);
	pCamera->SetProjectionMatrixAsPerspective(60.0, (double)(),
}