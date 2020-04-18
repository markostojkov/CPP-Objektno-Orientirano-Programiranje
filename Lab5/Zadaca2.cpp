#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int j=0;

class ComplexNumber{
private:
    float real;
    float imaginary;
public:
    ComplexNumber(){
        real=0;
        imaginary=0;
    }
    ComplexNumber(float real, float imaginary){
        this->real=real;
        this->imaginary=imaginary;
    }
    double module(){
        return sqrt((real*real)+(imaginary*imaginary));
    }
    ComplexNumber &operator=(const ComplexNumber &c){
        real=c.real;
        imaginary=c.imaginary;
        return *this;
    }
    friend ostream &operator<<(ostream &os, ComplexNumber &c){
        if(c.real==0)
            os<<c.imaginary<<"i"<<endl;
        else if(c.imaginary==0)
            os<<c.real<<endl;
        else
            os<<c.real<<"+"<<c.imaginary<<"i"<<endl;
        return os;
    }
    ComplexNumber operator+(const ComplexNumber &c){
        ComplexNumber temp;
        temp.imaginary=this->imaginary+c.imaginary;
        temp.real=this->real+c.real;
        return temp;
    }
    ComplexNumber operator-(const ComplexNumber &c){
        ComplexNumber temp;
        temp.imaginary=this->imaginary-c.imaginary;
        temp.real=this->real-c.real;
        return temp;
    }
    ComplexNumber operator*(const ComplexNumber &c) {
        ComplexNumber temp;
        temp.real=real*c.real;
        temp.imaginary=imaginary*c.imaginary;
        return temp;
    }
    ComplexNumber operator/(const ComplexNumber &c) {
        ComplexNumber temp;
        temp.real=real/c.real;
        temp.imaginary=imaginary/c.imaginary;
        return temp;
  }
    bool operator==(ComplexNumber &c){
        if(c.real==this->real){
            if(c.imaginary==this->imaginary){
                return true;
            }
            return false;
        }
        return false;
    }
    bool operator>(const ComplexNumber &c){
        if(real>c.real)
            return true;
        else if(c.real>real)
            return false;
        else{
            if(imaginary>c.imaginary)
                return true;
            else
                return false;
        }
    }
    bool operator<(const ComplexNumber &c){
        if(real<c.real)
            return true;
        else if(c.real<real)
            return false;
        else{
            if(imaginary<c.imaginary)
                return true;
            else
                return false;
        }
    }
    void setReal(float r){
        real=r;
    }
    void setImaginary(float i){
        imaginary=i;
    }
};

class Equation{
private:
    ComplexNumber *numbers;
    int n;
    char *operators;
    int m;
public:
    Equation(){
        n=0;
        m=0;
        numbers = new ComplexNumber[0];
        numbers = 0;
        operators = new char[0];
        strcpy(operators,"");
    }
    ~Equation(){
        delete [] numbers;
        delete [] operators;
    }
    Equation(const Equation &e){
        operators = new char[strlen(e.operators)+1];
        strcpy(operators,e.operators);
        numbers = new ComplexNumber[e.n];
        for(int i=0;i<e.n;i++)
            numbers[i]=e.numbers[i];
        n=e.n;
        m=e.m;
    }
    Equation &operator=(const Equation &e){
        if(this!=&e){
            delete [] operators;
            operators=new char[strlen(e.operators)+1];
            strcpy(operators,e.operators);
            delete [] numbers;
            numbers=new ComplexNumber[e.n];
            for(int i=0;i<e.n;i++)
                numbers[i]=e.numbers[i];
            n=e.n;
            m=e.m;
        }
        return *this;
    }
    friend istream &operator>>(istream &is, Equation &e){
        float a,b;
        char c;
        while(c!='='){
            is>>a>>b>>c;
            ComplexNumber temp1;
            temp1.setReal(a);
            temp1.setImaginary(b);
            ComplexNumber *temp = new ComplexNumber[e.n+1];
            for(int i=0;i<e.n;i++)
                temp[i]=e.numbers[i];
            delete [] e.numbers;
            temp[e.n++]=temp1;
            e.numbers=temp;

            if(c=='=')
                break;
            else{
            char *tempchar = new char[e.m+2];
            for(int i=0;i<e.m;i++)
                tempchar[i]=e.operators[i];
            //strcpy(tempchar,e.operators);
            tempchar[e.m++]=c;
            delete [] e.operators;
            e.operators=tempchar;
            }
        }
        return is;
    }
   ComplexNumber result(){
        ComplexNumber temp=numbers[0];
        for(int i=1;i<n;i++){
            if(operators[i-1]=='+'){
                temp=temp+numbers[i];
            }
            else if(operators[i-1]=='-'){
                temp=temp-numbers[i];
            }
            else if(operators[i-1]=='*'){
                temp=temp*numbers[i];
            }
            else if(operators[i-1]=='/'){
                temp=temp/numbers[i];
            }
        }
        return temp;
    }
    double sumModules(){
        double sum=0;
        for(int i=0;i<n;i++){
            sum+=numbers[i].module();
        }
        return sum;
    }
    void print1(){
        cout<<"I am working fine-2print f-ion"<<endl;
        for(int i=0;i<n;i++)
            cout<<numbers[i]<<" "
            ;
    }
    void print(){
        cout<<"I am working fine-print f-ion"<<endl;
        for(int i=0;i<m;i++)
            cout<<operators[i]<<" "
            ;
    }
};

int main() {
	int testCase;
	double real, imaginary;
	ComplexNumber first, second, result;

	cin >> testCase;

	if (testCase <= 8) {
		cin >> real;
		cin >> imaginary;
		first = ComplexNumber(real, imaginary);
		cin >> real;
		cin >> imaginary;
		second = ComplexNumber(real, imaginary);
	}

	if (testCase == 1) {
		cout << "===== OPERATOR + =====" << endl;
		result = first + second;
		cout << result;
	}
	else if (testCase == 2) {
		cout << "===== OPERATOR - =====" << endl;
		result = first - second;
		cout << result;
	}
	else if (testCase == 3) {
		cout << "===== OPERATOR * =====" << endl;
		result = first * second;
		cout << result;
	}
	else if (testCase == 4) {
		cout << "===== OPERATOR / =====" << endl;
		result = first / second;
		cout << result;
	}
	else if (testCase == 5) {
		cout << "===== OPERATOR == =====" << endl;
		cout << first;
		cout << second;
		if (first == second)
			cout << "EQUAL" << endl;
		else
			cout << "NOT EQUAL" << endl;
	}
	else if (testCase == 6) {
		cout << "===== OPERATOR > =====" << endl;
		cout << first;
		cout << second;
		if (first > second)
			cout << "FIRST GREATER THAN SECOND" << endl;
		else
			cout << "FIRST LESSER THAN SECOND" << endl;
	}
	else if (testCase == 7) {
		cout << "===== OPERATOR < =====" << endl;
		cout << first;
		cout << second;
		if (first < second)
			cout << "FIRST LESSER THAN SECOND" << endl;
		else
			cout << "FIRST GREATER THAN SECOND" << endl;
	}
	else if (testCase == 8) {
		cout << "===== MODULE =====" << endl;
		double module = first.module();
		cout << first;
		cout << "Module: " << module << endl;
		cout << second;
		module = second.module();
		cout << "Module: " << module << endl;
	}
	else if (testCase == 9) {
		cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
		Equation equation;
		cin >> equation;
		cout << equation.sumModules();
	}
	else if (testCase == 10) {
		cout << "===== EQUATION RESULT =====" << endl;
		Equation equation;
		cin >> equation;
		result = equation.result();
		cout << result;
	}
	return 0;
}