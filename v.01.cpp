//bibliotekos
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;

struct Studentas{
    string vardas;
    string pav;
    vector<int> paz;
    int egzas;
    float rez;
    };

Studentas ivesk();

int main(){
    vector<Studentas> Grupe;
    
    for(int j=0; j<3;j++){
        cout<<"Iveskite "<<j+1<< "studenta\n";

        Grupe.push_back(ivesk());
    }
    
    for(auto temp :Grupe)
        cout<<temp.vardas<<" | "<<temp.pav<<" | "<<temp.rez<<" | "<<endl;
}

Studentas ivesk(){
    Studentas Laik;
    int sum=0, n,m;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;
    cout<<"Kiek pazymiu norite ivesti?"; cin >>n;
    for (int i=0;i<n;i++) {
        cout<<"Iveskite "<< i+1 <<"paz. is"<<n<< " : "; cin>>m;
        Laik.paz.push_back(m);
        sum+=m; //reikia kiekviena karta kintamaji valyti
        }
    cout<<"Ivesk egzamino rezultata: "; cin>> Laik.egzas;
    Laik.rez= Laik.egzas*0.6 + double(sum)/double(Laik.paz.size()) *0.4;
    return Laik;
}