#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


class Movie {
    //Movie class with basic props with print method to dispay the props
    //And check the year

    protected:
        char name[100];
        char producer[50];
        char genre[50];
        int year;

    public:
        Movie() {}

        Movie(char *name, char *producer, char *genre, int year) {
            strcpy(this->name, name);
            strcpy(this->producer, producer);
            strcpy(this->genre, genre);
            this->year = year;
        }

        void print() {
            cout<<"Ime: "<< this->name<<endl;
            cout<<"Reziser: "<< this->producer<<endl;
            cout<<"Zanr: "<< this->genre<<endl;
            cout<<"Godina: "<< this->year<<endl;
        }
        
        bool isYear(int year) {
            return this->year == year;
        }
};


void printByYear(vector<Movie> &movies, int n, int year) {
    
    for(int i = 0; i < n; ++i) {
        if(movies.at(i).isYear(year)) movies.at(i).print();
    }
    
}

void inputMovies(vector<Movie> &movies, int n) {
    char name[100], producer[50], genre[50];
    int year;
        
    for(int i = 0; i < n; ++i) {
        cin >> name>> producer >> genre >> year;
        movies.push_back(Movie(name, producer, genre, year));
    }  
}

int main() {
    int n, year;
    cin >> n;
    
    vector<Movie> movies;
    inputMovies(movies, n);
    
    cin >> year;
    printByYear(movies, n, year);
    return 0;
}