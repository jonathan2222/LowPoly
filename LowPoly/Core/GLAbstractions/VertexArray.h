#ifndef YAMI_VERTEX_ARRAY_H
#define YAMI_VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace yami
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		unsigned int id;
	};
}

#endif