#include "FPSCamera.h"

#include "CameraConfig.h"
#include "../../Input/InputManager.h"
#include "../../Maths/Maths.h"
#include "../../Maths/MathsTransform.h"

yami::FPSCamera::FPSCamera() : Camera()
{
}

yami::FPSCamera::FPSCamera(const Vec3 & direction, float aspectRatio) : Camera(direction, aspectRatio)
{
}

yami::FPSCamera::FPSCamera(const Vec3 & direction, const Vec3 & position, float aspectRatio) : Camera(direction, position, aspectRatio)
{
}

yami::FPSCamera::~FPSCamera()
{
}

void yami::FPSCamera::update(GLFWwindow * window, float dt, int windowWidth, int windowHeight)
{
	Vec2 mousePos = InputManager::getMousePosition(window);
	mousePos.x /= windowWidth;
	mousePos.y /= windowHeight;

	float stepX = windowWidth / CAMERA_WIDTH;
	float cameraHeight = windowWidth / windowHeight * CAMERA_WIDTH;
	float stepY = windowWidth / cameraHeight;
	
	if (yami::InputManager::press(window, GLFW_KEY_W))
		setPosition(getPosition() + (FPS_CAMERA_SPEED * dt) * getDirection());
	if (yami::InputManager::press(window, GLFW_KEY_S))
		setPosition(getPosition() - (FPS_CAMERA_SPEED * dt) * getDirection());
	if (yami::InputManager::press(window, GLFW_KEY_D))
		setPosition(getPosition() + (FPS_CAMERA_SPEED * dt) * getRight());
	if (yami::InputManager::press(window, GLFW_KEY_A))
		setPosition(getPosition() - (FPS_CAMERA_SPEED * dt) * getRight());

	if (yami::InputManager::toggle(window, GLFW_KEY_C))
	{
		// Mouse position has changed!
		if (this->preMousePos != mousePos)
		{
			Vec3 dir = getDirection();

			Vec2 deltaPos = Vec2(0.5f, 0.5f) - mousePos;
			dir = MathsTransform::rotate(dir, MOUSE_SENSITIVITY_X * deltaPos.x * stepX * dt, getUp());
			dir = MathsTransform::rotate(dir, MOUSE_SENSITIVITY_Y * deltaPos.y * stepY * dt, getRight());
			lookIn(dir);
		}
	}

	this->preMousePos = mousePos;
}
