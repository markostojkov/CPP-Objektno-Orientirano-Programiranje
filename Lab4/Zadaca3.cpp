#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


class Pica {
protected:
    char ime[100];
    int cena;
    char sostojki[100];
    int popust;

public:
    Pica(char *ime, int cena, char *sostojki, int popust) {
        strcpy(this->ime, ime);
        this->cena = cena;
        strcpy(this->sostojki, sostojki);
        this->popust = popust;
    }

    const char* getIme() {
        return this->ime;
    }

    const char* getSostojki() {
        return this->sostojki;
    }

    int getPopust() {
        return this->popust;
    }

    int getCena() {
        return this->cena;
    }

    float getCenaSoPopust() {
        return this->cena - (this->cena *this->popust) / 100;
    }

    void pecati() {
        float cenaSoPopust = (this->popust / 100) * this->cena;
        cout<< this->ime << " " ;
        cout<< this->sostojki << " ";
        cout<<this->cena<<" "<<cena-((this->popust/100)*this->cena)<<endl;
    }

    bool istiSe(Pica pica) {
        return string(this->getSostojki()) == string(pica.getSostojki());
    } 

};


class Picerija {
protected:
    char ime[100];
    vector <Pica> pici;
    int brojNaPici;

public:
    Picerija(char *ime) {
        strcpy(this->ime, ime);
    }


    Picerija(const Picerija &picerija) {
        strcpy(this->ime, picerija.ime);
        this->brojNaPici = picerija.brojNaPici;
        for(int i = 0; i < picerija.pici.size(); i++) {
            this->pici.push_back(picerija.pici.at(i));
        }
    }

    const char* getIme() {
        return this->ime;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    void dodadi(const Pica &pica) {
        if(this->nePostoIstaPica(pica))
            this->pici.push_back(pica);
    }

    bool nePostoIstaPica(const Pica &pica) {
        for(int i = 0; i < this->pici.size(); i++) 
            if(this->pici.at(i).istiSe(pica)) return false;
        return true;
    }

    void piciNaPromocija() {
        for(int i = 0; i < this->pici.size(); i++) {
            Pica pica = this->pici.at(i);
            if(pica.getPopust() > 0)
                cout<< pica.getIme()<< " - "<< pica.getSostojki() << ", " << pica.getCena() << " " << pica.getCenaSoPopust() << endl;
        }
    }
};


int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
