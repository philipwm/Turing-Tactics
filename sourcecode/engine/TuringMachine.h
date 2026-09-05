#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include "Transitions.h"
#include "Tape.h"

class TuringMachine {
private:
    Transitions tr;
    Tape workTape;
    std::string currentState;

public:
    //TODO: add methods to getTape() and getcurrentstate() so the whole tape and currentstate are visible.
    void tmWrite(Bandsymbol newSymbol);
    int tmGetPosition() const;
    Tape getWorkTape();
    void tmMoveRight();
    void tmMoveLeft();
    Bandsymbol tmRead() const;
    void step();
};

#endif //TURINGMACHINE_H