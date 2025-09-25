//bibliotekos
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

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
void file_nuskaitymas(string path, string rezultato_tipas);
void sorting_values(vector<Studentas>& klasiu_vektorius);
bool comparison(const Studentas& a, const Studentas& b);

int main(){
    vector<Studentas> Grupe;
    int studentu_kiekis;
    string rezultato_tipas;
    int rezimas;
    string path;

    cout << " " << endl;
    cout << " --- STUDENTU REZULTATU SISTEMA --- " << endl;
    cout << " " << endl;

    cout << "Pasirinkite rezima: " << endl;
    cout<<"1:   viska suvesti rankiniu budu"<<endl;
    cout<<"2:   vardas ir pavarde - rankiniu budu; pazymiai - atsitiktiniai"<<endl;
    cout<<"3:   nuskaityti duomenis is file'o"<< endl;
    
    while (true) {
        if (cin >> rezimas && (rezimas == 1 || rezimas == 2 || rezimas == 3)) {
            break;
        }
        else{ 
        cout << "Bloga įvestis, iveskite 1, 2 arba 3: "<< endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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

    cout << " " << endl;
    if(rezimas == 1 || rezimas == 2){
        cout << "Kiek studentu noresite ivesti? "<< endl;
        cin >> studentu_kiekis; 
    } else {
        cout << "Pateikite filo, kuri norite nuskaityti path."<< endl;
        cin >> path;
    }

    //rezimo executionas
    for(int j=0; j<studentu_kiekis; j++){
        if(rezimas==1){
            cout<<"Iveskite studenta: "<<j+1<<"/"<<studentu_kiekis<<endl;
            Grupe.push_back(rankinis_ivedimas(rezultato_tipas));
        }
        else if (rezimas == 2){
            cout<<"Iveskite studenta: "<<j+1<<"/"<<studentu_kiekis<<endl;
            Grupe.push_back(atisitiktiniai_skaiciai(rezultato_tipas));
        }
    }
    if(rezimas == 3){
        file_nuskaitymas(path, rezultato_tipas);
        return 0;
        }

    sorting_values(Grupe);

    //lenteles atvaizdavimas
    if(rezultato_tipas=="vidurkis"){  
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (vidurkis)"<<endl;
        cout << endl;
        for(auto i: Grupe) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << i.rez_avg<< endl;
        }
    }
    else if(rezultato_tipas=="mediana"){
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (mediana)"<<endl;
        cout << endl;
        for(auto i: Grupe) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << i.rez_median<< endl;
        }
    }
    else{
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (vidurkis/mediana)"<<endl;
        cout << endl;
        for(auto i: Grupe) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<i.rez_avg<<"/"<<i.rez_median<<setw(10)<< endl;
        }
    }
}

Studentas rankinis_ivedimas(string tipas){
    Studentas Laik;
    int sum=0;
    string m;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoruoja paskutini inputa

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

    cout<<"Ivesk egzamino rezultata: "; 
    cin>> Laik.egzas;
    
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

void file_nuskaitymas(string path, string rezultato_tipas){
    ifstream inFile;
    fstream output_file;
    vector<string> header;
    string headerLine;
    string line;
    string token;
    vector<Studentas> students;
    int nameIdx=-1, surnameIdx=-1, examIdx=-1;
    vector<int> homeworkIdx;
    long lineNum = 0;
    

    //file'o nuskaitymas
    inFile.open(path);
    if (!inFile) {
        cout << "Nepavyko atidaryti file'o -- ivyko klaida.";
        exit(1); // uzbaigia kodo veikima su klaida jei kazkas negerai
    }

    // sutvarkome pirmaja eilute, kuri nurodo kur kokia reiksme yra:
    getline(inFile, headerLine);

    stringstream ss(headerLine);
    while (ss >> token) { 
        header.push_back(token);
    }

    //skirta nustatyti kur koks stulpelis
    for (int i=0; i<header.size(); i++) {
        string col = header[i];
        if (col.find("ardas") != string::npos) nameIdx = i;
        else if (col.find("avar") != string::npos) surnameIdx = i;
        else if (col.find("ND") != string::npos) homeworkIdx.push_back(i);
        else if (col.find("Egz") != string::npos) examIdx = i;
    }

    //duomenu nuskanavimas is txt file'o ir pridejimas prie vektoriaus
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        Studentas Laik;
        double sum=0;

        if (lineNum % 10000 == 0) {
            cout << "Nuskaitytų eilučių skaičius: "<< lineNum << endl;
        }

        while (ss >> token) { 
        tokens.push_back(token);
        }

        Laik.vardas = tokens[nameIdx];
        Laik.pav = tokens[surnameIdx];

        for (int idx: homeworkIdx) {
            string s = tokens[idx];
            s.erase(0, s.find_first_not_of(" \t\r\n"));
            s.erase(s.find_last_not_of(" \t\r\n") + 1);
            if (!s.empty())
                Laik.namu_darbu_balas.push_back(stoi(s));
            else
                Laik.namu_darbu_balas.push_back(0); // default if empty
        }

        Laik.egzas = stoi(tokens[examIdx]);
        
        for (int grade : Laik.namu_darbu_balas) {
            sum += grade;
        }

        if(rezultato_tipas=="vidurkis" || rezultato_tipas=="abu"){  
            if(Laik.namu_darbu_balas.size()!=0){  
                Laik.rez_avg= Laik.egzas*0.6 + double(sum)/double(Laik.namu_darbu_balas.size()) *0.4;
            } else {
                cout << "Nebuvo ivesta namu darbu!" << endl;
            }
        }
        if(rezultato_tipas=="mediana" || rezultato_tipas=="abu"){
            Laik.rez_median= Laik.egzas*0.6 + median_calculation(Laik.namu_darbu_balas) *0.4;
        }

        students.push_back(Laik);
        lineNum += 1;
    }

    inFile.close();
    sorting_values(students);

    output_file.open("rezultatas.txt", ios::out);

    if (output_file.is_open()){
        if(rezultato_tipas=="vidurkis"){
            output_file << left << setw(18) << "Vardas" << setw(18) << "Pavarde" << setw(18) << "Rezultatas (vidurkis)"<<endl;
            output_file << endl;

            for(auto i: students) {
                output_file << left<< setw(18) << i.vardas << setw(18) << i.pav <<setw(18) << i.rez_avg<< endl;
            }
        }
        else if(rezultato_tipas=="mediana"){
            output_file << left << setw(18) << "Vardas" << setw(18) << "Pavarde" << setw(18) << "Rezultatas (mediana)"<<endl;
            output_file << endl;

            for(auto i: students) {
                output_file << left<< setw(18) << i.vardas << setw(18) << i.pav <<setw(18) << i.rez_median<< endl;
            }
        }
        else{
            output_file << left << setw(18) << "Vardas" << setw(18) << "Pavarde" << setw(18) << "Rezultatas (vidurkis/mediana)"<<endl;
            output_file << endl;
            for(auto i: students) {
                output_file << left << setw(18) << i.vardas << setw(18) << i.pav << i.rez_avg<<"/"<<i.rez_median<< setw(18) << endl;
            }
        }

        output_file.close();
        cout<<"Rezultatai nuskaityti į rezultatai.txt file'ą!"<< endl;
     }
}

void sorting_values(vector<Studentas>& klasiu_vektorius){
    sort(klasiu_vektorius.begin(), klasiu_vektorius.end(), comparison);
}

bool comparison(const Studentas& a, const Studentas& b) {
    return a.vardas < b.vardas;
}

double median_calculation(vector<int> value){
    sort(value.begin(), value.end());
    int n = value.size();
    if(n % 2 == 1)
        return value[n/2];
    else
        return (value[n/2 - 1] + value[n/2]) / 2.0;
}