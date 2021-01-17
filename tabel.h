#ifndef tabel_h
#define tabel_h

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <set>
#include "coloana.h"
#include "utile.h"

using namespace std;

class Tabel {
  string nume;
  vector<Coloana *> coloane;
  set<string> numeColoane;

 private:
  void afiseazaTabel(string numeFisier);
  void afiseazaTabelBinar(string numeFisier);
  void afiseazaTabel(string numeFisier, vector<string> numeColoane);
  void afiseazaTabel(string numeFisier, vector<string> numeColoane, pair<string, string> conditieWhere);

 public:
  Tabel(string nume) {
    this->nume = nume;
  }

  Tabel(string nume, vector<Coloana *> coloane, set<string> numeColoane) {
    this->nume = nume;
    this->coloane = coloane;
    this->numeColoane = numeColoane;
  }

  Tabel(string numeTabel, string numeFisier) {
    nume = numeTabel;

    ifstream fisierTabel(numeFisier);

    if (!fisierTabel.is_open()) {
      cout << "Fisierul " + numeFisier + " nu poate fi citit\n";
    }

    string definitieColoana;

    while (getline(fisierTabel, definitieColoana)) {
      vector<string> col = Utile::delimiteaza(definitieColoana, ',', false);

      string numeColoana = Utile::eliminaSpatii(col[0]);
      string tipColoana = Utile::eliminaSpatii(col[1]);
      int dimensiuneColoana = stoi(Utile::eliminaSpatii(col[2]));
      string valoareImplicitaColoana;

      if (col.size() == 3) {
        valoareImplicitaColoana = "";
      } else if (col.size() == 4) {
        valoareImplicitaColoana = Utile::eliminaSpatii(col[3]);
      } else {
        cout << "Definitia unei coloane din fisierul " + numeFisier + " poate avea doar 3 sau 4 proprietati";
      }

      if (tipColoana == "text") {
        adaugaColoana(new ColoanaText(numeColoana, tipColoana, dimensiuneColoana,
                                      Utile::eliminaSubstring(valoareImplicitaColoana)));
      } else if (tipColoana == "integer") {
        int val;

        if (valoareImplicitaColoana.empty()) {
          val = 0;
        } else {
          val = stoi(valoareImplicitaColoana);
        }

        adaugaColoana(new ColoanaInteger(numeColoana, tipColoana, dimensiuneColoana, val));
      } else if (tipColoana == "float") {
        float val;

        if (valoareImplicitaColoana.empty()) {
          val = 0.0;
        } else {
          val = stof(valoareImplicitaColoana);
        }

        adaugaColoana(new ColoanaFloat(numeColoana, tipColoana, dimensiuneColoana, val));
      }
    }
  }

  string getNume();
  void adaugaColoana(Coloana *c);
  void Insert(string numeFisier, vector<vector<string>> valoriRanduri);
  void Select(string numeFisier, vector<string> numeColoane, pair<string, string> conditieWhere);
  void Delete(string numeFisier, string numeColoana, string valoare);
  void Display(string numeFisier);
  void Update(string numeFisier, pair<string, string> valoriSet, pair<string, string> conditieWhere);
  void DropIndex(string numeFisier, string numeIndex);
};

#endif