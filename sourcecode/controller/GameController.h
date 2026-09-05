#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "TuringMachine.h"
//#include "PuzzleLevel.h"

#include <QObject>
#include <QTimer>
#include <QString>


class GameController : public QObject{
    Q_OBJECT

public:
     GameController(QObject* parent = nullptr);

    void start();
    void pause();
    void step();


    void writeSymbol(Bandsymbol& symbol);
    void moveLeft();
    void moveRight();

    
    bool isRunning() const;
    TuringMachine* machine();
    Tape * m_tape();

    const TuringMachine& machine() const;

signals:
    void machineMoved();
    void tapeChanged();
    void started();
    void paused();

private slots:
    void onTimerTick();

private:
    TuringMachine m_tm;
    QTimer* m_timer;
    bool m_isRunning = false;
};

#endif // GAMECONTROLLER_H