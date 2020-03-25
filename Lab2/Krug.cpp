#include <iostream>
#include <cmath>

using namespace std;



class Circle {
    //Basic circle class to provide perimeter and area method
    
protected:
    float radius;
    const float pi = 3.14;

public:
    Circle() {
    }

    //Contstructor
    Circle(float radius) {
        this->radius = radius;
    }
    
    
    //Circle Perimeter method
    float perimeter() {
        return (2 * this->radius) * this->pi;
    }
    
    
    //Circle area method
    float area(){
        return pow(this->radius, 2) * this->pi;
    }
    
    
    //Circle method to check if perimeter is equal to area
    bool isPerimeterEqualToArea() {
        return this->perimeter() == this->area();
    }

};

int main() {
    
    //Get radius from stdin
    float radius;
    cin >> radius;

    //Init circle with radius
    Circle circle(radius);
    
    
    //Print circle methods
    cout << circle.perimeter() << endl;
    cout << circle.area() << endl;
    cout << circle.isPerimeterEqualToArea() <<endl;

    //Init circle without param
    Circle circle2();
    
    return 0;
}