#include <iostream>
#include <cstring>

using namespace std;

const char *NEAPOLITANSKI_STIL = "Neapolitan";


class ZicanInstrument {
    protected:
        char ime[20];
        int brojNaZici;
        float cena;        

    public:
        ZicanInstrument (char *ime, int brojNaZici, float cena) {
            strcpy(this->ime, ime);
            this->brojNaZici = brojNaZici;
            this->cena = cena;
        }

        friend ostream &operator<< (ostream &os, ZicanInstrument instrument) {
            cout << instrument.ime << 
                " " << instrument.brojNaZici <<
                " " << instrument.cena <<
                " ";
            return os;
        }
};


class Mandolina : public ZicanInstrument {
    protected:
        char forma[20];

    public:
        Mandolina (char *ime, int brojNaZici, float cena, char *forma) : ZicanInstrument(ime, brojNaZici, cena) {
            strcpy(this->forma, forma);
        }

        float cena () {
            if (strcmp(this->forma, NEAPOLITANSKI_STIL)) {
                return ((this->cena / 100.0) * 15) + this->cena;
            }
            return this->cena;
        }

        friend ostream &operator<< (ostream &os, Mandolina instrument) {
            cout << ZicanInstrument(instrument.ime, instrument.brojNaZici, instrument.cena);
            cout << instrument.forma;
            return os;
        }


};


class Violina : public ZicanInstrument {
    protected:
        float golemina;
    
    public:
        Violina (char *ime, int brojNaZici, float cena, float golemina) : ZicanInstrument(ime, brojNaZici, cena) {
            this->golemina = golemina;
        }

        float cena () {
            if (this->golemina == 0.25) {
                return (this->cena / 100.0 * 10) + this->cena;
            }
            else if (this->golemina == 1) {
                return (this->cena / 100.0 * 20) + this->cena;
            }
            return this->cena;
        }

        friend ostream &operator<< (ostream &os, Violina instrument) {
            cout << ZicanInstrument(instrument.ime, instrument.brojNaZici, instrument.cena);
            cout << instrument.golemina;
            return os;
        }
};


void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **instrumenti, int n) {
    for (int i = 0; i < n; i++) {
        if (zi == *instrumenti[i]) {
            cout << *instrumenti.cena() << endl;
        }
    }
}


int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}