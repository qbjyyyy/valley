#pragma once

#ifndef __CHARACTER_WITH_TOOLS_H__
#define __CHARACTER_WITH_TOOLS_H__
#include "cocos2d.h"

USING_NS_CC;

extern std::map<Vec2, bool> cropPositions;  // 用于记录每个位置是否已经有作物
#define gridWidth  150.0f  // 网格宽度
#define gridHeight  120.0f // 网格高度

class CharacterWithTools : public Sprite {
public:
    // 人物精灵
    static CharacterWithTools* create(const std::string& filename);
    

    CharacterWithTools();
    ~CharacterWithTools();

    // 初始化函数
    virtual bool init(const std::string& filename);

    void move();

    void update(float delta) override;

    bool checkCrop(Vec2 position);

    void plantcrop(Vec2 position);
private:
    //人物移动
    Vec2 velocity;
    Animation* walkLeftAnimation; // 向左走路动画
    Animation* walkRightAnimation; // 向右走路动画
    Animation* walkUpAnimation; // 向上走路动画
    Animation* walkDownAnimation; // 向下走路动画
    Animate* walkLeftAnimate; // 向左走路动画动作
    Animate* walkRightAnimate; // 向右走路动画动作
    Animate* walkUpAnimate; // 向上走路动画动作
    Animate* walkDownAnimate; // 向下走路动画动作

    // 按键事件处理
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void usetools(const std::string& filename);

    

};


#endif // __CHARACTER_WITH_TOOLS_H__