#include "View.h"
#include "glut.h"

Rect2 View::viewportRect;
Rect2 View::cameraRect;

void View::SetViewportRect(Rect2 rect)
{
	viewportRect = rect;
	glViewport(rect.position.x, rect.position.y, rect.size.x, rect.size.y);
	glMatrixMode(GL_PROJECTION);
}

void View::SetCameraRect(Rect2 rect)
{
	cameraRect = rect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(
		rect.position.x, rect.position.x + rect.size.x, 
		rect.position.y, rect.position.y + rect.size.y
	);
	glMatrixMode(GL_MODELVIEW);
}

Rect2 View::GetViewportRect()
{
	return viewportRect;
}

Rect2 View::GetCameraRect()
{
	return cameraRect;
}
