#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


enum Zanr {Akcija, Komedija, Drama};


class Film {
protected:
    char ime[50];
    int memorija;
    Zanr zanr;
    
public:
    Film(char *ime, int memorija, Zanr zanr) {
    	strcpy(this->ime, ime);
        this->memorija = memorija;
        this->zanr = zanr;
    }	
    
    Zanr getZanr() {
    	return this->zanr;
    }
    
    int getMemorija() {
    	return this->memorija;
    }
    
    void pecati() {
    	cout<< this->memorija << "MB-\"" << this->ime << "\"" <<endl;

    }
    
};


class DVD {
protected:
    vector <Film> film;
    int memoriskiKapacitet;
    
public:
    DVD(int memoriskiKapacitet) {
    	this->memoriskiKapacitet = memoriskiKapacitet;
    }
    
    Film getFilm(int i) {
    	return this->film.at(i);
    }
    
    int getBroj() {
    	return this->film.size();
    }
    
    void dodadiFilm(Film film) {
        if(this->memoriskiKapacitet >= film.getMemorija() + this->getIskoristenaMemorija())
    	this->film.push_back(film);
    }
    
    void pecatiFilmoviDrugZanr(Zanr zanr) {
        for(int i = 0; i < this->film.size(); i++) {
            if(this->film.at(i).getZanr() != zanr) {
            	this->film.at(i).pecati();
            }
        }
    }
    
    int getIskoristenaMemorija() {
        int memoriskiKapacitet = 0;
        for(int i = 0; i < this->film.size(); i++)
            memoriskiKapacitet += this->film.at(i).getMemorija();
        return memoriskiKapacitet;
    }

    float procentNaMemorijaOdZanr(Zanr zanr) {
        
        float vkupnoMemorija = 0.0;
        
    	for(int i = 0; i < this->film.size(); i++) {
            if(this->film.at(i).getZanr() == zanr) {
            	vkupnoMemorija += this->film.at(i).getMemorija();
            }
        }
        return (vkupnoMemorija / this->getIskoristenaMemorija()) * 100;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (Zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((Zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((Zanr) kojzanr);

    } else if (testCase == 6) {
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((Zanr) kojzanr)<<"%\n";

    }

    return 0;
}