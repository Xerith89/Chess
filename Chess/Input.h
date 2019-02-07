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
	int wheelDelta = 0;
	bool leftPressed = false;
	bool rightPressed = false;
	bool inWindow = false;
	unsigned int maxCharBufferSize = 256u;
	std::stack<char> charBuffer;
	std::bitset<256> keyCodes;
	void OnMseLeftClick(int x, int y);
	void OnMseRightClick(int x, int y);
	void OnMseLeftRelease(int x, int y);
	void OnMseRightRelease(int x, int y);
	void OnMseMove(int new_x, int new_y);
	void OnMseWheel(int x, int y, int delta);
	void OnMseLeave();
	void OnMseEnter();
	void OnKeyPress(unsigned int keycode);
	void OnKeyRelease(unsigned int keycode);
	void ResetKeyboard();
	void OnCharPress(unsigned int keycode);
public:
	std::pair<int, int> GetPos()const;
	int GetMseX()const;
	int GetMseY()const;
	bool LeftMsePressed()const;
	bool RightMsePressed()const;
	bool KbdKeyPressed(unsigned char keycode);
	bool KbdKeyReleased(unsigned char keycode);
	bool InWindow()const;
	int GetWheelDelta()const;
};
