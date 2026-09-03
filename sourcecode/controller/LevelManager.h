#ifndef LEVELMANAGER_H
#define LEVELAMANGER_H

#include "Puzzlelevel.h"
#include <QObject>
#include <QString>
#include <QVector>


class LevelManager : public QObject{
    Q_OBJECT

public:
    explicit LevelManager(QObject* parent = nullptr);

    bool loadLevels(const QString& directoryPath);
    bool loadLevel(int index);

    int currentLevelIndex() const;
    int levelCount() const;

    const PuzzleLevel& currentLevel() const;
    const QVector<PuzzleLevel>& levels() const;

    bool hasNextLevel() const;
    bool hasPreviousLevel() const;

public slots:
    void nextLevel();
    void previousLevel();
    void restartLevel();

signals:
    void levelChanged(const PuzzleLevel& level);
    void levelCompleted(int index);
    void allLevelsCompleted();

    void loadingError(const QString& message);

private:
    QVector<PuzzleLevel> m_levels;
    int m_currentIndex;
};

#endif // LEVELMANAGER_H