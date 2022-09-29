/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.h
Purpose: Meteor header file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Meteor : public GameObject {
public:
	Meteor();
	Meteor(Meteor& original);
	void Update(double dt) override;
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override { return "Meteor"; }
	void ResolveCollision(GameObject* objectB) override;
	bool CanCollideWith(GameObjectType collideAgainstType) override;
private:
	int health;
	int size;
	bool isDead;
};