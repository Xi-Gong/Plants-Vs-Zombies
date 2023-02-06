/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "SPSSpriteLayer.h"

#include "Based/MusicPlayer.h"

SPSSpriteLayer::SPSSpriteLayer() :
    _seedChooser(nullptr), _plantCardScrollView(ScrollView::create()),
    _plantCardTextScrollView(ScrollView::create()), _runtime(Runtime::getInstance()),
    _plantCardScrollViewPercent(0), _selectFinished(false),
    _plantsNumber(3), _isPlantIsCanSelect{true, true, true} {}

bool SPSSpriteLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    createSelectPlantsDialog();

    return true;
}

Text* SPSSpriteLayer::showPlantsInformation(Button* button, const unsigned int id) const {
    const string PlantsImageName[][5] = {{{"SunFlower_2"}, {"50"}, {"PlantsIcon4"}},
                                         {{"PeaShooter"}, {"100"}, {"PlantsIcon5"}},
                                         {{"Wallnut_body"}, {"50"}, {"PlantsIcon6"}}};
    Color3B color[] = {
        Color3B::YELLOW,
        Color3B::GREEN,
        Color3B(140, 80, 10),
    };

    /* 图片 */
    createPlantsImage(button, PlantsImageName[id][0]);

    auto PlantsLevelIamge = Sprite::createWithSpriteFrameName("PlantsLevel_Copper.png");
    PlantsLevelIamge->setPosition(Vec2(155, 74));
    PlantsLevelIamge->setScale(0.65f);
    button->addChild(PlantsLevelIamge);

    auto Background = Sprite::createWithSpriteFrameName("PlantsIconBackground.png");
    Background->setOpacity(0);
    button->addChild(Background);

    auto PlantsIconBackground = Sprite::createWithSpriteFrameName("PlantsIconBackground.png");
    PlantsIconBackground->setPosition(Vec2(93, 150));
    PlantsIconBackground->setScale(0.28f);
    PlantsIconBackground->setColor(color[id]);
    Background->addChild(PlantsIconBackground);

    auto PlantsIcon = Sprite::createWithSpriteFrameName(PlantsImageName[id][2] + ".png");
    PlantsIcon->setPosition(Vec2(73, 75));
    PlantsIcon->setScale(1.2f);
    PlantsIconBackground->addChild(PlantsIcon);

    /* 文本 */
    auto PlantsNeedSuns = ui::Text::create();
    PlantsNeedSuns->setFontName(GAME_FONT_NAME_2);
    PlantsNeedSuns->setColor(Color3B::BLACK);
    PlantsNeedSuns->setAnchorPoint(Vec2(1, 0.5f));
    PlantsNeedSuns->setPosition(Vec2(175, 20));
    PlantsNeedSuns->setFontSize(30);
    PlantsNeedSuns->setString(PlantsImageName[id][1]);
    button->addChild(PlantsNeedSuns);

    auto PlantsLevelText = ui::Text::create();
    PlantsLevelText->setFontName(GAME_FONT_NAME_1);
    PlantsLevelText->setColor(Color3B::BLACK);
    PlantsLevelText->setAnchorPoint(Vec2(1, 0.5f));
    PlantsLevelText->setPosition(Vec2(177, 77));
    PlantsLevelText->setFontSize(20);
    PlantsLevelText->setString("LVL1");
    button->addChild(PlantsLevelText);

    return PlantsNeedSuns;
}

void SPSSpriteLayer::createSelectPlantsDialog() {
    MusicPlayer::playMusic("swing");

    alreadySelectPlantsDialog();
    alreadyHavePlantsDialog();
    createScrollview();
    createPlantsCards();
    showRandPlantsInformation();
    createMouseListener();
}

void SPSSpriteLayer::alreadySelectPlantsDialog() {
    auto seedBank = Scale9Sprite::createWithSpriteFrameName("SeedBank.png");
    seedBank->setPosition(Vec2(-200, 1080));
    seedBank->setAnchorPoint(Vec2(0, 1));
    // SeedBank->setCapInsets(Rect(0, 6, 87, 373));
    seedBank->setContentSize(Size(210, 967));
    seedBank->runAction(MoveTo::create(0.2f, Vec2(0, 1080)));
    this->addChild(seedBank);

    for (unsigned int i = 0; i < 9; ++i) {
        auto Seed = Sprite::createWithSpriteFrameName("SeedPacketSilhouette.png");
        Seed->setContentSize(Size(180, 100));
        Seed->setPosition(Vec2(105, 897 - 103 * i));
        seedBank->addChild(Seed);
    }
}

void SPSSpriteLayer::alreadyHavePlantsDialog() {
    _seedChooser = Sprite::createWithSpriteFrameName("SeedChooser_Background.png");
    _seedChooser->setPosition(Vec2(595, -600));
    _seedChooser->setContentSize(Size(780, 1080));
    _seedChooser->setName("_seedChooer");
    _seedChooser->runAction(Sequence::create(MoveTo::create(0.2f, Vec2(595, 540)),
                                             CallFunc::create([&]() { createBeginButton(); }),
                                             nullptr));
    this->addChild(_seedChooser);

    auto SelectBackground = Sprite::createWithSpriteFrameName("SelectBackground.png");
    SelectBackground->setPosition(Vec2(190, 730));
    SelectBackground->setScaleY(0.96f);
    SelectBackground->setScaleX(1.14f);
    SelectBackground->setColor(Color3B(0, 255, 255));
    _seedChooser->addChild(SelectBackground);
    SelectBackground->runAction(RepeatForever::create(
        Sequence::create(FadeTo::create(0.2f, 150), FadeTo::create(0.2f, 50), nullptr)));

    auto State = SkeletonAnimation::createWithData(
        _runtime->gameData->getAnimationData().find("Stage")->second);
    State->setPosition(Vec2(195, 720));
    State->setScale(3.5f);
    State->setAnimation(0, "Rotate", true);
    _seedChooser->addChild(State);

    auto SeedChooserText =
        ui::Text::create(_runtime->gameData->getGameText().find("请选择你出战的植物！")->second,
                         GAME_FONT_NAME_1, 50);
    SeedChooserText->setColor(Color3B::YELLOW);
    SeedChooserText->setPosition(Vec2(400, 1000));
    _seedChooser->addChild(SeedChooserText);
}

void SPSSpriteLayer::createScrollview() {
    /* 植物卡牌滑动视图 */
    _plantCardScrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _plantCardScrollView->setContentSize(Size(800.0f, 420));
    _plantCardScrollView->setPosition(Vec2(0, 120));
    _plantCardScrollView->setInnerContainerSize(Size(800, 400));
    //_plantCardScrollView->setBounceEnabled(true);
    _plantCardScrollView->setScrollBarPositionFromCorner(Vec2(40, 0));
    _plantCardScrollView->setScrollBarWidth(7);
    _plantCardScrollView->setScrollBarAutoHideTime(2.0f);
    _plantCardScrollView->setScrollBarColor(Color3B::WHITE);
    // this->schedule(schedule_selector(SPSSpriteLayer::scrollViewUpdate), 0.1f);
    _seedChooser->addChild(_plantCardScrollView);

    /* 植物卡牌介绍滑动视图 */
    _plantCardTextScrollView = ui::ScrollView::create();
    _plantCardTextScrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _plantCardTextScrollView->setContentSize(Size(400.0f, 360.0f));
    _plantCardTextScrollView->setPosition(Vec2(360, 580));
    _plantCardTextScrollView->setBounceEnabled(true);
    _plantCardTextScrollView->setScrollBarPositionFromCorner(Vec2(10, 0));
    _plantCardTextScrollView->setScrollBarAutoHideTime(2.0f);
    _plantCardTextScrollView->setScrollBarWidth(7);
    _plantCardTextScrollView->setScrollBarColor(Color3B::WHITE);
    _seedChooser->addChild(_plantCardTextScrollView);
}

void SPSSpriteLayer::scrollViewUpdate(float Time) {
    _plantCardScrollViewPercent = (_plantCardScrollView->getScrolledPercentVertical()) * 25;
}

void SPSSpriteLayer::createMouseListener() {
    /* 鼠标滑动监听 */
    auto mouse = EventListenerMouse::create();
    mouse->onMouseScroll = [&](Event* event) {
        auto e = (EventMouse*)event;
        auto cur = e->getLocationInView();
        auto a = e->getScrollY();
        cur.x -= 200;

        if (_plantCardScrollView->getBoundingBox().containsPoint(cur)) {
            if (_plantCardRollingDistance + a >= 0 && _plantCardRollingDistance + a <= 50) {
                _plantCardRollingDistance += a;
            }
            if (_plantCardRollingDistance < 0)
                _plantCardRollingDistance = 0;
            if (_plantCardRollingDistance > 50)
                _plantCardRollingDistance = 50;
            _plantCardScrollView->jumpToPercentVertical(_plantCardRollingDistance * 2);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse,
                                                                                          this);
}

void SPSSpriteLayer::createPlantsCards() {
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            if (4 * i + j < _plantsNumber) {
                createButtons(Vec2(110 + 185 * j, 490 - 105 * i), 4 * i + j);
            }
        }
    }
}

void SPSSpriteLayer::showRandPlantsInformation() {
    preloadText();

    /* 开始进入创建随机动画 */
    srand(time(nullptr));
    createAnimationAndText(rand() % 3);
}

Button* SPSSpriteLayer::createButtons(const Vec2& vec2, const unsigned int& id) {
    auto button = Button::create("SeedPacket_Larger.png", "", "", TextureResType::PLIST);
    button->setPosition(
        Vec2(vec2.x, _plantCardScrollView->getInnerContainerSize().height + vec2.y - 540));
    button->setTitleColor(Color3B::RED);
    button->setTitleFontSize(25);
    button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: {
                MusicPlayer::playMusic("tap");
                break;
            }

            case ui::Widget::TouchEventType::ENDED: {
                if (_isPlantIsCanSelect[id]) {
                    // change 3 to 1 in order to start the game
                    if (seedBankButton.size() > 1) /* 583 */
                    {
                        ((Button*)_seedChooser->getChildByName("Begin"))->setEnabled(true);
                        ((Button*)_seedChooser->getChildByName("Begin"))
                            ->setTitleColor(Color3B::YELLOW);
                    }
                    if (seedBankButton.size() < 9) {
                        button->setEnabled(false);
                        button->setColor(Color3B(70, 70, 70));
                        button->setCascadeColorEnabled(true); /* 设置父节点影响子节点 */

                        createMoveButton(button, vec2, id);
                    }
                }

                createAnimationAndText(id);  // 创建植物动画

                break;
            }

            default: break;
        }
    });
    _plantCardScrollView->addChild(button);

    controlPlantCanSelect(button, id); /* 控制植物是否可以选择 */

    showPlantsInformation(button, id); /* 显示植物信息 */

    if (!_isPlantIsCanSelect[id]) {
        createProhibit(button);
    }

    return button;
}

void SPSSpriteLayer::preloadText() {
    for (unsigned int i = 0; i < 4; i++) {
        _animationText[i] = Text::create("", GAME_FONT_NAME_1, 30);
        _animationText[i]->setName("AnimationText");
        _animationText[i]->enableOutline(Color4B(0, 255, 255, 255));
        _animationText[i]->enableShadow(Color4B::GRAY, Size(4, -4), 1);

        if (i == 0) {
            _seedChooser->addChild(_animationText[i]);
        } else {
            _plantCardTextScrollView->addChild(_animationText[i]);
        }
    }
}

void SPSSpriteLayer::createPlantsImage(Button* button, const std::string& resource,
                                       const float& scale) const {
    auto image = Sprite::createWithSpriteFrameName(resource + ".png");
    image->setScale(scale);
    image->setPosition(Vec2(55, 50));
    button->addChild(image);
}

void SPSSpriteLayer::createMoveButton(Button* button, const Vec2& vec2, const unsigned int& id) {
    /* 创建移动卡牌 */
    auto MoveCard = ui::Button::create("SeedPacket_Larger.png", "", "", TextureResType::PLIST);
    MoveCard->setPosition(Vec2(vec2.x + 212, vec2.y + _plantCardScrollViewPercent));
    MoveCard->setTitleColor(Color3B::RED);
    MoveCard->setTitleFontSize(25);
    MoveCard->setTag(id);
    MoveCard->runAction(MoveTo::create(0.2f, Vec2(105, 1008 - 103 * seedBankButton.size())));
    this->addChild(MoveCard);

    showPlantsInformation(MoveCard, id);  // 显示信息

    /* 存储到卡牌栏中 */
    UserSelectCard seed_bank_button;
    seed_bank_button.cardButton = MoveCard;
    seed_bank_button.cardTag = id;
    seedBankButton.push_back(seed_bank_button);

    float PlantCardScrollViewPercentLast = _plantCardScrollViewPercent;
    MoveCard->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: {
                MusicPlayer::playMusic("tap2");
                break;
            }

            case ui::Widget::TouchEventType::ENDED: {
                createAnimationAndText(id);  // 创建植物动画
                sortPlantsCard(id);          // 对植物卡牌重新排序
                _plantCardScrollView->scrollToPercentVertical(
                    PlantCardScrollViewPercentLast / 25.0f, 0.5f, true);  // 滚动到初始位置
                _plantCardRollingDistance = PlantCardScrollViewPercentLast / 25.0f;
                MoveCard->runAction(Sequence::create(
                    MoveTo::create(0.2f,
                                   Vec2(vec2.x + 212, vec2.y + PlantCardScrollViewPercentLast)),
                    CallFuncN::create(
                        CC_CALLBACK_1(SPSSpriteLayer::removePlantsCardCallBack, this, id, button)),
                    nullptr));  // 植物卡牌取消选择
                break;
            }

            default: break;
        }
    });
}

void SPSSpriteLayer::createAnimationAndText(const unsigned int& id) {
    _seedChooser->removeChildByName("PlantsAnimation");
    for (unsigned int i = 0; i < _plantsNumber; i++)
        _animationText[i]->setString("");

    auto gameText = _runtime->gameData->getGameText();
    switch (id) {
        case 0:
            _plantCardTextScrollView->setInnerContainerSize(Size(400, 460));
            this->createPlantsAnimation("SunFlower_2", "SunFlower_Normal", "SunFlower_Normal",
                                        Vec2(200, 610), 1.5f);
            this->createPlantsText(0, gameText.find("SUNFLOWER_1")->second, Vec2(190, 910), 50);
            this->createPlantsText(1, gameText.find("SUNFLOWER_2")->second, Vec2(360, 1000), 30,
                                   Color3B::YELLOW, false);
            this->createPlantsText(2, gameText.find("SUNFLOWER_3")->second, Vec2(440, 1000), 30,
                                   Color3B::RED, false);
            this->createPlantsText(3, gameText.find("SUNFLOWER_4")->second, Vec2(360, 830), 30,
                                   Color3B::YELLOW, false);
            break;
        case 1:
            _plantCardTextScrollView->setInnerContainerSize(Size(400, 640));
            this->createPlantsAnimation("PeaShooter", "PeaShooter_Normal", "", Vec2(200, 610),
                                        1.8f);
            this->createPlantsText(0, gameText.find("PEASHOOTER_1")->second, Vec2(190, 910), 50);
            this->createPlantsText(2, gameText.find("PEASHOOTER_2")->second, Vec2(360, 1000), 30,
                                   Color3B::YELLOW, false);
            this->createPlantsText(3, gameText.find("PEASHOOTER_3")->second, Vec2(440, 1000), 30,
                                   Color3B::RED, false);
            this->createPlantsText(1, gameText.find("PEASHOOTER_4")->second, Vec2(360, 830), 30,
                                   Color3B::YELLOW, false);

            break;
        case 2:
            _plantCardTextScrollView->setInnerContainerSize(Size(400, 490));
            this->createPlantsAnimation("WallNut", "WallNut_Nornal", "WallNut_Normal",
                                        Vec2(200, 610), 1.5f);
            this->createPlantsText(0, gameText.find("WALLNUT_1")->second, Vec2(190, 910), 50);
            this->createPlantsText(2, gameText.find("WALLNUT_2")->second, Vec2(360, 1000), 30,
                                   Color3B::YELLOW, false);
            this->createPlantsText(3, gameText.find("WALLNUT_3")->second, Vec2(440, 1000), 30,
                                   Color3B::RED, false);
            this->createPlantsText(1, gameText.find("WALLNUT_4")->second, Vec2(360, 870), 30,
                                   Color3B::YELLOW, false);
            break;
        default: break;
    }
    _seedChooser->addChild(_plantsAnimation);
}

void SPSSpriteLayer::createPlantsAnimation(const std::string& filepath,
                                           const std::string& AnimationName,
                                           const std::string& skin, const Vec2& vec2,
                                           const float& scale) {
    auto animationData = _runtime->gameData->getAnimationData();
    /* 创建动画 */
    auto iter = animationData.find(filepath);
    if (iter != animationData.end()) /* 如果可以找到 */
    {
        _plantsAnimation = SkeletonAnimation::createWithData(iter->second);
        _plantsAnimation->setPosition(vec2);
        _plantsAnimation->setScale(scale);
        _plantsAnimation->setSkin(skin);
        _plantsAnimation->setAnimation(0, AnimationName, true);
        _plantsAnimation->setName("PlantsAnimation");
    }
}

void SPSSpriteLayer::createPlantsText(const unsigned int& ID, const std::string& name,
                                      const Vec2& vec2, const float& fontsize, Color3B color,
                                      bool AnchorPoint) {
    _animationText[ID]->setString(name);
    _animationText[ID]->setFontSize(fontsize);
    ;
    _animationText[ID]->setColor(color);
    _plantCardTextScrollView->scrollToTop(0.1f, true);
    AnchorPoint ? _animationText[ID]->setAnchorPoint(Vec2(0.5f, 0.5f)) :
                  _animationText[ID]->setAnchorPoint(Vec2(0, 1));
    switch (ID) {
        case 0: _animationText[ID]->setPosition(vec2); break;
        default:
            _animationText[ID]->setPosition(
                Vec2(vec2.x - _plantCardTextScrollView->getInnerContainerSize().width + 40,
                     vec2.y + _plantCardTextScrollView->getInnerContainerSize().height - 1000));
            break;
    }
}

void SPSSpriteLayer::sortPlantsCard(const unsigned int& id) {
    /* 删除取消选择的卡牌 */
    for (auto card = seedBankButton.begin(); card != seedBankButton.end();) {
        if (card->cardTag == id) {
            card = seedBankButton.erase(card);
        } else {
            ++card;
        }
    }

    /* 为植物卡牌重新设置位置 */
    int i = -1;
    for (auto& card : seedBankButton) {
        card.cardButton->runAction(MoveTo::create(0.2f, Vec2(105, 1008 - 103 * ++i)));
    }

    // change 4 to 1
    if (seedBankButton.size() <= 1) {
        ((Button*)_seedChooser->getChildByName("Begin"))->setEnabled(false);
        ((Button*)_seedChooser->getChildByName("Begin"))->setTitleColor(Color3B::WHITE);
    }
}

void SPSSpriteLayer::removePlantsCardCallBack(Node* node, const unsigned int& id, Button* button) {
    /* 删除移动卡牌精灵 */
    this->removeChildByTag(id);

    /* 设置卡牌精灵可以再次选择 */
    button->setEnabled(true);
    button->setColor(Color3B::WHITE);
}

void SPSSpriteLayer::createBeginButton() {
    auto button = Button::create("SeedChooser_Button_Disabled.png", "SeedChooser_Button.png", "",
                                 TextureResType::PLIST);
    button->setTitleText(_runtime->gameData->getGameText().find("开始战斗吧！")->second);
    button->setTitleColor(Color3B::WHITE);
    button->setTitleFontName(GAME_FONT_NAME_1);
    button->setTitleFontSize(20);
    button->setPosition(Vec2(390, 70));
    button->setScale(2.0f);
    button->setEnabled(false);
    button->setName("Begin");
    button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: {
                MusicPlayer::playMusic("tap");
                break;
            }

            case ui::Widget::TouchEventType::ENDED: {
                MusicPlayer::playMusic("swing");
                /* 设置按钮不可用 */
                for (auto& card : seedBankButton) {
                    card.cardButton->setEnabled(false);
                    card.cardButton->setColor(Color3B::GRAY);
                    card.cardButton->setCascadeColorEnabled(true);
                }
                // change 4 to 1
                if (seedBankButton.size() > 1) {
                    _seedChooser->runAction(
                        Sequence::create(MoveTo::create(0.35f, Vec2(605, -600)),
                                         CallFuncN::create(CC_CALLBACK_1(
                                             SPSSpriteLayer::selectPlantsCallBack, this)),
                                         nullptr));
                }
                break;
            }

            default: break;
        }
    });
    _seedChooser->addChild(button);
}

void SPSSpriteLayer::controlPlantCanSelect(Button* button, const unsigned int id) {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    auto coinNumbers = userWorldData.coinNumbers;
    auto killZombiesNumbers = userWorldData.killZombiesNumbers;

    // 解锁所有植物
    Vec2 vec[4] = {{1000, 500}, {2000, 1000}, {5000, 5000}, {10000, 10000}};

    if (id >= 9) {
        if (coinNumbers < vec[id - 9].x || killZombiesNumbers < vec[id - 9].y) {
            button->setColor(Color3B(70, 70, 70));
            button->setCascadeColorEnabled(true); /* 设置父节点影响子节点 */
            _isPlantIsCanSelect[id] = false;
        }
    }
}

void SPSSpriteLayer::createProhibit(Button* button) {
    auto prohibit = Sprite::createWithSpriteFrameName("Prohibit.png");
    prohibit->setPosition(Vec2(160, 20));
    prohibit->setScale(0.5f);
    button->addChild(prohibit);
}
