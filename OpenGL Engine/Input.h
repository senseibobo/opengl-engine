#pragma once
#include <unordered_map>
#include <iostream>
#include "glut.h"
class Input
{
public:
	Input() = delete;
	static void KeyPressed(int key, bool down);
	static void AddInputAction(const char* name, int key);
	static int GetAction(const char* name);
	static int GetAxis(const char* name1, const char* name2);
private:
	static std::unordered_map<const char*, std::vector<int>> inputMap;
	static std::unordered_map<int, bool> keys;
};