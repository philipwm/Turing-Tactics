#include "GameController.h"

GameController::GameController(QObject* parent=nullptr):
QObject(parent), m_timer(new QTimer(this)), isRunning(false){
    this->m_timer.Interval(200);

    this->connect(m_timer, &QTimer::timeout, this, &GameController::onTimerTick);
}

void GameController::start(){
    if(m_isRunning){
        return;
    }
    
    m_timer->start();
    this->m_isRunning = true;

    emit this->started();
}

void GameController::pause(){
    if(!m_isRunning) return;

    m_timer->stop();
    this->m_isRunning = false;

    emit this->paused();
}

void GameController::step(){
    m_tm.step();

    emit this->machineMoved();
}

void GameController::writeSymbol(Bandsymbol  & newsymbol){
    m_tm.tmWrite(newsymbol);

    emit this->tapeChanged();
}

void GameController::moveLeft(){
    m_tm.tmMoveLeft();

    emit this->machineMoved();
}

void GameController::moveRight(){
    m_tm.tmMoveRight();

    emit this->machineMoved();
}

bool GameController::isRunning() const{ return this->m_isRunning; }

TuringMachine* GameController::machine(){
    return &(this->m_tm);
}

const TuringMachine & GameController::machine() const{
    return this->m_tm;
}

void GameController::onTimerTick(){
    this->step();
}