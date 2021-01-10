#include "query.h"
#include "tabel.h"
#include "utile.h"
#include "baza_de_date.h"
#include "index.h"
#include <string>
#include <vector>

using namespace std;

static void parseazaQuery(BazaDeDate b, string query) {
  transform(query.begin(), query.end(), query.begin(), ::tolower);

  string comandaQuery = query.substr(0, query.find(" "));

  if (comandaQuery == "create") {
    string obiectQuery = query.substr(comandaQuery.size() + 1, query.find(" "));

    if (obiectQuery == "database")
      BazaDeDate::Create(query);
    else if (obiectQuery == "table")
      Tabel::Create(query);
  } else if (comandaQuery == "drop") {
    string obiectQuery = query.substr(comandaQuery.size() + 1, query.find(" "));

    if (obiectQuery == "index")
      Index::Drop(query);
    else if (obiectQuery == "table")
      Tabel::Drop(query);
  } else if (comandaQuery == "display")
    Tabel::Display(query);
  else if (comandaQuery == "insert") {
    pair<string, vector<string>> p = Tabel::Insert(query);
  } else if (comandaQuery == "delete")
    Tabel::Delete(query);
  else if (comandaQuery == "select")
    Tabel::Select(query);
  else if (comandaQuery == "update")
    Tabel::Update(query);
  else
    cout << "Comanda query-ului nu este suportata";
}

void Query::parseazaQueryuri(BazaDeDate b, string queryuri) {
  vector<string> qs = Utile::delimiteaza(queryuri, ';');

  for (auto query : qs) {
    parseazaQuery(b, query);
  }
}