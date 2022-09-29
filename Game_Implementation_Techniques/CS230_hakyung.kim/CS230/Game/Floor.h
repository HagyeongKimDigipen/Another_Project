/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.h
Purpose: Floor header file
Project: CS230
Author: Kevin Wright
Creation date: 5/4/2020
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"

class Floor : public GameObject {
public:
	Floor(RectInt rect);
	void Update(double) override;
	void Draw(TransformMatrix displayMatrix) override;
	std::string GetObjectTypeName() override;
	virtual GameObjectType GetObjectType() override; 
private:
};