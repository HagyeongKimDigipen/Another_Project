/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Purpose: Laser header file
Project: CS230
Author: Kevin Wright
Creation date: 5/27/2020
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"

class GameObjectManager;
enum class GameObjectType;

class Laser : public GameObject {
public:
	Laser(Vector2D pos, double rotation, Vector2D scale, Vector2D laserVelocity);
	void Update(double dt) override;
	std::string GetObjectTypeName() { return "Lazer"; }
	virtual GameObjectType GetObjectType() override;
private:
};