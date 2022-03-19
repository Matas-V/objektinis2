#pragma once
#include <iostream>
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

struct studentas {
  string vardas="", pavarde="";
  int egz=0;
  vector<int> paz;
  double rez=0;
};

studentas ivestis();
studentas generavimas();
void readFromFile(vector<studentas> &mas, string med, string filename);
studentas dealWithLine(string str, int nd);
void isvedimas(vector<studentas> temp, int n, string med);
void failoIsvedimas(vector<studentas> temp, string med, string fileKiet, string fileVarg);
double galutinis(studentas& temp, string med);
double mediana(studentas& temp);
void input_check(string &inp, string text);
void failuGeneravimas(string filename, int studKiek, int kiek);