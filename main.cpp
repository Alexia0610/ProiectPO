#include <iostream>
#include "query.h"
#include "baza_de_date.h"
#include "tabel.h"
#include "vector"
#include "string"

using namespace std;

vector<string> fisiereStructuraExistenta = {"./fisiere_input/structura_existenta/studenti.txt"};

int main(int argc, char *argv[]) {
  if (argc > 6) {
    cout << "Numarul de nume de fisiere trimise ca argument nu trebuie sa depaseasca un total de 5\n";
  }

  BazaDeDate clasaDeStudenti = BazaDeDate("clasa_de_studenti");

  for (int i = 0; i < fisiereStructuraExistenta.size(); i++) {
    vector<string> bucatiLocatieFisier = Utile::delimiteaza(fisiereStructuraExistenta[i], '/');
    string numeFisier = Utile::delimiteaza(bucatiLocatieFisier[bucatiLocatieFisier.size() - 1], '.')[0];

    clasaDeStudenti.adaugaTabel(new Tabel(numeFisier, fisiereStructuraExistenta[i]));
  }

  string input;

  for (int i = 1; i < argc; i++) {
    string numeFisier = argv[i];

    ifstream fisierInstructiuni(numeFisier);

    if (!fisierInstructiuni.is_open()) {
      cout << "Fisierul " + numeFisier + " nu poate fi citit\n";
    }

    string queryuri;

    while (getline(fisierInstructiuni, queryuri)) {
      Query::parseazaQueryuri(clasaDeStudenti, queryuri);
    }
  }

  cout << "Introduceti query-uri SQL delimitate de \";\" sau o noua linie\n";

  while (getline(cin, input)) {
    if (input.empty())
      cout << "Trebuie sa introduceti un SQL query valid!\n";

    Query::parseazaQueryuri(clasaDeStudenti, input);
  }

  return 0;
}
