#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "Transitionresults.h"

#include <map>
#include <utility>

class Transitions{
public:
  std::map< std::pair<std::string , Bandsymbol> ,Transitionresult> delta;
};

#endif //TRANSITIONS_H
