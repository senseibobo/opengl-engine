#include "Input.h"

std::unordered_map<const char*, std::vector<int>> Input::inputMap;
std::unordered_map<int, bool> Input::keys;


void Input::KeyPressed(int key, bool down)
{
	std::cout << "key pressed " << key << "\n";
	auto iter = keys.find(key);
	if (iter != keys.end())
	{
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
	bool pressed = false;
	std::vector<int>& mapKeys = inputMap[name];
	for (auto key : mapKeys)
	{
		if (keys[key]) return true;
	}
	return false;
}

int Input::GetAxis(const char* name1, const char* name2)
{
	return GetAction(name2) - GetAction(name1);
}
