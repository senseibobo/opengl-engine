#pragma once
#include "Component.h"
#include "Sprite.h"
class TrampolineComponent :
    public Component
{
public:
    void Start() override;
    void Process(float delta) override;
    void TurnOn();
    void TurnOff();
private:
    Sprite* sprite;
    bool on = false;
    float respawnTimer = 0.0f;
};

