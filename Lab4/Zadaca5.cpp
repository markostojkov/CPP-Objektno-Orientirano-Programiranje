












#include <iostream>
#include <cstring>
using namespace std;

class List{
private:
    int *br;
    int n;
public:
    List(int *br=0, int n=0)
    {
        this->n=n;
        this->br= new int[n];
        for(int i=0;i<n;i++)
        {
            this->br[i]=br[i];
        }
    }
    List &operator=(const List &l)
    {
        if(this!=&l)
        {
            delete [] br;
            this->n=l.n;
        	this->br= new int[l.n];
        	for(int i=0;i<l.n;i++)
        	{
            	this->br[i]=l.br[i];
        	}
        }
        return *this;
    }
    List(const List &l)
    {
        this->n=l.n;
       	this->br= new int[l.n];
       	for(int i=0;i<l.n;i++)
       	{
           	this->br[i]=l.br[i];
        }
    }
    int get_n(){ return n; }
    void pecati()
    {
        cout<<n<<": ";
        for(int i=0;i<n;i++)
        {
            cout<<br[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    int sum()
    {
        int suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=br[i];
        }
        return suma;
    }
    double average()
    {
        return (double)sum()/n;
    }
    ~List()
    {
        delete [] br;
    }
};

class ListContainer{
private:
    List *lista;
    int n;
    int tries;
public:
    ListContainer(List *lista=0, int n=0, int tries=0)
    {
        this->n=n;
        this->tries=tries;
        this->lista=new List[n];
        for(int i=0;i<n;i++)
        {
            this->lista[i]=lista[i];
        }
    }
    ListContainer &operator=(const ListContainer &lc)
    {
        if(this!=&lc)
        {
            delete [] lista;
            this->n=lc.n;
       		this->tries=lc.tries;
        	this->lista=new List[lc.n];
        	for(int i=0;i<lc.n;i++)
        	{
            	this->lista[i]=lc.lista[i];
        	}
        }
        return *this;
    }
    ListContainer(const ListContainer &lc)
    {
        this->n=lc.n;
   		this->tries=lc.tries;
       	this->lista=new List[lc.n];
       	for(int i=0;i<lc.n;i++)
       	{
           	this->lista[i]=lc.lista[i];
        }
    }
    void addNewList(List l)
    {
        bool isti_se=false;
        for(int i=0;i<n;i++)
        {
            if(lista[i].sum()==l.sum())
                isti_se=true;
        }
        if(!isti_se)
        {
            List *newlist=new List[n+1];
            for(int i=0;i<n;i++)
                newlist[i]=lista[i];
            newlist[n++]=l;
            delete [] lista;
            lista=newlist;
        }
        else tries++;
    }
    void print()
    {
        if(n==0)
        {
            cout<<"The list is empty"<<endl;
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                cout<<"List number: "<<i+1<<" List info: ";
                lista[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<n<<" Failed attempts: "<<tries<<endl;
        }
    }
    int sum()
    {
        int suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=lista[i].sum();
        }
        return suma;
    }
    double average()
    {
        int number_ns=0;
        for(int i=0;i<n;i++)
        {
            number_ns+=lista[i].get_n();
        }
        return sum()/(double)number_ns;
    }
    ~ListContainer()
    {
        delete [] lista;
    }
};

int main() {
	
	ListContainer lc;
	int N;	
	cin>>N;	
    
	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		
		cin>>n;
       
		for (int j=0;j<n;j++){
			cin>>niza[j];
            
		}
       
		List l=List(niza,n);
	
		lc.addNewList(l);
	}	
	
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}