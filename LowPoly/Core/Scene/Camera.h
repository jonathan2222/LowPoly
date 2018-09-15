#ifndef YAMI_CAMERA_H
#define YAMI_CAMERA_H

#include "GLFW\glfw3.h"

#include "../../Maths/Vectors/Vec3.h"
#include "../../Maths/Matrices/Mat4.h"

namespace yami
{
	class Camera
	{
	public:
		Camera();
		Camera(const Vec3& direction, float aspectRatio);
		Camera(const Vec3& direction, const Vec3& position, float aspectRatio);
		virtual ~Camera();

		virtual void update(GLFWwindow* window, float dt, int windowWidth, int windowHeight) {};

		void updateVP(const Vec3& worldUp);
		void updateProj();
		void updateView(const Vec3& worldUp);

		void lookAt(const Vec3& target);
		void lookIn(const Vec3& direction);

		void setAspectRatio(float aspectRatio);
		void setFOV(float fov);
		void setZNear(float zNear);
		void setZFar(float zFar);
		void setPosition(const Vec3& position);

		const Mat4& getProj() const;
		const Mat4& getView() const;
		Mat4 getVP() const;

		float getAspectRatio() const;
		float getFOV() const;
		float getZNear() const;
		float getZFar() const;
		const Vec3& getPosition() const;
		const Vec3 getDirection() const;
		const Vec3 getUp() const;
		const Vec3 getRight() const;

	private:
		void init(const Vec3& direction, const Vec3& position, const Vec3& worldUp, float fov, float aspectRatio, float zNear, float zFar);

	private:
		Mat4 projMat;
		Mat4 viewMat;

		Vec3 position;

		float aspectRatio;
		float fov;
		float zNear;
		float zFar;
	};
}

#endif

