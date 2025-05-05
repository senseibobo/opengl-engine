#include "Camera.h"
#include "GameObject.h"

Camera* Camera::currentCamera = nullptr;

void Camera::SetCurrent()
{
	current = true;
	currentCamera = this;
}

Camera* Camera::GetCurrentCamera()
{
	return currentCamera;
}

void Camera::Process(float deltaTime)
{
	UpdateView();
}

void Camera::UpdateView()
{
	Rect2 cameraRect;
	cameraRect.position = Vector2(0, 0);
	cameraRect.size = Vector2(800, 600);
	View::SetCameraRect(cameraRect);
}
