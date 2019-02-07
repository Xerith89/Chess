#pragma once
#include "Input.h"

void Input::OnMseLeftClick(int x, int y)
{
	if (inWindow){leftPressed = true;}
}

void Input::OnMseRightClick(int x, int y)
{
	if (inWindow) { rightPressed = true; }
}

void Input::OnMseLeftRelease(int x, int y)
{
	if (inWindow) { leftPressed = false; }
}

void Input::OnMseRightRelease(int x, int y)
{
	if (inWindow) { rightPressed = false; }
}

void Input::OnMseMove(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}

void Input::OnMseWheel(int x, int y, int delta)
{
	if (inWindow)
	{
		wheelDelta += delta;
		if (wheelDelta >= 120)
		{
			wheelDelta -= 120;
		}
		if (wheelDelta <= -120)
		{
			wheelDelta += 120;
		}
	}
}

void Input::OnMseLeave()
{
	inWindow = false;
}

void Input::OnMseEnter()
{
	inWindow = true;
}

void Input::OnKeyPress(unsigned int keycode)
{
	keyCodes[keycode] = true;
}

void Input::OnKeyRelease(unsigned int keycode)
{
	keyCodes[keycode] = false;
}

void Input::ResetKeyboard()
{
	keyCodes.reset();
}

void Input::OnCharPress(unsigned int keycode)
{
	if (charBuffer.size() != maxCharBufferSize)
	{
		charBuffer.push(static_cast<char>(keycode));
	}
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

bool Input::InWindow() const
{
	return inWindow;
}

int Input::GetWheelDelta() const
{
	return wheelDelta;
}
