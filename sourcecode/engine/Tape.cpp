#include "Tape.h"

#include <vector>
using std::vector;

int Tape::getPosition() const{
    return this->headPosition;
}

void Tape::moveLeft(){ this->headPosition += 1; }
void Tape::moveRight(){ this->headPosition -= 1; }

void Tape::write(Bandsymbol newSymbol){
    this->cells[this->headPosition] = newSymbol;
}

Bandsymbol Tape::read() const {
    auto pos = this->getPosition();
    return this->cells[pos];    
}

int Tape::mySize(){
    return this->cells.size();
}

Bandsymbol Tape::operator[](int x){
    return this->cells[x];
}
