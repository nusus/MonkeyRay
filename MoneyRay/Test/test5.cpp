#include "CConfig.h"
#if TEST5 == ON

#include "CGlobalInclude.h"
#include "CMRMesh.h"
#include "CMRApplication.h"

int main(void)
{
	MR::CMRMesh* pMesh = new MR::CMRMesh("box.3DS");
	MR::CMRApplication app;
	app.AddMesh(pMesh);
	return app.Run();

}
#endif