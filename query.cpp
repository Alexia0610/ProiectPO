#include "query.h"
#include "tabel.h"
#include "utile.h"
#include <string>
#include <vector>

using namespace std;

string Query::valideazaCreate(string query) {
  regex formatCreate("CREATE\\sTABLE\\s(\\w+)", std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatCreate)) {
    cout << "Query-ul \"" + query + "\" este invalid\n";

    return nullptr;
  }

  return elemQuery.str(1);
}

pair<string, string> Query::valideazaDrop(string query) {
  regex formatDrop("DROP\\s(TABLE|INDEX)\\s(\\w+)", std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatDrop)) {
    cout << "Query-ul \"" + query + "\" este invalid\n";

    return make_pair("", "");
  }

  return make_pair(elemQuery.str(1), elemQuery.str(2));
}

string Query::valideazaDisplay(string query) {
  regex formatDisplay("DISPLAY\\sTABLE\\s(\\w+)", std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatDisplay)) {
    cout << "Query-ul \"" + query + "\" este invalid\n";

    return "";
  }

  return elemQuery.str(1);
}

tuple<string, string, string> Query::valideazaDelete(string query) {
  regex formatDelete("DELETE\\sFROM\\s(\\w+)\\sWHERE\\s(\\w+)\\s\\=\\s(\\w+)", std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatDelete)) {
    cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    return make_tuple("", "", "");
  }

  return make_tuple(elemQuery.str(1), elemQuery.str(2), elemQuery.str(3));
}

vector<vector<string>> Query::valideazaValoriColoane(string s) {
  vector<vector<string>> seturiValoriColoane;

  s = Utile::eliminaParanteze(s);
  string deEliminat = "\"";
  s = Utile::eliminaSubstring(s, deEliminat);

  if (s.empty())
    return seturiValoriColoane;

  // Sterge toate caracterele '('
  s.erase(std::remove(s.begin(), s.end(), '('), s.end());

  // Delimiteaza seturile de valori; fiecare element din vector va contine un string cu toate valorile unui rand
  vector<string> valoriColoane = Utile::delimiteaza(s, ')', false);

  // Delimiteaza valorile unui rand in cate un string separat
  for (auto &i : valoriColoane) {
    seturiValoriColoane.push_back(Utile::delimiteaza(i, ',', true));
  }

  return seturiValoriColoane;
}

pair<string, vector<vector<string>>> Query::valideazaInsert(string query) {
  regex formatInsert("INSERT\\sINTO\\s(\\w+)\\sVALUES\\s(.+)", std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatInsert)) {
    cout << "Query-ul \"" + query + "\" este invalid\n";

    return make_pair(nullptr, vector<vector<string>>());
  }

  return make_pair(elemQuery.str(1), valideazaValoriColoane(elemQuery.str(2)));
}

tuple<vector<string>, string, pair<string, string>> Query::valideazaSelect(string query) {
  regex formatSelectAll(
      "SELECT\\sALL\\sFROM\\s(\\w+)(.*)",
      std::regex_constants::icase
  );
  smatch elemQuerySelectAll;
  vector<string> toSelect;

  if (!regex_search(query, elemQuerySelectAll, formatSelectAll)) {
    regex formatSelect("SELECT\\s(\\(.*\\))\\sFROM\\s(\\w+)(.*)", std::regex_constants::icase);
    smatch elemQuerySelect;

    if (!regex_search(query, elemQuerySelect, formatSelect)) {
      cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

      return make_tuple(toSelect, "", make_pair("", ""));
    }

    string coloane = Utile::eliminaParanteze(elemQuerySelect.str(1));
    vector<string> numeColoane = Utile::delimiteaza(coloane, ',', true);

    regex formatWhere("\\sWHERE\\s(\\w+)\\s\\=\\s(\\w+)", std::regex_constants::icase);
    smatch elemWhere;

    string maybeWhere = elemQuerySelect.str(3);

    if (!regex_search(maybeWhere, elemWhere, formatWhere)) {
      return make_tuple(numeColoane, elemQuerySelect.str(2), make_pair("", ""));
    }

    return make_tuple(numeColoane, elemQuerySelect.str(2),
                      make_pair(elemWhere.str(1), elemWhere.str(2)));
  }

  toSelect.emplace_back("*");

  return make_tuple(toSelect, elemQuerySelectAll.str(1), make_pair("", ""));
}

tuple<string, pair<string, string>, pair<string, string>> Query::valideazaUpdate(string query) {
  regex formatUpdate("UPDATE\\s(\\w+)\\sSET\\s(\\w+)\\s\\=\\s(\\w+)\\sWHERE\\s(\\w+)\\s\\=\\s(\\w+)",
                     std::regex_constants::icase);
  smatch elemQuery;

  if (!regex_search(query, elemQuery, formatUpdate)) {
    cout << "Query-ul de afisare a tabelului \"" + query + "\" este invalid\n";

    return make_tuple("", make_pair("", ""), make_pair("", ""));
  }

  return make_tuple(elemQuery.str(1), make_pair(elemQuery.str(2), elemQuery.str(3)),
                    make_pair(elemQuery.str(4), elemQuery.str(5)));
}