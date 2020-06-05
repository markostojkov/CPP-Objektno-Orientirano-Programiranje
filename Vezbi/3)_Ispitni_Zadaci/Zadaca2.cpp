#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


class Image
{
    protected:
        char *ime;
        char sopstvenik[50];
        int width;
        int height;

    public:
        Image(char *ime = "untitled", char *sopstvenik = "unknown", int width = 800, int height = 800)
        {
            this->ime = new char[strlen(ime)];
            strcpy(this->ime, ime);
            strcpy(this->sopstvenik, sopstvenik);
            this->width = width;
            this->height = height;
        }

        long int fileSize()
        {
            return this->width * this->height * 3;
        }

        bool const &operator> (Image image)
        {
            return this->fileSize() > image.fileSize();
        }

        friend ostream &operator<<(ostream &os, Image image)
        {
            os << image.ime << " " << image.sopstvenik << " " << image.fileSize() << endl;
            return os;
        }
};


class TransparentImage : public Image
{
    protected:
        bool podrzuvaTransparentnost;

    public:
        TransparentImage(char *ime = "untitled",
            char *sopstvenik = "unknown",
            int width = 800,
            int height = 800,
            bool podrzuvaTransparentnost = false
            ) : Image(ime, sopstvenik, width, height)
            {
                this->podrzuvaTransparentnost = podrzuvaTransparentnost;
            }

        int fileSize()
        {
            if (this->podrzuvaTransparentnost)
            {
                return (this->width * this->height) + ((this->width * this->height) / 8);
            }
            else
            {
                return this->width * this->height * 4;
            }
        }

        bool const &operator> (TransparentImage transparentImage)
        {
            return this->fileSize() > transparentImage.fileSize();
        }

        friend ostream &operator<<(ostream &os, TransparentImage transparentImage)
        {
            os << transparentImage.ime << " " << transparentImage.sopstvenik << " " << transparentImage.fileSize() << endl;
            return os;
        }
};


class Folder
{
    protected:
        char ime[255];
        char korisnik[50];
        Image **images;
        int brojNaSliki;

    public:
        Folder() {}

        Folder(char *ime, char *korisnik = "unknown")
        {
            strcpy(this->ime, ime);
            strcpy(this->korisnik, korisnik);
            this->brojNaSliki = 0;
            this->images = new Image*[this->brojNaSliki];
        }

        int folderSize()
        {
            int startingFolderSize = 0;

            for (int i = 0; i < this->brojNaSliki; i++)
            {   
                startingFolderSize += this->images[i]->fileSize();
            }
            
            return startingFolderSize;
        }

        Image *getMaxFile()
        {
            int staringFileSize = -1;
            int staringFileSizePos;

            for (int i = 0; i < this->brojNaSliki; i++)
            {
                if (this->images[i]->fileSize() > staringFileSize)
                {
                    staringFileSize = this->images[i]->fileSize();
                    staringFileSizePos = i;
                }
            }

            return this->images[staringFileSizePos];
        }

        Folder &operator+=(Image *image)
        {
            Image **temp = new Image*[this->brojNaSliki];

            for (int i = 0; i < this->brojNaSliki; i++)
            {
                temp[i] = this->images[i];
            }
            

            temp[this->brojNaSliki] = image;
            this->brojNaSliki++;

            this->images = temp;
        
            return *this;
        }

        friend ostream &operator<<(ostream &os, Folder folder)
        {
            os << folder.ime << endl;
            os << "--" << endl;

            for (int i = 0; i < folder.brojNaSliki; i++)
            {
                os << folder.images[i];
            }

            os << "--" << endl;
            os << "Folder size: " << folder.folderSize() << endl;

            return os;
        }

        Image* const &operator[](int pozicija)
        {
            if (this->brojNaSliki <= pozicija)
            {
                return NULL;
            }

            return this->images[pozicija];
        }
};


Folder max_folder_size(Folder *folder, int n)
{
    int maxFolderSize = -1;
    int maxFolderSizePozicija;

    for (int i = 0; i < n; i++)
    {
        if (folder[i].folderSize() > maxFolderSize)
        {
            maxFolderSize = folder[i].folderSize();
            maxFolderSizePozicija = i;
        }
    }

    return folder[maxFolderSizePozicija];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          Image *f = new Image(name,user_name, w, h);
            dir += f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          Image *tf = new TransparentImage(name,user_name, w, h, tl);
            dir += tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          Image *f = new Image(name,user_name, w, h);
            dir += f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          Image *tf = new TransparentImage(name,user_name, w, h, tl);
            dir += tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          Image *f = new Image(name,user_name, w, h);
            dir += f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          Image *tf = new TransparentImage(name,user_name, w, h, tl);
            dir += tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            Image *f = new Image(name,user_name, w, h);
              dir += f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            Image *f = new TransparentImage(name,user_name, w, h, tl);
              dir += tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
