#include <iostream>
#include <cmath> 

using namespace std;

class Shape {
protected:
    double positionX, positionY;
    string color;
    int borderThickness;

public:
    Shape(double x, double y, const string& c, int thickness = 0)
        : positionX(x), positionY(y), color(c), borderThickness(thickness) {}

    virtual ~Shape() {} 

    virtual void draw() const {
        cout << "Drawing a shape at (" << positionX << ", " << positionY << ")" << endl;
        cout << "Color: " << color << ", Border Thickness: " << borderThickness << endl;
    }

    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, const string& c, double r, int thickness = 0)
        : Shape(x, y, c, thickness), radius(r) {}

    void draw() const override {
        Shape::draw();
        cout << "This is a circle with radius: " << radius << endl;
    }

    double calculateArea() const override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() const override {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double x, double y, const string& c, double w, double h, int thickness = 0)
        : Shape(x, y, c, thickness), width(w), height(h) {}

    void draw() const override {
        Shape::draw();
        cout << "This is a rectangle with width: " << width << " and height: " << height << endl;
    }

    double calculateArea() const override {
        return width * height;
    }

    double calculatePerimeter() const override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double x, double y, const string& c, double s1, double s2, double s3, int thickness = 0)
        : Shape(x, y, c, thickness), side1(s1), side2(s2), side3(s3) {}

    void draw() const override {
        Shape::draw();
        cout << "This is a triangle with sides: " << side1 << ", " << side2 << ", " << side3 << endl;
    }

    double calculateArea() const override {
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() const override {
        return side1 + side2 + side3;
    }
};

class Polygon : public Shape {
private:
    int numSides;
    double sideLength;

public:
    Polygon(double x, double y, const string& c, int sides, double length, int thickness = 0)
        : Shape(x, y, c, thickness), numSides(sides), sideLength(length) {}

    void draw() const override {
        Shape::draw();
        cout << "This is a polygon with " << numSides << " sides, each of length: " << sideLength << endl;
    }

    double calculateArea() const override {
        return (numSides * sideLength * sideLength) / (4 * tan(M_PI / numSides));
    }

    double calculatePerimeter() const override {
        return numSides * sideLength;
    }
};

int main() {
    Circle circle(10, 20, "Red", 5);
    Rectangle rectangle(30, 40, "Blue", 8, 6);
    Triangle triangle(50, 60, "Green", 3, 4, 5);
    Polygon polygon(70, 80, "Yellow", 6, 4);

    Shape* shapes[] = { &circle, &rectangle, &triangle, &polygon };

    for (Shape* shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->calculateArea() << endl;
        cout << "Perimeter: " << shape->calculatePerimeter() << endl;
        cout << endl;
    }

    return 0;
}