#pragma once
#include "Rect2.h"
class View
{
public:
	View() = delete;
	static void SetViewportRect(Rect2 rect);
	static void SetCameraRect(Rect2 rect);
	static Rect2 GetViewportRect();
	static Rect2 GetCameraRect();

private:
	static Rect2 viewportRect;
	static Rect2 cameraRect;
};

