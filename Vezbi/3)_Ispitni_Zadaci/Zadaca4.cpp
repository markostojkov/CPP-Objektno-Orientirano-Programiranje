#include <iostream>
#include <cstring>

using namespace std;


enum TipNaUred
{
    Smartphone,
    Kompjuter
};


class InvalidProductionDate
{
    private:
        char *message;

    public:
        InvalidProductionDate(char *message)
        {
            this->message = new char[strlen(message) + 1];
            strcpy(this->message, message);
        }

        void error()
        {
            cout << this->message << endl;
        }
};


class Device
{
    private:
        char model[100];
        TipNaUred tipNaUred;
        float potrebniChasoviZaProverka;
        int godinaNaProizvodstvo;

    public:
        static double potrebniChasoviZaProverkaOsvnovnoVreme;

        Device()
        {}

        Device(char *model, TipNaUred tipNaUred, int godinaNaProizvodstvo)
        {
            strcpy(this->model, model);
            this->tipNaUred = tipNaUred;
            this->godinaNaProizvodstvo = godinaNaProizvodstvo;
            this->potrebniChasoviZaProverka = this->setPotrebniChasoviZaProverka(godinaNaProizvodstvo);
        }

        float setPotrebniChasoviZaProverka(int godinaNaProizvodstvo)
        {
            float potrebniChasoviZaProverka = this->potrebniChasoviZaProverkaOsvnovnoVreme;

            if (godinaNaProizvodstvo > 2015)
            {
                potrebniChasoviZaProverka += 2;
            }
            if (this->tipNaUred == Kompjuter)
            {
                potrebniChasoviZaProverka += 2;
            }

            return potrebniChasoviZaProverka;
        }

        int getProductionDate()
        {
            return this->godinaNaProizvodstvo;
        }

        friend ostream &operator<< (ostream &os, Device device)
        {
            os << device.model << endl;
            if (device.tipNaUred == Smartphone)
            {
                os << "Mobilen " << device.setPotrebniChasoviZaProverka(device.getProductionDate()) << endl;
            }
            else if (device.tipNaUred == Kompjuter)
            {
                os << "Laptop " << device.setPotrebniChasoviZaProverka(device.getProductionDate()) << endl;
            }
            return os;
        }

        static void setPocetniCasovi(double pocetniChasovi);
};


double Device::potrebniChasoviZaProverkaOsvnovnoVreme = 1;
void Device::setPocetniCasovi(double pocetniChasovi)
{
    Device::potrebniChasoviZaProverkaOsvnovnoVreme = pocetniChasovi;
}


class MobileServis
{
    private:
        char adresa[100];
        int brojNaUredi;
        Device *devices;

    public:
        MobileServis(char *adresa)
        {
            strcpy(this->adresa, adresa);
            this->brojNaUredi = 0;
            this->devices = new Device[this->brojNaUredi + 1];
        }

        MobileServis &operator+= (Device device)
        {
            int productionDate = device.getProductionDate();

            if (productionDate < 2000 || productionDate > 2019)
            {
                throw InvalidProductionDate("Невалидна година на производство");
            }
            else 
            {
                Device *temp = new Device[this->brojNaUredi + 1];
                
                for (int i = 0; i < this->brojNaUredi; i++)
                {
                    temp[i] = this->devices[i];
                }

                temp[this->brojNaUredi] = device;
                this->brojNaUredi++;
                this->devices = temp;
            }

            return *this;
        }

        void pecatiUredi()
        {
            cout << "Ime: " << this->adresa << endl;;
            for (int i = 0; i < this->brojNaUredi; i++)
            {
                cout << this->devices[i];
            }
        }
};


int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(TipNaUred)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(TipNaUred)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiUredi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(TipNaUred)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate invalidProductionDate)
            {
                invalidProductionDate.error();
            }
        }
        t.pecatiUredi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(TipNaUred)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate invalidProductionDate)
            {
                invalidProductionDate.error();
            }
        }
        MobileServis t2 = t;
        t2.pecatiUredi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(TipNaUred)tipDevice,godina);

            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate invalidProductionDate)
            {
                invalidProductionDate.error();
            }
        }
        t.pecatiUredi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiUredi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(TipNaUred)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate invalidProductionDate)
            {
                invalidProductionDate.error();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiUredi();
	}

	return 0;

}

