#ifndef TRANSITIONRESULTS_H
#define TRANSITIONRESULTS_H

#include "Symbol.h"
#include <string>

enum class Direction{
  left,
  right,
  neutral
};

class Transitionresult{
public:
  std::string nextState;
  Bandsymbol newSymbol;
  Direction direction;
};

#endif //TRANSITIONRESULTS_H
