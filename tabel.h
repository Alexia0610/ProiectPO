#ifndef tabel_h
#define tabel_h

#include "coloana.h"
#include <set>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class Tabel
{
  string nume;
  set<Coloana<> > coloane;

  Tabel(string _nume);

public:
  static bool valideazaCreate(string query)
  {
    regex formatQuery("CREATE\\sTABLE\\s(\\w+)", std::regex_constants::icase);

    return true;
  }

  static bool valideazaDrop(string query)
  {
    regex formatQuery("DROP\\sTABLE\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    if (!regex_search(query, numeTabel, formatQuery))
    {
      cout << "Query-ul de stergere a tabelului \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Tabelul " + numeTabel.str(1) + " va fi sters\n";
    cout << endl;

    return true;
  }

  static bool valideazaDisplay(string query)
  {
    regex formatQuery("DISPLAY\\sTABLE\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    if (!regex_search(query, numeTabel, formatQuery))
    {
      cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Tabelul " + numeTabel.str(1) + " va fi afisat\n";
    cout << endl;

    return true;
  }

  static bool valideazaDelete(string query)
  {
    regex formatQuery("DELETE\\sFROM\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    // if (!regex_search(query, numeTabel, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + numeTabel.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool valideazaInsert(string query)
  {
    regex formatQuery("INSERT\\sINTO\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    // if (!regex_search(query, numeTabel, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + numeTabel.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool valideazaSelect(string query)
  {
    regex formatQuery("SELECT\\sFROM\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    // if (!regex_search(query, numeTabel, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + numeTabel.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool valideazaUpdate(string query)
  {
    regex formatQuery("UPDATE\\s(\\w+)\\sSET\\s(\\w+)\\sWHERE\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    // if (!regex_search(query, numeTabel, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + numeTabel.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool Create(string query)
  {
    return valideazaCreate(query);
  }

  static bool Drop(string query)
  {
    return valideazaDrop(query);
  }

  static bool Display(string query)
  {
    return valideazaDisplay(query);
  }

  static bool Delete(string query)
  {
    return valideazaDelete(query);
  }

  static bool Insert(string query)
  {
    return valideazaInsert(query);
  }

  static bool Select(string query)
  {
    return valideazaSelect(query);
  }

  static bool Update(string query)
  {
    return valideazaUpdate(query);
  }
};

#endif