#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

enum Extension {txt, pdf, exe};


class File {
    protected:
        char *ime;
        Extension extension;
        char *sopstvenik;
        int golemina;

    public:
        File () {
            this->ime = new char[1];
            this->sopstvenik = new char[1];
            strcpy(this->ime, "");
            strcpy(this->sopstvenik, "");
            this->extension = txt;
            this->golemina = 0;
        }

        File (char *ime, Extension extension, char *sopstvenik, int golemina) {
            this->ime = new char[strlen(ime) + 1];
            this->sopstvenik = new char[strlen(sopstvenik) + 1];
            strcpy(this->ime, ime);
            strcpy(this->sopstvenik, sopstvenik);
            this->extension = extension;
            this->golemina = golemina;
        }

        File (const File &file) {
            this->ime = new char[strlen(file.getIme()) + 1];
            this->sopstvenik = new char[strlen(file.getSopstvenik()) + 1];
            strcpy(this->ime, file.getIme());
            strcpy(this->sopstvenik, file.getSopstvenik());
            this->extension = file.getExtension();
            this->golemina = file.getGolemina();
        }

        const char *getIme () const {
            return this->ime;
        }

        const char *getSopstvenik () const {
            return this->sopstvenik;
        }

        const Extension getExtension () const {
            return this->extension;
        }

        const int getGolemina () const {
            return this->golemina;
        }

        bool equals (const File &file) {
            if(string(this->ime) != string(file.getIme())) return false;
            if(string(this->sopstvenik) != string(file.getSopstvenik())) return false;
            if(this->golemina != file.getGolemina()) return false;
            return true;
        }

        bool equalsType (const File &file) {
            if(this->extension == file.getExtension()) return true;
            return false;
        }

        void print() {
            cout<<"File name: " << this->ime << endl;
            cout<<"File owner: " << this->sopstvenik << endl;
            cout<<"File size: " << this->golemina << endl;
        }

        ~File () {
            delete [] this->ime;
            delete [] this->sopstvenik;
        }

};


class Folder {
    protected:
        char *ime;
        int brojNaDatoteki;
        vector<File> file;

    public:
        Folder(char *ime) {
            this->ime = new char[strlen(ime) + 1];
            strcpy(this->ime, ime);
        }

        void print () {
            cout<< "Folder name: " << this->ime << endl;
            for(int i = 0; i < this->file.size(); i++) this->file.at(i).print();
        }

        void add (const File &file) {
            this->file.push_back(file);
        }

        void remove (const File &file) {
            for(int i = 0; i < this->file.size(); i++) {
                if(this->file.at(i).equals(file)) //this->file.erase(file);
            }
        }

        ~Folder() {
            delete [] this->ime;
        }
};


int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;	

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();
	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}