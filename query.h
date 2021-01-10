#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include "baza_de_date.h"

using namespace std;

class Query {
 public:
  static void parseazaQueryuri(BazaDeDate b, string queryuri);
};

#endif
