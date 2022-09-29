/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: Source file for Input Modle
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include "Input.h"
#include "Engine.h"		//Input

Input::Input() {
	keyDown.resize(static_cast<int>(KeyboardButton::Count));
	wasKeyDown.resize(static_cast<int>(KeyboardButton::Count));
}

bool Input::IsKeyDown(KeyboardButton key) const {
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyUp(KeyboardButton key) const {
	return keyDown[static_cast<int>(key)] == false;
}

bool Input::IsKeyReleased(KeyboardButton key) const {
	return keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true;
}

void Input::SetKeyDown(KeyboardButton key, bool value) { 
	keyDown[static_cast<int>(key)] = value; 
}

void Input::Update() {
	wasKeyDown = keyDown;
}

Input::InputKey::InputKey(KeyboardButton button) : button(button) {}

bool Input::InputKey::IsKeyDown() const {
	return Engine::GetInput().IsKeyDown(button);
}

bool Input::InputKey::IsKeyReleased() const {
	return Engine::GetInput().IsKeyReleased(button);
}
