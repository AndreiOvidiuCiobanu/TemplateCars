#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Masina {
protected:
    int nrLocuri;
    double litraj, dimensiune;
public:
    Masina(){}
    virtual void citire(){
        cout<<"Numar locuri, litraj(l), dimensiune(m)"<<endl;
        cin>>this->nrLocuri>>this->litraj>>this->dimensiune;
    }
    virtual void afisare(){
        cout<<"Numar locuri, litraj(l), dimensiune(m)"<<endl;
        cout<<this->nrLocuri<<" "<<this->litraj<<" "<<this->dimensiune<<endl;
    }
    virtual ~Masina();
};

class Mini: public Masina {
public:
    Mini():Masina(){}

};

class Mica: public Masina{
public:
    Mica():Masina(){}
};

class Compacta: public Masina{
public:
    Compacta():Masina(){}
};

class CompactaHatcback:public Compacta{
public:
    CompactaHatcback():Compacta(){}
};

class CompactaSedan:public Compacta{
public:
    CompactaSedan():Compacta(){}
};

class CompactaBreak:public Compacta{
public:
    CompactaBreak():Compacta(){}
};

class Monovolum:public Masina{
protected:
    bool locuri;///1 daca are 7 locuri 0, daca are 5
    bool sh;///1 daca e sh, 0 daca e noua
public:
    void citire(){
        Masina::citire();
        cout<<"Are 7 locuri? 1 sau 0"<<endl;
        cin>>this->locuri;
        cout<<"Este second hand? 1 sau 0"<<endl;
        cin>>this->sh;
    }
    void afisare(){
        Masina::afisare();
        if(this->locuri)
            cout<<"Masina monovulum are 7 locuri."<<endl;
        else
            cout<<"Masina monovolum are 5 locuri."<<endl;
        if(this->sh)
            cout<<"Masina sh."<<endl;
        else
            cout<<"Masina este noua."<<endl;
    }
    friend istream & operator>>(istream&in, Monovolum&mn){
        mn.citire();
        return in;
    }
    friend ostream & operator<<(ostream & out, Monovolum & mn){
        mn.afisare();
        return out;
    }
};

template <class T >
class Vanzare{
private:
    static int nrMasiniStoc;
    static int nrMasiniVandute;
    vector <T*> masini_stoc;
    vector <T*> masini_vandute;
public:
    Vanzare(){}
    bool operator-=(T masina ){
        for(int i=0;i<masini_stoc.size();i++){
            if(masini_stoc[i]==masina){
                masini_stoc.erase(masini_stoc.begin()+i);
                masini_vandute.push_back(masina);
                nrMasiniVandute++;
                nrMasiniStoc--;
                return true;
            }
        }
        return false;
        }
    void citire(){
        try{
        cout<<"Cate masini trebuie stocate?"<<endl;
        int n,op;
        cin>>n;
        this->nrMasiniStoc=n;
        cout<<"1. Masini mini"<<endl;
        cout<<"2. Masina mica"<<endl;
        cout<<"3. Masina compacta"<<endl;
        cout<<"3.1. Masina compacta hatchback"<<endl;
        cout<<"3.2. Masina compacta sedan"<<endl;
        cout<<"3.3. Masina compacta break"<<endl;
        for(int i=0;i<n;i++){
            cout<<"op=?"<<endl;
            cin>>op;
            switch(op){
                case 1:{
                    masini_stoc.push_back(new Mini());
                    break;
                }
                case 2 :{
                    masini_stoc.push_back(new Mica());
                    break;
                }
                case 3:{
                    cout<<"op?"<<endl;
                    cin>>op;
                    switch(op){
                    case 1:{
                        masini_stoc.push_back(new CompactaHatcback());
                        break;
                    }
                    case 2: {
                        masini_stoc.push_back(new CompactaSedan());
                        break;
                    }
                    case 3: {
                        masini_stoc.push_back(new CompactaBreak());
                        break;
                    }
                    default:break;
                }

                }
            default:break;
            }
            masini_stoc[i]->citire();
        }
        }
        catch(...){cout<<"Nu a functionat bine stocarea si afisarea."<<endl;}
    }
    void afisare(){
        for(int i=0;i<this->nrMasiniStoc;i++){
            if(Mini* m=dynamic_cast<Mini *>(masini_stoc[i]))
                cout<<"Este masina mini."<<endl;
            if(Mica * m=dynamic_cast<Mica *>(masini_stoc[i]))
                cout<<"Este masina mica."<<endl;
            if(CompactaSedan * m=dynamic_cast<CompactaSedan*>(masini_stoc[i]))
                cout<<"Este masina compacta sedan."<<endl;
            if(CompactaBreak * m = dynamic_cast<CompactaBreak*>(masini_stoc[i]))
                cout<<"Este masina compacta break."<<endl;
            if(CompactaHatcback * m=dynamic_cast<CompactaHatcback*>(masini_stoc[i]))
                cout<<"Este masina compacta hatchback."<<endl;
            masini_stoc[i]->afisare();
        }
    }
    friend istream&operator>>(istream&in, Vanzare &v){
        v.citire();
        return in;
    }
    friend ostream & operator<<(ostream&out, const Vanzare &v){
        v.afisare();
        return out;
    }
};
template <class T>
int Vanzare<T>::nrMasiniStoc=0;
template <class T>
int Vanzare<T>::nrMasiniVandute=0;
template <class T>
int Expozitie<T> ::nr =0;

template <>
class Vanzare <Monovolum*>{
private:
    static int nrMasiniStoc;
    static int nrMasiniVandute;
    vector <Monovolum*> masini_stoc;
    vector <Monovolum*> masini_vandute;
    bool set_masiniStoc(int n){
        nrMasiniStoc=n;
    }
    bool set_masiniVandute(int n=0){
       nrMasiniVandute=n;
    }
public:
    Vanzare(){}
    //friend istream&operator>>(istream&in, Monovolum&m){
       // m.citire();
       // return in;
//    /}
    void citire(){
        cout<<"Cate masini sunt in stoc?"<<endl;
        int n;
        cin>>n;
        set_masiniStoc(n);
        set_masiniVandute(0);
        Vanzare<Monovolum>::nrMasiniStoc;
        for(int i=0;i<n;i++){
            masini_stoc.push_back(new Monovolum());
            ///cin>>*(Monovolum*)masini_stoc[i];
            masini_stoc[i]->citire();
        }
    }
    void afisare(){
        cout<<"In stoc se afla "<<this->nrMasiniStoc<<"."<<endl;
        cout<<"S-au vandut "<<this->nrMasiniVandute<<"."<<endl;
        cout<<"Masini in stoc:"<<endl;
        for(int i=0;i<this->nrMasiniStoc;i++)
            masini_stoc[i]->afisare();
        cout<<"Masini vandute:"<<endl;
        for(int i=0;i<this->nrMasiniVandute;i++)
            masini_vandute[i]->afisare();
    }

};
template <>
int Vanzare<Monovolum*>::nrMasiniStoc;
template <>
int Vanzare<Monovolum*>::nrMasiniVandute;

int main()
{
    ///Vanzare<Masina> m;
   /// m.citire();
    ///m.afisare();
    Vanzare<Monovolum*> mn;
    mn.citire();
    mn.afisare();

return 0;
}
