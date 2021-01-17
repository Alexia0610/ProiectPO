#ifndef UTILE_H
#define UTILE_H

#include <vector>
#include <string>

using namespace std;

class Utile {
 public:
  static vector<string> delimiteaza(const string &s, char delim, bool adaugaGol);
  static string eliminaSpatii(const string &str, const string &whitespace = " \t");
  static string eliminaParanteze(string s);
  static string eliminaSubstring(string &str, const string &subStr = "\"");
  static void adaugaInFisierText(string nume, const string folder, string deAdaugat);
  static void adaugaInFisierText(string nume, const string folder, string deAdaugat, int format);
  static void adaugaInFisierBinar(string nume, const string folder, string deAdaugat);
  static void creeazaFisier(string nume, const string folder = "tabele");
  static void stergeFisier(string nume, const string folder = "tabele");
  static void creeazaFisierBinar(string nume, const string folder = "tabele");
};

#endif
