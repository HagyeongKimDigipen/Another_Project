/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Purpose: Logic for wrapping an object from one side of the screen to the other
Project: CS230
Author: Kevin Wright
Creation date: 5/31/2020
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"
#include "..\Engine\GameObject.h"
#include "ScreenWrap.h"


void ScreenWrap::TestForWrap() {
	if (object.GetPosition().y > Engine::GetWindow().GetSize().y + object.GetSprite().GetFrameSize().y / 2.0) {
		object.SetPositionY(0 - object.GetSprite().GetFrameSize().y / 2.0);
	} else if (object.GetPosition().y < 0 - object.GetSprite().GetFrameSize().y / 2.0) {
		object.SetPositionY(Engine::GetWindow().GetSize().y + object.GetSprite().GetFrameSize().y / 2.0);
	}
	if (object.GetPosition().x > Engine::GetWindow().GetSize().x + object.GetSprite().GetFrameSize().x / 2.0) {
		object.SetPositionX(0 - object.GetSprite().GetFrameSize().y / 2.0);
	} else if (object.GetPosition().x < 0 - object.GetSprite().GetFrameSize().x / 2.0) {
		object.SetPositionX(Engine::GetWindow().GetSize().x + object.GetSprite().GetFrameSize().x / 2.0);
	}
}