#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric>
#include <ctime>
#include <chrono>
#include <regex>
using namespace std;
using namespace std::chrono;

#define arr_size 10000
const string P[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
const string fileNames[5] = { "kursiokai1000.txt", "kursiokai10000.txt", "kursiokai100000.txt", "kursiokai1000000.txt", "kursiokai10000000.txt" };
const string outfileKiet[5] = { "kietiakai1000.txt", "kietiakai10000.txt", "kietiakai100000.txt", "kietiakai1000000.txt", "kietiakai10000000.txt" };
const string outfileVarg[5] = { "vargsiukai1000.txt", "vargsiukai10000.txt", "vargsiukai100000.txt", "vargsiukai1000000.txt", "vargsiukai10000000.txt" };

class zmogus {
  protected:
    string vardas;
    string pavarde;
  public:
    inline string getVardas() const { return vardas; }
    inline string getPavarde() const { return pavarde; }
    virtual void setVardas(string mvardas) = 0;
    virtual void setPavarde(string mpavarde) = 0;
    zmogus() : vardas(""), pavarde("") { }
};

class studentas : public zmogus {
  private:
    int egz;
    vector<int> paz;
    double rez;
  public:
    studentas() : rez(0), egz(0) { }

    inline string getVardas() const { return vardas; }
    void setVardas(string mvardas) { vardas = mvardas; }

    inline string getPavarde() const { return pavarde; }
    void setPavarde(string mpavarde) { pavarde = mpavarde; }

    inline vector<int> getPazymiai() const { return paz; }
    void setPazymys(int mpaz);
    void clearPaz() { paz.clear(); }

    inline int egzas() const { return egz; }
    void setEgzas(int megz) { egz = megz; }

    inline double galBalas() const { return rez; }
    void setGalBal(string med);

    void readStudentai(vector<studentas> &sar, string file, string med, int index);

    studentas(const studentas &s) { egz = s.egz; rez = s.rez; paz = s.paz; }
    ~studentas() { paz.clear(); }
    studentas& operator=(const studentas& other) {
      if (this == &other)
        return *this;
      egz = other.egz;
      rez = other.rez;
      paz = other.paz;
      return *this;
    }
};

studentas ivestis();
studentas generavimas();
void read_file(vector <studentas>& sar, string file, string med, int index);
void isvedimas(vector<studentas> &temp, int n, string med);
void failoIsvedimas(vector<studentas> &temp, string med, string fileKiet, string fileVarg);
double galutinis(string med, vector<int> temp, int egz);
double mediana(vector<int> temp);
void input_check(string &inp, string text);
void failuGeneravimas(string filename, int studKiek, int kiek);