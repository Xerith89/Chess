#pragma once
#include <utility>
#include <stack>
#include <bitset>

class Input {

	friend class Window;

public:
	Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	~Input() = default;

private:
	
	int x, y;
	bool leftPressed = false;
	bool rightPressed = false;
	
	std::bitset<256> keyCodes;
	void OnMseLeftClick(int x, int y);
	void OnMseRightClick(int x, int y);
	void OnMseMove(int new_x, int new_y);
	void OnKeyPress(unsigned int keycode);
	void OnKeyRelease(unsigned int keycode);
public:
	std::pair<int, int> GetPos()const;
	int GetMseX()const;
	int GetMseY()const;
	bool LeftMsePressed()const;
	bool RightMsePressed()const;
	bool KbdKeyPressed(unsigned char keycode);
	bool KbdKeyReleased(unsigned char keycode);
};
