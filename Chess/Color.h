#pragma once
//American spelling used to avoid confusion in the project
class Color {
	//32 bit value to pack four 8 bit colour values into
	unsigned int packedCol;
public:
	Color() = default;
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		:
		packedCol(r << 24u | g << 16 | b << 8 | a)
	{}
	Color(unsigned char r, unsigned char g, unsigned char b)
		:
		packedCol(r << 24u | g << 16 | b << 8 | 255)
	{}
};