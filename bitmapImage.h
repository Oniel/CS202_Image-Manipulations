//Oniel Toledo   Assignmnent 08   CS202

#ifndef H_BITMAP_IMAGE_HEADER
#define H_BITMAP_IMAGE_HEADER

#include <cmath>
#include <string>

using namespace std;

//class bitmapImage;

/**
A class for working with the Windows Bitmap File Format.
This supports bit depths of 16, 24, and 32 with uncompressed pixel data.

This does not support compressed bitmaps or bit depths of 1,4, or 8.  
 Compression is rarely used with this file format, though.

 Colors can be specified in RGB format (red, green, and blue intensity values)
 Red, Green, Blue colors range from 0-255 (0 -> off to 255 -> full intensity)
 For red, it would be (255, 0, 0) and in hex, (0xff0000).
	As a single value, 0xff0000 is 16,711,680
 For green, it would be (0, 255, 0) and in hex, (0x00ff00).
	As a single value, 0x00ff00 is 65,280
 */

class bitmapImage
{
private:
	int width, height;
	int **pixelData;
	void freePixelData();

public:
	bitmapImage();
	// create empty bitmap object

	bitmapImage(const string filename);
	// create bitmap object from file 'filename'.

	bitmapImage(int w, int h);
	// create empty bitmap object of size width by height

	virtual ~bitmapImage();
	// destructor

	void setSize(int width, int height);
	// set (for empty object) bitmap size

	bool loadFromBitmapFile(const string filename);
	// loads uncompressed bitmaps with colour depths of
	//  16,24, and 32 returns true, if successfully loaded
	//  and returns false otherwise.

	void saveToBitmapFile(const string filename) const;
	// saves bitmaps using 24 bit colour depth (typical default)

	void saveToBitmapFile(const string fn, int bitDepth) const;
	// saves using the specified depth of 16, 24, or 32

	int getHeight() const;
	// get bitmap object height

	int getWidth() const;
	// get bitmap object width

	int getRed(int colour) const;
	// get 'red' part of color value

	int getGreen(int colour) const;
	// get 'green' part of color value

	int getBlue(int colour) const;
	// get 'blue' part of color value

	int getColorForRGB(int red, int green, int blue) const;
	// convert red, green, and blue values to single color value

	int getPixel(int x, int y) const;
	// get contents of (x,y) in image map

	void setPixel(int x, int y, int colour);
	// set contents of (x,y) in image map with specified color

	void fillWith(int colour);
	// set contents of entire image map with specified color

	void fillRect(int left, int top, int width, int height, int colour);
	// set contents of rectangle within image map with specified color

	void setPixelRGB(int x, int y, int red, int green, int blue);
	// set contents of (x,y) in image map with specified color in RGB format

};

#endif

