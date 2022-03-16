#include "headers/main.h"

void readFromFile(vector<studentas> &mas, string med) {
  studentas a;
  string eil, delim = "ND";
  ifstream rf;
  rf.exceptions(std::ifstream::failbit);
  int nd=0;
  size_t pos=0;

  try {
    rf.open("kursiokai.txt");
    getline(rf, eil);
    while (( pos = eil.find(delim)) != std::string::npos) {
      nd++;
      eil.erase(0, pos + delim.length());
    }

    while(!rf.eof()) {
      getline(rf, eil);
      mas.reserve(mas.size() + 1);
      mas.push_back(dealWithLine(eil));
    }
    sort(mas.begin(), mas.end(), [](studentas a, studentas b){
      return a.vardas < b.vardas;
    });
    rf.close();
  } catch(ifstream::failure e) {
    cout << "KLAIDA! Patikrinkite ar turite duomenu faila kursiokai.txt" << endl;
  }
}

studentas dealWithLine(string str) {
  studentas a;
  int count=0;
  string word = "";
  for (int i=0; i<str.length(); i++) {
    if (str[i] == ' ' && count < 2) {
      if (word != "") {
        count == 0 ? a.vardas = word : a.pavarde = word;
        count++;
      }
      word = "";
    } else if (str[i] == ' ' && count >= 2) {
      if (word != "") {
        try {
          a.paz.push_back(stoi(word));
        } catch(const std::exception& e) {
          a.paz.push_back(0);
        }
        count++;
      }
      word = "";
    } else {
      word = word + str[i];
    }
  }
  a.egz = stoi(word);

  return a;
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
    for (int i=0; i<11; i++)
      if (p == P[i]) paz=true;
    if (paz) naujas.egz = stoi(p);
  }

  return naujas;
}

void isvedimas(vector<studentas> temp, int n, string med) {
  printf("%-20s %-20s", "Vardas", "Pavarde");
  if (med == "1") printf("%-16s \n", "Galutinis (Med.)");
  else printf("%-16s \n", "Galutinis (Vid.)");
  printf("----------------------------------------------------------\n");

  for (int i=0; i<n; i++) {
    temp.at(i).rez = galutinis(temp.at(i), med);
    printf("%-20s %-20s %-20.2f \n", temp.at(i).vardas.c_str(), temp.at(i).pavarde.c_str(), temp.at(i).rez);
  }
}

void failoIsvedimas(vector<studentas> temp, string med) {
  ofstream wf("rezultatai.txt");
  string outputas="";
  char buffer[1000];

  sprintf(buffer, "%-20s %-20s", "Vardas", "Pavarde"); outputas += buffer;
  if (med == "1") sprintf(buffer, "%-16s \n", "Galutinis (Med.)");
  else sprintf(buffer, "%-16s \n", "Galutinis (Vid.)");
  outputas += buffer;
  sprintf(buffer, "----------------------------------------------------------\n"); outputas += buffer;

  for (int i=0; i<temp.size(); i++) {
    temp.at(i).rez = galutinis(temp.at(i), med);
    sprintf(buffer, "%-20s %-20s %-20.2f \n", temp.at(i).vardas.c_str(), temp.at(i).pavarde.c_str(), temp.at(i).rez);
    outputas += buffer;
  }
  wf << outputas;
  cout << "Duomenys isvesti i rezultatu faila!" << endl;
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
}