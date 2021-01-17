#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>

using namespace std;

class Query {
 public:
  static string valideazaCreate(string query);
  static pair<string, string> valideazaDrop(string query);
  static string valideazaDisplay(string query);
  static tuple<string, string, string> valideazaDelete(string query);
  static vector<vector<string>> valideazaValoriColoane(string s);
  static pair<string, vector<vector<string>>> valideazaInsert(string query);
  static tuple<vector<string>, string, pair<string, string>> valideazaSelect(string query);
  static tuple<string, pair<string, string>, pair<string, string>> valideazaUpdate(string query);
};

#endif
