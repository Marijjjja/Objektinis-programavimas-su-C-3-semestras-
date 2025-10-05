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

Studentas rankinis_ivedimas(string tipas);
Studentas atisitiktiniai_skaiciai(string tipas);
double median_calculation(vector<int> value);
void file_nuskaitymas(string path, string rezultato_tipas, int rezimas);
void sorting_values(vector<Studentas>& klasiu_vektorius);
bool comparison(Studentas &a, Studentas &b);
void generated_files(int n);
bool studento_kategorija(double galutinis_balas);
void lenteles_atvaizdavimas(string tipas, vector<Studentas> vector);
int ivadas();

template <typename C>
  void printClockData () {
    cout << "- precision: ";
    typedef typename C::period P;
    if (ratio_less_equal<P,milli>::value) {
      typedef typename ratio_multiply<P,kilo>::type TT;
      cout << fixed << double(TT::num)/TT::den<< " milliseconds" << endl;
    } else {
      cout << fixed << double(P::num)/P::den << " seconds" << endl;
    }
    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
  }