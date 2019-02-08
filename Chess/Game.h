#pragma once
#include "Graphics.h"
#include "Input.h"
#include "Sprite.h"

class Game {
private:
	Window& wnd;
	Graphics gfx;
	void Render();
	void Update();
public:
	Game(Window& wnd);
	~Game() = default;
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;
	void Run();
};
