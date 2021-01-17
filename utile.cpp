#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include "utile.h"

using namespace std;

vector<string> Utile::delimiteaza(const string &s, char delim, bool adaugaGol = false) {
  vector<string> qs;
  stringstream ss(s);
  string query;

  while (getline(ss, query, delim)) {
    string q = eliminaSpatii(query);

    if (!q.empty() || (q.empty() && adaugaGol))
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

string Utile::eliminaParanteze(string s) {
  // Sterge '(' si ')' care incadreaza seturile de valori
  if (s.size() < 2) {
    return "";
  }

  return s.substr(1, s.size() - 2);
}

string Utile::eliminaSubstring(string &str, const string &subStr) {
  regex pattern(subStr);

  return regex_replace(str, pattern, "");
}

void Utile::creeazaFisier(string nume, const string folder) {
  string locatieFisier = folder + "/" + nume;

  ofstream g(locatieFisier, ios::out | ios::trunc);

  if (g.fail()) {
    string err = "Fisierul " + locatieFisier + " nu a putut fi creat";
    perror(err.c_str());
  } else {
    string msg = "Fisierul " + locatieFisier + " a fost creat cu succes";
    puts(msg.c_str());
  }

  g.close();
}

void Utile::stergeFisier(string nume, const string folder) {
  string locatieFisier = folder + "/" + nume;

  if (remove(locatieFisier.c_str()) != 0) {
    string err = "Fisierul " + locatieFisier + " nu a putut fi sters";
    perror(err.c_str());
  }
}

void Utile::creeazaFisierBinar(string nume, const string folder) {
  string locatieFisier = folder + "/" + nume;

  ofstream g(locatieFisier, ios::out | ios::trunc | ios::binary);

  if (g.fail()) {
    string err = "Fisierul " + locatieFisier + " nu a putut fi creat";
    perror(err.c_str());
  }

  g.close();
}

void Utile::adaugaInFisierText(string nume, const string folder, string deAdaugat) {
  string locatieFisier = folder + "/" + nume;

  ofstream g(locatieFisier, ios::out | ios::app);

  g << deAdaugat;

  g.close();
}

void Utile::adaugaInFisierText(string nume, const string folder, string deAdaugat, int format) {
  string locatieFisier = folder + "/" + nume;

  ofstream g(locatieFisier, ios::out | ios::app);

  g << left << setw(format) << deAdaugat;

  g.close();
}

void Utile::adaugaInFisierBinar(string nume, const string folder, string deAdaugat) {
  string locatieFisier = folder + "/" + nume;

  ofstream g(locatieFisier, ios::out | ios::binary | ios::app);

  g.write(deAdaugat.c_str(),deAdaugat.size());

  g.close();
}