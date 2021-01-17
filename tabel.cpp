#include "tabel.h"

string Tabel::getNume() {
  return nume;
}

void Tabel::adaugaColoana(Coloana *c) {
  string numeColoana = c->getNume();

  if (numeColoane.find(numeColoana) != numeColoane.end()) {
    cout << "O coloana numita " + numeColoana + " deja exista in tabel\n";
  } else {
    numeColoane.insert(numeColoana);
    coloane.push_back(c);
  }
}

void Tabel::Insert(string numeFisier, vector<vector<string>> valoriRanduri) {
  for (auto &valoriRand : valoriRanduri) {
    if (valoriRand.size() != coloane.size())
      cout << "Numarul de valori trebuie sa coincida numarului de coloane din tabel\n";

    for (int i = 0; i < coloane.size(); i++) {
      coloane[i]->adaugaValoare(valoriRand[i]);
    }
  }

  Utile::stergeFisier(nume);
  Utile::creeazaFisierBinar(nume);
  afiseazaTabelBinar(nume);
}

void Tabel::Select(string numeFisier, vector<string> numeColoane, pair<string, string> conditieWhere) {
  if (numeColoane.empty()) {
    cout << "S-a produs o eroare neasteptata pentru query-ul SELECT" << endl;
  }

  if (numeColoane.at(0) == "*") {
    afiseazaTabel(numeFisier);
  } else if (conditieWhere.first == "" && conditieWhere.second == "") {
    afiseazaTabel(numeFisier, numeColoane);
  } else {
    afiseazaTabel(numeFisier, numeColoane, conditieWhere);
  }
}

void Tabel::Delete(string numeFisier, string numeColoana, string valoare) {
  int nrRandUpdate = -1;

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      if (coloane[j]->getNume() == numeColoana && coloane[j]->valoareCaText(i) == valoare)
        nrRandUpdate = i;
    }
  }

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      if (coloane[j]->getNume() == numeColoana && i == nrRandUpdate)
        coloane[j]->stergeValoareaLa(i);
    }
  }

  if (nrRandUpdate > -1) {
    string msj = "Tabelul " + nume + " a fost updatat";
    Utile::adaugaInFisierText(numeFisier, "rezultate_query", msj);
    cout << msj << endl;
  }
}

void Tabel::Display(string numeFisier) {
  afiseazaTabel(numeFisier);
}

void Tabel::Update(string numeFisier, pair<string, string> valoriSet, pair<string, string> conditieWhere) {
  int nrRandUpdate = -1;

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      if (coloane[j]->getNume() == conditieWhere.first && coloane[j]->valoareCaText(i) == conditieWhere.second)
        nrRandUpdate = i;
    }
  }

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      if (coloane[j]->getNume() == valoriSet.first && i == nrRandUpdate)
        coloane[j]->inlocuiesteValoareaLa(i, valoriSet.second);
    }
  }

  if (nrRandUpdate > -1) {
    string msj = "Tabelul " + nume + " a fost updatat";
    Utile::adaugaInFisierText(numeFisier, "rezultate_query", msj);
    cout << msj << endl;
  }
}
void Tabel::DropIndex(string numeFisier, string numeIndex) {}

void Tabel::afiseazaTabel(string numeFisier) {
  for (auto &c : coloane) {
    cout << left << setw(c->getDimensiuneMaxText()) << c->getNume();
    Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                              c->getNume(), c->getDimensiuneMaxText());
  }

  cout << endl;
  Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      cout << left << setw(coloane[j]->getDimensiuneMaxText()) << coloane[j]->valoareCaText(i);
      Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                                coloane[j]->valoareCaText(i), coloane[j]->getDimensiuneMaxText());
    }

    cout << endl;
    Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");
  }

  cout << endl;
}

void Tabel::afiseazaTabelBinar(string numeFisier) {
  for (auto &c : coloane) {
    Utile::adaugaInFisierBinar(numeFisier, "tabele", c->getNume());
  }

  Utile::adaugaInFisierBinar(numeFisier, "tabele", "\n");

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      Utile::adaugaInFisierBinar(numeFisier, "tabele",coloane[j]->valoareCaText(i));
    }

    Utile::adaugaInFisierBinar(numeFisier, "tabele", "\n");
  }
}

void Tabel::afiseazaTabel(string numeFisier, vector<string> numeColoane) {
  for (auto &c : coloane) {
    for (auto &deAfisat : numeColoane) {
      if (c->getNume() == deAfisat) {
        cout << left << setw(c->getDimensiuneMaxText()) << c->getNume();
        Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                                  c->getNume(), c->getDimensiuneMaxText());
      }
    }
  }

  cout << endl;
  Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      for (auto &deAfisat : numeColoane) {
        if (coloane[j]->getNume() == deAfisat) {
          cout << left << setw(coloane[j]->getDimensiuneMaxText()) << coloane[j]->valoareCaText(i);
          Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                                    coloane[j]->valoareCaText(i), coloane[j]->getDimensiuneMaxText());
        }
      }
    }

    cout << endl;
    Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");
  }

  cout << endl;
}

void Tabel::afiseazaTabel(string numeFisier, vector<string> numeColoane, pair<string, string> conditieWhere) {
  for (auto &c : coloane) {
    for (auto &deAfisat : numeColoane) {
      if (c->getNume() == deAfisat) {
        cout << left << setw(c->getDimensiuneMaxText()) << c->getNume();
        Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                                  c->getNume(), c->getDimensiuneMaxText());
      }
    }
  }

  cout << endl;
  Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");

  vector<int> randuriDeAfisat;

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    for (int j = 0; j < coloane.size(); j++) {
      if (coloane[j]->getNume() == conditieWhere.first && coloane[j]->valoareCaText(i) == conditieWhere.second)
        randuriDeAfisat.push_back(i);
    }
  }

  bool afiseazaColoana = false;
  bool afiseazaRand = false;

  for (int i = 0; i < coloane[0]->getNrValori(); i++) {
    afiseazaRand = false;

    for (int j = 0; j < coloane.size(); j++) {
      afiseazaColoana = false;

      for (auto &deAfisat : numeColoane) {
        if (coloane[j]->getNume() == deAfisat) {
          afiseazaColoana = true;
          break;
        }
      }

      for (auto &nrRand : randuriDeAfisat) {
        if (i == nrRand) {
          afiseazaRand = true;
          break;
        }
      }

      if (afiseazaColoana && afiseazaRand) {
        cout << left << setw(coloane[j]->getDimensiuneMaxText()) << coloane[j]->valoareCaText(i);
        Utile::adaugaInFisierText(numeFisier, "rezultate_query",
                                  coloane[j]->valoareCaText(i), coloane[j]->getDimensiuneMaxText());
      }
    }

    if (afiseazaRand && afiseazaColoana) {
      cout << endl;
      Utile::adaugaInFisierText(numeFisier, "rezultate_query", "\n");
    }
  }

  cout << endl;
}
