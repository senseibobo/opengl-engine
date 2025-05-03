#include "Game.h"
#include "PhysicsRectangleShape.h"


std::vector<std::shared_ptr<GameObject>> gameObjects;

std::shared_ptr<GameObject> Game::AddObject()
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObjects.push_back(gameObject);
	return gameObject;
}

void Game::Start()
{
	InitInput();
	InitGame();
	FMOD::Sound* sound;
	std::shared_ptr<Sound> sound1 = Sound::CreateSound("audio/second_region.wav", true, 2.0);
	sound1->PlaySound();
	for (auto& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Game::Idle(float deltaTime)
{
	for (std::shared_ptr<GameObject> gameObject : gameObjects)
	{
		gameObject->Process(deltaTime);
	}
	glutPostRedisplay();
}

void Game::Physics(float deltaTime)
{
	for (std::shared_ptr<GameObject> gameObject : gameObjects)
	{
		gameObject->PhysicsProcess(deltaTime);
	}
}

void Game::Draw()
{
	for (auto gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}

void Game::Reset()
{
	gameObjects.clear();
	Game::InitGame();
}

void Game::AddPlayer()
{
	std::shared_ptr<GameObject> player = AddObject();
	std::shared_ptr<Player> playerComponent = std::make_shared<Player>();
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	std::shared_ptr<Camera> cameraComponent = std::make_shared<Camera>();
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	player->AddComponent(spriteComponent);
	player->AddComponent(collisionComponent);
	player->AddComponent(playerComponent);
	player->AddComponent(cameraComponent);
	std::shared_ptr<Transform> transform = player->GetTransform();
	transform->SetPosition(Vector2(400, 600));
	transform->SetScale(Vector2(0.02, 0.07));

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionShape->SetSize(texture->GetSize());
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
	cameraComponent->UpdateView();
}

void Game::AddGround(Vector2 position, Vector2 scale)
{
	scale *= (Vector2(1920, 1080) / Vector2(40, 40));
	std::shared_ptr<GameObject> ground = AddObject();
	std::shared_ptr<Transform> transform = ground->GetTransform();
	transform->SetPosition(position);
	transform->SetScale(scale);
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	spriteComponent->SetTiled(true);
	spriteComponent->SetTileSize(Vector2(40, 40));
	ground->AddComponent(collisionComponent);
	ground->AddComponent(spriteComponent);

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
	
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/brickTile.png");
	collisionShape->SetSize(texture->GetSize());
}

void Game::AddButton(Vector2 position, Vector2 size, std::string text)
{
	std::shared_ptr<GameObject> button = AddObject();
	std::shared_ptr<Button> buttonComponent = std::make_shared<Button>();
	button->AddComponent(buttonComponent);
	buttonComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	buttonComponent->SetAnchors(0.5, 0.5, 0.5, 0.5);
	buttonComponent->SetOffsets(-100, 100, 40, -40);
}

void Game::InitGame()
{
	AddPlayer();
	AddGround(Vector2(40.0, 1763.0), Vector2(0.04166666790843, 3.26481485366821)); // BigWallRight
	AddGround(Vector2(760.0, 1762.0), Vector2(0.04166666790843, 3.26296305656433)); // BigWallLeft
	AddGround(Vector2(400.0, 32.0), Vector2(0.41666665673256, 0.05925925821066)); // FloorMain
	AddGround(Vector2(600.0, 300.0), Vector2(0.125, 0.03703703731298)); // Platform1
	AddGround(Vector2(200.0, 500.0), Vector2(0.125, 0.03703703731298)); // Platform2
	AddGround(Vector2(620.0, 740.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform3
	AddGround(Vector2(640.0, 940.0), Vector2(0.08333333581686, 0.03703703731298)); // Platform4
	AddGround(Vector2(120.0, 1420.0), Vector2(0.04166666790843, 0.03703703731298)); // Platform5
	AddGround(Vector2(360.0, 1660.0), Vector2(0.04166666790843, 0.03703703731298)); // Platform6
	AddGround(Vector2(200.0, 1940.0), Vector2(0.125, 0.03703703731298)); // Platform7
	AddGround(Vector2(620.0, 1940.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform8
	AddGround(Vector2(620.0, 2100.0), Vector2(0.10416666418314, 0.03703703731298)); // Platform9
	AddGround(Vector2(100.0, 2140.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform10
	AddGround(Vector2(340.0, 2300.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform11
	AddGround(Vector2(580.0, 2500.0), Vector2(0.02083333395422, 0.03703703731298)); // Platform12
	AddGround(Vector2(360.0, 980.0), Vector2(0.04166666790843, 0.25925925374031)); // Wall1
	AddGround(Vector2(580.0, 1100.0), Vector2(0.02083333395422, 0.25925925374031)); // Wall2
	AddButton(Vector2(300, 300), Vector2(100,30), "Play");
}

void Game::InitInput()
{
	Input::AddInputAction("move_left", -GLUT_KEY_LEFT);
	Input::AddInputAction("move_right", -GLUT_KEY_RIGHT);
	Input::AddInputAction("jump", ' ');
	Input::AddInputAction("reset", 'r');
}
