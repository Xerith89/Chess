#pragma once
#include "Input.h"

void Input::OnKeyPress(unsigned int keycode)
{
	keyCodes[keycode] = true;
}

void Input::OnKeyRelease(unsigned int keycode)
{
	keyCodes[keycode] = false;
}

std::pair<int, int> Input::GetPos() const
{
	return std::pair<int, int>(x,y);
}

int Input::GetMseX() const
{
	return x;
}

int Input::GetMseY() const
{
	return y;
}

bool Input::LeftMsePressed() const
{
	return leftPressed;
}

bool Input::RightMsePressed() const
{
	return rightPressed;
}

bool Input::KbdKeyPressed(unsigned char keycode)
{
	return keyCodes[keycode];
}

bool Input::KbdKeyReleased(unsigned char keycode)
{
	return keyCodes[keycode];
}
