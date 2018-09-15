#include "InputManager.h"

#include "InputConfig.h"

std::unordered_map<int, std::pair<bool, int>> yami::InputManager::keyMap = std::unordered_map<int, std::pair<bool, int>>();

bool yami::InputManager::toggle(GLFWwindow* window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_TOGGLE);
	if (glfwGetKey(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first ^= 1;
	}
	else if (glfwGetKey(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	return keyMap[key].first;
}

bool yami::InputManager::press(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_PRESS);
	return keyMap[key].first = glfwGetKey(window, key) == GLFW_PRESS;
}

bool yami::InputManager::release(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_RELEASE);
	return keyMap[key].first = glfwGetKey(window, key) != GLFW_PRESS;
}

bool yami::InputManager::click(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_CLICK);
	if (glfwGetKey(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first = true;
		return true;
	}
	else if (glfwGetKey(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	keyMap[key].first = false;
	return false;
}

yami::Vec2 yami::InputManager::getMousePosition(GLFWwindow * window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return Vec2((float)x, (float)y);
}

bool yami::InputManager::mousePress(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_PRESS);
	return keyMap[key].first = glfwGetMouseButton(window, key) == GLFW_PRESS;
}

bool yami::InputManager::mouseRelease(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_RELEASE);
	return keyMap[key].first = glfwGetMouseButton(window, key) != GLFW_PRESS;
}

bool yami::InputManager::mouseToggle(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_TOGGLE);
	if (glfwGetMouseButton(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first ^= 1;
	}
	else if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	return keyMap[key].first;
}

bool yami::InputManager::mouseClick(GLFWwindow * window, int key)
{
	addKey(key);
	setType(key, YAMI_KEY_CLICK);
	if (glfwGetMouseButton(window, key) != GLFW_PRESS && (keyMap[key].second & 1) == 1)
	{
		keyMap[key].second &= ~(keyMap[key].second & 1);
		keyMap[key].first = true;
		return true;
	}
	else if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		keyMap[key].second |= 1;
	keyMap[key].first = false;
	return false;
}

bool yami::InputManager::isKeyActive(int key)
{
	return keyMap[key].first;
}

bool yami::InputManager::addKey(int key)
{
	if (keyMap.find(key) == keyMap.end())
	{
		keyMap.insert({ key, {false, YAMI_KEY_CLICK} });
		return true;
	}
	return false;
}

bool yami::InputManager::setType(int key, int type)
{
	if ((keyMap[key].second & (0xFF-1)) != type)
	{
		keyMap[key].second = type;
		keyMap[key].first = false; // Reset active
		return true;
	}
	return false;
}
