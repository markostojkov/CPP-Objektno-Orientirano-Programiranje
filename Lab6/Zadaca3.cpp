#include <iostream>
#include <cstring>
using namespace std;
 
class NBAPlayer{
    protected:
        char *ime;
        char tim[40];
        double poeni;
        double asistencii;
        double skokovi;
   
    public:
    NBAPlayer()
    {

    }
    
    NBAPlayer(const char *ime, const char *tim, double poeni, double asistencii, double skokovi)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->tim, tim);
        this->poeni = poeni;
        this->asistencii = asistencii;
        this->skokovi = skokovi;
    }
   
    NBAPlayer(const NBAPlayer &player)
    {      
        this->ime = new char[strlen(player.ime)+1];
        strcpy(this->ime, player.ime);
        strcpy(this->tim, player.tim);
        this->poeni = player.poeni;
        this->asistencii = player.asistencii;
        this->skokovi = player.skokovi;
    }
   
    NBAPlayer &operator=(const NBAPlayer &player)
    {    
        this->ime = new char[strlen(player.ime)+1];
        strcpy(this->ime, player.ime);
        strcpy(this->tim, player.tim);
        this->poeni = player.poeni;
        this->asistencii = player.asistencii;
        this->skokovi = player.skokovi;
        return *this;
    }
   
    double rating()
    {
        double poeniRating = this->poeni * 0.45;
        double asistenciiRating = this->asistencii * 0.3;
        double skokoviRating = this->skokovi * 0.25;

        return poeniRating + asistenciiRating + skokoviRating;
    }
   
    void print(){
        cout << ime << " - " << tim << endl;
        cout << "Points: " << poeni << endl;
        cout << "Assists: " << asistencii << endl;
        cout << "Rebounds: " << skokovi << endl;
        cout << "Rating: " << rating() << endl;
    }
};
 
class AllStarPlayer: public NBAPlayer{
    private:
        double poeni;
        double asistencii;
        double skokovi;
   
    public:
    AllStarPlayer(){}
   
    AllStarPlayer(const char *ime, const char *tim, double poeni, double asistencii, double skokovi
                  , double AllStarPoeni, double AllStarAsistencii, double AllStarSkokovi): NBAPlayer(ime, tim, poeni, asistencii, skokovi){
        this->poeni = AllStarPoeni;
        this->asistencii = AllStarAsistencii;
        this->skokovi = AllStarSkokovi;
    }
   
    AllStarPlayer(NBAPlayer &player, double AllStarPoeni, double AllStarAsistencii, double AllStarSkokovi): NBAPlayer(player){
        this->poeni = AllStarPoeni;
        this->asistencii = AllStarAsistencii;
        this->skokovi = AllStarSkokovi;
    }
   
    AllStarPlayer(const AllStarPlayer &player){
        this->poeni = player.poeni;
        this->asistencii = player.asistencii;
        this->skokovi = player.skokovi;
    }
   
    double allStarRating(){
        double poeniRating = this->poeni * 0.3;
        double asistenciiRating = this->asistencii * 0.4;
        double skokoviRating = this->skokovi * 0.3;
        
        return poeniRating + asistenciiRating + skokoviRating;
    }

    double novRating ()
    {
        return (this->allStarRating() + NBAPlayer::rating()) / 2;
    }
   
    void print(){
        NBAPlayer::print();
        cout << "All Star Rating: " << this->allStarRating() << endl;
        cout << "New Rating: " << this->novRating() << endl;
    }
   
};


int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    delete [] players;
    delete [] asPlayers;
}
