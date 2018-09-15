#include "Camera.h"

#include "CameraConfig.h"
#include "../../Maths/MathsTransform.h"

yami::Camera::Camera()
{
	this->fov = DEFAULT_FOV;
	this->aspectRatio = 0.0f;
	this->zNear = DEFAULT_ZNEAR;
	this->zFar = DEFAULT_ZFAR;
	this->position = Vec3();
}

yami::Camera::Camera(const Vec3 & direction, float aspectRatio)
{
	init(direction, Vec3(), Vec3(0.0f, 1.0f, 0.0f), DEFAULT_FOV, aspectRatio, DEFAULT_ZNEAR, DEFAULT_ZFAR);
}

yami::Camera::Camera(const Vec3 & direction, const Vec3 & position, float aspectRatio)
{
	init(direction, position, Vec3(0.0f, 1.0f, 0.0f), DEFAULT_FOV, aspectRatio, DEFAULT_ZNEAR, DEFAULT_ZFAR);
}

yami::Camera::~Camera()
{
}

void yami::Camera::updateVP(const Vec3 & worldUp)
{
	updateView(worldUp);
	updateProj();
}

void yami::Camera::updateProj()
{
	MathsTransform::perspective(this->projMat, this->fov, this->aspectRatio, this->zNear, this->zFar);
}

void yami::Camera::updateView(const Vec3& worldUp)
{
	MathsTransform::initCamera(this->viewMat, Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]), worldUp, position);
}

void yami::Camera::lookAt(const Vec3 & target)
{
	MathsTransform::initCamera(this->viewMat, Maths::normalize(target - this->position), Vec3(0.0f, 1.0f, 0.0f), this->position);
}

void yami::Camera::lookIn(const Vec3 & direction)
{
	MathsTransform::initCamera(this->viewMat, direction, Vec3(0.0f, 1.0f, 0.0f), this->position);
}

void yami::Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void yami::Camera::setFOV(float fov)
{
	this->fov = fov;
}

void yami::Camera::setZNear(float zNear)
{
	this->zNear = zNear;
}

void yami::Camera::setZFar(float zFar)
{
	this->zFar = zFar;
}

void yami::Camera::setPosition(const Vec3 & position)
{
	this->position = position;
	this->viewMat[3][0] = -Maths::dot(position, Vec3(this->viewMat[0][0], this->viewMat[1][0], this->viewMat[2][0]));
	this->viewMat[3][1] = -Maths::dot(position, Vec3(this->viewMat[0][1], this->viewMat[1][1], this->viewMat[2][1]));
	this->viewMat[3][2] = Maths::dot(position, Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]));
}

const yami::Mat4 & yami::Camera::getProj() const
{
	return this->projMat;
}

const yami::Mat4 & yami::Camera::getView() const
{
	return this->viewMat;
}

yami::Mat4 yami::Camera::getVP() const
{
	return this->projMat*this->viewMat;
}

float yami::Camera::getAspectRatio() const
{
	return this->aspectRatio;
}

float yami::Camera::getFOV() const
{
	return this->fov;
}

float yami::Camera::getZNear() const
{
	return this->zNear;
}

float yami::Camera::getZFar() const
{
	return this->zFar;
}

const yami::Vec3& yami::Camera::getPosition() const
{
	return this->position;
}

const yami::Vec3 yami::Camera::getDirection() const
{
	return Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]);
}

const yami::Vec3 yami::Camera::getUp() const
{
	return Vec3(this->viewMat[0][1], this->viewMat[1][1], this->viewMat[2][1]);
}

const yami::Vec3 yami::Camera::getRight() const
{
	return Vec3(this->viewMat[0][0], this->viewMat[1][0], this->viewMat[2][0]);
}

void yami::Camera::init(const Vec3 & direction, const Vec3 & position, const Vec3 & worldUp, float fov, float aspectRatio, float zNear, float zFar)
{
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->zNear = zNear;
	this->zFar = zFar;
	this->position = position;
	
	MathsTransform::initCamera(this->viewMat, direction, worldUp, position);
	MathsTransform::perspective(this->projMat, fov, aspectRatio, zNear, zFar);
}
