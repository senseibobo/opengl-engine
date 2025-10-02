#include "CheckpointComponent.h"
#include "GameObject.h"
#include <fstream>

void CheckpointComponent::PhysicsProcess(float deltaTime)
{
    if (saved) return;
	Vector2 checkpointPosition = GetGameObject()->GetTransform()->GetPosition();
	Vector2 playerPosition = Player::Instance->GetGameObject()->GetTransform()->GetPosition();
	if (checkpointPosition.DistanceTo(playerPosition) < 10.0f)
	{
        saved = true;
        std::ofstream file("savegame.txt");
        if (file.is_open())
        {
            file << playerPosition.x << " " << playerPosition.y;
            file.close();
            std::cout << "Checkpoint saved at: " << playerPosition.x << ", " << playerPosition.y << std::endl;
        }
	}
}
