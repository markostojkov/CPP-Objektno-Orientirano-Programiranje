#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;


class Employee 
{
    protected:
        char *ime;
        int godini;
        int rabotnoIskustvo;

    public:
        Employee()
        {
            this->ime = new char[12];
            this->godini = 0;
            this->rabotnoIskustvo = 0;
        }

        Employee(char *ime, int godini, int rabotnoIskustvo)
        {
            this->ime = new char[strlen(ime) + 1];
            strcpy(this->ime, ime);
            this->godini = godini;
            this->rabotnoIskustvo = rabotnoIskustvo;
        }
        virtual double plata() = 0;
        
        virtual double bonus() = 0;

        virtual int getType() = 0;

        int getGodini()
        {
            return this->godini;
        }

        virtual ~Employee(){
            delete [] this->ime;
        }
};


class SalaryEmployee : public Employee
{
    protected:
        int osnovnaPlata;

    public:
        SalaryEmployee(char *ime, int godini, int rabotnoIskustvo, int osnovnPlata)
        : Employee(ime, godini, rabotnoIskustvo)
        {
            this->osnovnaPlata = osnovnaPlata;
        }

        int getType()
        {
            return 1;
        }

        double plata()
        {
            return this->osnovnaPlata + this->bonus();
        }

        double bonus()
        {
            return (this->osnovnaPlata / 100.0) * this->rabotnoIskustvo;
        }
};


class HourlyEmployee : public Employee
{
    protected:
        int odraboteniSaati;
        int osnovnaPlataPoChas;

    public:
        HourlyEmployee(char *ime, int godini, int rabotnoIskustvo, int odraboteniSaati, int osnovnaPlataPoChas)
        : Employee(ime, godini, rabotnoIskustvo)
        {
            this->odraboteniSaati = odraboteniSaati;
            this->osnovnaPlataPoChas = osnovnaPlataPoChas;
        }

        int getType()
        {
            return 2;
        }

        double plata()
        {
            return (this->odraboteniSaati * this->osnovnaPlataPoChas) + this->bonus();
        }

        double bonus()
        {
            if (this->odraboteniSaati > 320)
            {
                return (this->osnovnaPlataPoChas / 100.0) * (this->odraboteniSaati - 320) * 50; 
            }
            return 0;
        }
};


class Freelancer : public Employee
{
    protected:
        int zavrseniProekti;
        double sumiOdProekti[10];

    public:
        Freelancer(char *ime, int godini, int rabotnoIskustvo, int zavrseniProekti, double sumiOdProekti[])
        : Employee(ime, godini, rabotnoIskustvo)
        {
            this->zavrseniProekti = zavrseniProekti;
            for (int i = 0; i < 10; i++)
            {
                this->sumiOdProekti[i] = sumiOdProekti[i];
            }
        }

        int getType()
        {
            return 3;
        }

        double plata()
        {
            return this->getSuma() + this->bonus();
        }

        double bonus()
        {
            if (this->zavrseniProekti > 5)
            {
                return (this->zavrseniProekti - 5) * 1000;
            }
            return 0;
        }

        double getSuma()
        {
            double suma = 0;
            for (int i = 0; i < 10; i++)
            {
                suma += this->sumiOdProekti[i]; 
            }
            return suma;
        }
};


class Company
{
    protected:
        char *imeNaKompanija;
        int brojNaVraboteni;
        Employee **employees;

    public:
        Company(char *imeNaKompanija)
        {
            this->imeNaKompanija = new char[strlen(imeNaKompanija) + 1];
            strcat(this->imeNaKompanija, imeNaKompanija);
            this->employees = new Employee*[0];
            this->brojNaVraboteni = 0;
        }

        double vkupnaPlata()
        {
            double plata = 0;
            for (int i = 0; i < this->brojNaVraboteni; i++)
            {
                plata += this->employees[i]->plata();
            }
            return plata;
        }

        double filtriranaPlata(Employee *employee)
        {
            double plata = 0;
            for (int i = 0; i < this->brojNaVraboteni; i++)
            {
                if (this->employees[i] == employee)
                {
                    plata += this->employees[i]->plata();
                }
            }
            return plata;
        }

        void pecatiRabotnici()
        {
            int freelancer = 0, salaryEmployee = 0, hourlyEmployee = 0;
            for (int i = 0; i < this->brojNaVraboteni; i++)
            {
                switch (this->employees[i]->getType())
                {
                case 1:
                    salaryEmployee++;
                    break;
                case 2:
                    hourlyEmployee++;
                    break;
                case 3:
                    freelancer++;
                    break;
                default:
                    break;
                }
            }
            cout << "Vo kompanijata " << this->imeNaKompanija << " rabotat:" <<endl;
            cout << "Salary employees: " << salaryEmployee << endl;
            cout << "Hourly employees: " << hourlyEmployee << endl;
            cout << "Freelancers: " << freelancer << endl;
        }

        Company& operator+=(Employee *e)
        {
            Employee** temp = new Employee*[this->brojNaVraboteni+1];
            for (int i = 0; i < this->brojNaVraboteni; i++)
                temp[i] = this->employees[i];
            temp[this->brojNaVraboteni++] =e ;
            delete [] this->employees;
            this->employees = temp;
            return *this;
        }

        ~Company()
        {
            delete [] this->imeNaKompanija;
            for (int i = 0; i < this->brojNaVraboteni; i++)
            {
                delete this->employees[i];
            }
            delete [] this->employees;
        }
};

bool operator ==(Employee &employee1, Employee &employee2)
{
    if (employee1.getGodini() == employee2.getGodini() && employee1.bonus() == employee2.bonus())
    {
        return true;
    }
    return false;
}


int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
    cin >> type;
    cin >> employeeName >> age >> experience;

    if (type == 1) {
        int basicSalary;
        cin >> basicSalary;
        c += new SalaryEmployee(employeeName, age, experience, basicSalary);
    }

    else if (type == 2) {
        int hoursWorked;
        int hourlyPay;
        cin >> hoursWorked >> hourlyPay;
        c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
    }

    else {
        int numProjects;
        cin >> numProjects;
        double projects[10];
        for (int i=0; i < numProjects; ++i) {
        cin >> projects[i];
        }
        c += new Freelancer(employeeName, age, experience, numProjects, projects);
    }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}