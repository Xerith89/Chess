#pragma once
#include "MyWindows.h"
#include <string>
#include <memory>
#include "Graphics.h"
#include <fstream>

class Sprite {
public:
	Sprite(const std::string Filename);
	~Sprite();
	Sprite(Sprite&&) = default;
	Sprite(const Sprite& sprite) = delete;
	Sprite operator=(const Sprite&) = delete;
	void RecordColor(int x, int y, Color c);
private:
	int width;
	int height;
	std::unique_ptr<Color[]> pColorPixels;
};