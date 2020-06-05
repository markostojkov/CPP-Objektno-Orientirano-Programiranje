#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;


class NegativnaVrednost
{
    private:
        char *message;

    public:
        NegativnaVrednost(char *message)
        {
            this->message = new char[strlen(message)];
            strcpy(this->message, message);
        }

        void error()
        {
            cout << this->message << endl;
        }
};



class Oglas
{
    private:
        char naslov[50];
        char kategorija[30];
        char opis[100];
        int cena;

    public:
        Oglas() {}

        Oglas(char *naslov, char *kategorija, char *opis, int cena)
        {
            strcpy(this->naslov, naslov);
            strcpy(this->kategorija, kategorija);
            strcpy(this->opis, opis);
            this->cena = cena;
        }

        int getCena()
        {
            return this->cena;
        }

        char *getKategorija()
        {
            return this->kategorija;
        }

        bool const &operator>(Oglas oglasZaSporedba)
        {
            if (this->cena > oglasZaSporedba.cena) return true;
            return false;
        }

        friend ostream &operator<<(ostream &os, Oglas oglas)
        {
            os << oglas.naslov << endl;
            os << oglas.opis << endl;
            os << oglas.cena << " evra" << endl;
            return os;
        }

};


class Oglasnik
{
    private:
        char imeNaOglasnik[20];
        Oglas *oglasi;
        int brojNaOglasi;
    
    public:
        Oglasnik(char *imeNaOglasnik)
        {
            strcpy(this->imeNaOglasnik, imeNaOglasnik);
            this->brojNaOglasi = 0;
            this->oglasi = new Oglas[this->brojNaOglasi];
        }

        Oglasnik &operator+=(Oglas oglas)
        {
            if (oglas.getCena() < 0)
            {
                throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            }

            Oglas *temp = new Oglas[this->brojNaOglasi + 1];

            for (int i = 0; i < this->brojNaOglasi; i++)
            {
                temp[i] = this->oglasi[i];
            }

            temp[this->brojNaOglasi] = oglas;
            this->brojNaOglasi++;
            this->oglasi = temp;

            return *this;
        }

        void oglasiOdKategorija(char *kategorija)
        {
            for (int i = 0; i < this->brojNaOglasi; i++)
            {
                if (strcmp(this->oglasi[i].getKategorija(), kategorija) == 0)
                {
                    cout << this->oglasi[i] << endl;
                }
            }
        }

        void najniskaCena()
        {
            int najniskaCena = this->oglasi[this->brojNaOglasi - 1].getCena();
            int najniskaCenaPozicija;

            for (int i = 0; i < this->brojNaOglasi; i++)
            {
                if (this->oglasi[i].getCena() < najniskaCena)
                {
                    najniskaCena = this->oglasi[i].getCena();
                    najniskaCenaPozicija = i;
                }
            }

            cout << this->oglasi[najniskaCenaPozicija] << endl;
        }

        friend ostream &operator<<(ostream &os, Oglasnik oglasnik)
        {
            cout << oglasnik.imeNaOglasnik << endl;

            for (int i = 0; i < oglasnik.brojNaOglasi; i++)
            {
                os << oglasnik.oglasi[i] << endl;
            }

            return os;
        }
};



int main(){
    
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;
    
    int tip;
    cin>>tip;
    
    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;    
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);
    
    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);  
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost negativnaVrednost)
            {
                negativnaVrednost.error();
            }
                      
        }
        cout<<ogl;
    
    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);            
            ogl+=o;            
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();
    
    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);            
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost negativnaVrednost)
            {
                negativnaVrednost.error();
            }
        }
        cout<<ogl;
        
        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);
        
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();
    
    }
    
	return 0;
}
