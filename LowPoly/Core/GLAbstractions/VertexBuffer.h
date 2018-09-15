#ifndef YAMI_VERTEX_BUFFER_H
#define YAMI_VERTEX_BUFFER_H

namespace yami
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	private:
		unsigned int id;
	};
}

#endif
