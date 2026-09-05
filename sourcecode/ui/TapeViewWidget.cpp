#include "TapeViewWidget.h"

#include <QPainter>
#include <QPaintEvent>

TapeViewWidget::TapeViewWidget(QWidget *parent) : QWidget(parent) {
    setMinimumHeight(100);

    this->m_headAnimation = new QPropertyAnimation(this, "animatedHeadPosition", this);
    this->m_headAnimation->setDuration(250); 
    this->m_headAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

void TapeViewWidget::setAnimatedHeadPosition(double newHeadPosition) {
    this->m_animatedHead = newHeadPosition;
    update(); 
}

void TapeViewWidget::updateTapeFromEngine(Tape* tape, int headPosition) {
    this->m_tape = tape;
    this->m_head = headPosition;

    m_headAnimation->stop();
    m_headAnimation->setStartValue(m_animatedHead);
    m_headAnimation->setEndValue(static_cast<double>(headPosition));
    m_headAnimation->start();
}

/* void TapeViewWidget::updateTapeFromData(QList<char> tapeData, int headPosition){
    this->m_head = headPosition;
    
} */

void TapeViewWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();
    int centerY = height / 2;
    int centerX = width / 2;

    painter.fillRect(rect(), QColor(245, 245, 247));

    int renderRange = (width / (cellSize + cellSpacing)) / 2 + 2;
    int currentCenterIndex = static_cast<int>(m_animatedHead);

    for (int i = currentCenterIndex - renderRange; i <= currentCenterIndex + renderRange; ++i) {
        double offsetFromHead = i - m_animatedHead;
        double x = centerX + offsetFromHead * (cellSize + cellSpacing) - (cellSize / 2.0);
        double y = centerY - (cellSize / 2.0);

        QRectF cellRect(x, y, cellSize, cellSize);

        Bandsymbol symbol = (i >= 0 && i < m_tape->mySize()) ? (*m_tape)[i] : Bandsymbol::blank;

        bool isCurrentHead = (i == m_head);
        painter.setPen(isCurrentHead ? QPen(QColor(0, 122, 255), 2) : QPen(Qt::gray, 1));
        painter.setBrush(isCurrentHead ? QColor(220, 235, 252) : Qt::white);
        painter.drawRoundedRect(cellRect, 8, 8);

        painter.setPen(Qt::black);
        QFont font = painter.font();
        font.setPointSize(14);
        font.setBold(true);
        painter.setFont(font);
        painter.drawText(cellRect, Qt::AlignCenter, QString(getBandsymbolStringsValue(symbol)));
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 122, 255));
    QPolygonF arrow;
    arrow << QPointF(centerX - 10, centerY - (this->cellSize / 2.0) - 12)
          << QPointF(centerX + 10, centerY - (this->cellSize / 2.0) - 12)
          << QPointF(centerX, centerY - (this->cellSize / 2.0) - 2);
    painter.drawPolygon(arrow);
}