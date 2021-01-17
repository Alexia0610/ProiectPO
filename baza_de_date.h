#ifndef baza_de_date_h
#define baza_de_date_h

#include <vector>
#include <map>
#include <string>
#include <regex>
#include <iostream>
#include "tabel.h"

using namespace std;

class BazaDeDate {
  string nume;
  vector<Tabel *> tabele;
  set<string> numeTabele;
  map<string, int> nrQueryExecutate;

 public:
  BazaDeDate(string _nume) {
    nume = _nume;
  }

  static pair<bool, bool> valideazaCreate(string query);
  static bool valideazaDrop(string query);
  void CreateTable(Tabel *tabel);
  void DropTable(string numeTabel);
  void executa(string query);
  void executaQueryuri(string queryuri);
  void incrementeazaQuery(string comandaQuery);
  string scrieFisierQuery(string query);
};

#endif