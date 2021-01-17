#ifndef coloana_h
#define coloana_h

#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include "utile.h"

using namespace std;

class Coloana {
 protected:
  string nume;
  string tip;
  int dimensiune;
  int nrValori;
 public:
  virtual string getNume() = 0;
  virtual string getTip() = 0;
  virtual int getDimensiune() = 0;
  virtual void adaugaValoare(string valoare) = 0;
  virtual void inlocuiesteValoareaLa(int index, string valoare) = 0;
  virtual void stergeValoareaLa(int index) = 0;
  virtual string valoareCaText(int index) = 0;
  virtual int getNrValori() = 0;
  virtual int getDimensiuneMaxText() = 0;
};

class ColoanaText : public Coloana {
  string valoareImplicita;
  vector<string> valori;

 public:
  ColoanaText(string nume, string tip, int dimensiune, string valoareImplicita) {
    this->nume = nume;
    this->tip = tip;
    this->dimensiune = dimensiune;
    this->valoareImplicita = valoareImplicita;
  }

  void adaugaValoare(string valoare) override {
    if (valoare.empty()) {
      valori.push_back(getValoareImplicita());
    } else {
      valori.push_back(valoare);
    }
  }

  virtual void stergeValoareaLa(int index) override {
    valori.erase(valori.begin() + index);
  }

  void inlocuiesteValoareaLa(int index, string val) override {
    valori.at(index) = stof(val);
  }

  string getNume() override {
    return nume;
  }

  string getTip() override {
    return tip;
  }

  int getDimensiune() override {
    return dimensiune;
  }

  string getValoareImplicita() {
    return valoareImplicita;
  }

  vector<string> getValori() {
    return valori;
  }

  string valoareCaText(int index) override {
    return valori.at(index);
  }

  int getNrValori() override {
    return valori.size();
  }

  int getDimensiuneMaxText() override {
    int dimensiune = nume.size();

    for (auto &v : valori) {
      int dimensiuneValoare = v.size();

      if (dimensiuneValoare > dimensiune)
        dimensiune = dimensiuneValoare;
    }

    return dimensiune + 5;
  }
};

class ColoanaInteger : public Coloana {
  int valoareImplicita;
  vector<int> valori;

 public:
  ColoanaInteger(string nume, string tip, int dimensiune, int valoareImplicita) {
    this->nume = nume;
    this->tip = tip;
    this->dimensiune = dimensiune;
    this->valoareImplicita = valoareImplicita;
  }

  void adaugaValoare(string valoare) override {
    try {
      if (valoare.empty()) {
        valori.push_back(getValoareImplicita());
      } else {
        valori.push_back(stoi(valoare));
      }
    }
    catch (exception &e) {
      cout << "Valoarea " + valoare + " nu este de tipul " + getTip() + " in coloana " + getNume() + "\n";
    }
  }

  virtual void stergeValoareaLa(int index) override {
    valori.erase(valori.begin() + index);
  }

  void inlocuiesteValoareaLa(int index, string val) override {
    try {
      valori.at(index) = stoi(val);
    }
    catch (exception &e) {
      cout << "Valoarea " + val + " nu este de tipul " + getTip() + " in coloana " + getNume() + "\n";
    }
  }

  string getNume() override {
    return nume;
  }

  string getTip() override {
    return tip;
  }

  int getDimensiune() override {
    return dimensiune;
  }

  int getValoareImplicita() {
    return valoareImplicita;
  }

  vector<int> getValori() {
    return valori;
  }

  string valoareCaText(int index) override {
    return to_string(valori.at(index));
  }

  int getNrValori() override {
    return valori.size();
  }

  int getDimensiuneMaxText() override {
    int dimensiune = nume.size();

    for (auto &v : valori) {
      int dimensiuneValoare = to_string(v).size();

      if (dimensiuneValoare > dimensiune)
        dimensiune = dimensiuneValoare;
    }

    return dimensiune + 5;
  }
};

class ColoanaFloat : public Coloana {
  float valoareImplicita;
  vector<float> valori;

 public:
  ColoanaFloat(string nume, string tip, int dimensiune, float valoareImplicita) {
    this->nume = nume;
    this->tip = tip;
    this->dimensiune = dimensiune;
    this->valoareImplicita = valoareImplicita;
  }

  void adaugaValoare(string valoare) override {
    try {
      if (valoare.empty()) {
        valori.push_back(getValoareImplicita());
      } else {
        valori.push_back(stof(valoare));
      }
    }
    catch (exception &e) {
      cout << "Valoarea " + valoare + " nu este de tipul " + getTip() + " in coloana " + getNume() + "\n";
    }
  }

  virtual void stergeValoareaLa(int index) override {
    valori.erase(valori.begin() + index);
  }

  void inlocuiesteValoareaLa(int index, string val) override {
    try {
      valori.at(index) = stof(val);
    }
    catch (exception &e) {
      cout << "Valoarea " + val + " nu este de tipul " + getTip() + " in coloana " + getNume() + "\n";
    }
  }

  string getNume() override {
    return nume;
  }

  string getTip() override {
    return tip;
  }

  int getDimensiune() override {
    return dimensiune;
  }

  float getValoareImplicita() {
    return valoareImplicita;
  }

  vector<float> getValori() {
    return valori;
  }

  string valoareCaText(int index) override {
    return to_string(valori.at(index));
  }

  int getNrValori() override {
    return valori.size();
  }

  int getDimensiuneMaxText() override {
    int dimensiune = nume.size();

    for (auto &v : valori) {
      int dimensiuneValoare = to_string(v).size();

      if (dimensiuneValoare > dimensiune)
        dimensiune = dimensiuneValoare;
    }

    return dimensiune + 5;
  }
};

#endif