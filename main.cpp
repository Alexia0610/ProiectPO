#include <iostream>
#include "baza_de_date.h"
#include "tabel.h"
#include "vector"
#include "string"

using namespace std;

vector<string> fisiereStructuraExistenta = {
    "./fisiere_input/structura_existenta/student.txt",
    "./fisiere_input/structura_existenta/curs.txt"
};

int main(int argc, char *argv[]) {
  if (argc > 6) {
    cout << "Numarul de nume de fisiere trimise ca argument nu trebuie sa depaseasca un total de 5\n";
  }

  BazaDeDate clasaDeStudenti = BazaDeDate("clasa_de_studenti");

  for (auto & i : fisiereStructuraExistenta) {
    vector<string> bucatiLocatieFisier = Utile::delimiteaza(i, '/', false);
    string numeFisier = Utile::delimiteaza(bucatiLocatieFisier[bucatiLocatieFisier.size() - 1], '.', false)[0];

    clasaDeStudenti.CreateTable(new Tabel(numeFisier, i));
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
      clasaDeStudenti.executaQueryuri(queryuri);
    }
  }

  cout << "Introduceti query-uri SQL delimitate de \";\" sau o noua linie\n";

  while (getline(cin, input)) {
    if (input.empty())
      cout << "Trebuie sa introduceti un SQL query valid!\n";

    clasaDeStudenti.executaQueryuri(input);
  }

  return 0;
}
