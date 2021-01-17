#include "baza_de_date.h"
#include "query.h"

using namespace std;

pair<bool, bool> BazaDeDate::valideazaCreate(string query) {
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

bool BazaDeDate::valideazaDrop(string query) {
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

void BazaDeDate::CreateTable(Tabel *tabel) {
  string n = tabel->getNume();

  if (numeTabele.find(n) != numeTabele.end()) {
    cout << "Baza de date contine deja un tabel denumit " + n + "\n";
  } else {
    numeTabele.insert(n);
    tabele.push_back(tabel);
    Utile::creeazaFisier(n);
  }
}

void BazaDeDate::DropTable(string numeTabel) {
  for (int i = 0; i < tabele.size(); i++) {
    if (tabele[i]->getNume() == numeTabel)
      tabele.erase(tabele.begin() + i);
  }
}

void BazaDeDate::executa(string query) {
  string comandaQuery = query.substr(0, query.find(' '));
  bool tabelExistent = false;
  string numeTabel;
  string numeFisier;

  if (comandaQuery == "create") {
    numeTabel = Query::valideazaCreate(query);

    if (!numeTabel.empty()) {

      numeFisier = scrieFisierQuery(query);
      CreateTable(new Tabel(numeTabel));
      tabelExistent = true;
    }
  } else if (comandaQuery == "drop") {
    pair<string, string> elemQuery = Query::valideazaDrop(query);
    numeTabel = elemQuery.second;

    if (elemQuery.first == "index")
      for (auto &t :tabele) {
        if (t->getNume() == numeTabel) {
          tabelExistent = true;

          numeFisier = scrieFisierQuery(query);
          t->DropIndex(numeFisier, numeTabel);
        }
      }
    else if (elemQuery.first == "table") {

      numeFisier = scrieFisierQuery(query);
      DropTable(numeTabel);
    }
  } else if (comandaQuery == "display") {
    numeTabel = Query::valideazaDisplay(query);

    for (auto &t :tabele) {
      if (t->getNume() == numeTabel) {
        tabelExistent = true;

        numeFisier = scrieFisierQuery(query);
        t->Display(numeFisier);
      }
    }
  } else if (comandaQuery == "insert") {
    pair<string, vector<vector<string>>> elemQuery = Query::valideazaInsert(query);
    numeTabel = elemQuery.first;

    for (auto &t :tabele) {
      if (t->getNume() == numeTabel) {
        tabelExistent = true;

        numeFisier = scrieFisierQuery(query);
        t->Insert(numeFisier, elemQuery.second);
      }
    }
  } else if (comandaQuery == "delete") {
    tuple<string, string, string> elemQuery = Query::valideazaDelete(query);
    numeTabel = get<0>(elemQuery);

    for (auto &t :tabele) {
      if (t->getNume() == numeTabel) {
        tabelExistent = true;

        numeFisier = scrieFisierQuery(query);
        t->Delete(numeFisier, get<1>(elemQuery), get<2>(elemQuery));
      }
    }
  } else if (comandaQuery == "select") {
    tuple<vector<string>, string, pair<string, string>> elemQuery = Query::valideazaSelect(query);
    numeTabel = get<1>(elemQuery);

    for (auto &t :tabele) {
      if (t->getNume() == numeTabel) {
        tabelExistent = true;

        numeFisier = scrieFisierQuery(query);
        t->Select(numeFisier, get<0>(elemQuery), get<2>(elemQuery));
      }
    }
  } else if (comandaQuery == "update") {
    tuple<string, pair<string, string>, pair<string, string>> elemQuery = Query::valideazaUpdate(query);
    numeTabel = get<0>(elemQuery);

    for (auto &t :tabele) {
      if (t->getNume() == numeTabel) {
        tabelExistent = true;

        numeFisier = scrieFisierQuery(query);
        t->Update(numeFisier, get<1>(elemQuery), get<2>(elemQuery));
      }
    }
  } else
    cout << "Comanda query-ului nu este suportata";

  if (!tabelExistent) {
    cout << "Tabelul cu numele \"" + numeTabel + "\" nu exista!" << endl;
  }
}

void BazaDeDate::executaQueryuri(string queryuri) {
  vector<string> qs = Utile::delimiteaza(queryuri, ';', false);

  for (auto query : qs) {
    cout << "Se executa query-ul: " + query << endl;
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    executa(query);
  }
}

void BazaDeDate::incrementeazaQuery(string comandaQuery) {
  map<string, int>::iterator lb = nrQueryExecutate.lower_bound(comandaQuery);

  if (lb != nrQueryExecutate.end() && !(nrQueryExecutate.key_comp()(comandaQuery, lb->first))) {
    nrQueryExecutate.insert(lb, map<string, int>::value_type(comandaQuery, lb->second++));
  } else {
    nrQueryExecutate.insert(lb, map<string, int>::value_type(comandaQuery, 1));
  }
}

string BazaDeDate::scrieFisierQuery(string query) {
  transform(query.begin(), query.end(), query.begin(), ::tolower);
  string comandaQuery = query.substr(0, query.find(' '));
  incrementeazaQuery(comandaQuery);

  string numeFisier = comandaQuery + "_" + to_string(nrQueryExecutate[comandaQuery]) + ".txt";
  string numeFolder = "rezultate_query";

  Utile::creeazaFisier(numeFisier, numeFolder);
  Utile::adaugaInFisierText(numeFisier, numeFolder, query + "\n");

  return numeFisier;
}