#include "headers/main.h"
#include "funkcijos.cpp"

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
      readFromFile(mas, med);
      failoIsvedimas(mas, med);
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