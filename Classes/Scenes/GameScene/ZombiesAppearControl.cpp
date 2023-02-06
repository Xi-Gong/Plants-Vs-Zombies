/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "ZombiesAppearControl.h"

ZombiesAppearControl::ZombiesAppearControl() :
    _zombiesAppearFrequency(0), _lastFrequencyZombiesWasDeath(false), _isBegin(false),
    _isShowWords(false), _time(0), _levelDataHandler(LevelDataHandler::getInstance()) {
    _random.seed(time(nullptr));
}

ZombiesType
    ZombiesAppearControl::createDifferentTypeZombies(const unsigned int& zombiesAppearFrequency) {
    int number = rand() % 100;
    int sum = 0, i = -1;

    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);
    auto& zombiesTypeProbabilityFrequency = levelData->zombiesTypeProbabilityFrequency;
    auto& zombiesTypeProbability = zombiesTypeProbabilityFrequency.at(zombiesAppearFrequency);
    auto& zombiesType = levelData->zombiesType;

    for (auto& probability : zombiesTypeProbability) {
        ++i;
        sum += probability;
        if (number < sum) {
            return static_cast<ZombiesType>(zombiesType.at(i));
        }
    }
    return ZombiesType::None;
}

ZombiesType ZombiesAppearControl::createDifferentTypeZombies() { return ZombiesType(); }

int ZombiesAppearControl::getZombiesNumbersForAppearFrequency(
    const unsigned int& ZombiesAppearFrequency) {
    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);

    const unsigned int number = levelData->zombiesNumbers.at(ZombiesAppearFrequency);
    return number + rand() % number;
}

int ZombiesAppearControl::getZombiesAppearFrequency() const { return _zombiesAppearFrequency; }

bool ZombiesAppearControl::getLastFrequencyZombiesWasDeath() const {
    return _lastFrequencyZombiesWasDeath;
}

bool ZombiesAppearControl::getIsBegin() const { return _isBegin; }

bool ZombiesAppearControl::getIsShowWords() const { return _isShowWords; }

double ZombiesAppearControl::getTime() const { return _time; }

int ZombiesAppearControl::getEqualProbabilityForRow() {
    uniform_int_distribution<unsigned> number(0, 4);

    if (_judgeZombieRow.size() == 5) {
        _judgeZombieRow.clear();
    }

    unsigned int row;
    do {
        row = number(_random);
    } while (_judgeZombieRow.count(row));

    _judgeZombieRow.insert(row);

    return _zombiesPosition[row];
}

void ZombiesAppearControl::setZombiesAppearFrequency(const unsigned int zombiesAppearFrequency) {
    _zombiesAppearFrequency = zombiesAppearFrequency;
}

void ZombiesAppearControl::setZombiesAppearFrequency() { ++_zombiesAppearFrequency; }

void ZombiesAppearControl::setLastFrequencyZombiesWasDeath(bool lastFrequencyZombiesWasDeath) {
    _lastFrequencyZombiesWasDeath = lastFrequencyZombiesWasDeath;
}

void ZombiesAppearControl::setTimeClear() { _time = 0; }

void ZombiesAppearControl::setTimeAdd() { ++_time; }

void ZombiesAppearControl::setTimeAdd(const double t) { _time = t; }

void ZombiesAppearControl::setIsBegin(const bool isBegin) { _isBegin = isBegin; }

void ZombiesAppearControl::setIsShowWords(const bool isShowWords) { _isShowWords = isShowWords; }
