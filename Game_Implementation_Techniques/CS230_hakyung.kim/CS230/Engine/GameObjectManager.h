/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.h
Purpose: GameObjectManager header file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#pragma once

#include <list>
#include "GameObject.h"

class GameObjectManager {
public:
	void Add(GameObject* obj);
	void Unload();

	void UpdateAll(double dt);
	void DrawAll(TransformMatrix& cameraMatrix);
	std::list<GameObject*>::iterator begin() { return gameObjects.begin(); }
	std::list<GameObject*>::iterator end() { return gameObjects.end(); }
	void CollideTest();
	void Remove(GameObject* obj) {
		gameObjects.remove(obj);
	}
private:
	std::list<GameObject*> gameObjects;
};