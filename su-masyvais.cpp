#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
using namespace std;

#define arr_size 1000

const string A[10] = { "Augustas",  "Tadas", "Matas", "Lukas", "Ignas", "Joris", "Simas", "Juozas", "Jonas", "Mykolas" };
const string B[10] = { "Griskevicius",  "Brazinskas", "Stanulionis", "Maironis", "Dauksa", "Zalionis", "Lapinskas", "Dabulis", "Sakalauskas", "Pakuckas" };
const string P[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

struct studentas {
  string vardas="", pavarde="";
  int paz[100], egz=0, k=0;
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
  studentas mas[1000];
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
  int j=rand() % 10, pk;
  temp.vardas = A[j];
  temp.pavarde = B[j];

  pk = rand() % 10 + 1;
  for (int i=0; i<pk; i++) {
    j = rand() % 10;
    temp.paz[temp.k] = stoi(P[j]);
    temp.k++;
  }
  j = rand() % 10; temp.egz = stoi(P[j]);
}

void ivestis(studentas& temp) {
  string p="1";
  bool paz=false;
  cout << "Iveskite varda: "; cin >> temp.vardas;
  cout << "Iveskite pavarde: "; cin >> temp.pavarde;

  while(p != "0") {
    cout << "Iveskite " << temp.k+1 << "-a(-i) pazymi arba 0, jei norite baigti: ";
    cin >> p;
    for (int i=0; i<10; i++)
      if (p == P[i]) paz=true;
    if (p != "0" && paz) {
      temp.paz[temp.k] = stoi(p);
      temp.k++;
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
  if (temp.k > 0) {
    if (med == "0") {
      v = accumulate(temp.paz, temp.paz + temp.k, v) * 1.0 / temp.k;
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*temp.egz;
}

double mediana(studentas& temp) {
  sort(temp.paz, temp.paz + temp.k);

  if (temp.k % 2 == 0) {
    int nr = temp.k / 2;
    int b = (temp.paz[nr] + temp.paz[nr-1]) / 2;
    return b;
  } else {
    int nr = temp.k / 2;
    return temp.paz[nr];
  }
}