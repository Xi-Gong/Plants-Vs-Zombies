/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSControlLayer.h"

#include "Based/MusicPlayer.h"
#include "GSAnimationLayer.h"
#include "GSButtonLayer.h"
#include "GSData.h"
#include "GSGameEndLayer.h"
#include "GSGameResultJudgement.h"
#include "GSInformationLayer.h"
#include "GSMacro.h"
#include "Plants/Plants-Files.h"
#include "ZombiesAppearControl.h"

GameMapInformation::GameMapInformation() : rowNumbers(5), columnNumbers(9) { MAP_INIT(plantsMap); }

GSControlLayer::GSControlLayer() :
    _runtime(Runtime::getInstance()), _levelDataHandler(LevelDataHandler::getInstance()),
    _gameMapInformation(nullptr), _selectPlantsTag(PlantsType::None), _plantPreviewImage(nullptr),
    _animationLayer(nullptr), _gameEndShieldLayer(nullptr), _zombiesAppearControl(nullptr) {
    srand(time(nullptr));
    LevelData* levelData = _levelDataHandler->readLevelData(_levelDataHandler->getLevelNumber());
    _munchZombiesFrequency = levelData->munchZombiesFrequency;
    _gameMapInformation = new GameMapInformation();
    _zombiesAppearControl = new ZombiesAppearControl();
}

GSControlLayer::~GSControlLayer() {
    delete _gameMapInformation;
    delete _zombiesAppearControl;
}

bool GSControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    createSchedule();
    createPlantsCardListener();
    createMouseListener();

    return true;
}

void GSControlLayer::setPlantMapCanPlant(const unsigned int colum, const unsigned int row) {
    controlLayerInformation->_gameMapInformation->plantsMap[colum][row] = NO_PLANTS;
}

void GSControlLayer::createSchedule() {
    schedule(
        [&](float) {
            controlCardEnabled();
            calculatePlantPosition();
            createZombies();
            controlRefurbishMusicAndText();
            judgeLevelIsFinished();
        },
        0.1f, "mainUpdate");

    schedule([&](float) { zombiesComeTiming(); }, 1.0f, "zombiesComing");
}

void GSControlLayer::controlCardEnabled() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    for (auto& card : userWorldData.userSelectCard) {
        /* 如果植物所需阳光数大于拥有阳光数 */
        if (buttonLayerInformation->plantsCards[card.cardTag].plantsNeedSunNumbers >
            userWorldData.sunNumbers) {
            buttonLayerInformation->plantsCards[card.cardTag].plantsCardText->setColor(
                Color3B::RED);
        } else {
            buttonLayerInformation->plantsCards[card.cardTag].plantsCardText->setColor(
                Color3B::BLACK);
        }
        /* 如果卡牌填充倒计时完成 */
        if (buttonLayerInformation->plantsCards[card.cardTag].timeBarIsFinished) {
            buttonLayerInformation->plantsCards[card.cardTag].plantsCards->setEnabled(true);
            /* 如果植物所需阳光数小于阳光数 */
            if (buttonLayerInformation->plantsCards[card.cardTag].plantsNeedSunNumbers <=
                userWorldData.sunNumbers) {
                buttonLayerInformation->plantsCards[card.cardTag].plantsCards->setColor(
                    Color3B::WHITE);
            } else {
                buttonLayerInformation->plantsCards[card.cardTag].plantsCards->setColor(
                    Color3B::GRAY);
            }
        }
    }
}

void GSControlLayer::calculatePlantPosition() {
    for (unsigned int i = 0; i < _gameMapInformation->rowNumbers; ++i) {
        for (unsigned int j = 0; j < _gameMapInformation->columnNumbers; ++j) {
            if (GRASS_INSIDE(_cur, i, j)) {
                _plantsPosition.x = j;
                _plantsPosition.y = i;
            }
        }
    }

    /* 如果不在范围内，移除到画面外 */
    if (GRASS_OUTSIDE(_cur)) {
        _plantsPosition.x = 100;
        _plantsPosition.y = 100;
    }
}

void GSControlLayer::createMouseListener() {
    /* 创建鼠标监听 */
    auto Mouse = EventListenerMouse::create();

    /* 鼠标移动 */
    Mouse->onMouseMove = [&](Event* event) {
        /* 获取鼠标位置 */
        _cur = ((EventMouse*)event)->getLocationInView();
        mouseMoveControl();
    };

    /* 鼠标按下 */
    Mouse->onMouseDown = [&](Event* event) { mouseDownControl((EventMouse*)event); };

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Mouse, this);
}

void GSControlLayer::createPlantsCardListener() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    for (auto& card : userWorldData.userSelectCard) {
        buttonLayerInformation->plantsCards[card.cardTag].plantsCards->addTouchEventListener(
            [&, card](Ref* sender, ui::Widget::TouchEventType type) {
                switch (type) {
                    case ui::Widget::TouchEventType::ENDED:
                        if (!buttonLayerInformation->mouseSelectImage->isSelectPlants) {
                            _selectPlantsTag = static_cast<PlantsType>(card.cardTag);
                        }
                        selectPlantsPreviewImage();
                        break;
                    default: break;
                }
            });
    }
}

void GSControlLayer::selectPlantsPreviewImage() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    if (buttonLayerInformation->mouseSelectImage->isSelectPlants) {
        MusicPlayer::playMusic("tap2");
        buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
            .progressTimer->setPercentage(0);
        buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
            .plantsCards->setColor(Color3B::WHITE);

        /* 加上所需的阳光数并更新 */
        userWorldData.sunNumbers =
            userWorldData.sunNumbers +
            buttonLayerInformation
                ->plantsCards[static_cast<unsigned int>(
                    buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                .plantsNeedSunNumbers;
        informationLayerInformation->updateSunNumbers();

        removePreviewPlant();

        /* 植物要求更新 */
        //            backgroundLayerInformation->gameType->updateRequirementNumbers("植物数量增加");
    } else {
        /* 如果植物所需阳光大于拥有阳光，则发出警告 */
        if (buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
                .plantsNeedSunNumbers > userWorldData.sunNumbers) {
            MusicPlayer::playMusic("buzzer");
            informationLayerInformation->sunNumberTextWarning();
        } else {
            MusicPlayer::playMusic("seedlift");

            /* 减去所需的阳光数并更新 */
            userWorldData.sunNumbers =
                userWorldData.sunNumbers -
                buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
                    .plantsNeedSunNumbers;
            informationLayerInformation->updateSunNumbers();

            /* 卡片变黑 */
            buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
                .plantsCards->setColor(Color3B::GRAY);
            buttonLayerInformation->plantsCards[static_cast<unsigned int>(_selectPlantsTag)]
                .progressTimer->setPercentage(100);

            /* 鼠标选择标记 */
            buttonLayerInformation->mouseSelectImage->isSelectPlants = true;
            buttonLayerInformation->mouseSelectImage->selectPlantsId = _selectPlantsTag;

            createPreviewPlants();
        }
    }
}

void GSControlLayer::createPreviewPlants() {
    CURSOR_VISIBLE(false)

    Plants *previewPlants = nullptr, *curPlants = nullptr; /* 预览植物 */
    switch (_selectPlantsTag) {
        case PlantsType::SunFlower:
            previewPlants = SunFlower::create(this);
            curPlants = SunFlower::create(this);
            break;
        case PlantsType::PeaShooter:
            previewPlants = PeaShooter::create(this);
            curPlants = PeaShooter::create(this);
            break;
        case PlantsType::WallNut:
            previewPlants = WallNut::create(this);
            curPlants = WallNut::create(this);
            break;
        default: break;
    }

    _plantPreviewImage = previewPlants->createPlantImage();

    _plantCurImage = curPlants->createPlantImage();
    _plantCurImage->setOpacity(255);
    _plantCurImage->setPosition(_cur);
    _plantCurImage->setGlobalZOrder(10);
}

void GSControlLayer::zombiesComeTiming() {
    if (!_zombiesAppearControl->getIsBegin()) {
        _zombiesAppearControl->setTimeClear();
        _zombiesAppearControl->setIsBegin(true);
    }

    /* 计时 */
    _zombiesAppearControl->setTimeAdd();
}

void GSControlLayer::createZombies() {
    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);
    /* 刷新僵尸 */
    if (_zombiesAppearControl->getLastFrequencyZombiesWasDeath()) {
        _zombiesAppearControl->setLastFrequencyZombiesWasDeath(false);
        _zombiesAppearControl->setTimeClear(); /* 距离上一波刷新时间清零 */
        if (_zombiesAppearControl->getZombiesAppearFrequency() < levelData->zombiesFrequency) {
            unsigned int zombiesNumbers =
                _zombiesAppearControl->getZombiesNumbersForAppearFrequency(
                    _zombiesAppearControl->getZombiesAppearFrequency());
            for (unsigned int i = 0; i < zombiesNumbers; ++i) {
                animationLayerInformation->createZombies();
            }
            /* 进攻波数自增一 */
            _zombiesAppearControl->setZombiesAppearFrequency();

            /* 进度条更新 */
            informationLayerInformation->updateProgressBar(
                _zombiesAppearControl->getZombiesAppearFrequency());
        }
    }
    informationLayerInformation->updateProgressBarHead();

    /* 控制僵尸的刷新 */
    if (controlRefurbishZombies()) {
        _zombiesAppearControl->setLastFrequencyZombiesWasDeath(true);
        _zombiesAppearControl->setIsBegin(false);
    }
}

bool GSControlLayer::controlRefurbishZombies() {
    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);
    if ((Zombies::getZombiesNumbers() <= 4 && _zombiesAppearControl->getZombiesAppearFrequency() >
                                                  3) /* 如果活着的僵尸数小于规定，刷新下一波 */

        || (Zombies::getZombiesNumbers() <= 0 && /* 如果没有存活僵尸则立即刷新僵尸 */
            _zombiesAppearControl->getZombiesAppearFrequency() > 1)

        || (_zombiesAppearControl->getTime() >= levelData->firstFrequencyTime &&
            _zombiesAppearControl->getZombiesAppearFrequency() == 0) /* 第一波刷新控制 */

        || (_zombiesAppearControl->getTime() >= 32 + rand() % 10 &&
            (_zombiesAppearControl->getZombiesAppearFrequency() == 1 ||
             _zombiesAppearControl->getZombiesAppearFrequency() == 2)) /* 第二三波刷新控制 */

        || (_zombiesAppearControl->getTime() >= 45 &&
            _zombiesAppearControl->getZombiesAppearFrequency() > 2) /* 如果大于45秒刷新下一波 */
    ) {
        return true;
    }
    return false;
}

void GSControlLayer::controlRefurbishMusicAndText() {
    /* 控制大波僵尸来袭的文字与音乐 */
    LevelData* levelData = _levelDataHandler->readLevelData(_levelDataHandler->getLevelNumber());
    if (_zombiesAppearControl->getTime() >= levelData->firstFrequencyTime &&
        _zombiesAppearControl->getZombiesAppearFrequency() == 0) {
        MusicPlayer::playMusic("awooga");
    }

    /* 最后一波僵尸的文字显示与旗子更新 */
    if (_zombiesAppearControl->getZombiesAppearFrequency() == levelData->zombiesFrequency &&
        !_zombiesAppearControl->getIsShowWords()) {
        if (informationLayerInformation->updateProgressBarFlag()) {
            _zombiesAppearControl->setIsShowWords(true);
        }
    }

    /* 前几波文字显示与旗子更新 */
    for (auto data = _munchZombiesFrequency.begin(); data != _munchZombiesFrequency.end();) {
        if (_zombiesAppearControl->getZombiesAppearFrequency() == *data) {
            if (informationLayerInformation->updateProgressBarFlag(-1) &&
                informationLayerInformation->updateProgressBarFlag(*data)) {
                data = _munchZombiesFrequency.erase(data);
            } else {
                ++data;
            }
        } else {
            ++data;
        }
    }
}

void GSControlLayer::updateFlag() {
    for (auto data : _munchZombiesFrequency) {
        if (_zombiesAppearControl->getZombiesAppearFrequency() > data) {
            informationLayerInformation->updateProgressBarFlag(data);
        }
    }
    if (_zombiesAppearControl->getIsShowWords())
        informationLayerInformation->updateProgressBarFinalFlag();
}

bool GSControlLayer::judgeMousePositionIsInMap() {
    return (_plantsPosition.x >= 0 && _plantsPosition.x <= 8 && _plantsPosition.y >= 0 &&
            _plantsPosition.y <= 4) ?
               true :
               false;
}

bool GSControlLayer::judgeMousePositionIsCanPlant() {
    return (_gameMapInformation->plantsMap[static_cast<unsigned int>(_plantsPosition.y)]
                                          [static_cast<unsigned int>(_plantsPosition.x)] ==
            NO_PLANTS) /* 能种植的范围内还没有种植 */
               ?
               true :
               false;
}

bool GSControlLayer::judgeMousePositionHavePlant() {
    return (_gameMapInformation->plantsMap[static_cast<unsigned int>(
                _plantsPosition.y)][static_cast<unsigned int>(_plantsPosition.x)] != NO_PLANTS) ?
               true :
               false;
}

void GSControlLayer::removePreviewPlant() {
    /* 移除预览植物 */
    _plantPreviewImage->removeFromParent();
    _plantCurImage->removeFromParent();
    buttonLayerInformation->mouseSelectImage->isSelectPlants = false;
    CURSOR_VISIBLE(true)
}

void GSControlLayer::removeShovel() {
    buttonLayerInformation->mouseSelectImage->isSelectShovel = false;
    _director->getOpenGLView()->setCursor("resources/images/System/cursor.png",
                                          Point::ANCHOR_TOP_LEFT);
}

void GSControlLayer::recoveryPlantsColor() {
    for (unsigned int i = 0; i < _gameMapInformation->rowNumbers; ++i) {
        for (unsigned int j = 0; j < _gameMapInformation->columnNumbers; ++j) {
            if (_gameMapInformation->plantsMap[i][j] != NO_PLANTS) {
                auto plant = _animationLayer->getChildByTag(SET_TAG(Vec2(j, i)));
                if (plant) {
                    plant->setColor(Color3B::WHITE);
                }
            }
        }
    }
}

void GSControlLayer::judgeLevelIsFinished() {
    /* 关卡结束 */
    LevelData* levelData = _levelDataHandler->readLevelData(_levelDataHandler->getLevelNumber());
    if (ZombiesGroup.size() <= 0 &&
        _zombiesAppearControl->getZombiesAppearFrequency() >= levelData->zombiesFrequency) {
        CURSOR_VISIBLE(true)

        setGameEnd();

        _gameEndShieldLayer->successfullEntry();
        //        auto judgeUserWin = new GSGameResultJudgement();
        //        auto gameType = judgeUserWin->judgeUserIsLose();
        //        if (gameType == GameTypes::None) {
        //            _gameEndShieldLayer->successfullEntry();
        //        } else {
        //            _gameEndShieldLayer->breakThrough(gameType); /* 闯关失败 */
        //        }
        //        delete judgeUserWin;
    }
}

void GSControlLayer::setGameEnd() {
    unschedule("mainUpdate");
    unschedule("zombiesComing");
    SunFlower::stopSun();
    Plants::stopPlantsAllAction();
    animationLayerInformation->stopRandomSun();

    _gameEndShieldLayer = GSGameEndLayer::create();
    _director->getRunningScene()->addChild(_gameEndShieldLayer, 10, "gameEndShieldLayer");
}

void GSControlLayer::mouseMoveControl() {
    /* 如果鼠标选择了植物 */
    if (buttonLayerInformation->mouseSelectImage->isSelectPlants) {
        int posX = static_cast<int>(_plantsPosition.x);
        int posY = static_cast<int>(_plantsPosition.y);
        if (posX >= 0 && posY >= 0 && posX < 9 && posY < 5) {
            if (_gameMapInformation->plantsMap[posY][posX] != NO_PLANTS) {
                _plantPreviewImage->setPosition(Vec2(-1000, -1000));
            } else {
                _plantPreviewImage->setPosition(
                    Vec2(GRASS_POSITION_LEFT + 122 * _plantsPosition.x + 60,
                         110 + 138 * (_plantsPosition.y + 1) - 60));
            }
        } else {
            _plantPreviewImage->setPosition(Vec2(-1000, -1000));
        }
        _plantCurImage->setPosition(_cur + Vec2(0, 30));
    }

    /* 鼠标上有铲子 */
    if (buttonLayerInformation->mouseSelectImage->isSelectShovel) {
        if (!_animationLayer) {
            _animationLayer = _director->getRunningScene()->getChildByName("animationLayer");
        }

        /* 循环把植物恢复到原来的颜色 */
        recoveryPlantsColor();

        if (judgeMousePositionIsInMap() &&
            judgeMousePositionHavePlant()) /* 如果在地图范围内 && 种有植物 */
        {
            auto plant = _animationLayer->getChildByTag(SET_TAG(_plantsPosition));
            if (plant) {
                plant->setColor(Color3B(100, 100, 100));
            }
        }
    }
}

void GSControlLayer::mouseDownControl(EventMouse* eventmouse) {
    if (eventmouse->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) /* 如果是右键按下 */
    {
        if (buttonLayerInformation->mouseSelectImage->isSelectPlants) /* 鼠标上有植物 */
        {
            MusicPlayer::playMusic("tap2");
            buttonLayerInformation
                ->plantsCards[static_cast<unsigned int>(
                    buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                .progressTimer->setPercentage(0);
            buttonLayerInformation
                ->plantsCards[static_cast<unsigned int>(
                    buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                .plantsCards->setColor(Color3B::WHITE);

            /* 加上所需的阳光数并更新 */
            auto& userWorldData = _runtime->userData->getUserWorldData();
            userWorldData.sunNumbers =
                userWorldData.sunNumbers +
                buttonLayerInformation->plantsInformation
                    ->PlantsNeedSunNumbers[static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId)];
            informationLayerInformation->updateSunNumbers();

            removePreviewPlant();
        }

        if (buttonLayerInformation->mouseSelectImage->isSelectShovel) /* 鼠标上有铲子 */
        {
            removeShovel();
            recoveryPlantsColor();
        }
    }

    if (eventmouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) /* 如果是左键按下 */
    {
        if (buttonLayerInformation->mouseSelectImage->isSelectPlants) {
            if (judgeMousePositionIsInMap() &&
                judgeMousePositionIsCanPlant()) /* 如果在地图范围内 && 可以种植植物 */
            {
                /* 种植植物 */
                animationLayerInformation->plantPlants();

                /* 地图记录种植的植物 */
                _gameMapInformation->plantsMap[static_cast<unsigned int>(_plantsPosition.y)]
                                              [static_cast<unsigned int>(_plantsPosition.x)] =
                    static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId);

                /* 设置倒计时并且按钮不可用 */
                unsigned int plantsTag = static_cast<unsigned int>(
                    buttonLayerInformation->mouseSelectImage->selectPlantsId);
                buttonLayerInformation
                    ->plantsCards[static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                    .timeBarIsFinished = false;
                buttonLayerInformation
                    ->plantsCards[static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                    .plantsCards->setEnabled(false);
                buttonLayerInformation
                    ->plantsCards[static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                    .plantsCards->setColor(Color3B::GRAY);
                buttonLayerInformation
                    ->plantsCards[static_cast<unsigned int>(
                        buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                    .progressTimer->runAction(Sequence::create(
                        ProgressFromTo::create(
                            buttonLayerInformation->plantsInformation
                                ->PlantsCoolTime[static_cast<unsigned int>(
                                    buttonLayerInformation->mouseSelectImage->selectPlantsId)],
                            100, 0),
                        CallFunc::create([=]() {
                            buttonLayerInformation->plantsCards[plantsTag].timeBarIsFinished = true;
                        }),
                        nullptr));
                removePreviewPlant();
            } else {
                if (_cur.x > CARD_BAR_RIGHT) {
                    MusicPlayer::playMusic("buzzer");
                    /* 卡牌颜色恢复 */
                    buttonLayerInformation
                        ->plantsCards[static_cast<unsigned int>(
                            buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                        .progressTimer->setPercentage(0);
                    buttonLayerInformation
                        ->plantsCards[static_cast<unsigned int>(
                            buttonLayerInformation->mouseSelectImage->selectPlantsId)]
                        .plantsCards->setColor(Color3B::WHITE);

                    /* 提示信息 */
                    informationLayerInformation->createPromptText();

                    removePreviewPlant();

                    /* 加上所需的阳光数并更新 */
                    auto& userWorldData = _runtime->userData->getUserWorldData();
                    userWorldData.sunNumbers =
                        userWorldData.sunNumbers +
                        buttonLayerInformation->plantsInformation
                            ->PlantsNeedSunNumbers[static_cast<unsigned int>(
                                buttonLayerInformation->mouseSelectImage->selectPlantsId)];
                    informationLayerInformation->updateSunNumbers();
                }
            }
        }
        if (buttonLayerInformation->mouseSelectImage->isSelectShovel) /* 鼠标上有铲子 */
        {
            MusicPlayer::playMusic("plant2");
            if (judgeMousePositionIsInMap() &&
                judgeMousePositionHavePlant()) /* 如果在地图范围内 && 种有植物 */
            {
                animationLayerInformation->deletePlants(); /* 铲除植物 */
            }
            removeShovel();
            recoveryPlantsColor();
        }
    }
}
