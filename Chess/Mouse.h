#pragma once
#include <utility>

class Mouse {
	friend class Window;
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> GetPos()const;
	int GetX()const;
	int GetY()const;
	bool LeftPressed()const;
	bool RightPressed()const;
	void UpdatePos(int new_x, int new_y);
private:
	int x;
	int y;
	bool leftPressed = false;
	bool rightPressed = false;
};
