//bibliotekos
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

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
Studentas atisitiktiniai_skaiciai(string tipas);
double median_calculation(vector<int> value);
void file_nuskaitymas(string path);

int main(){
    vector<Studentas> Grupe;
    int studentu_kiekis;
    string rezultato_tipas;
    int rezimas;
    string path;

    //pati pati pradzia
    cout << " " << endl;
    cout << " --- STUDENTU REZULTATU SISTEMA --- " << endl;
    cout << " " << endl;

    cout << "Pasirinkite rezima: " << endl;
    cout<<"1:   viska suvesti rankiniu budu"<<endl;
    cout<<"2:   vardas ir pavarde - rankiniu budu; pazymiai - atsitiktiniai"<<endl;
    cout<<"3:   nuskaityti duomenis is file'o"<< endl;
    
    do {
    cin >> rezimas; 
    } while(rezimas != 1 && rezimas != 2 && rezimas != 3);

    cout << " " << endl;
    if(rezimas == 1 || rezimas == 2){
        cout << "Kiek studentu noresite ivesti? "<< endl;
        cin >> studentu_kiekis; 
    } else {
        cout << "Pateikite filo, kuri norite nuskaityti path."<< endl;
        cin >> path;
        file_nuskaitymas(path);
    }
    

    cout << " " << endl;
    cout<<"Iveskite, kokiu formatu norite, kad butu pateikti rezultatai:"<<endl;
    cout<<"vidurkis:  rezultatu vidurkis"<<endl;
    cout<<"mediana :  rezultatu mediana"<<endl;
    cout<<"abu     :  rezultatu vidurkis ir mediana"<<endl;

    //uztikrinama, kad kol nebus ivestas teisingas variantas, tol prasysim vesti
    do {
    cin >> rezultato_tipas; 
    } while(rezultato_tipas != "vidurkis" && rezultato_tipas != "mediana" && rezultato_tipas != "abu");

    //rezimo executionas
    for(int j=0; j<studentu_kiekis; j++){
        cout<<"Iveskite studenta: "<<j+1<<"/"<<studentu_kiekis<<endl;
        if(rezimas==1){
        Grupe.push_back(rankinis_ivedimas(rezultato_tipas));
        }
        else{
        Grupe.push_back(atisitiktiniai_skaiciai(rezultato_tipas));
        }
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
          cout << endl;
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
        if(Laik.namu_darbu_balas.size()!=0){  
            Laik.rez_avg= Laik.egzas*0.6 + double(sum)/double(Laik.namu_darbu_balas.size()) *0.4;
        } else {
            cout << "Nebuvo ivesta namu darbu!" << endl;
        }
    }
    if(tipas=="mediana" || tipas=="abu"){
        Laik.rez_median= Laik.egzas*0.6 + median_calculation(Laik.namu_darbu_balas) *0.4;
    }
    return Laik;
}

Studentas atisitiktiniai_skaiciai(string tipas){
    Studentas Laik;
    int namu_darbu_kiekis;
    int sum=0;
    int grade;
    string m;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoruoja paskutini 

    cout << "Kiek norite, kad mokinys turetu namu darbu pazymiu?"<< endl;
    cin >> namu_darbu_kiekis;

    //atsitiktinio skaiciau generavimas
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(1, 10);

    for(int i=0; i<namu_darbu_kiekis; i++){
        grade = dist(gen);
        Laik.namu_darbu_balas.push_back(grade);
        sum += grade;
    }

    Laik.egzas = dist(gen);

    if(tipas=="vidurkis" || tipas=="abu"){  
        if(!Laik.namu_darbu_balas.empty()){  
            Laik.rez_avg= Laik.egzas*0.6 + double(sum)/double(Laik.namu_darbu_balas.size()) *0.4;
        }else{
            cout << "Nebuvo ivesta namu darbu!" << endl;
        }
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

void file_nuskaitymas(string path){
    ifstream inFile;
    string line;
    vector<string> header;
    string token;

    inFile.open(path);
    if (!inFile) {
        cout << "Nepavyko atidaryti file'o -- ivyko klaida.";
        exit(1); // uzbaigia kodo veikima su klaida jei kazkas negerai
    }

    // while (getline(inFile, line)) {   // read line by line
    //     cout << line << endl;          // print each line
    // }
    string headerLine;
    getline(inFile, headerLine);
    // cout << headerLine<< endl;

    stringstream ss(headerLine);

    while (getline(ss, token, ',')) {
    header.push_back(token);
    }

    inFile.close();
    // return 0;

}