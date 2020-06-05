#include <iostream>
#include <cstring>
#include <vector>

#define MAX 50

using namespace std;


enum VidNaKupuvac
{
    Standarden,
    Lojalen,
    Vip
};


class UserExistsException
{
    private:
        char *message;

    public:
        UserExistsException(char *message)
        {
            this->message = new char[strlen(message) + 1];
            strcpy(this->message, message);
        }

        void error()
        {
            cout << this->message << endl;
        }
};


class Customer
{
    protected:
        char ime[50];
        char elektronskaAdresa[50];
        VidNaKupuvac vidNaKupuvac;
        int dopolnitelenPopust;
        int brojNaKupeniProizvodi;
        int osnovenPopust;

    public:
        Customer()
        {

        }

        Customer(char *ime,
            char *elektronskaAdresa,
            VidNaKupuvac vidNaKupuvac,
            int brojNaKupeniProizvodi)
            {
                strcpy(this->ime, ime);
                strcpy(this->elektronskaAdresa, elektronskaAdresa);
                this->vidNaKupuvac = vidNaKupuvac;
                this->brojNaKupeniProizvodi = brojNaKupeniProizvodi;
                switch (vidNaKupuvac)
                {
                    case Standarden:
                        this->osnovenPopust = 0;
                        break;
                    case Lojalen:
                        this->osnovenPopust = 10;
                        break;
                    case Vip:
                        this->osnovenPopust = 10;
                        this->dopolnitelenPopust = 20;
                        break;
                    default:
                        break;
                }
            }

        char* getElektronskaAdresa()
        {
            return this->elektronskaAdresa;
        }

        VidNaKupuvac getVidNaKupuvac()
        {
            return this->vidNaKupuvac;
        }

        int getBrojNaKupeniProizvodi()
        {
            return this->brojNaKupeniProizvodi;
        }

        void setVidNaKupuvac(VidNaKupuvac vidNaKupuvac)
        {
            this->vidNaKupuvac = vidNaKupuvac;
            switch (vidNaKupuvac)
            {
                case Lojalen:
                    this->osnovenPopust = 10;
                    break;
                case Vip:
                    this->osnovenPopust = 10;
                    this->dopolnitelenPopust = 20;
                    break;
                default:
                    break;
            }
        }

        void setDiscount1(int n)
        {
            this->osnovenPopust = n;
        }

        friend ostream &operator<< (ostream &os, Customer customer)
        {
            os << customer.ime << endl;
            os << customer.elektronskaAdresa << endl;
            os << customer.brojNaKupeniProizvodi << endl;
            switch (customer.vidNaKupuvac)
            {
                case Standarden:
                    os << "standard " << customer.osnovenPopust << endl;
                    break;
                case Lojalen:
                    os << "loyal " << customer.osnovenPopust << endl;
                    break;
                case Vip:
                    os << "vip " << customer.dopolnitelenPopust + customer.osnovenPopust << endl;
                    break;
                default:
                    break;
            }
            return os;
        }
};


class FINKI_bookstore
{
    protected:
        vector<Customer> customers;
        int brojNaKupuvaci;

    public:
        FINKI_bookstore()
        {
            this->brojNaKupuvaci = 0;
        }

        FINKI_bookstore &operator+= (Customer customer)
        {
            for (int i = 0; i < this->brojNaKupuvaci; i++)
            {
                if (strcmp(this->customers.at(i).getElektronskaAdresa(), customer.getElektronskaAdresa()) == 0)
                {
                    throw UserExistsException("The user already exists in the list!");
                }
            }

            this->customers.push_back(customer);
            this->brojNaKupuvaci++;

            return *this;
        }

        void update()
        {
            for (int i = 0; i < this->brojNaKupuvaci; i++)
            {
                if (this->customers.at(i).getBrojNaKupeniProizvodi() > 5 && this->customers.at(i).getVidNaKupuvac() == Standarden)
                {
                    this->customers.at(i).setVidNaKupuvac(Lojalen);
                }
                else if(this->customers.at(i).getBrojNaKupeniProizvodi() > 10 && this->customers.at(i).getVidNaKupuvac() == Lojalen)
                {
                    this->customers.at(i).setVidNaKupuvac(Vip);
                }
            }
        }

        void setCustomers(Customer *customers, int n)
        {
            this->brojNaKupuvaci = n;
            for (int i = 0; i < n; i++)
            {
                this->customers.push_back(customers[i]);
            }
        }

        friend ostream &operator<< (ostream &os, FINKI_bookstore bookstore)
        {
            for (int i = 0; i < bookstore.brojNaKupuvaci; i++)
            {
                os << bookstore.customers[i];
            }
            return os;
        }
};


int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (VidNaKupuvac) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (VidNaKupuvac) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (VidNaKupuvac) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (VidNaKupuvac) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (VidNaKupuvac) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (VidNaKupuvac) tC, numProducts);
      customers[i] = c;
    }
    try
    {
        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (VidNaKupuvac) tC, numProducts);
        try
        {
            fc+=c;
        }
        catch(UserExistsException userExistsException)
        {
            userExistsException.error();
        }
        
        cout << fc;
    }
    catch(UserExistsException userExistsException)
    {
        userExistsException.error();
    }
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (VidNaKupuvac) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
   
}
