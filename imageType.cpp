//Oniel Toledo   Assignment 08   CS202
//The following file is an implementation file for the imageType class.
//Since the base class (bitmapImage) has much of the functionality that 
//the functions bellow need, there will be several calls the base function.
//The functions bellow take into account that the bitmapImage class has already
//read and stored a read bitmapImage, given this, the functions in imageType only
//perform image manipulations such as rotation, cropping, and resizing of the  
//two dimensional array. The colorToBW, smooth, brightness, and RGBshift functions
//change the value of the pixels in the image with the help of the functions in
//the base class. Each function also performs appropriate error checking

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include "bitmapImage.h"
#include "imageType.h"
using namespace std;

//imageType class constructor, parameters passed in are the file name, width, height, and image title values
//the constructor using the bitmapImage constructor also performs error checking for a valid file name
imageType::imageType(string fname, int w, int h, string imgtitle):bitmapImage(w, h){
if(fname !=""){//if fname is not set to default
    if(!loadFromBitmapFile(fname))//check and see if the file exists already, if not
        cout << "Error, unable to open" << fname << "." << endl;//display an error
    else//else, if file does exist store the fname into the class variable filename
       fileName = fname;
    }
 title= imgtitle;//store the passed image, if any
}


//******************************************************************************************
//function for converting images into black and white format
void imageType::colorToBW(){
  if(getWidth() !=0 || getHeight() !=0){
    for(int y=0; y<getHeight();y++){
      for(int x=0; x<getWidth();x++){//for an value x in row y...
            int cl =getPixel(x, y);//store the color value in pixel x,y of the image as cl
            int r  =getRed(cl);//store the red part of the color value
            int g  =getGreen(cl);//green
            int b  = getBlue(cl);//blue
            int nc = (r+g+b)/3;//add all three color values and divide by three store as nc
            setPixelRGB(x, y, nc, nc, nc);//set the current x,y pixel value to nc for R,G,B
            }
    }
  }
  else
    cout << "Error, invalid image size, color will not be changed to black and white" << endl;
}


//******************************************************************************************  
//function for smoothing an image, smoothing will be based on the average values for red,
//green, and blue in a 5 pixel radius. A new array is temporarily created and stores the values
//of the now smoothed pixel value, the original is kept the same for comparison purposes.
//after the smoothing has finished replace the original image with the temp and destroy the temp
void imageType::smooth(){
  //need two images, the original and anothor temporary file so the original can look at    
  //at the image's original pixels, to do this another object will be created   
  
  //create a new object temp with an x,y grid size specified by the current class 
  //object's x,y coordinates (getWidth(),getHeight())
  if(getWidth() !=0 || getHeight() !=0){
    bitmapImage temp(getWidth(), getHeight());
    for(int y=5;y<getHeight()-5;y++){
      for(int x=5;x<getWidth()-5;x++){//for pixel x in row y
	int cl =getPixel(x,y);//get the color value of pixel x,y
	int r =getRed(cl);//store red value 
	int g =getGreen(cl);//green value
	int b =getBlue(cl);//blue value
	for(int j=(y-5);j<(y+5);j++){
	  for(int i=(x-5);i<(x+5);i++){
	    cl =getPixel(i,j);//get pixel value for i,j
	    r +=getRed(cl);//add the red value from the red values in a 5 pixel radius
	    g +=getGreen(cl);//add the green value from the green values in a 5 pixel radius
	    b +=getBlue(cl);//add the blue value from the blue values in a 5 pixel radius
	  }
	}//end of secondary loop for radius
	r /= pow(11,2);//n = (2*radius+1)^2
	g /= pow(11,2);
	b /= pow(11,2);
	temp.setPixelRGB(x, y, r, g, b);//replay the pixel with the new r,g,b values
	cl=0;
	r=0;
	g=0;
	b=0;
      }
    }//end of main for loop
    
    //now replace the original image's pixel data with the new pixels created in the temp object
    for(int k=0;k<getHeight();k++){
      for(int h=0;h<getWidth();h++)
	setPixel(h, k, temp.getPixel(h, k));
    }
  }//end of if statement
  else
    cout << "Error, invalid image size, image will not be smoothed" << endl;
}


//******************************************************************************************  
//resizing function, will resize a valid image to a ratio of the original image's width
//divided by the new passed width
void imageType::resize(int w, int h){
  if(w <0 || h <0 || w >W_MAX || h >H_MAX)//if passed new values are not within range
    cout << "Error, invalid re-size parameters." << endl;
  else
    if(getHeight()!=0 && getWidth()!=0){
    bitmapImage  temp(w, h);//create a temporary object with passed sizes w,h
    //calculate and store the ratios between the new and old width and height
    double xRatio = static_cast<double>(getWidth())/static_cast<double>(w);
    double yRatio = static_cast<double>(getHeight())/static_cast<double>(h);
    
    for(int y=0; y<h; y++){
      for(int x=0; x<w; x++){
	int oldX = floor(x*xRatio);//oldX is the pixel that should be used for pixel w in temp
	int oldY = floor(y*yRatio);
	
	int oldPixelVal = getPixel(oldX, oldY);//get the pixel value for location oldX,oldY
	temp.setPixel(x, y, oldPixelVal);//store OldPixelVal, in the temp object w,h location

      }
    }     
    
    //set the size of the current class object by changing the width/height bitmap variables to w/h
    bitmapImage::setSize(w, h);
    
    //now deep copy temp object to the class object
    for(int y=0; y<getHeight(); y++)
      for(int x=0; x<getWidth(); x++)
	setPixel(x, y, temp.getPixel(x, y));

  }//end of else statement
    else//else, not image, output error message
      cout << "Error, no image to convert to resize." << endl;
}


//******************************************************************************************  
//function to resize the image based on the passed percentage (passed as 'ratio')
//the function works much the same way as the resize(double) function except the percentage
//is used rather than the ratio formula from the resize(double) function.
void imageType::resize(double ratio){
  if(ratio <= 0)
    cout << "Error, invalid re-size parameters." << endl;
  else
    if(getHeight()!=0 && getWidth()!=0 && ratio > 0.0){
      //need to convert ratio to a percentage form of x.xx
      ratio *= 0.01;//if percentage was set to 75% 75*0.01= 0.75, this is the desired format
      int newWidth = static_cast<int>(floor(getWidth()*ratio));//determine width for image resizing
      int newHeight= static_cast<int>(floor(getHeight()*ratio));//deterime height for image resizing
      //use newWidth and newHeight to create a temporary object
      bitmapImage temp(newWidth, newHeight);
      
      for(int y=0; y<newHeight; y++){
	for(int x=0; x<newWidth; x++){
	  //for the temp image, to find what x,y coordinates to use calculate
	  //which x,y coordinates from the original image should be used
	  int oldX = static_cast<int>(floor(x*ratio));
	  int oldY = static_cast<int>(floor(y*ratio));
	  //obtain the pixel value for the original image
	  int oldPixelVal =getPixel(oldX, oldY);
	  temp.setPixel(x, y, oldPixelVal);//set the x,y cell to the pixel value 'cl'
	}
    }
      //need to deep copy the temp image over to the original image
      bitmapImage::setSize(newWidth, newHeight);//set new size
      for(int y=0; y<newHeight; y++)
	for(int x=0; x<newWidth; x++)
	  setPixel(x, y, temp.getPixel(x, y));//set the pixel value of x,y to the value in the temp x,y

    }
    else
      cout << "Error, no image to convert to resize" << endl;
}


//******************************************************************************************  
//function for manipulating image brightness, based on percentage, if the passed parameters are
//invalid or if there is no image to be manipulate output error message accordingly
void imageType::brightness(double prcnt){
  if(prcnt < -100.0 || prcnt > 100.0)
    cout << "Error, invalid brightness percentage." << endl;
  else
    if(getHeight()==0 ||getWidth()==0)
      cout << "Error, no image to perform brightness change." << endl;
    else{//else the passed values are good, adjust the image.
      for(int y=0; y <getHeight(); y++){
	for(int x=0; x <getWidth(); x++){
	  int cl = getPixel(x, y);//store pixel value
	  int red = getRed(cl);//store red part of the pixel value
	  int green = getGreen(cl);//store the green part of the pixel value
	  int blue = getBlue(cl);
	  //create a new color value for red, green, and blue
	  int newRed = static_cast<int>(red * (1.0 + (prcnt/100.0)));
	  int newGreen = static_cast<int>(green * (1.0 + (prcnt/100.0)));
	  int newBlue = static_cast<int>(blue * (1.0 + (prcnt/100.0)));
	  //if calculated values for RGB are above 255 or below 0, set them to 255 or 0 accordingly
	  if(newRed > 255)
	    newRed =255;
	  if(newRed < 0)
	    newRed =0;
	  if(newGreen > 255)
	    newGreen =255;
	  if(newGreen < 0)
	    newGreen =0;
	  if(newBlue > 255)
	    newBlue =255;
	  if(newBlue < 0)
	    newBlue =0;
	  //replace pixel from image at x,y
	  bitmapImage::setPixelRGB(x, y, newRed, newGreen, newBlue);
	}
      }
    }
}


//******************************************************************************************  
//function for shifting the color hue by the passed colorShift color enum value.
//For any given RGB choice as a tint, the other 2 will be set to 0.
void imageType::RGBshift(color colorShift){
  if(getHeight()==0 || getWidth()==0)
    cout << "Error, no image to convert to color shift." << endl;
  else{
    if(colorShift == RED){//for color shift towards red tint
      for(int y=0; y<getHeight(); y++){
	for(int x=0; x<getWidth(); x++){
	  int cl = getPixel(x, y);
	  int red = getRed(cl);//read and store the red part of the pixel value
	  int green = getGreen(cl);//read and store the green part of the pixel value
	  int blue = getBlue(cl);//read and store the blue part of the pixel value
	  int newRed = (red-blue)+(red-green);//formula for calculating an appropriate red value
	  bitmapImage::setPixelRGB(x, y, newRed, 0, 0);}}//store the newly calculated red, and the other two to 0
    }
    else//for color shift towards green tint
      if(colorShift == GREEN){
	for(int y=0; y<getHeight();y++){
	  for(int x=0; x<getWidth(); x++){
	    int cl = getPixel(x, y);
	    int red = getRed(cl);
	    int green = getGreen(cl);
	    int blue = getBlue(cl);
	    int newGreen = (green-blue)+(green-red);
	    bitmapImage::setPixelRGB(x, y, 0, newGreen, 0);}}//set to a green hue
      }
      else//for color shift towards blue tint
	if(colorShift == BLUE){
	  for(int y=0; y<getHeight();y++){
	    for(int x=0; x<getWidth(); x++){
	      int cl = getPixel(x, y);
	      int red = getRed(cl);
	      int green = getGreen(cl);
	      int blue = getBlue(cl);
	      int newBlue = (blue-red)+(blue-green);
	      bitmapImage::setPixelRGB(x, y, 0, 0, newBlue);}}//set to a blue hue
	}
    
  }//end of if statement
}


//******************************************************************************************  
//function for rotating the the image based on passed degrees and an optional background color.
//if any of the parameters are invalid or if the image size is invalid output error message
//else convert degrees to radians, perform calculations needed to determine the new width and
//height of for a to be created temporary object, store rotated pixel data in the temp object,
//and finally deep copy temp object back to the original object
void imageType::rotate(double degrees, int background)
{
  if(getHeight()==0 || getWidth()==0)
    cout << "Error, no image to rotate." << endl;
  else
    if(degrees < -180.0 || degrees > 180.0)
      cout << "Error, invalid rotation percentage." << endl;
    else
      if(background < 0 || background > 16777215)
	cout << "Error, invalid background color." << endl;
      else{//all other possibilities are valid, rotate the image
	double radians = ((2*acos(-1)*degrees)/360);
	//calculations needed to dermine  minx,miny,maxx,maxy, and the newWidth and newHeight values
	int x1 = static_cast<int>(-(getHeight()*(sin(radians))));
	int y1 = static_cast<int>(getHeight()*(cos(radians)));
	int x2 = static_cast<int>(getWidth()*(cos(radians))-getHeight()*(sin(radians)));
	int y2 = static_cast<int>(getHeight()*(cos(radians))+getWidth()*(sin(radians)));
	int x3 = static_cast<int>(getWidth()*(cos(radians)));
	int y3 = static_cast<int>(getWidth()*(sin(radians)));
	int minx = min(0, min(x1, min(x2, x3)));
	int miny = min(0, min(y1, min(y2, y3)));
	int maxx = max(x1, max(x2, x3));
	int maxy = max(y1, max(y2, y3));
	int newWidth = maxx - minx;
	int newHeight = maxy - miny;

	//create a new object with the new size parameters       
	bitmapImage temp(newWidth, newHeight);
	temp.fillWith(background);//fill in the background color

	for(int y=0; y<newHeight; y++)
	  for(int x=0; x<newWidth; x++){
	    int sourceX = static_cast<int>((x+minx)*(cos(radians))+(y+miny)*(sin(radians)));
	    int sourceY = static_cast<int>((y+miny)*(cos(radians))-(x+minx)*(sin(radians)));
	    //if sourceX and sourceY are within the range of the original image do the following
	    if(sourceX>0 && sourceX<getWidth() && sourceY>0 && sourceY<getHeight()){
	      int cl = getPixel(sourceX, sourceY);//get pixel data from location sourceX,sourceY
	      //if(cl!=0)
	      temp.setPixel(x, y, cl);
	    }
	  }//end of for loop
	
	//resize the original class object to the temp's dimensions
	bitmapImage::setSize(newWidth, newHeight);
	//copy the temp object array values back into the original object's array
	for(int y=0; y<newHeight; y++)
	  for(int x=0; x<newWidth; x++){
	    int cl = temp.getPixel(x, y); 
	    bitmapImage::setPixel(x, y, cl);
	    }
      }//end of else statement
}


//******************************************************************************************  
//function for cropping a given image, the image will be cropped via the points passed  throught
//the function, the function also provides error checking and does not crop if either the 
//passed parameters or the image is invalid
void imageType::crop(int x1, int y1, int x2, int y2){
  //first three if statements are for error checking if parameters and getHeight,getWidth can pass
  //throught these three statements then it has good parameters and the image is valid
  if((x1<0||x1>getWidth())||(x2<0||x2>getWidth())||(y1<0 ||y1>getHeight())||(y2<0||y2>getHeight()))
    cout << "Error, invalid crop points." << endl;
  else
    if(x1>x2 || y1>y2)
      cout << "Error, invalid crop parameters." << endl;
    else
      if(getHeight()==0 || getWidth()==0)//for invalid image size
	cout << "Error, no image to crop." << endl;
      else{//for all other possibilities, good parameters have been passed
	//first determine the new width and height of the to be cropped image
	//create a temporary object with these sizes.
	int newWidth = x2-x1;
	int newHeight = y2-y1;
	bitmapImage temp(newWidth, newHeight);
	//starting at x1 until x2 is reached get the pixel at x,y...
	for(int y=y1; y<=y2; y++)
	  for(int x=x1; x<=x2; x++){
	    int cl = getPixel(x, y);
	    int newX = x-x1;//subtract the current x by the x1 to be plotted in the temp object
	    int newY = y-y1;
	    temp.setPixel(newX, newY, cl);//plot pixel data in temp
	  }
	//resize class object
	bitmapImage::setSize(newWidth, newHeight);
	for(int y=0; y<newHeight; y++)//replace the contents in the class object with the temp objects
	  for(int x=0; x<newWidth; x++){//pixel data
	    int cl = temp.getPixel(x, y);//get temp pixel data
	    bitmapImage::setPixel(x, y, cl);//replace object pixel data at x,y with cl
	  }
      }//end of else for valid image and parameters
}
