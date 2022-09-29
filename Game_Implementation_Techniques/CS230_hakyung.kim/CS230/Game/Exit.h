/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.h
Purpose: Exit header file
Project: CS230
Author: Kevin Wright
Creation date: 5/4/2020
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Exit : public GameObject {
public:
	Exit(RectInt rect);
	void Update(double) override;
	void Draw(TransformMatrix displayMatrix) override;
	void ResolveCollision(GameObject*) override;
	std::string GetObjectTypeName() { return "Exit"; }
private:
	virtual GameObjectType GetObjectType() override { return GameObjectType::Trigger; }
};