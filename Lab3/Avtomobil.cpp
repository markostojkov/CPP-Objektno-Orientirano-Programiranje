#include<iostream>
#include<cstring>
#include<stdlib.h>
#include <iomanip>
using namespace std;
class Person {
private:
    char name[20],surname[20];
public:
    Person() {
        strcpy(this->name,"not specified");
        strcpy(this->surname,"not specified");
    }
    Person(char *name, char *surname) {
        strcpy(this->name,name);
        strcpy(this->surname,surname);
    }
    ~Person() {}
    void print() {
        cout<<this->name<<" "<<this->surname<<endl;
    }
};
class Date {
private:
    int year,month,day;
public:
    Date() {
        this->year=0;
        this->month=0;
        this->day=0;
    }
    Date(int year, int month, int day) {
        this->year=year;
        this->month=month;
        this->day=day;
    }
    Date(const Date &p) {
        this->year=p.year;
        this->month=p.month;
        this->day=p.day;
    }
    ~Date() {}
    void print() {
        cout<<this->year<<".";
        cout<<this->month<<"."<<this->day<<endl;
    }
};
class Car {
private:
    Person sopstvenik;
    Date datum;
    float price;
public:
    Car() {
    }
    Car(Person sopstvenik, Date datum, float price) {
        this->sopstvenik=sopstvenik;
        this->datum=datum;
        this->price=price;
    }
    ~Car() {}
    float getPrice() {
        return this->price;
    }
    void print() {
        this->sopstvenik.print();
        this->datum.print();
        cout<<"Price: "<<getPrice()<<endl;
    }
};
void cheaperThan(Car* cars, int numCars, float price) {
    for(int i=0; i<numCars; i++) {
        if(cars[i].getPrice()<price)
            cars[i].print();
    }
}
int main() {
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);
        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);
        cin >> price;
        Car car(lik, date,  price);
        car.print();
    } else if (testCase == 2) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);
        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));
        cin >> price;
        Car car(lik, date,  price);
        car.print();
    } else {
        int numCars;
        cin >> numCars;
        Car cars[10];
        for (int i = 0; i < numCars; i++) {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);
            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);
            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }
    return 0;
}