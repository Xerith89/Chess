#pragma once
#include "MyWindows.h"
#include <string>
#include <memory>
#include "Color.h"
#include <fstream>

class Sprite {
public:
	Sprite(const std::string Filename);
	~Sprite();
	Sprite(Sprite&&) = default;
	Sprite(const Sprite& sprite) = delete;
	Sprite operator=(const Sprite&) = delete;
	void RecordColor(int x, int y, Color c);
	int GetWidth()const;
	int GetHeight()const;
	Color GetColor(int x, int y)const;
private:
	int width;
	int height;
	std::unique_ptr<Color[]> pColorPixels;
};