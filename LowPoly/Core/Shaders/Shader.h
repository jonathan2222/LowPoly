#ifndef YAMI_SHADER_H
#define YAMI_SHADER_H

#include "GL\glew.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace yami
{
	class Shader
	{
	public:
		// pathName is the path and the name of the directory which the files are in.
		Shader(const std::string& pathName); // Will create a vertex and fragment shader.
		Shader(const std::string& pathName, unsigned int flags); // The user specifies which shader it should use.
		~Shader();

		void bind();
		void unbind();

		void setTexture2D(const std::string& name, unsigned int unit);
		void setTexture2D(const std::string& name, unsigned int unit, GLuint textureID);
		void setUniform1i(const std::string& name, int value);
		void setUniform1b(const std::string& name, bool value);
		void setUniform1f(const std::string& name, float v1);
		void setUniform2f(const std::string& name, float v1, float v2);
		void setUniform2fv(const std::string& name, unsigned int count, const float* values);
		void setUniform3f(const std::string& name, float v1, float v2, float v3);
		void setUniform3fv(const std::string& name, unsigned int count, const float* values);
		void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
		void setUniform4fv(const std::string& name, unsigned int count, const float* values);
		void setUniformMatrix4fv(const std::string& name, unsigned int count, bool transpose, const float* values);

		const GLuint getID() const;

	private:
		void init(const std::string& pathName, unsigned int flags);
		int addUniform(const std::string& name);

		void addShaderpart(const std::string & pathName, GLuint type);
		GLuint loadShaderPart(const std::string & pathName, GLuint type);
		bool compileShaderPart(GLuint id);
		void link();

	private:
		GLuint id;
		std::vector<GLuint> ids;
		std::unordered_map<std::string, GLint> uniforms;
	};
}

#endif
