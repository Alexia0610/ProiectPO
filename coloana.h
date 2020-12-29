#ifndef coloana_h
#define coloana_h

#include <string>
#include <vector>

using namespace std;

template <typename T = string>
class Coloana
{
  string name;
  string tip;
  int dimensiune;
  T valoareImplicita;
  vector<T> valori;
};

#endif