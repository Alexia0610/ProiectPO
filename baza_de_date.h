#ifndef baza_de_date_h
#define baza_de_date_h

#include "tabel.h"
#include <set>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class BazaDeDate
{
  string nume;
  set<Tabel> tabele;

public:
  static pair<bool, bool> valideazaCreate(string query)
  {
    regex formatQuery("CREATE\\sDATABASE\\s(?:\\[IF NOT EXISTS\\]\\s)?(\\w+)", std::regex_constants::icase);
    regex ifNotExistsQuery("\\[IF NOT EXISTS\\]", std::regex_constants::icase);
    smatch exists;
    smatch numeBazaDeDate;

    bool existsInQuery = false;

    if (regex_search(query, numeBazaDeDate, ifNotExistsQuery))
      existsInQuery = true;

    if (!regex_search(query, numeBazaDeDate, formatQuery))
    {
      cout << "Query-ul de stergere a bazei de date \"" + query + "\" este invalid\n";

      return make_pair(false, false);
    }

    cout << "Baza de date " + numeBazaDeDate.str(1) + " va fi stearsa\n";
    cout << endl;

    return make_pair(true, existsInQuery);
  }

  static bool valideazaDrop(string query)
  {
    regex formatQuery("DROP\\DATABASE\\s(\\w+)", std::regex_constants::icase);
    smatch numeBazaDeDate;

    if (!regex_search(query, numeBazaDeDate, formatQuery))
    {
      cout << "Query-ul de stergere a bazei de date \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Baza de date " + numeBazaDeDate.str(1) + " va fi stearsa\n";
    cout << endl;

    return true;
  }

  static pair<bool, bool> Create(string query)
  {
    return valideazaCreate(query);
  }

  static bool Drop(string query)
  {
    return valideazaDrop(query);
  }
};

#endif