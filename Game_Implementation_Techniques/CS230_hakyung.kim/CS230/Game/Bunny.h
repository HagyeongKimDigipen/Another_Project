/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.h
Purpose: Bunny header file
Project: CS230
Author: hakyung.kim
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Bunny : public GameObject 
{
public:
	Bunny(Vector2D pos);
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override { return "Bunny"; }
	void ResolveCollision(GameObject* collideWith) override;
private:
	bool isDead;
};