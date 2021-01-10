#ifndef baza_de_date_h
#define baza_de_date_h

#include "tabel.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class BazaDeDate {
  string nume;
  vector<Tabel *> tabele;
  set<string> numeTabele;

 public:
  BazaDeDate(string _nume) {
    nume = _nume;
  }

  void adaugaTabel(Tabel *tabel) {
    string n = tabel->GetNume();

    if (numeTabele.find(n) != numeTabele.end()) {
      cout << "Baza de date contine deja un tabel denumit " + n + "\n";
    } else {
      numeTabele.insert(n);
      tabele.push_back(tabel);
    }
  }

  static pair<bool, bool> valideazaCreate(string query) {
    regex formatQuery("CREATE\\sDATABASE\\s(?:\\[IF NOT EXISTS\\]\\s)?(\\w+)", std::regex_constants::icase);
    regex ifNotExistsQuery("\\[IF NOT EXISTS\\]", std::regex_constants::icase);
    smatch exists;
    smatch numeBazaDeDate;

    bool existsInQuery = false;

    if (regex_search(query, numeBazaDeDate, ifNotExistsQuery))
      existsInQuery = true;

    if (!regex_search(query, numeBazaDeDate, formatQuery)) {
      cout << "Query-ul de stergere a bazei de baza_de_date \"" + query + "\" este invalid\n";

      return make_pair(false, false);
    }

    cout << "Baza de baza_de_date " + numeBazaDeDate.str(1) + " va fi stearsa\n";
    cout << endl;

    return make_pair(true, existsInQuery);
  }

  static bool valideazaDrop(string query) {
    regex formatQuery("DROP\\DATABASE\\s(\\w+)", std::regex_constants::icase);
    smatch numeBazaDeDate;

    if (!regex_search(query, numeBazaDeDate, formatQuery)) {
      cout << "Query-ul de stergere a bazei de baza_de_date \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Baza de baza_de_date " + numeBazaDeDate.str(1) + " va fi stearsa\n";
    cout << endl;

    return true;
  }

  static pair<bool, bool> Create(string query) {
    return valideazaCreate(query);
  }

  static bool Drop(string query) {
    return valideazaDrop(query);
  }
};

#endif