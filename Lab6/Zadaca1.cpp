#include <iostream>
#include <string.h>

using namespace std;


const int DANOK_NA_NEDVIZNINA = 5;

class Nedviznina 
{
    protected:
        char *adresa;
        int kvadratura;
        int cena;

        void constructor (char *adresa, int kvadratura, int cena)
        {
            this->adresa = new char[strlen(adresa) + 1];

            strcpy(this->adresa, adresa);
            this->kvadratura = kvadratura;
            this->cena = cena;
        }
    
    public:
        Nedviznina ()
        {
            char *adresa;
            this->constructor(adresa, 0, 0); 
        }

        const char* getAdresa ()
        {
            return this->adresa;
        }

        int cenaNaNedviznina ()
        {
            return this->kvadratura * this->cena;
        }

        void pecati ()
        {
            cout << this->adresa << ", Kvadratura: " << this->kvadratura << ", Cena po Kvadrat: " << this->cena << endl;
        }

        float danokNaImot ()
        {
            return (this->cenaNaNedviznina() / 100.0) * DANOK_NA_NEDVIZNINA;
        }

        friend istream &operator>> (istream &is, Nedviznina &n) {
            is>>n.adresa;
            is>>n.kvadratura;
            is>>n.cena;
            return is;
        }

        ~Nedviznina ()
        {
            delete [] this->adresa;
        }

};


class Vila : public Nedviznina 
{
    protected:
        int danokNaLuksuz;

    public:
        Vila ()
        {
            
        }

        void pecati ()
        {
            Nedviznina::pecati();
            cout << ", Danok na luksuz: "
            << this->danokNaLuksuz 
            << endl;
        }

        float danokNaImot ()
        {
            return (this->cenaNaNedviznina() / 100.0) * (DANOK_NA_NEDVIZNINA + this->danokNaLuksuz);
        }

        friend istream &operator>> (istream &is, Vila &v) {
            is>>v.adresa;
            is>>v.kvadratura;
            is>>v.cena;
            is>>v.danokNaLuksuz;
            return is;
        }

};


int main()
{
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}