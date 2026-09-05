#include "TuringMachine.h"

int TuringMachine::tmGetPosition() const{
    return this->workTape.getPosition();
}

Tape TuringMachine::getWorkTape(){
    return this->workTape;
}

void TuringMachine::tmMoveLeft(){
    this->workTape.moveLeft();
}

void TuringMachine::tmMoveRight(){
    this->workTape.moveRight();
}

void TuringMachine::tmWrite(Bandsymbol newSymbol){
    this->workTape.write(newSymbol);
}

Bandsymbol TuringMachine::tmRead() const{
    return this->workTape.read();
}

void TuringMachine::step(){
    Bandsymbol symbol = this->tmRead();
    std::pair key = std::make_pair(this->currentState, symbol);
    auto result = this->tr.delta[key];

    this->tmWrite(result.newSymbol);

    if(result.direction == Direction::left){
        this->tmMoveLeft();
    } else if(result.direction == Direction::right){
        this->tmMoveRight();
    }

    currentState = result.nextState;
}