#include "Model.h"

yami::Model::Model(std::vector<Mesh*> meshes)
{
	for (Mesh* m : meshes)
		this->meshes.push_back(m);
}

yami::Model::Model(std::vector<Mesh*> meshes, std::vector<Material::MaterialData> materials)
{
	for (Mesh* m : meshes)
		this->meshes.push_back(m);
	for(Material::MaterialData m : materials)
		this->materials.push_back(m);
}

yami::Model::~Model()
{
	for (unsigned int i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];
}

const std::vector<yami::Mesh*>& yami::Model::getMeshes() const
{
	return this->meshes;
}

const std::vector<yami::Material::MaterialData>& yami::Model::getMaterials() const
{
	return this->materials;
}

bool yami::Model::hasMaterial() const
{
	return !this->materials.empty();
}
