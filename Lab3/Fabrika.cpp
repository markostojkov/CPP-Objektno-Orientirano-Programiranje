#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class Rabotnik {
protected:
    char ime[30];
    char prezime[30];
    int plata;

public:
    Rabotnik() {}

    Rabotnik(char* ime, char* prezime, int plata) {
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->plata = plata;
    }

    const int getPlata() {
        return this->plata;
    }

    void pecati() {
        cout<< this->ime << " " << this->prezime << " " << this->plata << endl;
    }
};

class Fabrika {
protected:
    vector<Rabotnik> rabotnik;
    int brojVraboteni;

public:
    Fabrika() {}

    Fabrika(int brojVraboteni) {
        this->brojVraboteni = brojVraboteni;
    }

    void setRabotnik(Rabotnik rabotnik) {
        this->rabotnik.push_back(rabotnik);
    }

    void pecatiVraboteni() {
        cout<<"Site vraboteni:"<<endl;
        for(int i = 0; i < this->rabotnik.size(); i++) {
            this->rabotnik.at(i).pecati();
        }
    }

    void pecatiSoPlata(int plata) {
        cout<<"Vraboteni so plata povisoka od "<<plata<<" :"<<endl;
        for(int i = 0; i < this->rabotnik.size(); i++) {
            if(this->rabotnik.at(i).getPlata() > plata)
                this->rabotnik.at(i).pecati();
        }
    }
};


int main() {

    int brojNaVraboteni, plata, plataZaProverka;
    char ime[30], prezime[30];

    cin>>brojNaVraboteni;

    Fabrika fabrika(brojNaVraboteni);

    for(int i = 0; i < brojNaVraboteni; i++) {
        cin>>ime>>prezime>>plata;

        Rabotnik rabotnik(ime, prezime, plata);

        fabrika.setRabotnik(rabotnik);
    }

    cin>>plataZaProverka;

    fabrika.pecatiVraboteni();
    fabrika.pecatiSoPlata(plataZaProverka);

    return 0;
}