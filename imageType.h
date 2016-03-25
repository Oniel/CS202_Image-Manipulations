//Oniel Toledo  Assignmnet 08  CS202
//The following class is a derived class of the base clas bitmapImage
//The class has the ability to perform various array changes such
//as changing the pixel color of each x,y coordinate to black and white
//values, resizing, rotation, and cropping are also performed. The 
//brightness and RGBshift functions work much the same way as the
// colorToBW and are used to brighten or darken the image or change
//a colored image to have only a red, green, or blue hue.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include "bitmapImage.h"
using namespace std;

//enumeration used in the RGBshift function to
//identify which color shift is required
enum color {RED, GREEN, BLUE};

class imageType: public bitmapImage
{
 public:
  //constructor for fileName, width, height, and title
  imageType(string="", int=0, int=0, string="");
  //function to convert a colored image to black and white
  void colorToBW();
  //resizes an image based on a passed percentage
  void resize(double);
  //resizes an image based on the passed width and height
  void resize(int, int);
  //smooth (blurs) an image based on a 5 pixel radius
  void smooth();
  //adjusts pixel value to brighter or darker value
  void brightness(double);
  //shifts the pixel RGB values of an image to either red, green, or blue
  void RGBshift(color);
  //rotates an image based on the passed degree, a background can be 
  //assigned based on the passed int
  void rotate(double, int=0);
  //crops an image given the passe coordinates x1,y1 and x2,y2
  void crop(int, int, int, int);

 private:
  string fileName, title;//image file name and image title
  static const int H_MAX =10000;//maxium height acceptable
  static const int W_MAX =10000;//maximum width acceptable
};
