#include "Sprite.h"

Sprite::Sprite(const std::string Filename)
{
	//Window struct declaration
	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;

	//Try to load a file using the filename, if not, throw an exception
	std::ifstream file(Filename, std::ios::binary);
	if (file.fail()) { throw std::runtime_error("Bad File Name"); }

	//Reintepret as char pointers to fill the structs
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	width = bmInfoHeader.biWidth;

	//Check if we have a 32bit or 24bit image
	const bool i32bit = bmInfoHeader.biBitCount == 32;

	int yStart;
	int yEnd;
	int yDir;
	
	//Bitmaps sometimes start height at 0 and then goes into negative numbers, if it is, we want to reverse that
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
	//Allocate some memory for the pixel colors
	pColorPixels = std::make_unique<Color[]>(width*height);
	//Seek to the pixel color data
	file.seekg(bmFileHeader.bfOffBits);
	//Work out the padding for the alignment of the bits
	const int padding = (4 - (width * 3) % 4) % 4;
	//Start our loop through the image data and store the colors
	for (int y = yStart; y != yEnd; y += yDir)//y for loop
	{
		for (int x = 0; x < width; x++) //x loop
		{
			const unsigned char b = file.get(); //bitmap colour channels are loaded weirdly
			const unsigned char g = file.get();
			const unsigned char r = file.get();
			RecordColor(x, y, Color(r, g, b)); //set our pixel in the array by calling our Surface putpixel function
						
			//Padding is different for 32bit and 24bit
			if (i32bit) 
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!i32bit)
		{
			file.seekg(padding, std::ios::cur); 
		}
		file.seekg(padding, std::ios::cur);
	}
}

Sprite::~Sprite()
{
	//ensure our unique pointer is released
	pColorPixels.release();
}

void Sprite::RecordColor(int x, int y, Color c)
{
	//index in to the unique pointer color array and set the color
	pColorPixels.get()[y*width + x] = c;
}

int Sprite::GetWidth()const
{
	return width;
}

int Sprite::GetHeight() const
{
	return height;
}

Color Sprite::GetColor(int x, int y) const
{
	return pColorPixels.get()[y*width + x];
}

