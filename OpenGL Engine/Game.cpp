#include "Game.h"
#include "GameObject.h"

// Start method
void Game::Start()
{
    InitInput();
    InitGame();
    scene->Start();

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

// NewScene method: Fixed to prevent access violations
Scene* Game::NewScene()
{
    // Check if a scene is already created. If it exists, reset it properly.
    if (scene)
    {
        // Ensure any existing scene is cleaned up properly
        scene->Destroy();
        scene.reset();  // Reset the shared pointer to avoid dangling references.
    }

    // Create a new scene safely
    scene = std::make_shared<Scene>();
    Scene::SetCurrent(scene.get());

    return scene.get();
}

// Initialize the game
void Game::InitGame()
{
    NewScene();
    SetMainMenuScene();
}

// Input initialization
void Game::InitInput()
{
    Input::AddInputAction("move_left", -GLUT_KEY_LEFT);
    Input::AddInputAction("move_right", -GLUT_KEY_RIGHT);
    Input::AddInputAction("jump", ' ');
    Input::AddInputAction("reset", 'r');
}

// Set the Main Menu Scene
void Game::SetMainMenuScene()
{
    NewScene(); // Always ensure a fresh scene is created

    // Add button and set callback for scene change
    std::shared_ptr<Button> buttonComponent = scene->AddButton(Vector2(400, 300), Vector2(100, 30), "Play", [this]() {
        if (!this) {
            std::cerr << "Error: 'this' is invalid (nullptr)" << std::endl;
        }
        if (!scene) {
            std::cerr << "Error: scene is invalid (nullptr)" << std::endl;
        }

        // Set the scene change logic
        pendingSceneChange = [this]() {
            if (!this) {
                std::cerr << "Error: 'this' is invalid (nullptr) during scene change" << std::endl;
            }
            SetGameScene();
            };
        });

    // Create and position the camera
    std::shared_ptr<GameObject> camera = scene->AddObject();
    std::shared_ptr<Camera> cameraComponent = std::make_shared<Camera>();
    camera->AddComponent(cameraComponent);
    camera->GetTransform()->SetPosition(Vector2(400, 300));
    scene->Start();
}

// Set the Game Scene
void Game::SetGameScene()
{
    NewScene();

    // Add player and ground objects
    scene->AddPlayer(Vector2(600, 300));
    scene->AddGround(Vector2(40.0, 1763.0), Vector2(0.04166666790843, 3.26481485366821)); // BigWallRight
    scene->AddGround(Vector2(760.0, 1762.0), Vector2(0.04166666790843, 3.26296305656433)); // BigWallLeft
    scene->AddGround(Vector2(400.0, 32.0), Vector2(0.41666665673256, 0.05925925821066)); // FloorMain
    scene->AddGround(Vector2(600.0, 300.0), Vector2(0.125, 0.03703703731298)); // Platform1
    scene->AddGround(Vector2(200.0, 500.0), Vector2(0.125, 0.03703703731298)); // Platform2
    scene->AddGround(Vector2(620.0, 740.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform3
    scene->AddGround(Vector2(640.0, 940.0), Vector2(0.08333333581686, 0.03703703731298)); // Platform4
    scene->AddGround(Vector2(120.0, 1420.0), Vector2(0.04166666790843, 0.03703703731298)); // Platform5
    scene->AddGround(Vector2(360.0, 1660.0), Vector2(0.04166666790843, 0.03703703731298)); // Platform6
    scene->AddGround(Vector2(200.0, 1940.0), Vector2(0.125, 0.03703703731298)); // Platform7
    scene->AddGround(Vector2(620.0, 1940.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform8
    scene->AddGround(Vector2(620.0, 2100.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform9
    scene->AddGround(Vector2(100.0, 2140.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform10
    scene->AddGround(Vector2(340.0, 2300.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform11
    scene->AddGround(Vector2(580.0, 2500.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform12
    scene->AddGround(Vector2(360.0, 980.0), Vector2(0.04166666790843, 0.25925925374031)); // Wall1
    scene->AddGround(Vector2(580.0, 1100.0), Vector2(0.02083333395422, 0.25925925374031)); // Wall2
    scene->Start();
}
