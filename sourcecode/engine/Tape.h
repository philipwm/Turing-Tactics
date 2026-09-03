#ifndef TAPE_H
#define TAPE_H

#include "Symbol.h"
#include <vector>

class Tape {
private:
    int headPosition;
    std::vector<Bandsymbol> cells;

public:
    Bandsymbol read() const;
    void write(Bandsymbol newSymbol);

    void moveLeft();
    void moveRight();
    
    int getPosition() const;
    
};
#endif //TAPE_H