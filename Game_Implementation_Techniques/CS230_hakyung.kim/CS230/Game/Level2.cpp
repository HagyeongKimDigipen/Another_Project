/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Purpose: Source file for Level 2
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#include <string>

#include "../Engine/Engine.h"        //Engine::GetGameStateManager
#include "../Engine/Camera.h"

#include "Level2.h"
#include "Ship.h"
#include "Meteor.h"
#include "Score.h"

Level2::Level2() : levelReload(Input::KeyboardButton::R), levelNext(Input::KeyboardButton::Enter), debugCollision(Input::KeyboardButton::Escape), ship(nullptr) {}

void Level2::Load() {
	components.AddComponent(new HitParticles());
	components.AddComponent(new MeteorBitsParticles());
	components.AddComponent(new Score());
	components.AddComponent(new Camera(nullptr, { 0,0 }));

	Engine::GetGameObjectManager().Add(new Meteor());
	Engine::GetGameObjectManager().Add(new Meteor());
	Engine::GetGameObjectManager().Add(new Meteor());
	Engine::GetGameObjectManager().Add(new Meteor());
	Engine::GetGameObjectManager().Add(new Meteor());
	ship = new Ship({ Engine::GetWindow().GetSize() / 2.0 });
	Engine::GetGameObjectManager().Add(ship);
}

void Level2::Update(double dt) {
	Engine::GetGameObjectManager().UpdateAll(dt);

	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().Shutdown();
	}
	if (debugCollision.IsKeyReleased() == true) {
		Engine::Instance().ShowCollision(!Engine::Instance().ShowCollision());
	}
}

void Level2::Unload() {
	components.Clear();
	ship = nullptr;
}

void Level2::Draw() {
	if (Engine::Instance().ShowCollision() == true) {
		Engine::GetWindow().Clear(0xF4C0FFFF);
	}
	else {
		Engine::GetWindow().Clear(0x000000FF);
	}

	Camera* cameraPtr = components.GetComponent<Camera>();
	Engine::GetGameObjectManager().DrawAll(cameraPtr->GetCameraMatrix());

	Vector2DInt winSize = Engine::GetWindow().GetSize();
	Engine::Instance().DrawText(0, { 10, winSize.y - 75 }, "Score: " + std::to_string(components.GetComponent<Score>()->GetScore()));

	if (ship->IsDead() == true) {
		Engine::Instance().DrawText(0, winSize / 2 + Vector2DInt{ 0, 30 }, "Game Over", SpriteFont::Justified::CenterX);
		Engine::Instance().DrawText(0, winSize / 2 + Vector2DInt{ 0, -30 }, "Press r to restart", SpriteFont::Justified::CenterX);
	}
}