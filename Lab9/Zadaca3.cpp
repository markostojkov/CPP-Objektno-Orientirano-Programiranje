#include<iostream>
#include<cstring>
#include <stdio.h>

using namespace std;


class InvalidDateException
{
    protected:
        int den;
        int mesec;
        int godina;

    public:
        InvalidDateException(int den, int mesec, int godina)
        {
            this->den = den;
            this->mesec = mesec;
            this->godina = godina;
        }

        void printMessage()
        {
            printf("Invalid Date %d/%d/%d\n", this->den, this->mesec, this->godina);
        }
};


class NotSupportedCurrencyException
{
    protected:
        char valuta[3];

    public:
        NotSupportedCurrencyException(char *valuta)
        {
            strcpy(this->valuta, valuta);
        }

        void printMessage()
        {
            cout << this->valuta << " is not a supported currency" << endl;
        }  
};


class Transakcija 
{
    protected:
        int den;
        int mesec;
        int godina;
        double paricenIznos;

    public:
        static double EUR;
        static double USD;

        Transakcija(int den, int mesec, int godina, double paricenIznos)
        {
            this->checkDatum(den, mesec, godina);
            this->paricenIznos = paricenIznos;
        }

        static void setEUR(double eurVal);

        static void setUSD(double usdVal);

        void checkDatum(int den, int mesec, int godina)
        {
            if (den < 1 || den > 31 || mesec < 1 || mesec > 12)
            {
                throw InvalidDateException(den, mesec, godina);
            }
            this->den = den;
            this->mesec = mesec;
            this->godina = godina;
        }

        virtual double voDenari() = 0;

        virtual double voEvra() = 0;

        virtual double voDolari() = 0;

        virtual void pecati() {};

        ~Transakcija()
        {}
};


double Transakcija::EUR = 61.0;
double Transakcija::USD = 50.0;
void Transakcija::setEUR(double newEUR){
    EUR = newEUR;
}
void Transakcija::setUSD(double newUSD){
    USD = newUSD;
}

class DenarskaTransakcija : public Transakcija
{
public:
    DenarskaTransakcija(int den, int mesec, int godina, double paricenIznos)
        : Transakcija(den, mesec, godina, paricenIznos)
    {}

    double voDenari()
    {
        return this->paricenIznos;
    }

    double voEvra()
    {
        return this->paricenIznos / this->EUR;
    }

    double voDolari()
    {
        return this->paricenIznos / this->USD;
    }

    void pecati()
    {
        cout << this->den << "/" << this->mesec << "/" << this->godina << " " << this->paricenIznos << " MKD" << endl;
    }
};


class DeviznaTransakcija : public Transakcija
{
protected:
    char valuta[3];

public:
    DeviznaTransakcija(int den, int mesec, int godina, double paricenIznos, char *valuta)
        : Transakcija(den, mesec, godina, paricenIznos)
    {
        this->checkValuta(valuta);
    }

    void checkValuta(char *valuta)
    {
        if(strcmp(valuta, "USD") != 0 && strcmp(valuta, "EUR") != 0) throw NotSupportedCurrencyException(valuta);
        strcpy(this->valuta, valuta);
    }

    double voDenari()
    {
        if (strcmp(this->valuta, "USD") == 0)
        {
            return this->paricenIznos * this->USD;
        }
        else if(strcmp(this->valuta, "EUR") == 0)
        {
            return this->paricenIznos * this->EUR;
        }
        return 0;
    }

    double voEvra()
    {
        if (strcmp(this->valuta, "USD") == 0)
        {
            return this->paricenIznos * (this->USD / this->EUR);
        }
        else if(strcmp(this->valuta, "EUR") == 0)
        {
            return this->paricenIznos;
        }
        return 0;
    }

    double voDolari()
    {
        if (strcmp(this->valuta, "EUR") == 0)
        {
            return this->paricenIznos * (this->EUR / this->USD);
        }
        else if(strcmp(this->valuta, "USD") == 0)
        {
            return this->paricenIznos;
        }
        return 0;
    }

    void pecati()
    {
        cout << this->den << "/" << this->mesec << "/" << this->godina << " " << this->paricenIznos << " " << this->valuta << endl;
    }
};


class Smetka
{
    protected:
        Transakcija **transakcii;
        int izvrseniTransakcii;
        char brojNaSmetka[15];
        double pocetnoSaldo;

    public:
        Smetka(char *brojNaSmetka, double pocetnoSaldo)
        {
            strcpy(this->brojNaSmetka, brojNaSmetka);
            this->pocetnoSaldo = pocetnoSaldo;
            this->izvrseniTransakcii = 0;
            this->transakcii = new Transakcija*[this->izvrseniTransakcii];
        }

        Smetka &operator+=(Transakcija *transakcija)
        {
            Transakcija ** pom = new Transakcija*[this->izvrseniTransakcii + 1];
            for(int i = 0; i < this->izvrseniTransakcii; i++) {
                pom[i] = this->transakcii[i];
            }
            pom[this->izvrseniTransakcii] = transakcija;
            this->izvrseniTransakcii++;
            
            delete [] this->transakcii;

            this->transakcii = pom;

            return *this;
        }

        void izvestajVoDenari()
        {
            double izvestaj = this->pocetnoSaldo;

            for (int i = 0; i < this->izvrseniTransakcii; i++)
            {
                izvestaj += this->transakcii[i]->voDenari();
            }

            cout << "Korisnikot so smetka: " << this->brojNaSmetka <<
            " ima momentalno saldo od " << izvestaj << " MKD" << endl;
        }

        void izvestajVoEvra()
        {
            double izvestaj = this->pocetnoSaldo / Transakcija::EUR;

            for (int i = 0; i < this->izvrseniTransakcii; i++)
            {
                izvestaj += this->transakcii[i]->voEvra();
            }

            cout << "Korisnikot so smetka: " << this->brojNaSmetka <<
            " ima momentalno saldo od " << izvestaj << " EUR" << endl;
        }

        void izvestajVoDolari()
        {
            double izvestaj = this->pocetnoSaldo / Transakcija::USD;

            for (int i = 0; i < this->izvrseniTransakcii; i++)
            {
                izvestaj += this->transakcii[i]->voDolari();
            }

            cout << "Korisnikot so smetka: " << this->brojNaSmetka <<
            " ima momentalno saldo od " << izvestaj << " USD" << endl;
        }

        void pecatiTransakcii()
        {
            for (int i = 0; i < this->izvrseniTransakcii; i++)
            {
                this->transakcii[i]->pecati();
            }
        }

        ~Smetka()
        {
            delete [] this->transakcii;
        }

};


int main () {
	
	Smetka s ("300047024112789", 1500);
	
	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];
	
	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
        try
        {
            if (tip==2){
                cin>>valuta;
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
            }
            else {
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
            }
        }
        catch(NotSupportedCurrencyException currenyException)
        {
            currenyException.printMessage();
        }
        catch(InvalidDateException dateExpcetion)
        {
            dateExpcetion.printMessage();
        }
			
	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();
    
    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;
    
        
    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();
    
	
	
	return 0;
}