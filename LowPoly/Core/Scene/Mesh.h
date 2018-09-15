#ifndef YAMI_MESH_H
#define YAMI_MESH_H

#include "Vertex.h"
#include "..\GLAbstractions\VertexArray.h"
#include "..\GLAbstractions\IndexBuffer.h"

#include <vector>

namespace yami
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
		virtual ~Mesh();

		void uploadToGPU();

		VertexArray& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

	private:
		VertexArray* va;
		IndexBuffer* ib;
		VertexBuffer* vb;
	};
}

#endif