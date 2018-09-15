#ifndef YAMI_INPUT_MANAGER_H
#define YAMI_INPUT_MANAGER_H

#include "GLFW\glfw3.h"
#include "../Maths/Vectors/Vec2.h"

#include <unordered_map>

namespace yami
{
	class InputManager
	{
	public:
		static bool toggle(GLFWwindow* window, int key);
		static bool press(GLFWwindow* window, int key);
		static bool release(GLFWwindow* window, int key);
		static bool click(GLFWwindow* window, int key);

		static Vec2 getMousePosition(GLFWwindow* window);
		static bool mousePress(GLFWwindow* window, int key);
		static bool mouseRelease(GLFWwindow* window, int key);
		static bool mouseToggle(GLFWwindow* window, int key);
		static bool mouseClick(GLFWwindow* window, int key);

		static bool isKeyActive(int key);

	private:
		// Return false if already in list.
		static bool addKey(int key); 
		// Return false if already set.
		static bool setType(int key, int type);
		/* 
			This holds the key id, activated bool and a type id.
			The type id has its first bit reserved for additional information.
		*/
		static std::unordered_map<int, std::pair<bool, int>> keyMap;
	};
}

#endif
