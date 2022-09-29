/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.h
Purpose: Logic for wrapping an object from one side of the screen to the other
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\Component.h" 

class GameObject;

class ScreenWrap : public Component {
public:
	ScreenWrap(GameObject& object) : object(object) {}
	void TestForWrap();
private:
	GameObject& object;
};