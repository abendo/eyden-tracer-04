#include "Scene.h"

#include "CameraPerspective.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"
#include "Solid.h"
#include "SolidQuad.h"
#include "SolidCone.h"
#include "SolidSphere.h"

#include "ShaderFlat.h"
#include "ShaderEyelight.h"
#include "ShaderPhong.h"

#include "LightOmni.h"
#include "timer.h"

Mat RenderFrame(void)
{
	// Camera resolution
	const Size resolution(1200, 600);
	
	// Define a scene
	CScene scene;

	// Add camera to scene
	auto pCamera = std::make_shared<CCameraPerspective>(resolution, Vec3f(0, 0, -30.0f), Vec3f(0, 0, 1), Vec3f(0, 1, 0), 30);

	// Shader
	auto pShader = std::make_shared<CShaderEyelight>(RGB(0.5f, 1, 0));

	// Geometry
	CSolidCone solid_cone(pShader, Vec3f(10, -4, 0), 4, 8);
	CSolidSphere solid_sphere(pShader, Vec3f(0, 0, 0), 4, 36);
	auto prim_sphere = std::make_shared<CPrimSphere>(pShader, Vec3f(-10, 0, 0), 4);

	// Add everything to the scene
	scene.add(pCamera);
	scene.add(solid_cone);
	scene.add(solid_sphere);
	scene.add(prim_sphere);

	// Build BSPTree
	scene.buildAccelStructure(20, 3);

	// --- Scene description for 4.2 only ---

	//auto shd1 = std::make_shared<CShaderPhongBumpMapped>(scene, RGB(1, 0, 0), 0.1f, 0.5f, 0.5f, 40); // red surface
	//auto shd2 = std::make_shared<CShaderPhongBumpMapped>(scene, RGB(1, 1, 0), 0.1f, 0.5f, 0.5f, 40); // yellow surface
	//
	//auto shd3 = std::make_shared<CShaderPhong>(scene, RGB(0, 1, 1), 0.1f, 0.5f, 0.5f, 40); // cyan surface
	//auto shd4 = std::make_shared<CShaderPhong>(scene, RGB(0, 0, 1), 0.1f, 0.5f, 0.5f, 40); // blue surface
	//
	//scene.Add(std::make_shared<CPrimSphere>(Vec3f(-2, 1.7f, 0), 2, shd1));
	//scene.Add(std::make_shared<CPrimSphere>(Vec3f(1, -1, 1), 2.2f, shd3));
	//scene.Add(std::make_shared<CPrimSphere>(Vec3f(3, 0.8f, -2), 2, shd4));
	//scene.Add(std::make_shared<CPrimPlane>(Vec3f(0, -1, 0), Vec3f(0, 1, 0), shd2));
	//
	//Vec3f pointLightIntensity(7, 7, 7);
	//Vec3f lightPosition2(-3, 5, 4);
	//Vec3f lightPosition3(0, 1, 4);
	//
	//scene.Add(std::make_shared<CLightPoint>(pointLightIntensity, lightPosition2));
	//scene.Add(std::make_shared<CLightPoint>(pointLightIntensity, lightPosition3));

	// --- End description for 4.2 ---


	Mat img(resolution, CV_32FC3);							// image array
	Ray ray;												// primary ray

	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			scene.getActiveCamera()->InitRay(ray, x, y);	// initialize ray
			img.at<Vec3f>(y, x) = scene.RayTrace(ray);
		}

	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	DirectGraphicalModels::Timer::start("Rendering...");
	Mat img = RenderFrame();
	DirectGraphicalModels::Timer::stop();
	imshow("Image", img);
	waitKey();
	imwrite("image.jpg", img);
	return 0;
}
