#ifndef YAMI_DISPLAY_H
#define YAMI_DISPLAY_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <string>

namespace yami
{
	class Display
	{
	public:
		Display();
		Display(const std::string& title);
		Display(const std::string& title, unsigned int width, unsigned int height);
		virtual ~Display();

		void updateView(unsigned int width, unsigned int height);
		void setTitle(const std::string& title);
		void setTitleSuffix(const std::string& suffix);

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		GLFWwindow* getWindowPtr() const;
		float getAspectRatio() const;

	public:
		static Display* displayPtr;
		bool sizeUpdated;

	private:
		void init();
		static void resizeCallback(GLFWwindow* window, int width, int height);

	private:
		unsigned int width;
		unsigned int height;
		std::string title;
		GLFWwindow* window;
	};
}

#endif
