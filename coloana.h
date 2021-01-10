#ifndef coloana_h
#define coloana_h

#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include "utile.h"

using namespace std;

class Coloana {};

template<typename T>
class ColoanaTip : public Coloana {
  string nume;
  string tip;
  int dimensiune;
  T valoareImplicita;
  vector<T> valori;

 public:
  ColoanaTip(string nume, string tip, int dimensiune, T valoareImplicita) {
    this->nume = nume;
    this->tip = tip;
    this->dimensiune = dimensiune;
    this->valoareImplicita = valoareImplicita;
  }

  template<typename A>
  void adaugaElement(T element) {
    valori.insert(element);
  }

  string GetNume() {
    return nume;
  }

  string GetTip() {
    return tip;
  }

  int GetDimensiune() {
    return dimensiune;
  }

  T GetValoareImplicita() {
    return valoareImplicita;
  }

  vector<T> GetValori() {
    return valori;
  }
};

#endif