<<<<<<< HEAD
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
using namespace std;

#define arr_size 10000
const string P[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

struct studentas {
  string vardas="", pavarde="";
  int egz=0;
  vector<int> paz;
  double rez=0;
};

studentas ivestis();
studentas generavimas();
void readFromFile(vector<studentas> &mas, string med);
void isvedimas(vector<studentas> temp, int n, string med);
void failoIsvedimas(studentas temp, string med);
double galutinis(studentas& temp, string med);
double mediana(studentas& temp);
void input_check(string &inp, string text);

int main() {
  int n=0;
  string med, gen, k;
  bool pass=0;
  vector<studentas> mas;
  mas.reserve(2);
  srand(time(0));

  input_check(gen, "Ar duomenis ivedinesite(1) pats ar sugeneruoti(0)?");

  if (gen == "0") {
    n = rand() % 10 + 1;
    med = rand() % 10 >= 5 ? "1" : "0";
    pass = 1;
  } else {
    input_check(gen, "Ar duomenis ivedinesite ranka(1) ar skaityti is failo(0)?");
    input_check(med, "Pasirinkite ka noresit skaiciuoti galutinio ivertinimo: vidurki(0) ar mediana(1)?");

    if (gen == "0") {
      isvedimas(mas, 0, med);
      readFromFile(mas, med);
    } else {
      while(!pass) {
        cout << "Kiek studentu noresite ivesti?" << endl;
        cin >> k;
        if (int(k[0]) >= 49 && int(k[0]) <= 57) {
          if (stoi(k) <= arr_size && stoi(k) > 0) {
            n = stoi(k);
            pass=1;
          }
        }
      }
    }
  }

  if (pass) {
    for (int i=0; i<n; i++) {
      mas.reserve(mas.size() + 1);
      if (gen == "0")
        mas.push_back(generavimas());
      else
        mas.push_back(ivestis());
    }
    isvedimas(mas, mas.size(), med);
  }

  return 0;
}

void readFromFile(vector<studentas> &mas, string med) {
  studentas a;
  string line;
  ifstream rf("kursiokai.txt");
  int nd=0;

  getline(rf, line);
  for (int i=0; i<line.length(); i++) {
    if (line[i] == 'N' && line[i+1] == 'D')
      nd++;
  }

  while(!rf.eof()) {
    int p;
    rf >> a.vardas; rf >> a.pavarde;
    for (int i=0; i<nd; i++) {
      rf >> p; a.paz.push_back(p);
    }
    rf >> a.egz;
    failoIsvedimas(a, med);
    // mas.reserve(mas.size() + 1);
    // mas.push_back(a);
  }
  // sort(mas.begin(), mas.end(), [](studentas a, studentas b){
  //   return a.vardas < b.vardas;
  // });
  rf.close();
}

void input_check(string &inp, string text) {
  bool state=0;
  while(!state) {
    cout << text << endl;
    cin >> inp;
    if (inp == "0" || inp == "1")
      state=1;
  }
}

studentas generavimas() {
  studentas naujas;
  string A[10] = { "Augustas",  "Tadas", "Matas", "Lukas", "Ignas", "Joris", "Simas", "Juozas", "Jonas", "Mykolas" };
  string B[10] = { "Griskevicius",  "Brazinskas", "Stanulionis", "Maironis", "Dauksa", "Zalionis", "Lapinskas", "Dabulis", "Sakalauskas", "Pakuckas" };
  int j=rand() % 10, pk;
  naujas.vardas = A[j];
  naujas.pavarde = B[j];

  pk = rand() % 10 + 1;
  for (int i=0; i<pk; i++) {
    j = rand() % 10;
    naujas.paz.push_back(stoi(P[j]));
    naujas.paz.reserve(naujas.paz.size() + 1);
  }
  j = rand() % 10; naujas.egz = stoi(P[j]);
  return naujas;
}

studentas ivestis() {
  studentas naujas;
  string p="0";
  bool paz=false;
  cout << "Iveskite varda: "; cin >> naujas.vardas;
  cout << "Iveskite pavarde: "; cin >> naujas.pavarde;

  while(p != "q") {
    cout << "Iveskite " << naujas.paz.size()+1 << "-a(-i) pazymi arba q, jei norite baigti: ";
    cin >> p;
    for (int i=0; i<11; i++)
      if (p == P[i]) paz=true;
    if (p != "q" && paz) {
      naujas.paz.push_back(stoi(p));
      naujas.paz.reserve(naujas.paz.size() + 1);
    }
    paz=false;
  }

  while(!paz) {
    cout << "Iveskite egzamino iverti: ";
    cin >> p;
    for (int i=0; i<10; i++)
      if (p == P[i]) paz=true;
    if (paz) naujas.egz = stoi(p);
  }

  return naujas;
}

void isvedimas(vector<studentas> temp, int n, string med) {
  cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas";
  if (med == "1") cout << setw(20) << "Galutinis (Med.)" << endl;
  else cout << setw(20) << "Galutinis (Vid.)" << endl;
  cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;

  for (int i=0; i<n; i++) {
    temp[i].rez = galutinis(temp[i], med);
    cout << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << temp[i].rez << endl;
  }
}

void failoIsvedimas(studentas temp, string med) {
  temp.rez = galutinis(temp, med);
  cout << setw(15) << temp.vardas << setw(15) << temp.pavarde << setw(19) << fixed << setprecision(2) << temp.rez << endl;
}

double galutinis(studentas& temp, string med) {
  double v=0;
  if (temp.paz.size() > 0) {
    if (med == "0") {
      v = accumulate(temp.paz.begin(), temp.paz.end(), v) * 1.0 / temp.paz.size();
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*temp.egz;
}

double mediana(studentas& temp) {
  sort(temp.paz.begin(), temp.paz.end());

  if (temp.paz.size() % 2 == 0) {
    int nr = temp.paz.size() / 2;
    int b = (temp.paz[nr] + temp.paz[nr-1]) / 2;
    return b;
  } else {
    int nr = temp.paz.size() / 2;
    return temp.paz[nr];
  }
=======
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define arr_size 10000
const string P[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

struct studentas {
  string vardas="", pavarde="";
  int egz=0;
  vector<int> paz;
  double rez=0;
};

void ivestis(studentas& temp);
void generavimas(studentas& temp);
void isvedimas(studentas temp[], int n, string med);
double galutinis(studentas& temp, string med);
double mediana(studentas& temp);
void input_check(string &inp, string text);

int main() {
  int n=0;
  string med, gen, k;
  bool pass=0;
  studentas mas[arr_size];
  srand(time(0));

  input_check(gen, "Ar duomenis ivedinesite(1) pats ar sugeneruoti(0)?");

  if (gen == "0") {
    n = rand() % 10 + 1;
    med = rand() % 10 >= 5 ? "1" : "0";
  } else {
    while(!pass) {
      cout << "Kiek studentu noresite ivesti?" << endl;
      cin >> k;
      if (int(k[0]) >= 49 && int(k[0]) <= 57) {
        if (stoi(k) <= arr_size && stoi(k) > 0) {
          n = stoi(k);
          pass=1;
        }
      }
    }
    input_check(med, "Pasirinkite ka noresit skaiciuoti galutinio ivertinimo: vidurki(0) ar mediana(1)?");
  }

  for (int i=0; i<n; i++) {
    if (gen == "0")
      generavimas(mas[i]);
    else
      ivestis(mas[i]);
    mas[i].paz.reserve(2);
  }
  isvedimas(mas, n, med);
  return 0;
}

void input_check(string &inp, string text) {
  bool state=0;
  while(!state) {
    cout << text << endl;
    cin >> inp;
    if (inp == "0" || inp == "1")
      state=1;
  }
}

void generavimas(studentas& temp) {
  string A[10] = { "Augustas",  "Tadas", "Matas", "Lukas", "Ignas", "Joris", "Simas", "Juozas", "Jonas", "Mykolas" };
  string B[10] = { "Griskevicius",  "Brazinskas", "Stanulionis", "Maironis", "Dauksa", "Zalionis", "Lapinskas", "Dabulis", "Sakalauskas", "Pakuckas" };
  int j=rand() % 10, pk;
  temp.vardas = A[j];
  temp.pavarde = B[j];

  pk = rand() % 10 + 1;
  for (int i=0; i<pk; i++) {
    j = rand() % 10;
    temp.paz.push_back(stoi(P[j]));
    temp.paz.reserve(temp.paz.size() + 1);
  }
  j = rand() % 10; temp.egz = stoi(P[j]);
}

void ivestis(studentas& temp) {
  string p="0";
  bool paz=false;
  cout << "Iveskite varda: "; cin >> temp.vardas;
  cout << "Iveskite pavarde: "; cin >> temp.pavarde;

  while(p != "q") {
    cout << "Iveskite " << temp.paz.size()+1 << "-a(-i) pazymi arba q, jei norite baigti: ";
    cin >> p;
    for (int i=0; i<11; i++)
      if (p == P[i]) paz=true;
    if (p != "q" && paz) {
      temp.paz.push_back(stoi(p));
      temp.paz.reserve(temp.paz.size() + 1);
    }
    paz=false;
  }

  while(!paz) {
    cout << "Iveskite egzamino iverti: ";
    cin >> p;
    for (int i=0; i<10; i++)
      if (p == P[i]) paz=true;
    if (paz) temp.egz = stoi(p);
  }
}

void isvedimas(studentas temp[], int n, string med) {
  cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas";
  if (med == "1") cout << setw(20) << "Galutinis (Med.)" << endl;
  else cout << setw(20) << "Galutinis (Vid.)" << endl;
  cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;

  for (int i=0; i<n; i++) {
    temp[i].rez = galutinis(temp[i], med);
    cout << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << temp[i].rez << endl;
  }
}

double galutinis(studentas& temp, string med) {
  double v=0;
  if (temp.paz.size() > 0) {
    if (med == "0") {
      v = accumulate(temp.paz.begin(), temp.paz.end(), v) * 1.0 / temp.paz.size();
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*temp.egz;
}

double mediana(studentas& temp) {
  sort(temp.paz.begin(), temp.paz.end());

  if (temp.paz.size() % 2 == 0) {
    int nr = temp.paz.size() / 2;
    int b = (temp.paz[nr] + temp.paz[nr-1]) / 2;
    return b;
  } else {
    int nr = temp.paz.size() / 2;
    return temp.paz[nr];
  }
>>>>>>> 7adb090ac5afaa6ba28777ba0f14371b9b9bd139
}