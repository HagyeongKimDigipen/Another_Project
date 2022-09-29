/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input_Doodle.cpp
Purpose: Interface between doodle and our engine
Project: CS230
Author: Kevin Wright
Creation date: 3/17/2020
-----------------------------------------------------------------*/

#include "doodle/input.hpp"	//doodle::KeyboardButtons
#include "Input.h"
#include "Engine.h"			// Logger, Input

Input::KeyboardButton DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return Input::KeyboardButton::Enter;
	} else if (button == doodle::KeyboardButtons::Escape) {
		return Input::KeyboardButton::Escape;
	} else if (button == doodle::KeyboardButtons::Space) {
		return Input::KeyboardButton::Space;
	} else if (button == doodle::KeyboardButtons::Left) {
		return Input::KeyboardButton::Left;
	} else if (button == doodle::KeyboardButtons::Right) {
		return Input::KeyboardButton::Right;
	} else if (button == doodle::KeyboardButtons::Up) {
		return Input::KeyboardButton::Up;
	} else if (button == doodle::KeyboardButtons::Down) {
		return Input::KeyboardButton::Down;
	} else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<Input::KeyboardButton>(static_cast<int>(Input::KeyboardButton::A) + offset);
	}
	return Input::KeyboardButton::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	Input::KeyboardButton button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::KeyboardButton::None) {
		Engine::GetLogger().LogEvent("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) {
	Input::KeyboardButton button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::KeyboardButton::None) {
		Engine::GetLogger().LogEvent("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}