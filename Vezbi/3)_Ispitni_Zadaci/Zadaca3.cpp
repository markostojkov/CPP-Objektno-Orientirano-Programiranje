#include <iostream>
#include <cstdlib>
#include <cstring>


using namespace std;


class SMS
{
    protected:
        double cena;
        char pretplatnickiBroj[20];
    
    public:
        static double procentZaRegularnaPoraka;
        static double porecentZaStranstvoPoraka;

        SMS()
        { }

        SMS(char *pretplatnickiBroj, double cena)
        {
            strcpy(this->pretplatnickiBroj, pretplatnickiBroj);
            this->cena = cena;
        }

        char *getPretplatnickiBroj()
        {
            return this->pretplatnickiBroj;
        }

        double getCena()
        {
            return this->cena;
        }

        friend ostream &operator<<(ostream &os, SMS *smsPoraka)
        {
            os << "Tel: " << smsPoraka->getPretplatnickiBroj() << " - cena: " << smsPoraka->SMS_cena() << "den." << endl;

            return os;
        }

        static void set_rProcent(double n);

        static void set_sProcent(double n);

        virtual const int classType() = 0;

        virtual double SMS_cena() = 0;

        virtual ~SMS()
        {

        }
};

double SMS::procentZaRegularnaPoraka = 300;
double SMS::porecentZaStranstvoPoraka = 150;

void SMS::set_rProcent(double n)
{
    SMS::procentZaRegularnaPoraka = n;
}

void SMS::set_sProcent(double n)
{
    SMS::porecentZaStranstvoPoraka = n;
}


class RegularSMS : public SMS
{
    protected:
        char *message;
        bool roaming;
    
    public:
        RegularSMS(char *pretplatnickiBroj, double cena, char *message, bool roaming)
            : SMS(pretplatnickiBroj, cena)
        {
            this->message = new char[strlen(message) + 1];
            strcpy(this->message, message);
            this->roaming = roaming;
        }

        double SMS_cena()
        {
            int cenaSporedKarakteri = strlen(this->message) / 160;
            if (strlen(this->message) % 160 > 0)
            {
                cenaSporedKarakteri++;
            }

            double cena = this->cena * cenaSporedKarakteri;

            if (this->roaming)
            {
                return cena + (cena * SMS::procentZaRegularnaPoraka) / 100.0;
            }
            
            cena += (cena * 18) / 100.0;

            return cena;
        }

        const int classType()
        {
            return 1;
        }
};


class SpecialSMS : public SMS
{
    protected:
        bool humanitarniCeli;
    
    public:
        SpecialSMS(char *pretplatnickiBroj, double cena, bool humanitarniCeli)
            : SMS(pretplatnickiBroj, cena)
        {
            this->humanitarniCeli = humanitarniCeli;
        }

        double SMS_cena()
        {
            double cena = this->cena;

            if (this->humanitarniCeli)
            {
                return cena;
            }
            cena += cena * SMS::porecentZaStranstvoPoraka / 100.0;
            
            return cena;
        }

        const int classType()
        {
            return 2;
        }
};


void vkupno_SMS(SMS** poraka, int n)
{
    double regularnaCena = 0, specijalnaCena = 0;
    int regularniPoraki = 0, specijalniPoraki = 0;

    for (int i = 0; i < n; i++)
    {
        if (poraka[i]->classType() == 1)
        {
            regularnaCena += poraka[i]->SMS_cena();
            regularniPoraki++;
        }
        else
        {
            specijalnaCena += poraka[i]->SMS_cena();
            specijalniPoraki++;
        }
    }

    cout << "Vkupno ima " << regularniPoraki << " regularni SMS poraki i nivnata cena e: " << regularnaCena << endl;
    cout << "Vkupno ima " << specijalniPoraki << " specijalni SMS poraki i nivnata cena e: " << specijalnaCena << endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;
				
				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << sms1;
        
            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;	
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << sms2;
        
        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << sms1;
        
            cin >> tel;
			cin >> cena;
			cin >> hum;	
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << sms2;
        
        delete sms1, sms2;
	}
	
	return 0;
}
