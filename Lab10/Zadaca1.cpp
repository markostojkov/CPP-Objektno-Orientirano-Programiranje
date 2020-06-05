#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

template <typename T>
class Array
{
    private:
        T *array;
        int brojNaElementi;

    public:
        Array<T>(int brojNaElementi)
        {
            this->brojNaElementi = brojNaElementi;
            this->array = new T[this->brojNaElementi];
        }

        void Erase()
        {
            for (int i = 0; i < this->getLength() - 1; i++)
            {
                delete this->array[i];
            }
            delete [] this->array;
        }

        T &operator[](int pozicija)
        {
            if(pozicija >= 0 && pozicija < this->getLength())
                return this->array[pozicija];
        }

        int getLength()
        {
            return this->brojNaElementi;
        }

        friend ostream &operator<<(ostream &os, Array<T> array)
        {
            for (int i = 0; i < array.getLength(); i++)
            {
                if (i == array.getLength() - 1)
                {
                    os << "Array[" << i << "] = " << array[i];
                }
                else
                {
                    os << "Array[" << i << "] = " << array[i] << ", ";
                }         
            }
            return os;            
        }
};


template <typename T>
void BubbleSort(Array<T> &array)
{
    int n = array.getLength();

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (array[i] > array[j])
            {
                T temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

template <typename T>
T Sum(Array<T> &array)
{
    T vkupnaSuma = 0;

    for (int i = 0; i < array.getLength(); i++)
    {
        vkupnaSuma += array[i];
    }

    return vkupnaSuma;
    
}

template <typename T>
T Average(Array<T> &array)
{
    return Sum(array) / array.getLength();
}

template <typename T, typename M>
bool Equal (Array<T> &arrayFirst, Array<M> &arraySecond)
{
    return Sum(arrayFirst) == Sum(arraySecond);
}

template <typename T>
bool Equal (Array <T> &t, Array<double> &d)
{
    if(t.getLength()!=d.getLength()) return false;
    bool flag1=false,flag2=false;
    for(int i=0; i<t.getLength(); i++)
        if(abs(t[i]-d[i])<0.1) flag1=true;
        else
        {
            flag1=false;
            break;
        }
    if(abs(Average(t)-Average(d))<0.5)
        flag2=true;
    else flag2=false;
    if(flag1&&flag2)
        return true;
    else return false;
}


int main()
{
 
    int n;
    double r;
 
    cin>>r;
    cin>>n;
 
    Array<int> anArray(n);
    Array<double> adArray(n);
    Array<int> intArray2(n);
 
    for (int nCount = 0; nCount < n; nCount++)
    {
 
        cin>>anArray[nCount];
        adArray[nCount] = anArray[nCount] + r;
    }
 
    BubbleSort(anArray);
 
    intArray2 = anArray;
 
    cout<<"The arrays: "<<endl;
    cout<<anArray;
    cout<<endl<<"and "<<endl;
    cout<<intArray2;
    cout<<endl;
    cout<<((Equal(anArray,intArray2))?" ARE":" ARE NOT")<<" same!"<<endl;
    cout<<"The Average of the array adArray is: "<<Average(adArray)<<endl;
 
    cout<<"The arrays: "<<endl;
    cout<<anArray;
    cout<<endl<<"and "<<endl;
    cout<<adArray;
    cout<<endl;
    cout<<((Equal(anArray,adArray))?" ARE":" ARE NOT")<<" same!";
 
    return 0;
}