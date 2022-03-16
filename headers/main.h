#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <ctime>
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
studentas dealWithLine(string str);
void isvedimas(vector<studentas> temp, int n, string med);
void failoIsvedimas(vector<studentas> temp, string med);
double galutinis(studentas& temp, string med);
double mediana(studentas& temp);
void input_check(string &inp, string text);