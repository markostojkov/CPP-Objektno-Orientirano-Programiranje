#include <iostream>
#include <cstring>
#include <vector>


using namespace std;


class AlkoholPercentException
{
public:
    AlkoholPercentException()
    {
    }

    void printMessage()
    {
        cout << "Pogresno vnesen procent na alkohol!" << endl;
    }

};


class RegistrationException
{
public:
    RegistrationException()
    {
    }

    void printMessage()
    {
        cout << "Pogresno vnesena registracija" << endl;
    }
};


class ImaMasa
{
public:
    virtual double vratiMasa() = 0;

    virtual void pecati() = 0;
};


class PaketPijalok
{
protected:
    double volumenNaEdenPaket;
    int kolicina;

public:
    static const double masaNaAmbalaza = 0.2;
    static const double gustina = 0.8;

    PaketPijalok(double volumenNaEdenPaket, int kolicina)
    {
        this->volumenNaEdenPaket = volumenNaEdenPaket;
        this->kolicina = kolicina;
    }

    double vratiMasa()
    {
        return (this->volumenNaEdenPaket * PaketPijalok::gustina + PaketPijalok::masaNaAmbalaza) * this->getKolicina();
    }

    void pecati()
    {
        cout << "Kolicina " << this->kolicina;
    }

    int getKolicina()
    {
        return this->kolicina;
    }
};


class PaketSok : public PaketPijalok, public ImaMasa
{
protected:
    bool gaziran;

public:
    static const double negaziranSokTezina = 0.1;

    PaketSok(double volumenNaEdenPaket, int kolicina, bool gaziran)
        : PaketPijalok(volumenNaEdenPaket, kolicina)
    {
        this->gaziran = gaziran;
    }

    double vratiMasa()
    {
        return this->gaziran ? PaketPijalok::vratiMasa() :
            PaketPijalok::vratiMasa() + PaketSok::negaziranSokTezina * PaketPijalok::getKolicina();
    }

    void pecati()
    {
        cout << "Paket sok" << endl;
        cout << "kolicina " << kolicina << ", so po " <<
            PaketPijalok::volumenNaEdenPaket * PaketPijalok::gustina << " l(dm3)" << endl;
    }
};


class PaketVino : public PaketPijalok, public ImaMasa
{
protected:
    double procentNaAlkohol;

public:
    static const double procentAlkoholKoeficient = 0.9;

    PaketVino(double volumenNaEdenPaket, int kolicina, double procentNaAlkohol)
        : PaketPijalok(volumenNaEdenPaket, kolicina)
    {
        try
        {
            if (procentNaAlkohol > 1 || procentNaAlkohol < 0)
            {
                throw AlkoholPercentException();
            }
            this->procentNaAlkohol = procentNaAlkohol;
        }
        catch (AlkoholPercentException alkoholPercentException)
        {
            alkoholPercentException.printMessage();
        }

    }

    double vratiMasa()
    {
        return PaketPijalok::vratiMasa() * (PaketVino::procentAlkoholKoeficient + this->procentNaAlkohol);
    }

    void pecati()
    {
        cout << "Paket vino" << endl;
        cout << "kolicina " << this->kolicina << ", " << this->procentNaAlkohol * 100
            << "% alkohol od po " << this->volumenNaEdenPaket * PaketPijalok::gustina << " l(dm3)" << endl;
    }
};


class Kamion
{
protected:
    char registracija[9];
    char vozac[50];
    ImaMasa** paketi;
    int brojNaPaketi;

public:
    Kamion(char* registracija, char* vozac)
    {
        this->brojNaPaketi = 0;
        strcpy(this->vozac, vozac);
        this->registriraj(registracija);
    }

    void registriraj(char* registracija)
    {
        if (!isalpha(registracija[0]) || !isalpha(registracija[1]) ||
            !isalpha(registracija[6]) || !isalpha(registracija[7]))
        {
            throw RegistrationException();
        }
        strcpy(this->registracija, registracija);
    }

    void dodadiElement(ImaMasa *paket)
    {
        ImaMasa **temp = new ImaMasa *[this->brojNaPaketi + 1];
        for (int i = 0; i < this->brojNaPaketi; i++)
        {
            temp[i] = this->paketi[i];
        }

        temp[this->brojNaPaketi] = paket;
        this->brojNaPaketi++;
        this->paketi = temp;
    }

    void pecati()
    {
        cout << "Kamion so registracija " << this->registracija
            << " i vozac " << this->vozac << " prenesuva: " << endl;
        for (int i = 0; i < this->brojNaPaketi; i++)
        {
            this->paketi[i]->pecati();
        }
    }

    Kamion pretovar(char* registracija, char* vozac)
    {
        Kamion novKamion(registracija, vozac);
        double maxMasa = -1;
        int maxMasaPozicija;
        for (int i = 0; i < this->brojNaPaketi; i++)
        {
            if (this->paketi[i]->vratiMasa() > maxMasa)
            {
                maxMasaPozicija = i;
                maxMasa = this->paketi[i]->vratiMasa();
            }
        }

        for (int i = 0; i < this->brojNaPaketi; i++)
        {
            if (i != maxMasaPozicija)
            {
                novKamion.dodadiElement(this->paketi[i]);
            }
        }

        return novKamion;
    }

    double vratiVkupnaMasa()
    {
        double vkupnaMasa = 0.0;

        for (int i = 0; i < this->brojNaPaketi; i++)
        {
            vkupnaMasa += this->paketi[i]->vratiMasa();
        }

        return vkupnaMasa;
    }
};




int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    try
    {
        cin >> reg;
        cin >> ime;
        Kamion A(reg, ime);
        ImaMasa** d = new ImaMasa * [5];
        cin >> vol >> kol;
        cin >> g;
        d[0] = new PaketSok(vol, kol, g);
        cin >> vol >> kol;
        cin >> proc;
        d[1] = new PaketVino(vol, kol, proc);
        cin >> vol >> kol;
        cin >> proc;
        d[2] = new PaketVino(vol, kol, proc);
        cin >> vol >> kol;
        cin >> g;
        d[3] = new PaketSok(vol, kol, g);
        cin >> vol >> kol;
        cin >> proc;
        d[4] = new PaketVino(vol, kol, proc);

        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout << "Vkupna masa: " << A.vratiVkupnaMasa() << endl;
        cin >> reg;
        cin >> ime;
        Kamion B = A.pretovar(reg, ime);
        B.pecati();
        cout << "Vkupna masa: " << B.vratiVkupnaMasa() << endl;

    }
    catch (RegistrationException registrationException)
    {
        registrationException.printMessage();
    }

}
