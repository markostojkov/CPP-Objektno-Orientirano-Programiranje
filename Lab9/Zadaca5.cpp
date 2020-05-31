#include<iostream>
#include<cstring>
#include <vector>

using namespace std;


class ArithmeticException
{
    protected:

    public:
        ArithmeticException()
        {
        }

        void printMessage()
        {
            cout << "Division by zero is not allowed" << endl;
        }
};

class NumbersNotDivisibleException
{
    protected:
        int broj;

    public:
        NumbersNotDivisibleException(int broj)
        {
            this->broj = broj;
        }

        void printMessage()
        {
            cout << "Division by " << this->broj << " is not supported" << endl;
        }
};

class ArrayFullException
{
    protected:

    public:
        ArrayFullException()
        {
        }

        void printMessage()
        {
            cout << "The array is full. Increase the capacity" << endl;
        }
};

class IndexOutOfBoundsException
{
    protected:
        int index;

    public:
        IndexOutOfBoundsException(int index)
        {
            this->index = index;
        }

        void printMessage()
        {
            cout << "Index " << this->index <<" is out of bounds" << endl;
        }
};

class NumberIsNotPositiveException
{
    protected:
        int broj;

    public:
        NumberIsNotPositiveException(int broj)
        {
            this->broj = broj;
        }

        void printMessage()
        {
            cout << "Number " << this->broj << " is not positive integer" << endl;
        }
};


class PositiveIntegers
{
    protected:
        vector<int> broevi;
        int brojNaElementi;
        int maxKapacitet;

    public:
        PositiveIntegers()
        {
            this->brojNaElementi = 0;
        }

        PositiveIntegers(int maxKapacitet)
        {
            this->maxKapacitet = maxKapacitet;
            this->brojNaElementi = 0;
        }

        void increaseCapacity(int capacity)
        {
            this->maxKapacitet += capacity;
        }

        PositiveIntegers &operator=(PositiveIntegers positiveIntegers)
        {
            this->brojNaElementi = positiveIntegers.brojNaElementi;
            this->maxKapacitet = positiveIntegers.maxKapacitet;
            this->broevi = positiveIntegers.broevi;
            return *this;
        }

        PositiveIntegers &operator+=(int broj)
        {
            if (broj < 1)
            {
                throw NumberIsNotPositiveException(broj);
            }
            if (this->maxKapacitet <= this->brojNaElementi)
            {
                throw ArrayFullException();
            }
            this->broevi.push_back(broj);
            this->brojNaElementi++;
            return *this;
        }

        PositiveIntegers &operator*(int mnozitel)
        {
            for (int i = 0; i < this->brojNaElementi; i++)
            {
                this->broevi.at(i) *= mnozitel;
            }
            return *this;
        }

        PositiveIntegers &operator/(int delitel)
        {
            if (delitel == 0) throw ArithmeticException();
            for (int i = 0; i < this->brojNaElementi; i++)
            {
                if (this->broevi.at(i) % delitel != 0)
                {
                    throw NumbersNotDivisibleException(delitel);
                }
                this->broevi.at(i) /= delitel;
            }
            return *this;
        }

        int &operator[](int pozicija)
        {
            if (this->brojNaElementi < pozicija || pozicija < 0)
            {
                throw IndexOutOfBoundsException(pozicija);
            }
            return this->broevi.at(pozicija);
        }

        void print()
        {
            cout << "Size: " << this->brojNaElementi << " Capacity: " << this->maxKapacitet << " Numbers:";
            for (int i = 0; i < this->brojNaElementi; i++)
            {
                cout << " " << this->broevi.at(i);
            }
            cout << endl;
        }
};


int main() {

    int n,capacity;
    cin >> n >> capacity;
    PositiveIntegers pi (capacity);
    for (int i=0;i<n;i++){
        try
        {
            int number;
            cin>>number;
            pi+=number;
        }
        catch(NumberIsNotPositiveException numberIsNotPositiveException)
        {
            numberIsNotPositiveException.printMessage();
        }
        catch(ArrayFullException arrayFullException)
        {
            arrayFullException.printMessage();
        }
    }
    cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
    pi.print();
    int incCapacity;
    cin>>incCapacity;
    pi.increaseCapacity(incCapacity);
    cout<<"===INCREASING CAPACITY==="<<endl;
    pi.print();
    
    int n1;
    cin>>n1;
    for (int i=0;i<n1;i++){
        try
        {
            int number;
            cin>>number;
            pi+=number;
        }
        catch(NumberIsNotPositiveException numberIsNotPositiveException)
        {
            numberIsNotPositiveException.printMessage();
        }
        catch(ArrayFullException arrayFullException)
        {
            arrayFullException.printMessage();
        }
    }
    cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;
    
    pi.print();
    PositiveIntegers pi1;
    
    cout<<"===TESTING DIVISION==="<<endl;	
    try
    {
        pi1 = pi/0;
        pi1.print();
    }
    catch(ArithmeticException arithmeticException)
    {
        arithmeticException.printMessage();
    }
    catch(NumbersNotDivisibleException numbersNotDivisibleException)
    {
        numbersNotDivisibleException.printMessage();
    }
    try
    {
        pi1 = pi/1;
        pi1.print();
    }
    catch(ArithmeticException arithmeticException)
    {
        arithmeticException.printMessage();
    }
    catch(NumbersNotDivisibleException numbersNotDivisibleException)
    {
        numbersNotDivisibleException.printMessage();
    }

    try
    {
        pi1 = pi/2;
        pi1.print();
    }
    catch(ArithmeticException arithmeticException)
    {
        arithmeticException.printMessage();
    }
    catch(NumbersNotDivisibleException numbersNotDivisibleException)
    {
        numbersNotDivisibleException.printMessage();
    }
    
    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();
    
    cout<<"===TESTING [] ==="<<endl;
    try
    {
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch(IndexOutOfBoundsException indexOutOfBoundsException)
    {
        indexOutOfBoundsException.printMessage();
    }
    
    try
    {
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException indexOutOfBoundsException)
    {
        indexOutOfBoundsException.printMessage();
    }

    try
    {
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;	
    }
    catch(IndexOutOfBoundsException indexOutOfBoundsException)
    {
        indexOutOfBoundsException.printMessage();
    }

    try
    {	
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException indexOutOfBoundsException)
    {
        indexOutOfBoundsException.printMessage();
    }

    return 0;
}