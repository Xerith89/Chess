#include "Sprite.h"

Sprite::Sprite(const std::string Filename)
{
	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;

	std::ifstream file(Filename, std::ios::binary);
	if (file.fail()) { throw "Bad File Name"; }

	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	width = bmInfoHeader.biWidth;

	const bool i32bit = bmInfoHeader.biBitCount == 32;

	int yStart;
	int yEnd;
	int yDir;
	
	if (bmInfoHeader.biHeight < 0)
	{
		height = -bmInfoHeader.biHeight;
		yEnd = height;
		yStart = 0;
		yDir = 1;
	}
	else
	{
		height = bmInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		yDir = -1;
	}
	
	pColorPixels = std::make_unique<Color[]>(width*height);

	file.seekg(bmFileHeader.bfOffBits);
	
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += yDir)//y for loop
	{
		for (int x = 0; x < width; x++) //x loop
		{
			const unsigned char b = file.get(); //bitmap colour channels are loaded weirdly
			const unsigned char g = file.get();
			const unsigned char r = file.get();
			RecordColor(x, y, Color(r, g, b)); //set our pixel in the array by calling our Surface putpixel function
			if (i32bit) //32bit image?
			{
				file.seekg(1, std::ios::cur);//move on by 1
			}
		}
		if (!i32bit)//if not
		{
			file.seekg(padding, std::ios::cur); //apply our padding
		}
		file.seekg(padding, std::ios::cur);//apply padding again
	}
}

Sprite::~Sprite()
{
	pColorPixels.release();
}

void Sprite::RecordColor(int x, int y, Color c)
{
	pColorPixels.get()[y*width + x] = c;
}

