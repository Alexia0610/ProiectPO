#include <vector>
#include <string>
#include <sstream>
#include "utile.h"

using namespace std;

vector<string> Utile::delimiteaza(const string &s, char delim) {
  vector<string> qs;
  stringstream ss(s);
  string query;

  while (getline(ss, query, delim)) {
    string q = eliminaSpatii(query);

    if (!q.empty())
      qs.push_back(q);
  }

  return qs;
}

string Utile::eliminaSpatii(const string &str, const string &whitespace) {
  const auto inceput = str.find_first_not_of(whitespace);

  if (inceput == string::npos)
    return "";

  const auto sfarsit = str.find_last_not_of(whitespace);
  const auto sfarsitNou = sfarsit - inceput + 1;

  return str.substr(inceput, sfarsitNou);
}