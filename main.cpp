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
    // string atsakymas;

    rezimas = ivadas();

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
    else if(rezimas == 3 || rezimas == 5){
        cout << "Pateikite file'o path: "<< endl;
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
    if(rezimas == 3 || rezimas == 5){
        file_nuskaitymas(path, rezultato_tipas, rezimas);
        return 0;
        }
    
    sorting_values(Grupe);
    lenteles_atvaizdavimas(rezultato_tipas, Grupe);

}