#include <iostream>
#include <cstring>
using namespace std;
 
class Lekar {
    protected:
        int faksimil;
        char ime[100];
        char prezime[100];
        double pocetna;
   
    public:
    Lekar(){}
   
    Lekar(int faksimil, char *ime, char *prezime, double pocetna){
        this->faksimil = faksimil;
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->pocetna = pocetna;
    }
   
    Lekar(const Lekar &rhs){
        this->faksimil = rhs.faksimil;
        strcpy(this->ime, rhs.ime);
        strcpy(this->prezime, rhs.prezime);
        this->pocetna = rhs.pocetna;
    }
   
    void pecati(){
        cout << this->faksimil << ": " << this->ime << " " << this->prezime << endl;
           
    }
   
    double plata(){
        return this->pocetna;
    }
};
 
class MaticenLekar: public Lekar {
    private:
        int brPacienti;
        double *kotizacii;
   
    public:
        MaticenLekar(){
            this->brPacienti = 0;
            this->kotizacii = new double[brPacienti];
        }
       
        MaticenLekar(Lekar &rhs, int brPacienti, double *kotizacii): Lekar(rhs){
            this->brPacienti = brPacienti;
            this->kotizacii = new double[brPacienti+1];
            for(int i=0; i<brPacienti; i++)
                this->kotizacii[i] = kotizacii[i];
        }
   
        MaticenLekar(const MaticenLekar &rhs){
            this->brPacienti = rhs.brPacienti;
            this->kotizacii = new double[rhs.brPacienti+1];
            for(static int i=0; i<rhs.brPacienti; i++)
                this->kotizacii[i] = rhs.kotizacii[i];
        }
       
    void pecati(){
        Lekar::pecati();
        //cout << Lekar::faksimil << ": " << Lekar::ime << " " << Lekar::prezime << endl;
        cout << "Prosek na kotizacii: ";
            int sum=0;
            for(int i=0; i<brPacienti; i++)
                sum+=kotizacii[i];
        cout << sum/brPacienti << endl;
    }
   
    double plata(){
        double sum=0;
        for(int i=0; i<this->brPacienti; i++){
            sum+=kotizacii[i];
        }
        return Lekar::pocetna+sum/this->brPacienti*0.3;
    }
};
 
int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;
   
    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];
   
    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);      
    }
   
    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }
   
    int testCase;
    cin>>testCase;
   
    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }
   
    delete [] lekari;
    delete [] maticni;
   
    return 0;
}