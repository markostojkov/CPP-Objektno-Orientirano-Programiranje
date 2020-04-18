#include <iostream>
#include <cstring>
using namespace std;

class Automobile{
private:
    char *marka;
    int *registracija;
    int maxbrzina;
public:
    Automobile() {
        marka = new char[0];
        strcpy(marka,"");
        registracija=new int[0];
        registracija=0;
        maxbrzina=0;
    }
    Automobile (char *m, int *r, int max) {
        this->marka= new char[strlen(m)+1];
        strcpy(marka,m);
        this->registracija= new int [5];
        for (int i=0; i<5; i++) {
            registracija[i]=r[i];
        }
        maxbrzina=max;
    }
    Automobile(const Automobile &a){
        marka = new char[strlen(a.marka)+1];
        strcpy(marka,a.marka);
        registracija = new int[5];
        for(int i=0;i<5;i++)
            registracija[i]=a.registracija[i];
        maxbrzina=a.maxbrzina;
    }
    Automobile &operator=(const Automobile &a){
        if(this!=&a){
            delete [] marka;
            marka = new char[strlen(a.marka)+1];
            strcpy(marka,a.marka);
            delete [] registracija;
            registracija = new int[5];
            for(int i=0;i<5;i++)
                registracija[i]=a.registracija[i];
            maxbrzina=a.maxbrzina;
        }
        return *this;
    }
    ~Automobile(){
        delete [] marka;
        delete [] registracija;
    }
    bool operator==(const Automobile &a){
        int flag=1;
        for(int i=0;i<5;i++){
            if(registracija[i]!=a.registracija[i]){
                flag=0;
                break;
            }
        }
        if(flag==1)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &os, Automobile &a){
        os<<"Marka\t"<<a.marka<<"\tRegistracija[ " ;
        for(int i=0;i<5;i++){
            os<<a.registracija[i]<<" ";
        }
        os<< "]";
        return os;
    }
    int getBrzina(){
        return maxbrzina;
    }
};

class RentACar {
private:
    char ime[100];
    Automobile *niza; //dinamichka alokacija
    int broj;
public:
    RentACar(){
        strcpy(ime,"");
        niza = new Automobile[0];
        niza=0;
        broj=0;
    }
    RentACar(char *ime){
        strcpy(this->ime,ime);
        niza = new Automobile[0];
        niza=0;
        broj=0;
    }
    RentACar(const RentACar &r){
        strcpy(ime,r.ime);
        niza = new Automobile[r.broj];
        for(int i=0;i<r.broj;i++)
            niza[i]=r.niza[i];
        broj=r.broj;
    }
    RentACar &operator=(const RentACar &r){
        if(this!=&r){
            delete [] niza;
            niza = new Automobile[r.broj];
            for(int i=0;i<r.broj;i++)
                niza[i]=r.niza[i];
            broj=r.broj;
            strcpy(ime,r.ime);
        }
        return *this;
    }
    void operator+=(const Automobile &r){
        Automobile *temp = new Automobile[broj+1];
        for(int i=0;i<broj;i++)
            temp[i]=niza[i];
        delete [] niza;
        temp[broj++]=r;
        niza=temp;
    }
    void operator-=(const Automobile &r){
        int flag=0,j=0;
        for(int i=0;i<broj;i++)
            if(niza[i]==r)
            flag=1;
        if(flag==1){
            Automobile *temp = new Automobile[broj-1];
            for(int i=0;i<broj;i++){
                if((niza[i]==r)==false)
                    temp[j++]=niza[i];
            }
            delete [] niza;
            broj=j;
            niza=temp;
        }
    }
    void pecatiNadBrzina(int brzina){
        cout<<ime<<endl;
        for(int i=0;i<broj;i++)
            if(niza[i].getBrzina()>brzina)
            cout<<niza[i];
    }

    ~RentACar() {
        delete [] niza;
    }
};

int main(){
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;

       	Automobile nov=Automobile(marka,regisracija,maximumBrzina);

    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
