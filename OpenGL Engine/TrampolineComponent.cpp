#include "TrampolineComponent.h"
#include "GameObject.h"
#include "Player.h"



void TrampolineComponent::Start()
{
	sprite = GetGameObject()->GetComponent<Sprite>().get();
}

void TrampolineComponent::Process(float delta)
{
	if (!on)
	{
		respawnTimer -= delta;
		if (respawnTimer <= 0.0)
			TurnOn();
	}
	else
	{
		if (Player::Instance->GetGameObject()->GetTransform()->GetPosition()
				.DistanceTo(GetGameObject()->GetTransform()->GetPosition()) < 20.0f)
		{
			Player::Instance->AddVelocity(Vector2(0, 1100.0));
			TurnOff();
			respawnTimer = 3.0f;
		}
	}
}

void TrampolineComponent::TurnOn()
{
	on = true;
	sprite->SetVisible(true);
}

void TrampolineComponent::TurnOff()
{
	on = false;
	sprite->SetVisible(false);
}
