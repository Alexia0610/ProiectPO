#ifndef UTILE_H
#define UTILE_H

#include <vector>
#include <string>

using namespace std;

class Utile {
 public:
  static vector<string> delimiteaza(const string &s, char delim);
  static string eliminaSpatii(const string &str, const string &whitespace = " \t");
  static string parseazaDateColoana(string date);
};

#endif
