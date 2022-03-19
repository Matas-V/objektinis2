#include "headers/main.h"

void readFromFile(vector<studentas> &mas, string med, string filename) {
  studentas a;
  string eil, delim = "ND";
  stringstream my_buffer;
  ifstream rf;
  duration<double> diff;
  // rf.exceptions(std::ifstream::failbit);
  int nd=0, p;
  size_t pos=0;

  auto start = high_resolution_clock::now();

  try {
    rf.open(filename);
    getline(rf, eil);
    while (( pos = eil.find(delim)) != std::string::npos) {
      nd++;
      eil.erase(0, pos + delim.length());
    }

    // my_buffer << rf.rdbuf();
    

    // while (!my_buffer.eof()) {
    //   my_buffer >> a.vardas >> a.pavarde;
    //   for (int i=0; i<nd; i++) {
    //     my_buffer >> p;
    //     a.paz.push_back(p);
    //   }
    //   my_buffer >> a.egz;
    //   mas.reserve(mas.size() + 1);
    //   mas.push_back(a);
    // }

    while(rf) {
      if (!rf.eof()) {
        getline(rf, eil);
        mas.reserve(mas.size() + 1);
        a = dealWithLine(eil, nd);
        a.rez = galutinis(a, med);
        mas.push_back(a);
      } else break;
    }
    rf.close();

    auto end = high_resolution_clock::now();
    diff = end - start;
    cout << "Failo is " << mas.size()-1 << " irasu nuskaitymo laikas: " << diff.count() << endl;

    start = high_resolution_clock::now();
    sort(mas.begin(), mas.end(), [](studentas a, studentas b){
      return a.rez > b.rez;
    });
    end = high_resolution_clock::now();
    diff = end - start;
    cout << mas.size()-1 << " irasu rusiavimas pagal pazymius su sort laikas: " << diff.count() << endl;

    // cout << filename << " nuskaitytas!" << endl;
  } catch(ifstream::failure e) {
    // kazkodel visada sita popina no matter what, del while nuskaitymo idk
    cout << "KLAIDA! Patikrinkite, ar tikrai turite faila " << filename << endl;
  }
}

studentas dealWithLine(string str, int nd) {
  stringstream ss;
  studentas a;
  int count=0, p;
  string word = "";
  ss.clear();
  ss << str;

  ss >> a.vardas >> a.pavarde;
  for (int i=0; i<nd; i++) {
    ss >> p;
    a.paz.push_back(p);
  }
  ss >> a.egz;

  // printf("%s %s %d %d \n", a.vardas.c_str(), a.pavarde.c_str(), a.paz.at(2), a.egz);

  // for (int i=0; i<str.length(); i++) {
  //   if (str[i] == ' ' && count < 2) {
  //     if (word != "") {
  //       count == 0 ? a.vardas = word : a.pavarde = word;
  //       count++;
  //     }
  //     word = "";
  //   } else if (str[i] == ' ' && count >= 2) {
  //     if (word != "") {
  //       if (count < nd) {
  //         try {
  //           a.paz.push_back(stoi(word));
  //         } catch(const std::exception& e) {
  //           a.paz.push_back(0);
  //         }
  //         count++;
  //       } else a.egz = stoi(word);
  //     }
  //     word = "";
  //   } else {
  //     word = word + str[i];
  //   }
  // }

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

void failoIsvedimas(vector<studentas> temp, string med, string fileKiet, string fileVarg) {
  char buffer[1000];
  string outkiet="", outvarg="";
  duration<double> diff;

  sprintf(buffer, "%-20s %-20s", "Vardas", "Pavarde");
  outkiet += buffer; outvarg += buffer;
  if (med == "1") sprintf(buffer, "%-16s \n", "Galutinis (Med.)");
  else sprintf(buffer, "%-16s \n", "Galutinis (Vid.)");
  outkiet += buffer; outvarg += buffer;
  sprintf(buffer, "----------------------------------------------------------\n");
  outkiet += buffer; outvarg += buffer;

  auto start = high_resolution_clock::now();

  for (int i=0; i<temp.size(); i++) {
    // temp.at(i).rez = galutinis(temp.at(i), med);
    sprintf(buffer, "%-20s %-20s %-20.2f \n", temp.at(i).vardas.c_str(), temp.at(i).pavarde.c_str(), temp.at(i).rez);
    if (temp.at(i).rez >= 5) {
      outkiet += buffer;
    } else outvarg += buffer;
  }

  auto end = high_resolution_clock::now();
  diff = end - start;
  cout << temp.size()-1 << " irasu dalijimo i dvi grupes laikas: " << diff.count() << endl;

  start = high_resolution_clock::now();
  ofstream wfk(fileKiet);
  ofstream wfv(fileVarg);
  wfk << outkiet;
  wfv << outvarg;
  wfk.close();
  wfv.close();
  end = high_resolution_clock::now();
  diff = end - start;
  cout << temp.size()-1 << " irasu kietiaku ir vargsiuku irasymo i failus laikas: " << diff.count() << endl;
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

void failuGeneravimas(string filename, int studKiek, int kiek) {
  ofstream wf(filename);
  string outputas="", a="";
  char buffer[1000];

  sprintf(buffer, "%-20s %-20s", "Vardas", "Pavarde"); outputas += buffer;
  for (int i=0; i<kiek; i++) {
    a = "ND" + to_string(i+1);
    sprintf(buffer, "%-10s", a.c_str());
    outputas += buffer;
  }
  sprintf(buffer, "%-10s \n", "Egz."); outputas += buffer;

  for (int i=0; i<studKiek; i++) {
    string vard = "Vardas"+to_string(i);
    string pavard = "Pavarde"+to_string(i);
    sprintf(buffer, "%-20s %-20s", vard.c_str(), pavard.c_str());
    outputas += buffer;
    for (int j=0; j<kiek; j++) {
      sprintf(buffer, "%-10d", rand()%10+1);
      outputas += buffer;
    }
    sprintf(buffer, "%-10d \n", rand()%10+1);
    outputas += buffer;
  }
  wf << outputas;
  cout << "Duomenu failas " << filename << " sukurtas!" << endl;
  wf.close();
}