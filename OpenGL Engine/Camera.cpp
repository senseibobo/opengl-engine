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
	std::shared_ptr<Transform> transform = GetGameObject()->GetTransform();
	int oldLevel = level;
	level = ((int)transform->GetPosition().y) / 600;
	if (oldLevel != level)
	{
		UpdateView();
	}
}

void Camera::UpdateView()
{
	Rect2 cameraRect;
	cameraRect.position = Vector2(0, level*View::GetCameraRect().size.y);
	cameraRect.size = Vector2(800,600);
	std::cout << "cameraRect:" << cameraRect.position.x << ", " << cameraRect.position.y << ", " << cameraRect.size.x << ", " << cameraRect.size.y << "\n";
	View::SetCameraRect(cameraRect);
}
