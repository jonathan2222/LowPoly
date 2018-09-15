#include <crtdbg.h>

#include "Core\Window\Display.h"
#include "Utils\Error.h"

#include "Core\GLAbstractions\VertexArray.h"
#include "Core\GLAbstractions\IndexBuffer.h"
#include "Core\GLAbstractions\UniformBuffer.h"
#include "Utils\ModelGenerator.h"

#include "Core\Shaders\Shader.h"

#include "Core\Scene\FPSCamera.h"
#include "Maths\Vectors\Vec3.h"
#include "Maths\MathsTransform.h"

#include "Input\InputManager.h"

#include "Utils\Utils.h"
#include "Utils\Timer.h"

#include "Core\Scene\Model.h"
#include "Utils\ModelLoader.h"
#include "Core\Scene\Renderer.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	yami::Error::init();
	yami::Display* display = new yami::Display("Low Poly");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	/*
	yami::Quaternion normalRotation;
	normalRotation.setRotation(yami::Vec3(0.0f, 0.0f, 1.0f), yami::Vec3(0.0f, -1.0f, 0.0f));
	yami::Error::print("Q: a: " + yami::Utils::toString(normalRotation.getAngle()) + ", v: " + yami::Utils::toString(normalRotation.getAxis()));
	yami::Vec3 b(0.0f, 0.0f, 1.0f);
	yami::Error::print("b: " + yami::Utils::toString(b) + ", res: " + yami::Utils::toString(normalRotation*b));
	*/
	yami::Model* boxModel = yami::ModelGenerator::generateBox(1.0f, 10);

	yami::Model* sphereModel = yami::ModelGenerator::generateSphere(0.5f, 10);

	yami::Model* terrain = yami::ModelGenerator::generateQuad({ 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f, 0.0f}, 1.0f, 10);
	//yami::Model* terrain = yami::ModelGenerator::generateTerrain(4, 2);
	
	yami::Model* barrel = yami::ModelLoader::loadModel("./Resources/Models/Barrel.fbx");
	yami::Model* sword = yami::ModelLoader::loadModel("./Resources/Models/Sword2.fbx");

	yami::FPSCamera camera(yami::Vec3(0.0f, 0.0f, -1.0f), yami::Vec3(0.0f, 0.0f, 5.0f), display->getAspectRatio());
	glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);

	yami::Renderer renderer;
	renderer.setWireframe(false);
	yami::Shader shader = renderer.getShader();

	yami::Vec3 offset(2.0f, 0.0f, 0.0f);
	yami::Mat4 worldMat = yami::MathsTransform::translate(0.0f, 0.0f, 2.0f);

	yami::Timer timer;
	float fpsDisplayTimer = 1.0f;

	int activeState = 0;
	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	glfwSetInputMode(display->getWindowPtr(), GLFW_STICKY_KEYS, GL_TRUE);
	while (glfwGetKey(display->getWindowPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(display->getWindowPtr()) == 0)
	{
		timer.update();
		if (display->sizeUpdated)
		{
			camera.setAspectRatio(display->getAspectRatio());
			camera.updateProj();
			display->sizeUpdated = false;
		}

		// ----------------- Update -----------------
		if (yami::InputManager::toggle(display->getWindowPtr(), GLFW_KEY_C))
		{
			if (activeState != 1)
			{
				glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);
				glfwSetInputMode(display->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			camera.update(display->getWindowPtr(), timer.getDeltaTime(), display->getWidth(), display->getHeight());
			glfwSetCursorPos(display->getWindowPtr(), display->getWidth() / 2, display->getHeight() / 2);
			activeState = 1;
		}
		else
		{
			if(activeState != 2)
				glfwSetInputMode(display->getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			activeState = 2;
		}

		//worldMat = yami::MathsTransform::rotate(worldMat, 0.0f, timer.getDeltaTime(), 0.0f);
		yami::Quaternion worldBaseRot(timer.getDeltaTime(), yami::Vec3(0.0f, 1.0f, 0.0f));
		worldMat = worldBaseRot.getMatrix4() * worldMat;
		
		// ----------------- Render -----------------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.resetMaterial(); // Use default material
		
		shader.bind();
		yami::Mat4 terrainW(1.0f);
		terrainW = yami::MathsTransform::translate(terrainW, 0.0f, -1.0f, 0.0f);
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(terrainW)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(terrain);

		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(worldMat)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(boxModel);
		
		yami::Mat4 scale(0.1f);
		scale[3][3] = 1.0f;
		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(scale)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(boxModel);

		yami::Mat4 w3 = yami::MathsTransform::translate(0.0f, 0.0f, -3.0f) * yami::MathsTransform::scale(1.0f, 1.0f, 1.0f);
		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(w3)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(sphereModel);

		//shader.bind();
		yami::Mat4 w2 = yami::MathsTransform::translate(-3.0f, 0.0f, 0.0f);
		//shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		//w2 = yami::MathsTransform::rotate(w2, -yami::MathsConstatns::PI / 2.0f, 0.0f, 0.0f);
		shader.setUniformMatrix4fv("world", 1, false, &(w2)[0][0]);
		//shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(sword);
		
		yami::Mat4 w(1.0f);
		w[3][3] = 1.0f;
		yami::Quaternion baseRotation(-yami::MathsConstatns::PI / 2.0f, yami::Vec3(1.0f, 0.0f, 0.0f));
		//w = yami::MathsTransform::scale(w, 10.0f, 10.0f, 10.0f);
		w = w * baseRotation.getMatrix3();
		//w = yami::MathsTransform::rotate(w, -yami::MathsConstatns::PI / 2.0f, 0.0f, 0.0f);
		w = yami::MathsTransform::translate(w, 2.0f, 0.0f, 0.0f);
		shader.bind();
		shader.setUniform3fv("camPos", 1, &(camera.getPosition())[0]);
		shader.setUniformMatrix4fv("world", 1, false, &(w)[0][0]);
		shader.setUniformMatrix4fv("vp", 1, false, &(camera.getVP())[0][0]);
		renderer.render(barrel);

		if (fpsDisplayTimer >= 1.0)
		{
			display->setTitleSuffix(" FPS: " + std::to_string(1.0 / timer.getDeltaTime()));
			fpsDisplayTimer = 0.0;
		}
		else fpsDisplayTimer += timer.getDeltaTime();

		glfwSwapBuffers(display->getWindowPtr());
		glfwPollEvents();
	}

	delete sphereModel;
	delete boxModel;
	delete barrel;
	delete sword;
	delete terrain;
	delete display;

	return 0;
}