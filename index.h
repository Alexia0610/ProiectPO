#ifndef index_h
#define index_h

#include "tabel.h"
#include "coloana.h"
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class Index {
  string name;
  Tabel *tabel;
  string numeColoana;

 public:
  static bool valideazaCreate(string query) {
    regex formatQuery("CREATE\\sINDEX\\s(?:\\[IF NOT EXISTS\\]\\s)?(\\w+)\\sON\\s(\\w+)\\s?\\((\\w+)\\)",
                      std::regex_constants::icase);
    regex ifNotExistsQuery("\\[IF NOT EXISTS\\]", std::regex_constants::icase);

    return true;
  }

  static bool valideazaDrop(string query) {
    regex formatQuery("DROP\\INDEX\\s(\\w+)", std::regex_constants::icase);
    smatch numeTabel;

    if (!regex_search(query, numeTabel, formatQuery)) {
      cout << "Query-ul de stergere a indexului \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Indexul " + numeTabel.str(1) + " va fi sters\n";
    cout << endl;

    return true;
  }

  static bool Create(string query) {
    return valideazaCreate(query);
  }

  static bool Drop(string query) {
    return valideazaDrop(query);
  }
};

#endif