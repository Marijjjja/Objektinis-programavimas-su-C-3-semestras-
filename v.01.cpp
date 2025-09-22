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
    vector<int> namu_darbu_balas;
    int egzas;
    float rez_avg;
    float rez_median;
    };

Studentas rankinis_ivedimas(string tipas);
double median_calculation(vector<int> value);

int main(){
    vector<Studentas> Grupe;
    int studentu_kiekis;
    string rezultato_tipas;

    //pati pati pradzia
    cout << " --- STUDENTU REZULTATU SISTEMA --- " << endl;
    cout << "Kiek studentu noresite ivesti? "<< endl;
    cin >> studentu_kiekis; 

    cout<<"Iveskite, kokiu formatu norite, kad butu pateikti rezultatai:"<<endl;
    cout<<"Jei vidurkis: vidurkis"<<endl;
    cout<<"Jei mediana: mediana"<<endl;
    cout<<"Jei vidurki ir mediana: abu"<<endl;

    //uztikrinama, kad kol nebus ivestas teisingas variantas, tol prasysim vesti
    do {
    cin >> rezultato_tipas; 
    } while(rezultato_tipas != "vidurkis" && rezultato_tipas != "mediana" && rezultato_tipas != "abu");

    for(int j=0; j<studentu_kiekis; j++){
        cout<<"Iveskite "<<j+1<< " studenta\n";
        Grupe.push_back(rankinis_ivedimas(rezultato_tipas));
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

Studentas rankinis_ivedimas(string tipas){
    Studentas Laik;
    int sum=0;
    string m;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoruoja paskutini 

    bool flag = true;
    while(flag){
        cout<<"iveskite namu darbu pazymi (arba ENTER, kad pabaigti): "<< endl;
        getline(cin, m);
        if(m.empty()){
          cout << "namu darbu vedimas baigesi"<< endl;
          flag = false;
        }
        else{
            int grade = stoi(m); //stoi konvertuoja duomenu tipa is string i int
            Laik.namu_darbu_balas.push_back(grade);
            sum += grade; 
        }
    }

    cout<<"Ivesk egzamino rezultata: "; cin>> Laik.egzas;
    
    if(tipas=="vidurkis" || tipas=="abu"){  
        Laik.rez_avg= Laik.egzas*0.6 + double(sum)/double(Laik.namu_darbu_balas.size()) *0.4;
    }
    if(tipas=="mediana" || tipas=="abu"){
        Laik.rez_median= Laik.egzas*0.6 + median_calculation(Laik.namu_darbu_balas) *0.4;
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