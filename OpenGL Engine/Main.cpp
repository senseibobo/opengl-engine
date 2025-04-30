#pragma once
#include <stdlib.h>
#include <chrono>
#include "glut.h"
#include "Game.h"
#include "View.h"


#define PHYSICS_INTERVAL 1

// game related stuff


// time
auto start_time = std::chrono::high_resolution_clock::now();
long long elapsed_ms = 0;
long long elapsed_physics_ms = 0;
float lastDeltaTime = 0.00001f;
float lastPhysicsDeltaTime = 0.000001f;


std::unique_ptr<Game> game;


void Keyboard(unsigned char k, int x, int y)
{
	Input::KeyPressed((int)k, true);
}
void KeyboardUp(unsigned char k, int x, int y)
{
	Input::KeyPressed((int)k, false);
}
void Special(int k, int x, int y)
{
	Input::KeyPressed(-k, true);
}
void SpecialUp(int k, int x, int y)
{
	Input::KeyPressed(-k, false);
}

void Idle() {
	long long old_elapsed_ms = elapsed_ms;
	auto elapsed = std::chrono::high_resolution_clock::now() - start_time;
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
	float deltaTime = (elapsed_ms - old_elapsed_ms) / 1000.0;
	lastDeltaTime = deltaTime;
	game->Idle(deltaTime);
}

void Physics(int n) {
	long long old_elapsed_ms = elapsed_physics_ms;
	auto elapsed = std::chrono::high_resolution_clock::now() - start_time;
	elapsed_physics_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
	float deltaTime = (elapsed_physics_ms - old_elapsed_ms) / 1000.0;
	lastPhysicsDeltaTime = deltaTime;
	game->Physics(deltaTime);
	glutTimerFunc(PHYSICS_INTERVAL, Physics, 0);
}

void InitOpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	game->Draw();

	glutSwapBuffers();
}

void ResizeWindow(int width, int height)
{
	int viewportWidth;
	int viewportHeight;
	if (width > height * 4 / 3)
	{
		viewportHeight = height;
		viewportWidth = height * 4 / 3;
	}
	else
	{
		viewportWidth = width;
		viewportHeight = width * 3 / 4;
	}
	View::SetViewportRect(Rect2(
			Vector2(width / 2.0 - viewportWidth / 2.0, height / 2.0 - viewportHeight / 2.0),
			Vector2(viewportWidth, viewportHeight)
		));

}

int main(int argc, char** argv)
{
	game = std::make_unique<Game>();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Unity clone");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ResizeWindow);
	glutTimerFunc(PHYSICS_INTERVAL, Physics, 0);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
	InitOpenGL();
	game->Start();
	glutMainLoop();
	return 0;
}