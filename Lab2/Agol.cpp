#include <iostream>
using namespace std;


class Angle {
    //Angle class that keeps data of angle in deg, min, sec
    //Does basic set operations and manipulates the object props
    
protected:
    //Values are protected in case of inheritance
    int degree, minutes, seconds;

public:
    Angle() {}

    //Set function for degrees
    void setDegree(int degree) {
    	this->degree = degree;
    }
    
    //Set function for minutes
    void setMinutes(int minutes) {
    	this->minutes = minutes;
    }
    
    //Set function for seconds
    void setSeconds(int seconds) {
    	this->seconds = seconds;
    }
    
    //*if values are not set
    //This function converts the angle from deg, min, sec to decimal degrees
    float toDecimalDegrees(int degree, int minutes, int seconds) {
        return degree + (minutes / 60) + seconds / 3600;
    }
    
    //*if values are set in the object
    float toDecimalDegrees() {
        return this->degree + this->minutes / 60 + this->seconds / 3600;
    }
    
    //Converts the angle to seconds
    int toSeconds() {
        return this->degree * 3600 + this->minutes * 60 + this->seconds;
    }
    
    //Returns true if angle is less than 180 degrees
    bool isValid(int degree, int minutes, int seconds) {
        return this->toDecimalDegrees(degree, minutes, seconds) < 180;
    }
};


int main() {
	
	//Init angle class    
    Angle angle;
    
    //Gets values from stdin
    int deg, min, sec;
    cin >> deg >> min >> sec;

    //Simple angle validation
    if (angle.isValid(deg, min, sec)) {
	
        //Angle object setters
        angle.setDegree(deg);
        angle.setMinutes(min);
        angle.setSeconds(sec);
        
        //Angle value from deg, min, sec to sec
        cout << angle.toSeconds();
       

    }else cout<<"Nevalidni vrednosti za agol";
    
    return 0;
}
