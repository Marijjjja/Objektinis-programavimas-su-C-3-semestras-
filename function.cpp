#include "header.h"

void lenteles_atvaizdavimas(string tipas, vector<Studentas> vector){
    if(tipas=="vidurkis"){  
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (vidurkis)"<<endl;
        cout << endl;
        for(auto i: vector) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << i.rez_avg<< endl;
            }
        }
    else if(tipas=="mediana"){
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (mediana)"<<endl;
        cout << endl;
        for(auto i: vector) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << i.rez_median<< endl;
        }
        }
    else{
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Rezultatas (vidurkis/mediana)"<<endl;
        cout << endl;
        for(auto i: vector) {
            cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<i.rez_avg<<"/"<<i.rez_median<<setw(10)<< endl;
            }
        }
    }

Studentas rankinis_ivedimas(string tipas){
    Studentas Laik;
    int sum=0;
    string m;
    int grade;
        
    cout<<"Ivesk varda: "; cin>> Laik.vardas;
    cout<<"Ivesk pavarde: "; cin>> Laik.pav;


    cout << "iveskite namu darbu pazymi (iveskite -1, kad pabaigti): " << endl;
    while (cin >> grade) {
        if (grade == -1) break;        // stop condition
        Laik.namu_darbu_balas.push_back(grade);
        sum += grade;
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

void file_nuskaitymas(string path, string rezultato_tipas, string kategorija){
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
            if (!s.empty())
                Laik.namu_darbu_balas.push_back(stoi(s));
            else
                Laik.namu_darbu_balas.push_back(0);
        }

        Laik.egzas = stoi(tokens[examIdx]);
        
        for (int grade: Laik.namu_darbu_balas) {
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

        if(kategorija=="T"){
            output_file << left 
                        << setw(18) << "Vardas" 
                        << setw(18) << "Pavarde" 
                        << setw(18) << "Kategorija" << endl << endl;

            for(auto i: students) {
                if(studento_kategorija(i.rez_avg)){
                    output_file << left
                                << setw(18) << i.vardas 
                                << setw(18) << i.pav 
                                << setw(18) << "yay!" << endl;
                } else {
                    output_file << left
                                << setw(18) << i.vardas 
                                << setw(18) << i.pav 
                                << setw(18) << "auch..." << endl;
                }
            }
        }
        else {
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
}

void generated_files(int n){
    ifstream inFile;
    fstream output_file;
    double rezultatas;
    int grade;
    double sum;
    int nd_kiekis;
    vector<int> skaiciu_vektorius;

    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(1, 10);
    uniform_int_distribution<> dist_0(1, 20);

    nd_kiekis = dist(rd);

    output_file.open("duomenys__.txt", ios::out);
        output_file << left << setw(18) << "Vardas" 
                            << setw(18) << "Pavarde";
        for(int j=0; j<nd_kiekis; j++){
            output_file << setw(8) << ("ND" + to_string(j+1));
        }
        output_file<< setw(18) << "Egzaminas"<<endl;
        output_file << endl;

    for(int i=0; i<n; i++){

        rezultatas = dist(rd);

        output_file << left << setw(18) << ("Vardas" + to_string(i+1))
                            << setw(18) << ("Pavarde" + to_string(i+1));

        for(int j=0; j<nd_kiekis; j++){
            output_file << setw(8) << dist(rd);
        }
        output_file<< setw(18) << rezultatas << endl;

        }
        output_file.close();
    }


void sorting_values(vector<Studentas>& klasiu_vektorius){
    sort(klasiu_vektorius.begin(), klasiu_vektorius.end(), comparison);
}

bool comparison(Studentas &a, Studentas &b) {
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

bool studento_kategorija(double galutinis_balas) {
    return galutinis_balas >= 5.0;
}