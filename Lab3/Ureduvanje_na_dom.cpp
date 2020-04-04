#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


class Table {
protected:
    int length;
    int width;
    
public:
    Table() {
    	this->length = 0;
        this->width = 0;
    }
    
    Table(int length, int width) {
    	this->length = length;
        this->width = width;
    }

    void print() {
    	cout<<" Masa: "<<this->length<<" "<<this->width<<endl;
    }
};

class Room {
protected:
    Table table;
    int length;
    int width;
    
public:
    Room() {
        this->table = table;
    	this->length = 0;
        this->width = 0;
    }
    
    Room(Table table, int length, int width) {
        this->table = table;
    	this->length = length;
        this->width = width;
    }

    void print() {
    	cout<<" Soba: "<<this->length<<" "<<this->width;
        this->table.print();
    }
};

class House {
protected:
    Room room;
    char address[50];
    
public:
    House() {
        this->room = room;
    	strcpy(this->address, "");
    }
    
    House(Room room, char* address) {
        this->room = room;
    	strcpy(this->address, address);
    }

    void print() {
    	cout<<"Adresa: "<<this->address;
        this->room.print();
    }
};


//ne smee da se menuva main funkcijata!
int main(){
    int n, masaSirina,masaDolzina, sobaSirina,sobaDolzina;
    char adresa[30];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>masaSirina;
        cin>>masaDolzina;
    	Table m(masaSirina,masaDolzina);
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Room s(m, sobaSirina,sobaDolzina);
        cin>>adresa;
    	House k(s,adresa);
    	k.print();
	}
    
    return 0;
}