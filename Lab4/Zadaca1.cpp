#include<iostream>
#include<cstring>

using namespace std;

class Avtomobil{
private:
    char boja[20];
    char brand[20];
    char model[20];
public:
    Avtomobil (const char *boja="", const char *brand="", const char *model="")
    {
        strcpy(this->boja, boja);
        strcpy(this->brand, brand);
        strcpy(this->model, model);
    }
    Avtomobil &operator=(const Avtomobil &a)
    {
        if(this!=&a)
        {
            strcpy(this->boja, a.boja);
        	strcpy(this->brand, a.brand);
        	strcpy(this->model, a.model);
        }
        return *this;
    }
    void pecati()
    {
        cout<<boja<<" "<<brand<<" "<<model<<endl;
    }
};

class ParkingPlac{
private:
    char adresa[20];
    char *id;
    int cena;
    int zarabotka;
    Avtomobil *avtomobil;
    int n;
public:
    ParkingPlac(const char *adresa="", const char *id="", int cena=0)
    {
        this->avtomobil=new Avtomobil[0];
        strcpy(this->adresa, adresa);
        this->n=0;
        this->zarabotka=0;
        this->cena=cena;
        this->id=new char [strlen(id)+1];
        strcpy(this->id, id);
    }
    ParkingPlac &operator=(const ParkingPlac &pp)
    {
        if(this!=&pp)
        {
            delete [] avtomobil;
            delete [] id;
            strcpy(this->adresa, pp.adresa);
            this->n=pp.n;
       	 	this->zarabotka=pp.zarabotka;
        	this->cena=pp.cena;
            this->id=new char [strlen(pp.id)+1];
        	strcpy(this->id, pp.id);
            this->avtomobil=new Avtomobil[pp.n];
            for(int i=0; i<pp.n; i++)
                avtomobil[i]=pp.avtomobil[i];
        }
        return *this;
    }
    ~ParkingPlac()
    {
        delete [] id;
        delete [] avtomobil;
    }
    void pecati()
    {
        if(zarabotka)
            cout<<id<<" "<<adresa<<" - "<<zarabotka<<" denari"<<endl;
        else
            cout<<id<<" "<<adresa<<endl;
    }
    char *getId()
    {
        return id;
    }
    void platiCasovi(int casovi)
    {
        zarabotka+=casovi*cena;
    }
    bool daliIstaAdresa(ParkingPlac p)
    {
        return (strcmp(adresa, p.adresa)==0);
    }
    void parkirajVozilo(Avtomobil novoVozilo)
    {
        Avtomobil *nov= new Avtomobil[n+1];
        for(int i=0;i<n;i++)
            nov[i]=avtomobil[i];
        nov[n++]=novoVozilo;
        delete [] avtomobil;
        avtomobil=nov;
    }
    void pecatiParkiraniVozila()
    {
        cout<<"Vo parkingot se parkirani slednite vozila: "<<endl;
        for(int i=0; i<n; i++)
        {
            cout<<i+1<<".";
            avtomobil[i].pecati();
        }
    }
};
int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;
			
			ParkingPlac edna(adresa,id,cenacas);
	        
	        p[i]=edna;
		}
	    
		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;
	        
	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}  
}