#ifndef TAPEVIEWWIDGET_H
#define TAPEVIEWWIDGET_H

#include "Tape.h"

#include <QWidget>
//#include <Qlist>
#include <QPropertyAnimation>
#include <QVariantList>

class TapeViewWidget : public QWidget{
    Q_OBJECT
    Q_PROPERTY(double animatedHeadPosition READ animatedHeadPosition WRITE setAnimatedHeadPosition)

private:
    Tape* m_tape;
    int m_head;
    double m_animatedHead;
    QPropertyAnimation* m_headAnimation; 
    const int cellSize = 80;
    const int cellSpacing = 8;

public:
    TapeViewWidget(QWidget* parent=nullptr);
    double animatedHeadPosition() const;
    void setAnimatedHeadPosition(double newHeadPosition);

public slots:
    void updateTapeFromEngine(Tape* tape, int headPosition);
    //void updateTapeFromData(QList<char> tapeData, int headPosition);
    void paintEvent(QPaintEvent* event);

};


#endif// TAPEVIEWWIDGET_H
