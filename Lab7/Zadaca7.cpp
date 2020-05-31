#include <iostream>
#include <cmath>

using namespace std;

const double Pi = 3.14;


class Shape 
{
    protected:
        int strana;

    public:
        Shape()
        {
            this->strana = 0;
        }

        Shape(int strana)
        {
            this->strana = strana;
        }

        int getStrana()
        {
            return this->strana;
        }

        virtual double plostina() = 0;

        virtual void pecati() = 0;

        virtual int getType() = 0;
};


class Kvadrat : public Shape
{
    public:
        Kvadrat(int strana) : Shape(strana)
        { }

        Kvadrat()
        { }

        double plostina()
        {
            return pow(this->strana, 2);
        }

        void pecati()
        {
            cout << "Kvadrat so plostina = " << this->plostina() << endl;
        }

        int getType()
        {
            return 1;
        }
};


class Krug : public Shape
{        
    public:
        Krug ()
        { }

        Krug(int strana) : Shape(strana)
        { }

        Krug(Shape &shape) : Shape(shape.getStrana())
        { }

        double plostina()
        {
            return pow(this->strana, 2) * Pi;
        }

        void pecati()
        {
            cout << "Krug so plostina = " << this->plostina() << endl;
        }

        int getType()
        {
            return 2;
        }
};


class Triagolnik : public Shape
{        
    public:
        Triagolnik(int strana) : Shape(strana)
        { }

        Triagolnik()
        { }

        double plostina()
        {
            return  (sqrt(3) / 4.0) * pow(this->strana, 2);
        }

        void pecati()
        {
            cout << "Triagolnik so plostina = " << this->plostina() << endl;
        }

        int getType()
        {
            return 3;
        }
};


void checkNumTypes(Shape *niza[], int n)
{
    int brojKvadrati = 0, brojKrugovi = 0, brojTriagolnici = 0, shapeType;

    for (int i = 0; i < n; i++)
    {
        shapeType = niza[i]->getType();

        switch (shapeType)
        {
        case 1:
            brojKvadrati++;
            break;
        case 2:
            brojKrugovi++;
            break;
        case 3:
            brojTriagolnici++;
            break;
        default:
            break;
        }
    }

    cout << "Broj na kvadrati vo nizata = " << brojKvadrati << endl;
    cout << "Broj na krugovi vo nizata = " << brojKrugovi << endl;
    cout << "Broj na triagolnici vo nizata = " << brojTriagolnici << endl;
}


int main(){


	int n;
	cin >> n;

    Shape** niza;
    niza = new Shape*[n];  	

	int classType;
	int side;

	for(int i = 0; i < n; ++i){

		cin >> classType;
		cin >> side;
		
        switch (classType)
        {
        case 1:
            niza[i] = new Kvadrat(side);
            break;
        case 2:
            niza[i] = new Krug(side);
            break;
        case 3:
            niza[i] = new Triagolnik(side);
            break;
        default:
            break;
        }
	}
    
    
	for(int i = 0; i < n; ++i){

		niza[i]->pecati();
	}

	checkNumTypes(niza, n);

    delete [] *niza;

	return 0;
}