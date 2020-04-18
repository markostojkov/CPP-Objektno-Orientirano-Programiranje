#include <iostream>
#include <cstring>
using namespace std;


class PlDrustvo {
    protected:
        char *ime;
        int pominatiTuri;
        int brojNaClenovi;

        void copy(char *ime, int pominatiTuri, int brojNaClenovi) {
            this->ime = new char[strlen(ime) + 1];
            strcpy(this->ime, ime);
            this->pominatiTuri = pominatiTuri;
            this->brojNaClenovi = brojNaClenovi; 
        }

    public:
        PlDrustvo () {
            char *ime;
            this->copy(ime, 0, 0);
        }

        PlDrustvo (char *ime, int pominatiTuri, int brojNaClenovi) {
            this->copy(ime, pominatiTuri, brojNaClenovi);
        }

        PlDrustvo &operator= (PlDrustvo &planinskoDrustvo){
            if(this != &planinskoDrustvo){
                this->copy(planinskoDrustvo.ime, planinskoDrustvo.pominatiTuri, planinskoDrustvo.brojNaClenovi);
            }
            return *this;
        }

        PlDrustvo &operator+ (PlDrustvo &planinskoDrustvo) {

            int brojNaClenovi = this->brojNaClenovi + planinskoDrustvo.brojNaClenovi;

            if(this->brojNaClenovi > planinskoDrustvo.brojNaClenovi){
                PlDrustvo temp(this->ime, this->pominatiTuri, brojNaClenovi);
                return temp;
            }
            else if(this->brojNaClenovi < planinskoDrustvo.brojNaClenovi){
                PlDrustvo temp(planinskoDrustvo.ime, planinskoDrustvo.pominatiTuri, brojNaClenovi);
                return temp;
            }
        }

        bool operator < (PlDrustvo &planinskoDrustvo) {
            if (this->brojNaClenovi < planinskoDrustvo.brojNaClenovi) return true;
            else return false;
        }

        bool operator > (PlDrustvo &planinskoDrustvo) {
            if (this->brojNaClenovi > planinskoDrustvo.brojNaClenovi) return true;
            else return false;
        }

        friend ostream &operator<< (ostream &os, PlDrustvo &planinskoDrustvo) {
            cout << "Ime: " 
                 << planinskoDrustvo.ime
                 << " "
                 << "Turi: " 
                 << planinskoDrustvo.pominatiTuri
                 << " "
                 << "Clenovi: " 
                 << planinskoDrustvo.brojNaClenovi 
                 << endl; 
            return os;
        }

        friend void najmnoguClenovi(PlDrustvo *drustva, int brojnadrustva);

        ~PlDrustvo(){}
};

void najmnoguClenovi(PlDrustvo *planinskiDrustva, int brojNaDrustva){
    int max = 0;
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: ";
    for(int i = 0; i < brojNaDrustva; i++){
        if(planinskiDrustva[i].brojNaClenovi > planinskiDrustva[max].brojNaClenovi)
            max = i;
    }
    cout<< planinskiDrustva[max];
}

int main()
{        		
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;
    	
   	}
    
    pl = drustva[0] + drustva[1];
    cout<<pl;
    
    najmnoguClenovi(drustva, 3);
    
    return 0;
}

