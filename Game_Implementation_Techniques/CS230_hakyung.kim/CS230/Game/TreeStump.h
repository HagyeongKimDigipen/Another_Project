#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class TreeStump : public GameObject {
public:
	TreeStump(Vector2D pos, int size);
	GameObjectType GetObjectType() { return GameObjectType::TreeStump; }
	std::string GetObjectTypeName() override { return "Tree Stump"; }
private:
};