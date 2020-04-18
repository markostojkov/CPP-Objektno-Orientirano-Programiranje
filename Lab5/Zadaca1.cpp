#include <iostream>

using namespace std;


class Matrica {
    protected:
        int row;
        int column;
        float matrica[10][10];
    
    public:
        Matrica () {
            this->row = 0;
            this->column = 0;
        }

        Matrica (int row, int column) {
            this->row = row;
            this->column = column;
            for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->column; j++) {
                    this->matrica[i][j] = 0;
                }
            }
        }

        Matrica &operator+ (const int number) {
            for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->column; j++) {
                    this->matrica[i][j] += number;
                }
            }
            return *this;
        }

        Matrica &operator- (Matrica &m) {
            for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->column; j++) {
                    this->matrica[i][j] -= m.matrica[i][j];
                }
            }
            return *this;
        }

        Matrica &operator* (Matrica &m) {
            Matrica temp(this->row, m.column);

            for(int i = 0; i < this->row; ++i)
                for(int j = 0; j < m.column; ++j)
                    for(int k = 0; k < this->column; ++k)
                        temp.matrica[i][j] += this->matrica[i][k] * m.matrica[k][j];
            
            *this=temp;
            return *this;
        }

        friend ostream &operator<< (ostream &os, Matrica &m) {
            for(int i = 0; i < m.row; i++) {
                for(int j = 0; j < m.column; j++) {
                    os<< m.matrica[i][j] << " ";
                }
                os<< endl;
            }
            return os;
        }

        friend istream &operator>> (istream &is, Matrica &m) {
            is>>m.row>>m.column;
            for(int i = 0; i < m.row; i++) {
                for(int j = 0; j < m.column; j++) {
                    is>>m.matrica[i][j];
                }
            }
            return is;
        }
};


int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;
}