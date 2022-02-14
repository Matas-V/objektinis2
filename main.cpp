#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct studentas {
  string vardas="", pavarde="";
  int paz[3] = {0}, egz=0;
  double rez=0, med=0;
};

void ivestis(studentas& temp);
void isvedimas(studentas temp[], int n);
double galutinis(studentas& temp);
double mediana(studentas& temp);

int main() {
  int n;
  studentas mas[10000];

  cout << "Kiek studentu noresite ivesti?" << endl;
  cin >> n;

  for (int i=0; i<n; i++)
    ivestis(mas[i]);

  isvedimas(mas, n);

  return 0;
}

void ivestis(studentas& temp) {
  cout << "Iveskite varda: "; cin >> temp.vardas;
  cout << "Iveskite pavarde: "; cin >> temp.pavarde;

  for (int i=0; i<3; i++) {
    cout << "Iveskite " << i+1 << "-a(-i) pazymi: ";
    cin >> temp.paz[i];
  }
  cout << "Iveskite egzamino iverti: "; cin >> temp.egz;
}

void isvedimas(studentas temp[], int n) {
  cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.) / Galutinis (Med.)" << endl;
  cout << setfill('-') << setw(70) << '-' << setfill(' ') << endl;

  for (int i=0; i<n; i++) {
    temp[i].rez = galutinis(temp[i]);
    temp[i].med = mediana(temp[i]);
    cout << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << temp[i].rez << temp[i].med << endl;
  }
}

double galutinis(studentas& temp) {
  int sum=0, kiek=0;

  for (int i=0; i<3; i++) {
    sum += temp.paz[i];
    kiek++;
  }
  sum += temp.egz; kiek++;

  return sum*1.0 / kiek;
}

double mediana(studentas& temp) {
  int a[3+1];
  for (int i=0; i<3; i++) a[i] = temp.paz[i];
  a[3] = temp.egz;

  for (int i=0; i<3; i++) {
    for (int j=i+1; j<4; j++) {
      if (a[i] > a[j])
        swap(a[i], a[j]);
    }
  }

  return (a[1] + a[2]) / 2;
}