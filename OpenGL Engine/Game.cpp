#include "Game.h"
#include "GameObject.h"

// Start method
void Game::Start()
{
    InitInput();
    InitGame();

    FMOD::Sound* sound;
    std::shared_ptr<Sound> sound1 = Sound::CreateSound("audio/second_region.wav", true, 2.0);
    sound1->PlaySound();
}

// Idle method
void Game::Idle(float deltaTime)
{
    if (pendingSceneChange)
    {
        pendingSceneChange();
        pendingSceneChange = nullptr;
        return;
    }

    for (std::shared_ptr<GameObject> gameObject : scene->GetGameObjects())
    {
        gameObject->Process(deltaTime);
    }

    glutPostRedisplay();
}

// Physics method
void Game::Physics(float deltaTime)
{
    for (std::shared_ptr<GameObject> gameObject : scene->GetGameObjects())
    {
        gameObject->PhysicsProcess(deltaTime);
    }
}

// Draw method
void Game::Draw()
{
    for (auto gameObject : scene->GetGameObjects())
    {
        gameObject->Draw();
    }
}

Scene* Game::NewScene()
{
    std::cout << "Checking if a scene already exists\n";
    if (scene)
    {
        std::cout << "Scene already exists, removing\n";
        scene->Destroy();
        scene.reset(); 
    }
    else
        std::cout << "Scene didn't exist\n";

    scene = std::make_shared<Scene>();
    Scene::SetCurrent(scene.get());

    return scene.get();
}

void Game::InitGame()
{
    SetMainMenuScene();
}

void Game::InitInput()
{
    Input::AddInputAction("move_left", -GLUT_KEY_LEFT);
    Input::AddInputAction("move_right", -GLUT_KEY_RIGHT);
    Input::AddInputAction("jump", ' ');
    Input::AddInputAction("reset", 'r');
}

void Game::SetMainMenuScene()
{
    NewScene();

    std::shared_ptr<Button> buttonComponent = scene->AddButton(Vector2(400, 300), Vector2(100, 30), "Play", [this]() {
        pendingSceneChange = [this]() {
            if (!this) {
                std::cerr << "Error: 'this' is invalid (nullptr) during scene change" << std::endl;
            }
            SetGameScene();
            };
        });

    std::shared_ptr<GameObject> camera = scene->AddObject();
    std::shared_ptr<Camera> cameraComponent = std::make_shared<Camera>();
    camera->AddComponent(cameraComponent);
    camera->GetTransform()->SetPosition(Vector2(400, 300));
    scene->Start();
}

void Game::SetGameScene()
{
    NewScene();
    std::cout << "NEW SCENE\n";

    scene->AddPlayer(Vector2(600, 300));
    scene->AddGround(Vector2(-40.0, 2999.0), Vector2(0.04166666790843, 4.44444465637207)); // BigWallRight
    scene->AddGround(Vector2(840.0, 2999.0), Vector2(0.04166666790843, 4.44444465637207)); // BigWallLeft
    scene->AddGround(Vector2(100.0, 699.0), Vector2(0.10416666418314, 0.18518517911434)); // Ground1
    scene->AddGround(Vector2(360.0, 639.0), Vector2(0.16666667163372, 0.07407407462597)); // Ground2
    scene->AddGround(Vector2(680.0, 739.0), Vector2(0.16666667163372, 0.25925925374031)); // Ground3
    scene->AddGround(Vector2(160.0, 1099.0), Vector2(0.125, 0.03703703731298)); // Ground4
    scene->AddGround(Vector2(620.0, 1259.0), Vector2(0.1875, 0.03703703731298)); // Ground5
    scene->AddGround(Vector2(620.0, 1259.0), Vector2(0.1875, 0.03703703731298)); // Ground6
    scene->AddGround(Vector2(568.0, 1552.0), Vector2(0.125, 0.28148147463799)); // Ground7
    scene->AddGround(Vector2(160.0, 1672.0), Vector2(0.16666667163372, 0.05925925821066)); // Ground8
    scene->AddGround(Vector2(96.0, 1736.0), Vector2(0.16666667163372, 0.05925925821066)); // Ground9
    scene->AddGround(Vector2(32.0, 1800.0), Vector2(0.16666667163372, 0.05925925821066)); // Ground10
    scene->AddGround(Vector2(-32.0, 1864.0), Vector2(0.16666667163372, 0.05925925821066)); // Ground11
    scene->AddGround(Vector2(-96.0, 1928.0), Vector2(0.16666667163372, 0.05925925821066)); // Ground12
    scene->AddGround(Vector2(432.0, 2216.0), Vector2(0.11666666716337, 0.05925925821066)); // Ground13
    scene->AddGround(Vector2(712.0, 2384.0), Vector2(0.09166666865349, 0.13333334028721)); // Ground14
    scene->AddGround(Vector2(192.0, 2584.0), Vector2(0.20000000298023, 0.05925925821066)); // Ground15
    scene->AddGround(Vector2(464.0, 2696.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground16
    scene->AddGround(Vector2(672.0, 2840.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground17
    scene->AddGround(Vector2(304.0, 2920.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground18
    scene->AddGround(Vector2(112.0, 3144.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground19
    scene->AddGround(Vector2(400.0, 3224.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground20
    scene->AddGround(Vector2(608.0, 3400.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground21
    scene->AddGround(Vector2(128.0, 3512.0), Vector2(0.0166666675359, 0.02962962910533)); // Ground22
    scene->AddGround(Vector2(656.0, 3592.0), Vector2(0.15000000596046, 0.05925925821066)); // Ground23
    scene->AddGround(Vector2(80.0, 3976.0), Vector2(0.08333333581686, 0.11851851642132)); // Ground24
    scene->AddGround(Vector2(200.0, 3760.0), Vector2(0.00833333376795, 0.13333334028721)); // Ground25
    scene->AddGround(Vector2(296.0, 3728.0), Vector2(0.00833333376795, 0.10370370000601)); // Ground26
    scene->AddGround(Vector2(672.0, 3976.0), Vector2(0.13333334028721, 0.05925925821066)); // Ground27
    scene->AddGround(Vector2(72.0, 4336.0), Vector2(0.02500000037253, 0.04444444552064)); // Ground28
    scene->AddGround(Vector2(312.0, 4400.0), Vector2(0.02500000037253, 0.04444444552064)); // Ground29
    scene->AddGround(Vector2(552.0, 4512.0), Vector2(0.02500000037253, 0.04444444552064)); // Ground30
    scene->AddGround(Vector2(680.0, 4720.0), Vector2(0.02500000037253, 0.04444444552064)); // Ground31
    scene->AddGround(Vector2(408.0, 5000.0), Vector2(0.19166666269302, 0.02962962910533)); // Ground32

    scene->Start();
}
