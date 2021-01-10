#ifndef tabel_h
#define tabel_h

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <set>
#include "coloana.h"
#include "utile.h"

using namespace std;

class Tabel {
  string nume;
  vector<Coloana *> coloane;
  set<string> numeColoane;

 public:
  Tabel(string nume) {
    this->nume = nume;
  }

  Tabel(string nume, vector<Coloana *> coloane, set<string> numeColoane) {
    this->nume = nume;
    this->coloane = coloane;
    this->numeColoane = numeColoane;
  }

  Tabel(string numeTabel, string numeFisier) {
    nume = numeTabel;

    ifstream fisierTabel(numeFisier);

    if (!fisierTabel.is_open()) {
      cout << "Fisierul " + numeFisier + " nu poate fi citit\n";
    }

    string definitieColoana;

    while (getline(fisierTabel, definitieColoana)) {
      vector<string> col = Utile::delimiteaza(definitieColoana, ',');

      string numeColoana = Utile::eliminaSpatii(col[0]);
      string tipColoana = Utile::eliminaSpatii(col[1]);
      int dimensiuneColoana = stoi(Utile::eliminaSpatii(col[2]));
      string valoareImplicitaColoana;

      if (col.size() == 3) {
        valoareImplicitaColoana = "";
      } else if (col.size() == 4) {
        valoareImplicitaColoana = Utile::eliminaSpatii(col[3]);
      } else {
        cout << "Definitia unei coloane din fisierul " + numeFisier + " poate avea doar 3 sau 4 proprietati";
      }

      if (tipColoana == "text") {
        string val = valoareImplicitaColoana;

        insereazaColoana(new ColoanaTip<string>(numeColoana, tipColoana, dimensiuneColoana, val));
      } else if (tipColoana == "integer") {
        int val;

        if (valoareImplicitaColoana.empty()) {
          val = 0;
        } else {
          val = stoi(valoareImplicitaColoana);
        }

        insereazaColoana(new ColoanaTip<int>(numeColoana, tipColoana, dimensiuneColoana, val));
      } else if (tipColoana == "float") {
        float val;

        if (valoareImplicitaColoana.empty()) {
          val = 0.0;
        } else {
          val = stoi(valoareImplicitaColoana);
        }

        insereazaColoana(new ColoanaTip<float>(numeColoana, tipColoana, dimensiuneColoana, val));
      }
    }
  }

  template<typename T>
  void insereazaColoana(ColoanaTip<T>* c) {
    string numeColoana = c->GetNume();

    if (numeColoane.find(numeColoana) != numeColoane.end()) {
      cout << "O coloana numita " + numeColoana + " deja exista in tabel\n";
    } else {
      numeColoane.insert(numeColoana);
      coloane.push_back(c);
    }
  }

  static bool valideazaCreate(string query) {
    regex formatQuery("CREATE\\sTABLE\\s(\\w+)", std::regex_constants::icase);

    return true;
  }

  static bool valideazaDrop(string query) {
    regex formatQuery("DROP\\sTABLE\\s(\\w+)", std::regex_constants::icase);
    smatch queryInfo;

    if (!regex_search(query, queryInfo, formatQuery)) {
      cout << "Query-ul de stergere a tabelului \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Tabelul " + queryInfo.str(1) + " va fi sters\n";
    cout << endl;

    return true;
  }

  static bool valideazaDisplay(string query) {
    regex formatQuery("DISPLAY\\sTABLE\\s(\\w+)", std::regex_constants::icase);
    smatch queryInfo;

    if (!regex_search(query, queryInfo, formatQuery)) {
      cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

      return false;
    }

    cout << "Tabelul " + queryInfo.str(1) + " va fi afisat\n";
    cout << endl;

    return true;
  }

  static bool valideazaDelete(string query) {
    regex formatQuery("DELETE\\sFROM\\s(\\w+)", std::regex_constants::icase);
    smatch queryInfo;

    // if (!regex_search(query, queryInfo, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + queryInfo.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static vector<string> valideazaStringColoane(string s) {
    if (s.size() >= 2) {
      s = s.substr(1, s.size() - 2);
    }

    // Se sterg toate caracterele '('
    s.erase(std::remove(s.begin(), s.end(), '('), s.end());

    vector<string> infoColoane = Utile::delimiteaza(s, ')');

    for (int i = 0; i < infoColoane.size(); i++) {
      return Utile::delimiteaza(infoColoane[i], ',');
    }
  }

  static pair<string, vector<string>> valideazaInsert(string query) {
    regex formatQuery("INSERT\\sINTO\\s(\\w+)\\sVALUES\\s(.+)", std::regex_constants::icase);
    smatch queryInfo;

    if (!regex_search(query, queryInfo, formatQuery)) {
      cout << "Query-ul de inserare a valorilor \"" + query + "\" este invalid\n";

      return pair<string, vector<string>>("", vector<string>());
    }

    cout << "In tabelul " + queryInfo.str(1) + " vor fi inserate valorile " + queryInfo.str(2) + "\n";

    return pair<string, vector<string>>(queryInfo.str(1), valideazaStringColoane(queryInfo.str(2)));
  }

  static bool valideazaSelect(string query) {
    regex formatQuery("SELECT\\sFROM\\s(\\w+)", std::regex_constants::icase);
    smatch queryInfo;

    // if (!regex_search(query, queryInfo, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + queryInfo.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool valideazaUpdate(string query) {
    regex formatQuery("UPDATE\\s(\\w+)\\sSET\\s(\\w+)\\sWHERE\\s(\\w+)", std::regex_constants::icase);
    smatch queryInfo;

    // if (!regex_search(query, queryInfo, formatQuery)) {
    //   cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    //   return false;
    // }

    // cout << "Tabelul " + queryInfo.str(1) + " va fi afisat\n";
    // cout << endl;

    return true;
  }

  static bool Create(string query) {
    return valideazaCreate(query);
  }

  static bool Drop(string query) {
    return valideazaDrop(query);
  }

  static bool Display(string query) {
    return valideazaDisplay(query);
  }

  static bool Delete(string query) {
    return valideazaDelete(query);
  }

  static pair<string, vector<string>> Insert(string query) {
    return valideazaInsert(query);
  }

  static bool Select(string query) {
    return valideazaSelect(query);
  }

  static bool Update(string query) {
    return valideazaUpdate(query);
  }

  string GetNume() {
    return nume;
  }
};

#endif