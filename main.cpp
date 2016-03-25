//  CS202 - Provided Main.

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

#include "imageType.h"

using namespace std;

// ********************************************************************************

int main()
{
	string	stars;
	stars.append(60,'*');

	cout << stars << endl;
	cout << "CS 202 - Assignment #8." << endl;
	cout << "Image Manipulation Program." << endl << endl;

// ----------------------------------------------
//  Test for color to B&W function.

	imageType	img0;
	string		fName0 = "image0.bmp";

	cout << "Image Test #0, file: " << fName0 << endl;

	if (!img0.loadFromBitmapFile("null.txt") )
		cout << "Error opening null.txt" << endl;

	if (!img0.loadFromBitmapFile(fName0) ) {
		cout << "Error opening " << fName0 << endl;
	} else {
		img0.colorToBW();
		img0.saveToBitmapFile("T0new"+fName0);
	}

	cout << endl;

// ----------------------------------------------
//  Test for smooth function.

	imageType	img1a, img1b;
	string		fName1a = "image1a.bmp";
	string		fName1b = "image1b.bmp";

	cout << "Image Test #1 A, file: " << fName1a << endl;

	if (!img1a.loadFromBitmapFile(fName1a) ) {
		cout << "Error opening " << fName1a << endl;
	} else {
		img1a.smooth();
		img1a.saveToBitmapFile("T1new"+fName1a);
	}

	cout << "Image Test #1 B, file: " << fName1b << endl;

	if (!img1b.loadFromBitmapFile(fName1b) ) {
		cout << "Error opening " << fName1b << endl;
	} else {
		img1b.smooth();
		img1b.smooth();
		img1b.saveToBitmapFile("T1new"+fName1b);
	}

	cout << endl;

// ----------------------------------------------
//  Tests for resize function.

	imageType	img2;
	string		fName2 = "image2.bmp";

	cout << "Image Test #2 A, file: " << fName2 << endl;

	img2.resize(150, 120);				// error

	if (!img2.loadFromBitmapFile(fName2) ) {
		cout << "Error opening " << fName2 << endl;
	} else {
		img2.resize(1500, -1200);			// error
		img2.resize(-1500, 1200);			// error	
		img2.resize(0.0);				// error

		img2.resize(1500, 1200);
		img2.saveToBitmapFile("T2newA"+fName2);		// larger
	}

	cout << "Image Test #2 B, file: " << fName2 << endl;

	if (!img2.loadFromBitmapFile(fName2) ) {
		cout << "Error opening " << fName2 << endl;
	} else {
		img2.resize(800, 600);
		img2.saveToBitmapFile("T2newB"+fName2);		// smaller
	}

	cout << "Image Test #2 C, file: " << fName2 << endl;

	if (!img2.loadFromBitmapFile(fName2) ) {
		cout << "Error opening " << fName2 << endl;
	} else {
		img2.resize(150.0);
		img2.saveToBitmapFile("T2newC"+fName2);		// larger
	}

	cout << "Image Test #2 D, file: " << fName2 << endl;

	if (!img2.loadFromBitmapFile(fName2) ) {
		cout << "Error opening " << fName2 << endl;
	} else {
		img2.resize(75.0);
		img2.saveToBitmapFile("T2newD"+fName2);		// smaller
	}

	cout << endl;

// ----------------------------------------------
//  Test for brightness function.

	string		fName3 = "image3.bmp";
	cout << "Image Test #3, file: " << fName3 << endl;

	imageType	img3(fName3, 1280, 853, "Zion Canyon");

	img3.brightness(795.0);				// error
	img3.brightness(-395.0);			// error

	img3.brightness(95.0);
	img3.saveToBitmapFile("T3newA"+fName3);

	if (!img3.loadFromBitmapFile(fName3) ) {
		cout << "Error re-opening " << fName3 << endl;
	} else {
		img3.brightness(-35.0);
		img3.saveToBitmapFile("T3newB"+fName3);

		img3.loadFromBitmapFile(fName3);
		img3.brightness(-100.0);
		img3.saveToBitmapFile("T3newC"+fName3);		// total dark
	}

	cout << endl;

// ----------------------------------------------
//  Test for brightness function.

	string		fName4 = "image4.bmp";
	string		fName5 = "image5.bmp";
	string		fName6 = "image6.bmp";
	imageType	img4, img5, img6;

// image 4

	cout << "Image Test #4, file: " << fName4 << endl;

	img4.RGBshift(RED);				// error

	if (!img4.loadFromBitmapFile(fName4) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img4.RGBshift(RED);
		img4.saveToBitmapFile("T4newR"+fName4);
	}

	if (!img4.loadFromBitmapFile(fName4) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img4.RGBshift(GREEN);
		img4.saveToBitmapFile("T4newG"+fName4);
	}

	if (!img4.loadFromBitmapFile(fName4) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img4.RGBshift(BLUE);
		img4.brightness(45.0);
		img4.saveToBitmapFile("T4newB"+fName4);
	}

	cout << endl;

// image 5

	cout << "Image Test #5, file: " << fName5 << endl;

	if (!img5.loadFromBitmapFile(fName5) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img5.RGBshift(RED);
		img5.saveToBitmapFile("T5newR"+fName5);
	}

	if (!img5.loadFromBitmapFile(fName5) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img5.RGBshift(GREEN);
		img5.saveToBitmapFile("T5newG"+fName5);
	}

	if (!img5.loadFromBitmapFile(fName5) ) {
		cout << "Error opening " << fName4 << endl;
	} else {
		img5.RGBshift(BLUE);
		img5.brightness(45.0);
		img5.saveToBitmapFile("T5newB"+fName5);
	}

	cout << endl;

// image 6

	cout << "Image Test #6, file: " << fName6 << endl;

	if (!img6.loadFromBitmapFile(fName6) ) {
		cout << "Error opening " << fName6 << endl;
	} else {
		img6.RGBshift(RED);
		img6.saveToBitmapFile("T6newR"+fName6);
	}

	if (!img6.loadFromBitmapFile(fName6) ) {
		cout << "Error opening " << fName6 << endl;
	} else {
		img6.RGBshift(GREEN);
		img6.saveToBitmapFile("T6newG"+fName6);
	}

	if (!img6.loadFromBitmapFile(fName6) ) {
		cout << "Error opening " << fName6 << endl;
	} else {
		img6.RGBshift(BLUE);
		img6.brightness(45.0);
		img6.saveToBitmapFile("T6newB"+fName6);
	}

	cout << endl;

// ----------------------------------------------
//  Test for rotate function.

	string		fName7 = "image7.bmp";
	imageType	img7;

	cout << "Image Test #7, file: " << fName7 << endl;

	img7.rotate(25.0, 16777215);			// error, no image

	if (!img7.loadFromBitmapFile(fName7) ) {
		cout << "Error opening " << fName7 << endl;
	} else {
		img7.rotate(25.0, 26777215);			// error, bad color
		img7.rotate(25.0, -122310);			// error, bad color
		img7.rotate(225.0, 0);				// error, bad pct
		img7.rotate(-325.0, 0);				// error, bad pct

		img7.rotate(25.0, 16777215);			// right tilt
		img7.saveToBitmapFile("T7newA"+fName7);
	}

	if (!img7.loadFromBitmapFile(fName7) ) {
		cout << "Error opening " << fName7 << endl;
	} else {
		img7.rotate(-25.0, 16777215);			// left tilt
		img7.saveToBitmapFile("T7newB"+fName7);
	}

	if (!img7.loadFromBitmapFile(fName7) ) {
		cout << "Error opening " << fName7 << endl;
	} else {
		img7.rotate(90.0, 0);				// full right tilt
		img7.saveToBitmapFile("T7newC"+fName7);
	}

	cout << endl;

// ----------------------------------------------
//  Test for crop function. 1200 x 827

	string		fName8 = "image8.bmp";
	string		fName9 = "image9.bmp";
	imageType	img8, img9;

	cout << "Image Test #8, file: " << fName8 << endl;

	if (!img8.loadFromBitmapFile(fName8) ) {
		cout << "Error opening " << fName8 << endl;
	} else {
		img8.crop(-450, 36, 1197, 472);			// error, bad crop points
		img8.crop(450, 736, 1197, 472);			// error, bad crop points
		img8.crop(450, 36, 1297, 472);			// error, bad crop points
		img8.crop(450, 36, 1197, 972);			// error, bad crop points
		img8.crop(450, 636, 1197, 472);			// error, bad crop parameters
		img8.crop(950, 36, 897, 472);			// error, bad crop parameters

		img8.crop(450, 36, 1197, 672);			// remove window
		img8.saveToBitmapFile("T8new"+fName8);
	}

	cout << "Image Test #9, file: " << fName9 << endl;

	if (!img9.loadFromBitmapFile(fName9) ) {
		cout << "Error opening " << fName8 << endl;
	} else {
		img9.crop(345, 4, 1194, 675);			// remove person
		img9.saveToBitmapFile("T8new"+fName9);
	}

	cout << endl;

// ----------------------------------------------

	return 0;
}


