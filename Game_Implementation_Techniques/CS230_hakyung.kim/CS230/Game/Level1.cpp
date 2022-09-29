/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Purpose: Source file for Level 1
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#include <string>
#include <iostream>
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/Camera.h"

#include "Screens.h"
#include "Level1.h"
#include "Hero.h"
#include "Ball.h"
#include "Bunny.h"
#include "treeStump.h"
#include "Floor.h"
#include "Exit.h"
#include "Gravity.h"
#include "Score.h"
#include "Background.h"

const double Gravity::gravity = 1875;

Level1::Level1() : levelReload(Input::KeyboardButton::R), levelNext(Input::KeyboardButton::Enter),
					debugCollision(Input::KeyboardButton::Escape), lives(3) { }

void Level1::Load() {
	timer = 120;

	double floor = 127;

	Engine::GetGameObjectManager().Add(new Ball({ 600, floor }));
	Engine::GetGameObjectManager().Add(new Ball({ 2700, floor }));
	Engine::GetGameObjectManager().Add(new Ball({ 4800, floor }));
	Engine::GetGameObjectManager().Add(new Bunny({ 1000, floor }));
	Engine::GetGameObjectManager().Add(new Bunny({ 2000, floor }));
	Engine::GetGameObjectManager().Add(new Bunny({ 3200, floor }));
	Engine::GetGameObjectManager().Add(new Bunny({ 3800, floor }));
	Engine::GetGameObjectManager().Add(new TreeStump({ 300, floor }, 3));
	Engine::GetGameObjectManager().Add(new TreeStump({ 1200, floor }, 2));
	Engine::GetGameObjectManager().Add(new TreeStump({ 2200, floor }, 1));
	Engine::GetGameObjectManager().Add(new TreeStump({ 2800, floor }, 5));
	Engine::GetGameObjectManager().Add(new TreeStump({ 5100, floor }, 5));
	Engine::GetGameObjectManager().Add(new Floor({ {0, 0}, {1471, static_cast<int>(floor)} }));
	Engine::GetGameObjectManager().Add(new Floor({ {1636, 0}, {4262, static_cast<int>(floor)} }));
	Engine::GetGameObjectManager().Add(new Floor({ {4551, 0}, {5760, static_cast<int>(floor)} }));
	Engine::GetGameObjectManager().Add(new Exit({ {5550, static_cast<int>(floor)}, {5760, 683} }));
	heroPtr = new Hero({ 100, floor - 0.1 });
	Engine::GetGameObjectManager().Add(heroPtr);
	
	components.AddComponent(new Camera(heroPtr, { 0,0 }));
	Background* bgPtr = new Background();
	components.AddComponent(bgPtr);
	bgPtr->Add("assets/clouds.png", 4);
	bgPtr->Add("assets/moutains.png", 2);
	bgPtr->Add("assets/foreground.png", 1);
	components.AddComponent(new Gravity());
	components.AddComponent(new Score());
}

void Level1::Update(double dt) {
	Engine::GetGameObjectManager().UpdateAll(dt);
	timer -= dt;
	if (timer <= 0 || heroPtr->IsDead() == true) {
		if (lives > 0) {
			lives--;
			Engine::GetGameStateManager().ReloadState();
		}
		else {
			Engine::GetGameStateManager().SetNextState(LEVEL2);
		}
	}

	components.GetComponent<Camera>()->Update();

	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(LEVEL2);
	}
	if (debugCollision.IsKeyReleased() == true) {
		Engine::Instance().ShowCollision(!Engine::Instance().ShowCollision());
	}
}

void Level1::Unload() {
	components.Clear();
	heroPtr = nullptr;
}

void Level1::Draw() {
	Engine::GetWindow().Clear(0x3399DAFF);

	Camera* cameraPtr = components.GetComponent<Camera>();
	components.GetComponent<Background>()->Draw(cameraPtr->GetCameraPosition());
	Engine::GetGameObjectManager().DrawAll(cameraPtr->GetCameraMatrix());

	Vector2DInt winSize = Engine::GetWindow().GetSize();
	Engine::Instance().DrawText(0, { 10, winSize.y - 75 }, "Lives: " + std::to_string(lives));
	unsigned int score = components.GetComponent<Score>()->GetScore();
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	Engine::Instance().DrawText(0, { winSize.x / 2, winSize.y - 75 }, scoreString, SpriteFont::Justified::CenterX);
	Engine::Instance().DrawText(0, { winSize.x - 10, winSize.y - 75 }, "Time: " + std::to_string(static_cast<int>(timer)), SpriteFont::Justified::Right);
}