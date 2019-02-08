#pragma once

class Color {
	unsigned int packedCol;
public:
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		:
		packedCol(r << 24u | g << 16 | b << 8 | a)
	{}
};