#include <iostream>
#include <cstring>
using namespace std;
class Potpisuvac {
    char ime[20], prezime[20], embg[14];
public:
    Potpisuvac() {}
    Potpisuvac(char *ime, char *prezime, char *embg) {
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        strcpy(this->embg,embg);
    }
    ~Potpisuvac() {}
    string getembg() {
        return this->embg;
    }
};
class Dogovor {
    int brDogovor;
    char kategorija[50];
    Potpisuvac p[3];
public:
    Dogovor(int brDogovor, char *kategorija, Potpisuvac p[3]) {
        this->brDogovor=brDogovor;
        strcpy(this->kategorija,kategorija);
        for(int i=0; i<3; i++) {
            this->p[i]=p[i];
        }
    }
    ~Dogovor() {}
    bool proverka() {
        if(p[0].getembg()==p[1].getembg() || p[0].getembg()==p[2].getembg() || p[1].getembg()==p[2].getembg())
            return 1;
        else
            return 0;
    }
};
//ne smee da se menuva main funkcijata
int main() {
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}