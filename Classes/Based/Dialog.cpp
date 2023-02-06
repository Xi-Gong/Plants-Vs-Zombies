/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "Dialog.h"

Dialog::Dialog() :
    _runtime(Runtime::getInstance()), _shieldListener(nullptr), _mouseListener(nullptr),
    _phasePosition(Vec2::ZERO) {}

EventListenerTouchOneByOne* Dialog::createTouchListener(Sprite* sprite) {
    static Vec2 phasePosition = Vec2(Vec2::ZERO);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&, sprite](Touch* t, Event* e) {
        if (sprite->getBoundingBox().containsPoint(t->getLocation())) {
            phasePosition = t->getLocation() - sprite->getPosition();
            return true;
        } else
            return false;
    };
    listener->onTouchMoved = [=](Touch* t, Event* e) {
        sprite->setPosition(t->getLocation() - phasePosition);
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                                          sprite);

    return listener;
}

void Dialog::setMouseListener(EventListenerMouse* listener) { _mouseListener = listener; }

Label* Dialog::label(const std::string& name, const float& fontsize, const Vec2& vec2,
                     const float& space, const Color3B& color, const float& scale) {
    auto label = Label::createWithTTF(name, GAME_FONT_NAME_1, fontsize);
    label->setScaleX(scale);
    label->setColor(color);

    // set column spacing
    label->setAdditionalKerning(space);

    label->enableShadow(Color4B(100, 20, 100, 255));
    label->setPosition(vec2);
    return label;
}

void Dialog::createLabel(Sprite* sprite, MenuItemImage* MenuItem, const std::string& name,
                         Vec2& vec2, float& fontsize, const float& space, const Color3B& color) {
    auto label = Label::createWithTTF(name, GAME_FONT_NAME_1, fontsize);
    label->setPosition(vec2);
    label->setColor(color);
    label->enableShadow(Color4B(100, 25, 100, 255));

    // set column spacing
    label->setAdditionalKerning(space);

    MenuItem->addChild(label);

    auto Buttons = Menu::create(MenuItem, NULL);
    Buttons->setPosition(Vec2(0, 0));
    sprite->addChild(Buttons);
}

void Dialog::createShieldLayer(Node* node) {
    // set shieldLayer
    _shieldListener = EventListenerTouchOneByOne::create();
    _shieldListener->onTouchBegan = [](Touch* touch, Event* event) -> bool { return true; };
    _shieldListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_shieldListener, node);
}

void Dialog::setMouseListenerEnable(bool isEnable) { _mouseListener->setEnabled(isEnable); }
