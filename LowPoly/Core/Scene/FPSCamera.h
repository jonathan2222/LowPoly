#ifndef YAMI_FPS_CAMERA_H
#define YAMI_FPS_CAMERA_H

#include "Camera.h"

#include "../../Maths/Vectors/Vec2.h"
#include "../../Maths/Vectors/Vec3.h"

namespace yami
{
	class FPSCamera	: public Camera
	{
	public:
		FPSCamera();
		FPSCamera(const Vec3& direction, float aspectRatio);
		FPSCamera(const Vec3& direction, const Vec3& position, float aspectRatio);
		virtual ~FPSCamera();

		void update(GLFWwindow* window, float dt, int windowWidth, int windowHeight) override;

	private:
		Vec2 preMousePos;
	};
}

#endif
