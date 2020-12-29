#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "tabel.h"
#include "baza_de_date.h"
#include "index.h"

using namespace std;

string eliminaSpatii(const string &str, const string &whitespace = " \t")
{
  const auto inceput = str.find_first_not_of(whitespace);

  if (inceput == string::npos)
    return "";

  const auto sfarsit = str.find_last_not_of(whitespace);
  const auto sfarsitNou = sfarsit - inceput + 1;

  return str.substr(inceput, sfarsitNou);
}

vector<string> delimiteaza(const string &s, char delim)
{
  vector<string> qs;
  stringstream ss(s);
  string query;

  while (getline(ss, query, delim))
  {
    string q = eliminaSpatii(query);

    if (!q.empty())
      qs.push_back(q);
  }

  return qs;
}

int main()
{
  string input;

  cout << "Introduceti query-uri SQL delimitate de ; sau o noua linie\n";

  while (getline(cin, input))
  {
    if (input.empty())
      cout << "Trebuie sa introduceti un SQL query valid!\n";

    vector<string> queryuri = delimiteaza(input, ';');

    for (auto query : queryuri)
    {
      transform(query.begin(), query.end(), query.begin(), ::tolower);
      
      string comandaQuery = query.substr(0, input.find(" "));

      if (comandaQuery == "create") {
        string obiectQuery = query.substr(comandaQuery.size() + 1, input.find(" "));

        if (obiectQuery == "database")
          BazaDeDate::Create(query);
        else if (obiectQuery == "table")
          Tabel::Create(query);
      }
      else if (comandaQuery == "drop") {
        string obiectQuery = query.substr(comandaQuery.size() + 1, input.find(" "));

        if (obiectQuery == "index")
          Index::Drop(query);
        else if (obiectQuery == "table")
          Tabel::Drop(query);
      }
      else if (comandaQuery == "display")
        Tabel::Display(query);
      else if (comandaQuery == "insert")
        Tabel::Insert(query);
      else if (comandaQuery == "delete")
        Tabel::Delete(query);
      else if (comandaQuery == "select")
        Tabel::Select(query);
      else if (comandaQuery == "update")
        Tabel::Update(query);
      else
        cout << "Comanda query-ului nu este suportata";
    }
  }

  return 0;
}
