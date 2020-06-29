#include <iostream>
#include <cstring>

using namespace std;


enum VidNaKupuvac
{
    Standarder,
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
            this->message = new char[strlen(message)];
            strcpy(this->message, message);
        }

        void error()
        {
            cout << this->message << endl;
        }
};



class Customer
{
    private:
        char ime[50];
        char email[50];
        VidNaKupuvac vidNaKupuvac;      
        int osnovenPopust;
        int dopolnitelenPopust;
        int brojNaKupeniProizvodi;

        void setPopustBasedOnMember()
        {
            if (this->vidNaKupuvac == Lojalen)
            {
                this->osnovenPopust = 10;
                this->dopolnitelenPopust = 0;

            }
            else if(this->vidNaKupuvac == Vip)
            {
                this->osnovenPopust = 10;
                this->dopolnitelenPopust = 20;
            }
            else
            {
                this->osnovenPopust = 0;
                this->dopolnitelenPopust = 0;
            }
        }

    public:
        Customer() { }

        Customer(char ime[50],
            char email[50],
            VidNaKupuvac vidNaKupuvac,    
            int brojNaKupeniProizvodi) 
        {
            strcpy(this->ime, ime);
            strcpy(this->email, email);
            this->vidNaKupuvac = vidNaKupuvac;
            this->brojNaKupeniProizvodi = brojNaKupeniProizvodi;
            this->setPopustBasedOnMember();
        }

        char *getEmail()
        {
            return this->email;
        }

        int getPopust()
        {
            return this->osnovenPopust + this->dopolnitelenPopust;
        }

        void setDiscount1(int osnovenPopust)
        {
            this->osnovenPopust = osnovenPopust;
        }

        void update()
        {
            if (this->brojNaKupeniProizvodi >= 10 && this->vidNaKupuvac == Lojalen)
            {
                this->vidNaKupuvac = Vip;
            }
            if (this->brojNaKupeniProizvodi >= 5 && this->vidNaKupuvac != Vip)
            {
                this->vidNaKupuvac = Lojalen;
            }
            this->setPopustBasedOnMember();
        }

        friend ostream &operator<< (ostream &os, Customer customer)
        {
            os << customer.ime << endl;
            os << customer.email << endl;
            os << customer.brojNaKupeniProizvodi << endl;

            if (customer.vidNaKupuvac == Lojalen)
            {
                os << "loyal " << customer.getPopust() << endl;
            }
            else if(customer.vidNaKupuvac == Vip)
            {
                os << "vip " << customer.getPopust() << endl;
            }
            else
            {
                os << "standard " << customer.getPopust() << endl;
            }

            return os;
        }
};


class FINKI_bookstore
{
    private:
        Customer *customers;
        int brojNaKupuvaci;

    public:
        FINKI_bookstore()
        {
            this->brojNaKupuvaci = 0;
            this->customers = new Customer[this->brojNaKupuvaci];
        }

        FINKI_bookstore &operator+= (Customer customer)
        {
            Customer* temp = new Customer[this->brojNaKupuvaci];

            for (int i = 0; i < this->brojNaKupuvaci; i++)
            {
                if (strcmp(customer.getEmail(), this->customers[i].getEmail()) == 0)
                {
                    throw UserExistsException("The user already exists in the list!");
                }
                temp[i] = this->customers[i];
            }

            temp[this->brojNaKupuvaci] = customer;
            this->brojNaKupuvaci++;
            
            this->customers = temp;

            return *this;
        }

        void setCustomers(Customer customers[], int n)
        {
            this->customers = new Customer[n];
            this->brojNaKupuvaci = n;
            for (int i = 0; i < n; i++)
            {
                this->customers[i] = customers[i];
            }
        }

        void update()
        {
            for (int i = 0; i < this->brojNaKupuvaci; i++)
            {
                this->customers[i].update();
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
  const int MAX = 50;
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
