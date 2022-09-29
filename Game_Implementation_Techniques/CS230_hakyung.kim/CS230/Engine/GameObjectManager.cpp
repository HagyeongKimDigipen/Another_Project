/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: GameObject header file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#pragma once
#include "Engine.h"
#include "TransformMatrix.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Collision.h"

void GameObjectManager::Add(GameObject* obj) {
	gameObjects.push_back(obj);
}

void GameObjectManager::Unload() {
	Engine::GetLogger().LogEvent("Clear Game Objects");
	for (GameObject* obj : gameObjects) {
		delete obj;
	}
	gameObjects.clear();
}

void GameObjectManager::UpdateAll(double dt) {
	std::list<GameObject*> destroyList;
	for (GameObject* object : gameObjects) {
  		object->Update(dt);
		if (object->ShouldDestroy() == true) {
			destroyList.push_back(object);
		}
	}
	for (GameObject* object : destroyList) {
		gameObjects.remove(object);
		delete object;
	}
}

void GameObjectManager::DrawAll(TransformMatrix& cameraMatrix) {
	for (GameObject* object : gameObjects) { 
  		object->Draw(cameraMatrix);
	} 
}

void GameObjectManager::CollideTest() {
	for (GameObject* objectA : gameObjects) {
		for (GameObject* objectB : gameObjects) {
			if (objectA != objectB && objectA->CanCollideWith(objectB->GetObjectType())) {
				if (objectA->DoesCollideWith(objectB)) {
 					Engine::GetLogger().LogEvent("Collision Detected: " + objectA->GetObjectTypeName() + " and " + objectB->GetObjectTypeName());
					objectA->ResolveCollision(objectB);
				}
			}
		}
	}
}