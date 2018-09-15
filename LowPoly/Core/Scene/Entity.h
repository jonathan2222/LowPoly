#ifndef YAMI_ENTITY_H
#define YAMI_ENTITY_H

#include "../../Maths/Vectors/Vec3.h"
#include "../../Maths/Matrices/Mat4.h"

#include "Model.h"

#include <vector>

namespace yami
{
	class Entity
	{
	public:
		Entity(const Vec3& position);
		virtual ~Entity();

		Mat4& getLocalMatrix();
		Mat4& getWorldMatrix();

	private:
		Model* model;
		Mat4 localMatrix;
		Mat4 worldMatrix;

	};
}

#endif