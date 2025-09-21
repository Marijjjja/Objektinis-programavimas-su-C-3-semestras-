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

using namespace std;

struct Studentas{
    string vardas;
    string pav;
    vector<int> paz;
    int egzas;
    float rez_avg;
    float rez_median;
    };

Studentas ivesk(string tipas);
double median_calculation(vector<int> value);

int main(){
    vector<Studentas> Grupe;
    int studentu_kiekis;
    string rezultato_tipas;

    //pati pati pradzia
    cout << "Kiek studentu noresite ivesti? "<< endl;
    cin >> studentu_kiekis;

    cout<<"Iveskite, kokiu formatu norite, kad pateikciau rezultata:"<<endl;
    cout<<"Jei vidurkis: vidurkis"<<endl;
    cout<<"Jei mediana: mediana"<<endl;
    cout<<"Jei vidurki ir mediana: abu"<<endl;
    cin >> rezultato_tipas;

    for(int j=0; j<studentu_kiekis; j++){
        cout<<"Iveskite "<<j+1<< "studenta\n";
        Grupe.push_back(ivesk(rezultato_tipas));
    }

    //lenteles atvaizdavimas
    if(rezultato_tipas=="vidurkis"){  
        cout<< " vardas    pavarde    rezultatas(vidurkis)"<<endl;
        cout<< "--------------------------------------------" << endl;
        for(auto temp: Grupe)
            cout<<" "<<temp.vardas<<"        "<<temp.pav<<"         "<< fixed << setprecision(2)<<temp.rez_avg<<"   "<<endl;
    }
    else if(rezultato_tipas=="mediana"){
        cout<< " vardas    pavarde    rezultatas(mediana)"<<endl;
        cout<< "--------------------------------------------" << endl;
        for(auto temp: Grupe)
            cout<<" "<<temp.vardas<<"        "<<temp.pav<<"         "<< fixed << setprecision(2)<<temp.rez_median<<"   "<<endl;
    }
    else{
        cout<< " vardas    pavarde    rezultatas(vid./mediana)"<<endl;
        cout<< "--------------------------------------------" << endl;
        for(auto temp: Grupe)
            cout<<" "<<temp.vardas<<"        "<<temp.pav<<"         "<<fixed<< setprecision(2)<<temp.rez_avg<<"/"<<fixed<< setprecision(2)<<temp.rez_median<<endl;
    }

}

Studentas ivesk(string tipas){
    Studentas Laik;
    int sum=0, n,m;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;
    cout<<"Kiek namu darbu pazymiu norite ivesti?"; cin >>n;

    for (int i=0;i<n;i++){
        cout<<"Iveskite "<< i+1 <<"-ji namu darbu paz. is "<<n<< " : "; cin>>m;
        Laik.paz.push_back(m);
        sum+=m;
        }

    cout<<"Ivesk egzamino rezultata: "; cin>> Laik.egzas;
    
    if(tipas=="vidurkis" || tipas=="abu"){  
        Laik.rez_avg= Laik.egzas*0.6 + double(sum)/double(Laik.paz.size()) *0.4;
    }
    if(tipas=="mediana" || tipas=="abu"){
        Laik.rez_median= Laik.egzas*0.6 + median_calculation(Laik.paz) *0.4;
    }
    return Laik;
}

double median_calculation(vector<int> value){
    sort(value.begin(), value.end());
    int n = value.size();
    if(n % 2 == 1)
        return value[n/2];
    else
        return (value[n/2 - 1] + value[n/2]) / 2.0;
}