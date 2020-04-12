#include<iostream>
#include<cstring>

using namespace std;
enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char * ime;
    float verzija;
    Tip tip;
    float golemina;
    void copy (const OperativenSistem &os) {
        this->ime = new char [strlen(os.ime)+1];
        strcpy(this->ime,os.ime);
        this->verzija=os.verzija;
        this->tip = os.tip;
        this->golemina=os.golemina;
    }
public :
    OperativenSistem (char * ime="", float verzija=0.0, Tip tip =(Tip) 0, float golemina=0.0) {
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->tip = tip;
        this->golemina=golemina;
    }
    OperativenSistem (const OperativenSistem &os) {
        copy(os);
    }
    OperativenSistem &operator = (const OperativenSistem &os) {
        if (this!=&os) {
            delete [] ime;
            copy(os);
        }
        return *this;
    }
    ~OperativenSistem() {
        delete [] ime;
    }

    void pecati() {
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        return strcmp(ime,os.ime)==0&&verzija==os.verzija &&tip==os.tip&&golemina==os.golemina;
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (verzija==os.verzija)
            return 0;
        else if (os.verzija>verzija)
            return -1;
        else return 1;
    }

    bool istaFamilija(const OperativenSistem &os) {
        return strcmp(ime,os.ime)==0&&tip==os.tip;
    }

};

class Repozitorium {
private:
    char ime[20];
    OperativenSistem * sistemi;
    int brSistemi;

    void copy(const Repozitorium &r) {
        strcpy(this->ime,r.ime);
        this->brSistemi=r.brSistemi;
        this->sistemi = new OperativenSistem [brSistemi];
        for (int i=0; i<brSistemi; i++)
            this->sistemi[i]=r.sistemi[i];
    }
public:
    Repozitorium(char * repoName="") {
        strcpy(this->ime,repoName);
        sistemi = new OperativenSistem [0];
        brSistemi = 0;
    }

    Repozitorium (const Repozitorium &r) {
        copy(r);
    }

    Repozitorium &operator = (const Repozitorium &r) {
        if (this!=&r) {
            delete [] sistemi;
            copy(r);
        }
        return *this;
    }


    ~Repozitorium () {
        delete [] sistemi;
    }

    void pecatiOperativniSistemi() {
        cout<<"Repozitorium: "<<ime<<endl;
        for (int i=0; i<brSistemi; i++)
            sistemi[i].pecati();
    }
    void izbrishi (const OperativenSistem &izbrishi) {
        int idx = -1;
        for (int i=0; i<brSistemi; i++) {
            if (sistemi[i].ednakviSe(izbrishi)) {
                idx = i;
                break;
            }
        }
        if (idx==-1)
            return ;

        OperativenSistem * tmp = new OperativenSistem[brSistemi-1];
        int j=0;
        for (int i=0; i<brSistemi; i++) {
            if (i!=idx) {
                tmp[j]=sistemi[i];
                j++;
            } else {
                continue;
            }
        }
        brSistemi--;
        delete [] sistemi;
        sistemi = tmp;

    }
    void dodadi (const OperativenSistem &os) {
        for (int i=0; i<brSistemi; i++)
            if (sistemi[i].istaFamilija(os)&&sistemi[i].sporediVerzija(os)==-1) {
                sistemi[i]=os;
                return ;
            }

        OperativenSistem * tmp = new OperativenSistem [brSistemi+1];
        for (int i=0; i<brSistemi; i++)
            tmp[i]=sistemi[i];

        tmp[brSistemi++]=os;
        delete [] sistemi;
        sistemi = tmp;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++) {
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }
    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}