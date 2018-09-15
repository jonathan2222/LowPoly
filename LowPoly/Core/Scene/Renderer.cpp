#include "Renderer.h"

yami::Renderer::Renderer()
{
	this->shader = new Shader("./Resources/Shaders/testShader");
	this->shader->bind();
	this->ubo = new UniformBuffer("Material", shader->getID(), 1);
	yami::Material::MaterialData tempMatData;
	this->ubo->setData(&tempMatData, sizeof(yami::Material::MaterialData));
	setWireframe(false);
}

yami::Renderer::~Renderer()
{
	delete this->ubo;
	delete this->shader;
}

void yami::Renderer::setWireframe(bool on)
{
	if (on)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		isWireframeOn = true;
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		isWireframeOn = false;
	}
}

void yami::Renderer::render(const Model * model)
{
	render(model->getMeshes(), model->getMaterials());
}

void yami::Renderer::render(const Model * model, const Material::MaterialData & material)
{
	render(model->getMeshes(), material);
}

void yami::Renderer::render(const std::vector<Mesh*>& meshes, const Material::MaterialData & material) const
{
	unsigned int materialIndex = 0;
	shader->bind();
	if (isWireframeOn)
		shader->setUniform3f("emissionColor", 1.0f, 1.0f, 1.0f);
	else
		shader->setUniform3f("emissionColor", 0.0f, 0.0f, 0.0f);

	ubo->setSubData(&material, sizeof(yami::Material::MaterialData), 0);
	for (yami::Mesh* m : meshes)
	{
		m->getVertexBuffer().bind();
		m->getIndexBuffer().bind();
		glDrawElements(GL_TRIANGLES, m->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
		materialIndex++;
	}
}

void yami::Renderer::render(const std::vector<Mesh*>& meshes, const std::vector<Material::MaterialData>& materials) const
{
	unsigned int materialIndex = 0;
	shader->bind();
	if (isWireframeOn)
		shader->setUniform3f("emissionColor", 1.0f, 1.0f, 1.0f);
	else
		shader->setUniform3f("emissionColor", 0.0f, 0.0f, 0.0f);

	for (yami::Mesh* m : meshes)
	{
		if(!materials.empty())
			ubo->setSubData(&(materials[materialIndex]), sizeof(yami::Material::MaterialData), 0);
		m->getVertexBuffer().bind();
		m->getIndexBuffer().bind();
		glDrawElements(GL_TRIANGLES, m->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
		materialIndex++;
	}
}

void yami::Renderer::resetMaterial()
{
	Material::MaterialData defaultMaterial = { { 0.1f, 0.1f, 0.1f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 90.0f } };
	this->ubo->setSubData(&defaultMaterial, sizeof(yami::Material::MaterialData), 0);
}

yami::Shader & yami::Renderer::getShader()
{
	return *this->shader;
}
