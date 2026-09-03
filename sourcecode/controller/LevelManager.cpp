#include "LevelManager.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

LevelManager::LevelManager(QObject* parent): QObject(parent){
    this->m_currentIndex = -1;
}

bool LevelManager::loadLevels(const QString& directoryPath){
    QDir directory(directoryPath);

    if (!directory.exists()) {
        emit loadingError(
            QString("Level directory does not exist: %1").arg(directoryPath)
        );

        return false;
    }

    const QStringList files =
        directory.entryList(
            {"*.json"},
            QDir::Files,
            QDir::Name
        );

    m_levels.clear();
    m_currentIndex = -1;

    for (const QString& fileName : files) {
        QFile file(directory.filePath(fileName));

        if (!file.open(QIODevice::ReadOnly)) {
            emit loadingError(
                QString("Could not open level: %1")
                    .arg(fileName)
            );

            continue;
        }

        const QByteArray data = file.readAll();

        QJsonParseError parseError;
        const QJsonDocument document =
            QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            emit loadingError(
                QString("Invalid JSON in %1: %2")
                    .arg(fileName)
                    .arg(parseError.errorString())
            );

            continue;
        }

        try {
            PuzzleLevel level =
                PuzzleLevel::fromJson(document.object());

            m_levels.append(level);
        }
        catch (const std::exception& e) {
            emit loadingError(
                QString("Could not load %1: %2")
                    .arg(fileName)
                    .arg(e.what())
            );
        }
    }

    if (m_levels.isEmpty()) {
        emit loadingError("No valid levels were found.");
        return false;
    }

    return loadLevel(0);
}

bool LevelManager::loadLevel(int index){
    if (index < 0 || index >= m_levels.size()) {
        emit loadingError(
            QString("Invalid level index: %1").arg(index)
        );

        return false;
    }

    m_currentIndex = index;

    emit levelChanged(m_levels[m_currentIndex]);

    return true;
}

int LevelManager::currentLevelIndex() const{
    return m_currentIndex;
}

int LevelManager::levelCount() const{
    return m_levels.size();
}

const PuzzleLevel& LevelManager::currentLevel() const{
    return m_levels.at(m_currentIndex);
}

const QVector<PuzzleLevel>& LevelManager::levels() const{
    return m_levels;
}

bool LevelManager::hasNextLevel() const{
    return m_currentIndex >= 0 &&
           m_currentIndex + 1 < m_levels.size();
}

bool LevelManager::hasPreviousLevel() const{
    return m_currentIndex > 0;
}

void LevelManager::nextLevel(){
    if (hasNextLevel()) {
        loadLevel(m_currentIndex + 1);
    }
    else {
        emit allLevelsCompleted();
    }
}

void LevelManager::previousLevel(){
    if (hasPreviousLevel()) {
        loadLevel(m_currentIndex - 1);
    }
}

void LevelManager::restartLevel(){
    if (m_currentIndex >= 0) {
        emit levelChanged(m_levels[m_currentIndex]);
    }
}
