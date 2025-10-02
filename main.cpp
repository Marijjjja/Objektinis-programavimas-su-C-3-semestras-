#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include "header.h"

using namespace std;

int main(){
    vector<Studentas> Grupe;
    int studentu_kiekis;
    string rezultato_tipas;
    int rezimas;
    string path;
    int number;
    string atsakymas;

    cout << " " << endl;
    cout << " --- STUDENTU REZULTATU SISTEMA --- " << endl;
    cout << " " << endl;

    cout << "Pasirinkite rezima: " << endl;
    cout<<"1:   viska suvesti rankiniu budu"<<endl;
    cout<<"2:   vardas ir pavarde - rankiniu budu; pazymiai - atsitiktiniai"<<endl;
    cout<<"3:   nuskaityti duomenis is file'o"<< endl;
    cout<<"4:   sugeneruoti atsitiktinius duomenis"<< endl;
    
    while (true) {
        if (cin >> rezimas && (rezimas == 1 || rezimas == 2 || rezimas == 3 || rezimas==4)) {
            break;
        }
        else{ 
        cout << "Bloga įvestis, iveskite 1, 2, 3, 4: "<< endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout<<"Ar norite, kad rezultatai butu sukategorizuoti? T (taip), N (ne)"<< endl;
    cin >> atsakymas;

    if(rezimas == 4){
        cout << "Iveskite, kiek eiluciu norite, kad jusu file'e butu"<< endl;
        cin >> number;
        generated_files(number);
        cout << "File'as su "<< number <<" eiluciu buvo sukurtas."<<endl;
        return 0;
    }

    cout << endl;
    cout<<"Iveskite, kokiu formatu norite, kad butu pateikti rezultatai:"<<endl;
    cout<<"vidurkis:  rezultatu vidurkis"<<endl;
    cout<<"mediana :  rezultatu mediana"<<endl;
    cout<<"abu     :  rezultatu vidurkis ir mediana"<<endl;

    do {
    cin >> rezultato_tipas; 
    } while(rezultato_tipas != "vidurkis" && rezultato_tipas != "mediana" && rezultato_tipas != "abu");
    cout << endl;

    if(rezimas == 1 || rezimas == 2){
        cout << "Kiek studentu noresite ivesti? "<< endl;
        cin >> studentu_kiekis; 
    } 
    else {
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
        file_nuskaitymas(path, rezultato_tipas, atsakymas);
        return 0;
        }

    sorting_values(Grupe);

    if(atsakymas=="T"){
        cout << left << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Kategorija"<<endl;
        cout << endl;
        for(auto i: Grupe) {
            if(studento_kategorija(i.rez_avg)){
                cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << "yay!" << endl;
            } else {
                cout << left<< setw(10) << i.vardas << setw(10) << i.pav <<setw(10) << "auch..." << endl;
            }
        }
    } 
    else {
        lenteles_atvaizdavimas(rezultato_tipas, Grupe);
        }
}