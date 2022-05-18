#include "headers/main.h"

void studentas::setPazymys(int mpaz) {
  paz.reserve(paz.size() + 1);
  paz.push_back(mpaz);
}

void studentas::setGalBal(string med) {
  rez = galutinis(med, paz, egz);
}

void studentas::readStudentai(vector <studentas>& sar, string file, string med, int index) {
  read_file(sar, file, med, index);
}

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
      my_buffer >> line; st.setVardas(line);
      my_buffer >> line; st.setPavarde(line);
      for (int i = 0; i < nd; i++){
        my_buffer >> p;
        st.setPazymys(p);
      }
      my_buffer >> p;
      st.setEgzas(p);
      st.setGalBal(med);
      st.clearPaz();
      sar.push_back(st);
    }
    sar.shrink_to_fit();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "Failo nuskaitymas ir sudejimas i vektoriu uztruko: " << diff.count() << endl;

    sort(sar.begin(), sar.end(), [](studentas a, studentas b){
      if (a.galBalas() == b.galBalas()) return a.getVardas() < b.getVardas();
      return a.galBalas() < b.galBalas();
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
  naujas.setVardas(A[j]);
  naujas.setPavarde(B[j]);

  pk = rand() % 10 + 1;
  for (int i=0; i<pk; i++) {
    j = rand() % 10;
    naujas.setPazymys(stoi(P[j]));
  }
  j = rand() % 10; naujas.setEgzas(stoi(P[j]));
  return naujas;
}

studentas ivestis() {
  studentas naujas;
  string p="0";
  bool paz=false;
  cout << "Iveskite varda: "; cin >> p; naujas.setVardas(p);
  cout << "Iveskite pavarde: "; cin >> p; naujas.setPavarde(p);

  while(p != "q") {
    cout << "Iveskite " << naujas.getPazymiai().size()+1 << "-a(-i) pazymi arba q, jei norite baigti: ";
    cin >> p;
    for (int i=0; i<11; i++)
      if (p == P[i]) paz=true;
    if (p != "q" && paz) {
      naujas.setPazymys(stoi(p));
    }
    paz=false;
  }

  while(!paz) {
    cout << "Iveskite egzamino iverti: ";
    cin >> p;
    for (int i=0; i<11; i++)
      if (p == P[i]) paz=true;
    if (paz) naujas.setEgzas(stoi(p));
  }

  return naujas;
}

void isvedimas(vector<studentas> &temp, int n, string med) {
  printf("%-20s %-20s", "Vardas", "Pavarde");
  if (med == "1") printf("%-16s \n", "Galutinis (Med.)");
  else printf("%-16s \n", "Galutinis (Vid.)");
  printf("----------------------------------------------------------\n");

  for (auto &stud: temp) {
    stud.setGalBal(med);
    printf("%-20s %-20s %-20.2f \n", stud.getVardas().c_str(), stud.getPavarde().c_str(), stud.galBalas());
  }
}

void failoIsvedimas(vector<studentas> &temp, string med, string fileKiet, string fileVarg) {
  string outkiet="", outvarg="";
  vector<studentas> kiet;
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

  for (int i=temp.size()-1; i>=0; i--) {
    if (temp.at(i).galBalas() >= 5) {
      kiet.push_back(temp.at(i));
      temp.pop_back();
    }
  }
  kiet.shrink_to_fit();
  temp.shrink_to_fit();

  auto end = high_resolution_clock::now();
  diff = end - start;
  cout << "2 strategijos vectoriaus skaidymo laikas: " << diff.count() << endl;

  for (auto &stud: kiet) {
    sprintf(buffer, "%-20s %-20s %-20.2f \n", stud.getVardas().c_str(), stud.getPavarde().c_str(), stud.galBalas());
    outkiet += buffer;
  }

  for (auto &stud: temp) {
    sprintf(buffer, "%-20s %-20s %-20.2f \n", stud.getVardas().c_str(), stud.getPavarde().c_str(), stud.galBalas());
    outvarg += buffer;
  }

  ofstream wfk(fileKiet);
  ofstream wfv(fileVarg);
  wfk << outkiet;
  wfv << outvarg;
  wfk.close();
  wfv.close();
}

double galutinis(string med, vector<int> temp, int egz) {
  double v=0;
  if (temp.size() > 0) {
    if (med == "0") {
      v = accumulate(temp.begin(), temp.end(), v) * 1.0 / temp.size();
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*egz;
}

double mediana(vector<int> temp) {
  sort(temp.begin(), temp.end());

  if (temp.size() % 2 == 0) {
    int nr = temp.size() / 2;
    double b = (temp.at(nr) + temp.at(nr-1)) / 2;
    return b;
  } else {
    int nr = temp.size() / 2;
    return temp.at(nr);
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
