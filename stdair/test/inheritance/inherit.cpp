// STL
#include <cassert>
#include <iostream>
#include <string>

// ////////////////////////////////////
typedef unsigned int Size_T;
typedef std::pair<Size_T, Size_T> RectangleSize_T;

// ////////////////////////////////////
/** Rectangle */
struct Rectangle {

  /** Constructor */
  Rectangle (const Size_T& iWidth, const Size_T& iHeight)
    : _width (iWidth), _height (iHeight) { }
  /** Destructor */
  virtual ~Rectangle () { }
  
  /** Get the size. */
  RectangleSize_T getSize() const {
    return RectangleSize_T (_width, _height);
  }

  /** Display. When the object is actually inherits from Rectangle,
      the display() method actually called is the one of the
      inheriting object. */
  virtual void display () const {
    std::cout << "Hello, I am a rectangle of size (" << _width << " x "
              << _height << ")" << std::endl;
  }

  // //////// Attributes /////////
  /** Width, Height */
  Size_T _width;
  Size_T _height;
};

/** Square */
struct Square : public Rectangle {

  /** Constructor */
  Square (const Size_T& iWidth) : Rectangle (iWidth, iWidth) { }
  /** Destructor */
  virtual ~Square () { }
  
  /** Get the size. That method overshadows the Rectangle::getSize() one. */
  Size_T getSize() const {
    return _width;
  }
  
  /** Display */
  void display () const {
    std::cout << "Hello, I am a square of size (" << _width << ")"
              << std::endl;
  }
};


// ////////// M A I N //////////////
int main (int argc, char* argv[]) {

  Square lSquare (10);
  lSquare.display();
  const Size_T& lSquareSize = lSquare.getSize();
  std::cout << " and my size is: " << lSquareSize << std::endl;

  Rectangle& lRectangle = lSquare;
  lRectangle.display();
  const RectangleSize_T& lRectangleSize = lRectangle.getSize();
  std::cout << " and my size is: " << lRectangleSize.first << " x "
            << lRectangleSize.second << std::endl;
  
  Rectangle lRectangleCopy = lSquare;
  lRectangleCopy.display();
  const RectangleSize_T& lRectangleCopySize = lRectangleCopy.getSize();
  std::cout << " and my size is: " << lRectangleCopySize.first << " x "
            << lRectangleCopySize.second << std::endl;
  
  return 0;
}
