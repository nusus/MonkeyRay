#include "MonkeyRay.h"
#include "CMRImportedMesh.h"
#include "CMRUniform.h"


using namespace MR;

int main(int argc, char* arg[])
{
	SmartPtr<CMRView> spView = new CMRView;
	CMRCamera* pCamera = spView->GetCamera();

	vmath::vec3 eye(-5.0, -5.0, 5.0);
	vmath::vec3 center(0.0, 0.0, 0.0);
	vmath::vec3 up(1.0, 1.0, 1.0);

	pCamera->SetViewMatrixAsLookAt(eye, center, up);
	pCamera->SetProjectionMatrixAsPerspective(60.0, (double)(spView->GetWidth() / spView->GetHeight()), 0.1, 1000);
	
	SmartPtr<CMRImportedMesh> spMesh = new CMRImportedMesh("box.3DS");
	
	SmartPtr<CMRShader> spVertexShader = new CMRShader(CMRShader::VERTEX, "ocean.vert");
	SmartPtr<CMRShader> spFragmentShader = new CMRShader(CMRShader::FRAGMENT, "ocean.frag");
	spMesh->AddShader(spVertexShader);
	spMesh->AddShader(spFragmentShader);
	
	GLint data[] = { 0 };
	SmartPtr<CMRUniformRef> spUniform = new CMRUniform1iv("tex_object", data);
	
	GLfloat global_time_data[] = { 0.0f };
	SmartPtr<CMRUniformRef> globalTimeUniform = new CMRUniform1fv("iGlobalTime", global_time_data);
	
	GLfloat resolution_data[] = { 640.0f, 480.0f, 0.0f };
	SmartPtr<CMRUniformRef> resolutionUniform = new CMRUniform3fv("iResolution", resolution_data);
	
	spMesh->AddUniform(spUniform);
	spMesh->AddUniform(globalTimeUniform);
	spMesh->AddUniform(resolutionUniform);

	spView->SetSceneData(spMesh.Get());
	
	CMRDirector* pDirector = CMRDirector::Instance(spView.Get());
	return pDirector->Run();
}