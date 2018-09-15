#include "Entity.h"

#include "../../Maths/MathsTransform.h"

yami::Entity::Entity(const Vec3 & position)
{
	this->localMatrix = Mat4(1.0f);
	this->worldMatrix = MathsTransform::translate(position.x, position.y, position.z);
}

yami::Entity::~Entity()
{
}

yami::Mat4 & yami::Entity::getLocalMatrix()
{
	return this->localMatrix;
}

yami::Mat4 & yami::Entity::getWorldMatrix()
{
	return this->worldMatrix;
}
