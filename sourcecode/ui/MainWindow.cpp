#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QHeaderView>
#include <QGroupBox>

MainWindow::MainWindow(GameController *controller ,QWidget *parent) : m_controller(controller) ,QMainWindow(parent) {
    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    // Initial mock tape state
    m_tapeData = {'1', '1', '0', '1', ' ', ' ',' ',' '};
    m_headPos = 0;

    setupUI();
    setupConnections();

    m_tapeView->updateTapeFromData(m_tapeData, m_headPos);
}

void MainWindow::setupUI() {
    resize(900, 600);
    setWindowTitle("Turing Machine Simulator");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_tapeView = new TapeViewWidget(this);

    QSplitter *bottomSplitter = new QSplitter(Qt::Horizontal, this);

    QWidget *tableContainer = new QWidget(this);
    QVBoxLayout *tableLayout = new QVBoxLayout(tableContainer);

    m_transitionTable = new QTableWidget(0, 5, this);
    m_transitionTable->setHorizontalHeaderLabels({"State In", "Read", "State Out", "Write", "Direction"});
    m_transitionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout *tableBtnLayout = new QHBoxLayout();
    m_addRuleBtn = new QPushButton("Add Rule", this);
    m_deleteRuleBtn = new QPushButton("Delete Selected", this);
    tableBtnLayout->addWidget(m_addRuleBtn);
    tableBtnLayout->addWidget(m_deleteRuleBtn);

    tableLayout->addWidget(m_transitionTable);
    tableLayout->addLayout(tableBtnLayout);

    QGroupBox *controlGroup = new QGroupBox("Execution Controls", this);
    QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);

    m_playBtn = new QPushButton("Play", this);
    m_pauseBtn = new QPushButton("Pause", this);
    m_stepBtn = new QPushButton("Step", this);
    m_resetBtn = new QPushButton("Reset", this);

    m_speedSlider = new QSlider(Qt::Horizontal, this);
    m_speedSlider->setRange(50, 1000); //delay range
    m_speedSlider->setValue(500);
    m_speedSlider->setInvertedAppearance(true); // Left = faster, Right = slower

    m_speedLabel = new QLabel("Delay: 200 ms", this);

    controlLayout->addWidget(m_playBtn);
    controlLayout->addWidget(m_pauseBtn);
    controlLayout->addWidget(m_stepBtn);
    controlLayout->addWidget(m_resetBtn);
    controlLayout->addSpacing(20);
    controlLayout->addWidget(m_speedLabel);
    controlLayout->addWidget(m_speedSlider);
    controlLayout->addStretch();

    bottomSplitter->addWidget(tableContainer);
    bottomSplitter->addWidget(controlGroup);
    bottomSplitter->setStretchFactor(0, 3);
    bottomSplitter->setStretchFactor(1, 1);

    QSplitter *mainSplitter = new QSplitter(Qt::Vertical, this);
    mainSplitter->addWidget(m_tapeView);
    mainSplitter->addWidget(bottomSplitter);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 2);

    mainLayout->addWidget(mainSplitter);
}

void MainWindow::setupConnections() {
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTick);

    connect(m_playBtn, &QPushButton::clicked, this, &MainWindow::onPlay);
    connect(m_pauseBtn, &QPushButton::clicked, this, &MainWindow::onPause);
    connect(m_stepBtn, &QPushButton::clicked, this, &MainWindow::onStep);
    connect(m_resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(m_speedSlider, &QSlider::valueChanged, this, &MainWindow::onSpeedChanged);

    connect(m_addRuleBtn, &QPushButton::clicked, this, &MainWindow::onAddRule);
    connect(m_deleteRuleBtn, &QPushButton::clicked, this, &MainWindow::onDeleteRule);
    connect(m_transitionTable, &QTableWidget::cellChanged, this, &MainWindow::onCellChanged);
}

void MainWindow::onTick() {
    onStep(); 
}

void MainWindow::onPlay() {
    m_timer->start();
}

void MainWindow::onPause() {
    m_timer->stop();
}

void MainWindow::onStep() {
    // TODO: Connect this to GameController::step() logic
    // Mock tape step movement for UI demonstration:
    m_headPos++;
    if (m_headPos >= m_tapeData.size()) {
        m_tapeData.append(' ');
    }
    m_tapeView->updateTapeFromEngine(m_controller.m_tape(), m_headPos);
}

void MainWindow::onReset() {
    m_timer->stop();
    m_headPos = 0;
    m_tapeView->updateTapeFromEngine(m_controller->m_tape(), m_headPos);
}

void MainWindow::onSpeedChanged(int value) {
    m_timer->setInterval(value);
    m_speedLabel->setText(QString("Delay: %1 ms").arg(value));
}

void MainWindow::onAddRule() {
    int row = m_transitionTable->rowCount();
    m_transitionTable->insertRow(row);

    m_transitionTable->setItem(row, 0, new QTableWidgetItem("q0"));
    m_transitionTable->setItem(row, 1, new QTableWidgetItem("0"));
    m_transitionTable->setItem(row, 2, new QTableWidgetItem("q1"));
    m_transitionTable->setItem(row, 3, new QTableWidgetItem("1"));
    m_transitionTable->setItem(row, 4, new QTableWidgetItem("R"));
}

void MainWindow::onDeleteRule() {
    int row = m_transitionTable->currentRow();
    if (row >= 0) {
        m_transitionTable->removeRow(row);
        // TODO: Sync deletion to underlying TuringMachine object
    }
}

void MainWindow::onCellChanged(int row, int column) {
    QTableWidgetItem *item = m_transitionTable->item(row, column);
    if (!item) return;

    QString newValue = item->text();
    
    // TODO: Sync rule change directly to backend backend engine
    // Example: TuringMachine::updateRule(row, column, newValue.toStdString());
}