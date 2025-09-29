#include "Input.h"
#include "Game.h"

std::unordered_map<const char*, std::vector<int>> Input::inputMap;
std::unordered_map<int, bool> Input::keys;
std::unordered_map<int, bool> Input::keysJustPressed;
std::unordered_map<int, bool> Input::keysJustReleased;


void Input::KeyPressed(int key, bool down)
{
	std::cout << "key pressed " << key << "\n";
	auto iter = keys.find(key);
	if (iter != keys.end())
	{
		std::cout << "naso sam ga\n";
		if (down && !keys[key]) keysJustPressed[key] = true;
		else if(!down && keys[key]) keysJustReleased[key] = true;
		keys[key] = down;
	}
}

void Input::AddInputAction(const char* name, int key)
{
	auto iter = inputMap.find(name);
	if (iter == inputMap.end())
	{
		inputMap[name] = std::vector<int>();
	}
	inputMap[name].push_back(key);
	
	auto iter2 = keys.find(key);
	if (iter2 == keys.end())
	{
		keys[key] = false;
		keysJustPressed[key] = false;
		keysJustReleased[key] = false;
	}
}

int Input::GetAction(const char* name)
{
	auto iter = inputMap.find(name);
	if (iter == inputMap.end())
	{
		std::cout << "ERROR: Action name not found\n";
		return 0;
	}

	std::vector<int>& mapKeys = inputMap[name];
	for (auto key : mapKeys)
	{
		if (keys[key]) return true;
	}
	return false;
}

int Input::GetActionPressed(const char* name)
{
	auto iter = inputMap.find(name);
	if (iter == inputMap.end())
	{
		std::cout << "ERROR: Action name not found\n";
		return 0;
	}

	std::vector<int>& mapKeys = inputMap[name];
	for (auto key : mapKeys)
	{
		if (keysJustPressed[key]) return true;
	}
	return false;
}

int Input::GetActionReleased(const char* name)
{
	auto iter = inputMap.find(name);
	if (iter == inputMap.end())
	{
		std::cout << "ERROR: Action name not found\n";
		return 0;
	}

	std::vector<int>& mapKeys = inputMap[name];
	for (auto key : mapKeys)
	{
		if (keysJustReleased[key]) return true;
	}
	return false;
}

int Input::GetAxis(const char* name1, const char* name2)
{
	return GetAction(name2) - GetAction(name1);
}

void Input::ResetPressedReleased()
{
	for (auto& pair : keysJustPressed) pair.second = false;
	for (auto& pair : keysJustReleased) pair.second = false;
}
