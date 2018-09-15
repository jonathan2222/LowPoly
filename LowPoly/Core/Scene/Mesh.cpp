#include "Mesh.h"

yami::Mesh::Mesh()
{
	this->va = nullptr;
	this->ib = nullptr;
	this->vb = nullptr;
}

yami::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->vertices.reserve(vertices.size());
	for (Vertex v : vertices)
		this->vertices.push_back(v);

	this->indices.reserve(indices.size());
	for (unsigned int i : indices)
		this->indices.push_back(i);

	uploadToGPU();
}

yami::Mesh::~Mesh()
{
	delete this->va;
	delete this->ib;
	delete this->vb;
}

void yami::Mesh::uploadToGPU()
{
	delete this->va;
	delete this->ib;
	delete this->vb;

	this->va = new VertexArray();
	this->va->bind();
	this->vb = new VertexBuffer(&this->vertices[0], sizeof(Vertex)*this->vertices.size());
	VertexBufferLayout layout;
	layout.push<float>(3); // Position
	layout.push<float>(3); // Normal
	va->addBuffer(*this->vb, layout);
	this->ib = new IndexBuffer(&this->indices[0], this->indices.size());
	this->va->unbind();
}

yami::VertexArray & yami::Mesh::getVertexBuffer()
{
	return *this->va;
}

yami::IndexBuffer & yami::Mesh::getIndexBuffer()
{
	return *this->ib;
}
