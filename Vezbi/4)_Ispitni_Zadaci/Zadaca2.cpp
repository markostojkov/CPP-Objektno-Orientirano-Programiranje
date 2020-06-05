#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

enum TipNaChlen
{
    Basic,
    Premium
};


class NotValidYear
{
    private:
        char *message;

    public:
        NotValidYear(char *message)
        {
            this->message = new char[strlen(message) + 1];
            strcpy(this->message, message);
        }

        void error()
        {
            cout << this->message << endl;
        }
};


class Chlen
{
    protected:
        char ime[100];
        TipNaChlen tipNaChlen;
        int osnovenPopust;
        int dopolnitelenPopust;
        int godinaNaClenarina;

    public:
        Chlen() { }

        Chlen(char *ime, TipNaChlen tipNaChlen, int godinaNaClenarina)
        {
            strcpy(this->ime, ime);
            this->tipNaChlen = tipNaChlen;
            this->godinaNaClenarina = godinaNaClenarina;
            this->setPopusti(tipNaChlen);
        }

        void setPopusti(TipNaChlen tipNaChlen)
        {
            this->osnovenPopust = 10;
            this->dopolnitelenPopust = 0;

            if (tipNaChlen == Premium)
            {
                this->dopolnitelenPopust = 15;
            }
        }

        void setPopust1(int popust)
        {
            this->osnovenPopust = popust;
        }

        int getAllPopust()
        {
            return this->osnovenPopust + this->dopolnitelenPopust;
        }

        int getGodinaNaClenarina()
        {
            return this->godinaNaClenarina;
        }

        friend ostream &operator<<(ostream &os, Chlen chlen)
        {
            os << chlen.ime << endl;

            if (chlen.tipNaChlen == Basic)
            {
                os << "basic " << chlen.godinaNaClenarina << " "
                   << chlen.getAllPopust() << endl;
            }
            else
            {
                os << "premium " << chlen.godinaNaClenarina << " "
                   << chlen.getAllPopust() << endl;
            }

            return os;
        }
};


class FINKI_club
{
    protected:
        int cenaNaOsnovnaClenarina;
        int brojNaClenovi;
        Chlen *clenovi;

    public:
        FINKI_club()
        {
            this->brojNaClenovi = 0;
            this->clenovi = new Chlen[this->brojNaClenovi];
        }

        FINKI_club(int cenaNaOsnovnaClenarina)
        {
            this->cenaNaOsnovnaClenarina = cenaNaOsnovnaClenarina;
            this->brojNaClenovi = 0;
            this->clenovi = new Chlen[this->brojNaClenovi];
        }

        FINKI_club &operator-=(int tekovnaGodina)
        {
            Chlen *temp = new Chlen[this->brojNaClenovi];
            int novBrojNaClenovi = 0;

            if (tekovnaGodina < 1)
            {
                throw NotValidYear("Vnesena e negativna vrednost za godinata!");
            }

            for (int i = 0; i < this->brojNaClenovi; i++)
            {
                if (!(this->clenovi[i].getGodinaNaClenarina() < tekovnaGodina))
                {
                    temp[novBrojNaClenovi] = this->clenovi[i];
                    novBrojNaClenovi++;
                }
            }

            this->brojNaClenovi = novBrojNaClenovi;
            this->clenovi = temp;

            return *this;
        }

        friend ostream &operator<<(ostream &os, FINKI_club klub)
        {
            for (int i = 0; i < klub.brojNaClenovi; i++)
            {
                os << klub.clenovi[i];
            }

            return os;
        }

        void naplatiChlenarina()
        {
            for (int i = 0; i < this->brojNaClenovi; i++)
            {
                cout << this->clenovi[i];
                cout << this->cenaNaOsnovnaClenarina - 
                     (this->cenaNaOsnovnaClenarina * this->clenovi[i].getAllPopust() / 100.0) << endl;
            }
        }

        void setChlenovi(Chlen clenoviInput[], int n)
        {
            this->clenovi = new Chlen[n];
            this->brojNaClenovi = n;
            for (int i = 0; i < n; i++)
            {
                this->clenovi[i] = clenoviInput[i];
            }
        }
};

int main(){
	int testCase;
	cin >> testCase;

	char ime[100];
    int tipChlen;
	int popust;
    int god;


	if (testCase == 1){
		cout << "===== Testiranje na klasata Chlen ======" << endl;
        cin.get();
		cin.getline(ime,100);
        cin >> tipChlen;
		cin >> god;
        cout << "===== CONSTRUCTOR ======" << endl;
		Chlen c(ime, (TipNaChlen) tipChlen, god);
		cout << c;

	}

    if (testCase == 2){
		cout << "===== Testiranje na static clenovi ======" << endl;
		cin.get();
		cin.getline(ime,100);
        cin >> tipChlen;
		cin >> god;
        cout << "===== CONSTRUCTOR ======" << endl;
		Chlen c(ime, (TipNaChlen) tipChlen, god);
		cout << c;

		c.setPopust1(5);

        cout << c;
	}

	if (testCase == 3){
		cout << "===== Testiranje na klasata FINKI-club ======" << endl;
        FINKI_club fc;
        int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (TipNaChlen) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);

        cout << fc <<endl;
	}

	if (testCase == 4){
		cout << "===== Testiranje na operatorot -= ======" << endl;
		FINKI_club fc;
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (TipNaChlen) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);
        cout << "OPERATOR -=" << endl;
        int godina;
        cin >> godina;
        fc-=godina;

        cout << fc;
	}

	if (testCase == 5){
		cout << "===== Testiranje na operatorot -= (so iskluchok) ======" << endl;
		FINKI_club fc;
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (TipNaChlen) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);
        cout << "OPERATOR -=" << endl;
        int godina;
        cin >> godina;
        try
        {
            fc-=godina;
        }
        catch(NotValidYear notValidYear)
        {
            notValidYear.error();
        }
        
        
        
        cout << fc;
	}

	if (testCase == 6){
		cout << "===== Testiranje na metodot naplatiChlenarina  ======" << endl << endl;
		FINKI_club fc(1000);
		int n;
        cin >> n;
        Chlen chlen[100];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(ime,100);
            cin >> tipChlen;
            cin >> god;
            Chlen c(ime, (TipNaChlen) tipChlen, god);
            chlen[i] = c;
        }

        fc.setChlenovi(chlen, n);

        cout << "Naplati chlenarina:" << endl;
        fc.naplatiChlenarina();
	}
	return 0;
}
