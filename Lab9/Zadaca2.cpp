#include <iostream>
#include <cstring>

using namespace std;

const double LIKE_COEF = 0.1;
const double COMMENT_COEF = 0.5;
const double TWEET_COEF = 0.5;

enum TextEnum 
{
    UsernameType,
    PasswordType,
    EmailType
};

enum ErrorType
{
    InvalidPassword,
    InvalidEmail,
    MaximumSizeTeam
};

void message(char *message, ErrorType errorType, int maxUsers = 0)
{
    switch (errorType)
    {
        case InvalidPassword:
        case InvalidEmail:
            cout << message << endl;
            break;
        case MaximumSizeTeam:
            cout << "You can't add more than " << maxUsers << " users" << endl;
            break;
        default:
            break;
    }
}


class ErrorHandler
{
    private:
        char error[50];

    public:
        ErrorHandler(char *error)
        {
            strcpy(this->error, error);
        }

        void error()
        {
            cout << this->error << endl;
        }
};




class User
{
    protected:
        char username[50];
        char password[50];
        char email[50];

    public:
        User(char *username, char *password, char *email)
        {
            this->checkForErrors(password, PasswordType);
            this->checkForErrors(email, EmailType);
            strcpy(this->username, username);
            strcpy(this->password, password);
            strcpy(this->email, email);
        }

        void checkForErrors(char *text, TextEnum textType)
        {
            switch (textType)
            {
                case PasswordType:
                    try
                    {
                        bool containsUpper = false, containsLower = false, containsNumber = false;
                        for (int i = 0; i < 50; i++)
                        {
                            if (islower(this->password[i])) containsLower = true;
                            if (isupper(this->password[i])) containsUpper = true;
                            if (isdigit(this->password[i])) containsNumber = true;
                        }
                        if (!containsUpper && !containsLower && !containsNumber)
                            throw ErrorHandler("Password is too weak.");
                    }
                    catch(ErrorHandler &errorHandler)
                    {
                        errorHandler.error();
                    }
                    break;
                case EmailType:
                    try
                    {
                        int atContains = 0;
                        for (int i = 0; i < 50; i++)
                        {
                            if (this->email[i] == '@') atContains++;

                        }
                        if (atContains > 1)
                            throw ErrorHandler("Mail is not valid.");
                    }
                    catch(ErrorHandler &errorHandler)
                    {
                        errorHandler.error();
                    }
                    break;
                default:
                    break;
                }
        }

        virtual double popularity() = 0;
};


class FacebookUser : public User
{
    protected:
        int brojNaPrijateli;
        int brojNaLajkovi;
        int brojNaKomentari;

    public:
        FacebookUser(char *username,
            char *password,
            char *email,
            int friends,
            int likes,
            int comments) : User(username, password, email)
            {
                this->brojNaPrijateli = friends;
                this->brojNaLajkovi = likes;
                this->brojNaKomentari = comments;
            }

        double popularity()
        {
            return this->brojNaPrijateli + 
            this->brojNaLajkovi * LIKE_COEF + 
            this->brojNaKomentari + COMMENT_COEF;
        }
};


class TwitterUser : public User
{
    protected:
        int brojNaTvitovi;
        int followers;

    public:
        TwitterUser(char *username,
            char *password,
            char *email,
            int brojNaTvitovi,
            int followers) : User(username, password, email)
            {
                this->brojNaTvitovi = brojNaTvitovi;
                this->followers = followers;
            }

        double popularity()
        {
            return this->followers + 
            this->brojNaTvitovi * TWEET_COEF;
        }
};


class SocialNetwork
{
    protected:
        User **users;
        int brojNaKorisnici;
        int maxKorisnici;
    public: 

        SocialNetwork()
        {
            this->brojNaKorisnici = 0;
            this->maxKorisnici = 5;
        }

        SocialNetwork &operator+=(User *user)
        {
            try
            {
                if (this->brojNaKorisnici + 1 > this->maxKorisnici) {
                    char *error = "You can't add more than " + this->maxKorisnici + "users";
                    throw ErrorHandler(error);
                }
                User ** pom = new User*[this->brojNaKorisnici + 1];
                for(int i = 0; i < this->brojNaKorisnici; i++) {
                    pom[i] = users[i];
                }
                pom[this->brojNaKorisnici] = user;
                this->brojNaKorisnici++;
                this->users = new User*[this->brojNaKorisnici];

                for(int i = 0; i < this->brojNaKorisnici; i++) {
                    this->users[i] = pom[i];
                }
                delete [] pom;

                return *this;
            }
            catch(ErrorHandler &errorHandler)
            {
                errorHandler.error();
            }
        }

        void changeMaximumSize(int n)
        {
            this->maxKorisnici = n;
        }

        double avgPopularity()
        {
            double averagePopularity = 0.0;
            for (int i = 0; i < this->brojNaKorisnici; i++)
            {
                averagePopularity += this->users[i]->popularity();
            }
            return averagePopularity;
        }
};


int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
          
        // TODO: Try-catch
        User * u = new FacebookUser(username,password,email,friends,likes,comments);
        network += u;
          
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;
          
        // TODO: Try-catch  
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
          
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;
    
    // TODO: Try-catch
    User * u= new TwitterUser(username,password,email,followers,tweets);
    network += u;
    
    cout << network.avgPopularity();

    return 0;
}
