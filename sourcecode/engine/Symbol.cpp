#include "Symbol.h"

const char* getBandsymbolStringsValue(Bandsymbol symbol){
    auto intVal = static_cast<int>(symbol);
    return BandsymbolStrings[intVal];
}