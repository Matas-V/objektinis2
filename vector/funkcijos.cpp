#include "headers/main.h"

void read_file(vector <studentas>& sar, string file, string med, int index) {
  studentas st;
  string line, delim = "ND";
  size_t pos=0;
  int nd=0, p;
  ifstream fd;
  fd.exceptions(std::ifstream::failbit);
  auto start = std::chrono::high_resolution_clock::now();
  try {
    fd.open(file);
    stringstream my_buffer;
    my_buffer << fd.rdbuf();
    fd.close();

    getline(my_buffer, line);
    while (( pos = line.find(delim)) != std::string::npos) {
      nd++;
      line.erase(0, pos + delim.length());
    }
    
    while(!my_buffer.eof()) {
      my_buffer >> st.vardas;
      my_buffer >> st.pavarde;
      for (int i = 0; i < nd; i++){
        my_buffer >> p;
        st.paz.push_back(p);
      }
      my_buffer >> st.egz;
      st.rez = galutinis(st, med);
      st.paz.clear();
      sar.push_back(st);
    }
    sar.shrink_to_fit();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Failo nuskaitymas ir sudejimas i vektoriu uztruko: " << diff.count() << endl;

    sort(sar.begin(), sar.end(), [](studentas a, studentas b){
      if (a.rez == b.rez) return a.pavarde < b.pavarde;
      return a.rez < b.rez;
    });

    failoIsvedimas(sar, med, outfileKiet[index], outfileVarg[index]);
  } catch(const std::exception& e) {
    cout << "Failas " << file << " nerastas..." << '\n';
  }
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

void isvedimas(vector<studentas> &temp, int n, string med) {
  printf("%-20s %-20s", "Vardas", "Pavarde");
  if (med == "1") printf("%-16s \n", "Galutinis (Med.)");
  else printf("%-16s \n", "Galutinis (Vid.)");
  printf("----------------------------------------------------------\n");

  for (auto &stud: temp) {
    stud.rez = galutinis(stud, med);
    printf("%-20s %-20s %-20.2f \n", stud.vardas.c_str(), stud.pavarde.c_str(), stud.rez);
  }
}

void failoIsvedimas(vector<studentas> &temp, string med, string fileKiet, string fileVarg) {
  string outkiet="", outvarg="";
  vector<studentas> kiet, varg;
  duration<double> diff;
  char buffer[1000];

  sprintf(buffer, "%-20s %-20s", "Vardas", "Pavarde");
  outkiet += buffer; outvarg += buffer;
  if (med == "1") sprintf(buffer, "%-16s \n", "Galutinis (Med.)");
  else sprintf(buffer, "%-16s \n", "Galutinis (Vid.)");
  outkiet += buffer; outvarg += buffer;
  sprintf(buffer, "----------------------------------------------------------\n");
  outkiet += buffer; outvarg += buffer;

  auto start = high_resolution_clock::now();

  for (auto &stud : temp) {
    if (stud.rez >= 5) kiet.push_back(stud);
    else varg.push_back(stud);
  }
  kiet.shrink_to_fit();
  varg.shrink_to_fit();

  auto end = high_resolution_clock::now();
  diff = end - start;
  cout << temp.size()-1 << " irasu dalijimo i du vektorius laikas: " << diff.count() << endl;

  for (auto &stud: kiet) {
    sprintf(buffer, "%-20s %-20s %-20.2f \n", stud.vardas.c_str(), stud.pavarde.c_str(), stud.rez);
    outkiet += buffer;
  }

  for (auto &stud: varg) {
    sprintf(buffer, "%-20s %-20s %-20.2f \n", stud.vardas.c_str(), stud.pavarde.c_str(), stud.rez);
    outvarg += buffer;
  }

  ofstream wfk(fileKiet);
  ofstream wfv(fileVarg);
  wfk << outkiet;
  wfv << outvarg;
  wfk.close();
  wfv.close();
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
    double b = (temp.paz[nr] + temp.paz[nr-1]) / 2;
    return b;
  } else {
    int nr = temp.paz.size() / 2;
    return temp.paz[nr];
  }
}

void failuGeneravimas(string filename, int studKiek, int kiek) {
  stringstream ss;

  ss << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
  for (int i=0; i<kiek; i++)
    ss << setw(10) << "ND" + to_string(i+1);
  ss << setw(10) << "Egz." << endl;

  for (int i=0; i<studKiek; i++) {
    ss << setw(20) << "Vardas"+to_string(i) << setw(20) << "Pavarde"+to_string(i);

    for (int j=0; j<kiek; j++)
      ss << setw(10) << rand()%10+1;
    ss << setw(10) << rand()%10+1 << endl;
  }

  ofstream wf(filename);
  wf << ss.rdbuf();
  ss.clear();
  wf.close();
  cout << "Duomenu failas " << filename << " sukurtas!" << endl;
}
