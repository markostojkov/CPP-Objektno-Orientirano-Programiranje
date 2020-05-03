#include <iostream>
#include <string.h>

using namespace std;

const int POENI_OD_POBEDA = 3;

class Ekipa
{
protected:
    char ime[15];
    int pobedi;
    int porazi;
    
    void constructor (char *ime, int pobedi, int porazi)
    {
        strcpy(this->ime, ime);
        this->pobedi = pobedi;
        this->porazi = porazi;
    }

public:
    Ekipa()
    {

    }

    Ekipa (char *ime, int pobedi, int porazi)
    {
        this->constructor(ime, pobedi, porazi);
    }

    void pecati ()
    {
        cout << "Ime: " << this->ime << " Pobedi: " << this->pobedi << " Porazi: " << this->porazi;
    }

    ~Ekipa()
    {

    }
};


class FudbalskaEkipa : public Ekipa
{
    protected:
        int crveniKartoni;
        int zoltiKartoni;
        int nereseniNatprevari;

        void constructor (char *ime, int pobedi, int porazi, int crveniKartoni, int zoltiKartoni, int nereseniNatprevari)
        {
            Ekipa::constructor(ime, pobedi, porazi);
            this->crveniKartoni = crveniKartoni;
            this->zoltiKartoni = zoltiKartoni;
            this->nereseniNatprevari = nereseniNatprevari;
        }

    public:
        FudbalskaEkipa()
        {
            char *ime;
            this->constructor(ime, 0, 0, 0, 0, 0);
        }

        FudbalskaEkipa(char *ime, int pobedi, int porazi, int crveniKartoni, int zoltiKartoni, int nereseniNatprevari)
        {
            this->constructor(ime, pobedi, porazi, crveniKartoni, zoltiKartoni, nereseniNatprevari);
        }

        int getPoeni ()
        {
            return this->pobedi * POENI_OD_POBEDA + this->nereseniNatprevari;
        } 

        void pecati ()
        {
            Ekipa::pecati();
            cout << " Nereseni: " << this->nereseniNatprevari << " Poeni: " << this->getPoeni() << endl;
        }

        ~FudbalskaEkipa()
        {

        }
};


int main()
{
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}