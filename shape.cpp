#include "shape.hpp"

/*Introduction Paragraph:
	This program defines the derived classes of the Shape base class, Rectangle, Circle, Sphere, and RectPrism. It reads the shapes that are defined in the input testfiles and constructs a vector of Shape pointers that points to each Rectangle/Circle/Sphere/orRectPrism. Finally, it finds and returns the maximum area and volume of all the shapes in the vector.
*/

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initialize Shape's private variable 
Shape:: Shape(string name){			// make base class constructor
	name_ = name;					// set name_ to name
}

string Shape::getName(){			
	return name_; 					// return name_
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle"){	// Rectangle constructor and initialize width_ and length_
	width_ = width; 
	length_ = length;
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
double Rectangle::getArea() const{
	return length_ * width_;					// return area of length_ * width_
	}
double Rectangle::getVolume() const{
	return 0;									// return a volume of 0
	}
Rectangle Rectangle::operator + (const Rectangle& rec){ 
	Rectangle newrect;							// create new rectangle
	double length = length_ + rec.getLength();	// length is the sum of lengths
	double width = width_ + rec.getWidth(); 	// width is sum of widths
	newrect = Rectangle(width, length);			// set width and length as the parameters for newrect
	return newrect;								// return newrect Rectangle
	}
Rectangle Rectangle:: operator - (const Rectangle& rec){
	Rectangle newrect; 										// create new rectangle
	double length = max(0.0, length_ - rec.getLength());	// length is the difference of lengths
	double width = max(0.0, width_ - rec.getWidth());		// width is the difference of widths
	newrect = Rectangle(width, length);						// set width and length as parameters for newrect
	return newrect;											// return newrect Rectangle
	}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle"){
	radius_ = radius;							// initialize radius_ to radius
	}	
double Circle::getRadius()const{return radius_;}
double Circle::getArea()const{
	double area = M_PI * radius_ * radius_;		// set area to area of a circle
	return area;								// return area
	}
double Circle::getVolume()const{
	return 0; 
	}											// return 0 for volume
Circle Circle:: operator + (const Circle& cir){
	Circle newcirc(0.0);						// initialize a circle
	double radius = radius_ + cir.getRadius();	// radius is the sum of radii
	newcirc = Circle(radius);					// set newcirc to circle w/radius radius
	return newcirc;	
	}
Circle Circle:: operator - (const Circle& cir){
	Circle newcirc(0.0); 									// create new Circle
	double radius = max(0.0, radius_ - cir.getRadius());	// find new radius
	newcirc = Circle(radius);								// set radius as Circle's parameter
	return newcirc;											// return Circle
	}
	
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere"){
	radius_ = radius;							// initialize radius_ to radius
	}	
double Sphere::getRadius()const{return radius_;}
double Sphere::getArea()const{
	double area = M_PI * radius_ * radius_* 4;	// set area to area of a sphere
	return area;
	}
double Sphere::getVolume()const{
	double volume = (4.0/3.0) * radius_ * radius_ * radius_ * M_PI;	
	return volume; 
	}
Sphere Sphere:: operator + (const Sphere& sph){
	Sphere newsphere(0.0);
	double radius = radius_ + sph.getRadius();	// radius is the sum of radii
	newsphere = Sphere(radius);
	return newsphere;
	}
Sphere Sphere:: operator - (const Sphere& sph){
	Sphere newsphere(0.0); 										// create new Circle
	double radius = max(0.0, radius_ - sph.getRadius());		// find new radius
	newsphere = Sphere(radius);									// set radius as Circle's parameter
	return newsphere;											// return Circle
	}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){	// RectPrism constructor and initialize width_,length_, and height_
	width_ = width; 
	length_ = length;
	height_ = height;
}
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
double RectPrism::getArea() const{
	return 2*(length_ * width_ + height_ * length_ + height_ * width_);	// return area of RectPrism
	}
double RectPrism::getVolume() const{
	return length_ * width_ * height_;			// return volume of RectPrism
	}
RectPrism RectPrism::operator + (const RectPrism& rectp){ 
	RectPrism newrectp(0.0, 0.0, 0.0);			// create new rectangle prism
	double length = length_ + rectp.getLength();// length is the sum of lengths
	double width = width_ + rectp.getWidth(); 	// width is sum of widths
	double height = height_ + rectp.getHeight();// height is sum of heights
	newrectp = RectPrism(width, length, height);// set parameters for newrectp
	return newrectp;							// return newrectp RectPrism
	}
RectPrism RectPrism:: operator - (const RectPrism& rectp){
	RectPrism newrectp(0.0, 0.0, 0.0); 						// create new rectangle prism
	double length = max(0.0, length_ - rectp.getLength());	// length is the difference of lengths
	double width = max(0.0, width_ - rectp.getWidth());		// width is the difference of widths
	double height = max(0.0, height_ - rectp.getHeight());	// height is the difference of heights
	newrectp = RectPrism(width, length, height);			// set parameters for newrectp
	return newrectp;										// return newrect Rectangle
	}
 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){	// char* is the same as string
	// @@Insert your code here
	// if it's a pointer, always has to be new --> Rect* r = new Rect(), try replacing new with & and see if they're the same
	int i, size;									// initialize variables
	string name;
	vector<Shape*> shapes; 
	ifstream file(file_name, std::ifstream::in);	// open and read file
	file >> size;									// read the size value
	for(i = 0; i < size; i++){						// increment through the list size
		file >> name;								// read the name
		if(name == "Rectangle"){					// if a Rectangle
			double w, l;
			file >> w >> l;					// read the next values
			Shape* s = new Rectangle(w,l);	// create a pointer to the Rectangle
			shapes.push_back(s);			// push to the shape vector
		}
		if(name == "Circle"){				// same for if a Circle
			double r; 
			file >> r; 
			Shape* s = new Circle(r);
			shapes.push_back(s);
		}
		if(name == "Sphere"){				// same for if a Sphere
			double r;
			file >> r;
			Shape* s = new Sphere(r);
			shapes.push_back(s);
		}
		if(name == "RectPrism"){			// same for if RectPrism
			double w, l, h;
			file >> w >> l >> h;
			Shape*s = new RectPrism(w, l, h);
			shapes.push_back(s);
		}
	}
	file.close();	// close file
	return shapes;	// return vector
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int i;						
	int size = shapes.size();		// set size to length of shapes
	double a;

	for(i = 0; i < size; i++){		// increment through shapes vector
		a = shapes[i]->getArea();	// set a to area of shape[i]
		if (a > max_area)			// compare to see if a is larger
			max_area = a;			// if true, set max_area to a
	}
	return max_area;				// return the largest area
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	int i;							// initialize variables
	int size = shapes.size();
	double v;
	for(i = 0; i < size; i++){		// increment through shapes vector
		v = shapes[i]->getVolume();	// set v to volume of shape[i]
		if( v > max_volume)			// compare to see if v is larger
			max_volume = v;			// if true, set max_volume to v
	}
	return max_volume;				// return the largest volume
}

