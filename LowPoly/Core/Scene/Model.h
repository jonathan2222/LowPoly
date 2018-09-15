#ifndef YAMI_MODEL_H
#define YAMI_MODEL_H

#include "Mesh.h"
#include "Material.h"
#include <vector>

namespace yami
{
	class Model
	{
	public:
		Model(std::vector<Mesh*> meshes);
		Model(std::vector<Mesh*> meshes, std::vector<Material::MaterialData> materials);
		~Model();

		const std::vector<Mesh*>& getMeshes() const;
		const std::vector<Material::MaterialData>& getMaterials() const;

		bool hasMaterial() const;

	private:
		std::vector<Mesh*> meshes;
		std::vector<Material::MaterialData> materials;
	};
}

#endif
