#include "GameCamera.h"
#include "Transform.h"
#include "GameObject.h"

void GameCamera::Process(float deltaTime)
{
	std::shared_ptr<Transform> transform = GetGameObject()->GetTransform();
	int oldLevel = level;
	level = ((int)transform->GetPosition().y) / 600;
	if (oldLevel != level)
	{
		UpdateView();
	}
}

void GameCamera::UpdateView()
{
	Rect2 cameraRect;
	cameraRect.position = Vector2(0, level * View::GetCameraRect().size.y);
	cameraRect.size = Vector2(800, 600);
	std::cout << "cameraRect:" << cameraRect.position.x << ", " << cameraRect.position.y << ", " << cameraRect.size.x << ", " << cameraRect.size.y << "\n";
	View::SetCameraRect(cameraRect);
}
