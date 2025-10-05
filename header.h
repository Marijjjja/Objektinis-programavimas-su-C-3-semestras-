#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

struct Studentas{
    string vardas;
    string pav;
    vector<int> namu_darbu_balas;
    int egzas;
    float rez_avg;
    float rez_median;
    };

struct Kategorizacija{
    vector<Studentas> islaike;
    vector<Studentas> neislaike;
};

Studentas rankinis_ivedimas(string tipas);
Studentas atisitiktiniai_skaiciai(string tipas);
Kategorizacija studento_kategorizacija(vector<Studentas> vektorius);
double median_calculation(vector<int> value);
void file_nuskaitymas(string path, string rezultato_tipas, int rezimas);
void sorting_values(vector<Studentas>& klasiu_vektorius);
bool comparison(Studentas &a, Studentas &b);
void generated_files(int n);
void lenteles_atvaizdavimas(string tipas, vector<Studentas> vector);
int ivadas();