#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TapeViewWidget.h"
#include "GameController.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(GameController* controller, QWidget *parent = nullptr);

private slots:
    void onTick();

    void onPlay();
    void onPause();
    void onStep();
    void onReset();
    void onSpeedChanged(int value);

    void onAddRule();
    void onDeleteRule();
    void onCellChanged(int row, int column);

private:
    void setupUI();
    void setupConnections();

    TapeViewWidget *m_tapeView;
    QTableWidget *m_transitionTable;
    GameController* m_controller;
    
    QPushButton *m_playBtn;
    QPushButton *m_pauseBtn;
    QPushButton *m_stepBtn;
    QPushButton *m_resetBtn;
    QPushButton *m_addRuleBtn;
    QPushButton *m_deleteRuleBtn;
    QSlider *m_speedSlider;
    QLabel *m_speedLabel;

    QTimer *m_timer;
   // QList<char> m_tapeData;
    int m_headPos = 0;
};

#endif//MAINWINDOW_H