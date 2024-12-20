#pragma once

#ifndef __CHARACTER_WITH_TOOLS_H__
#define __CHARACTER_WITH_TOOLS_H__
#include "cocos2d.h"

USING_NS_CC;


class CharacterWithTools : public Sprite {
public:
    // ���ﾫ��
    static CharacterWithTools* create(const std::string& filename);
    

    CharacterWithTools();
    ~CharacterWithTools();

    // ��ʼ������
    virtual bool init(const std::string& filename);

    void move(const Vec2& direction);

    void update(float delta) override;
private:
    //�����ƶ�
    Vec2 velocity;
    Animation* walkLeftAnimation; // ������·����
    Animation* walkRightAnimation; // ������·����
    Animation* walkUpAnimation; // ������·����
    Animation* walkDownAnimation; // ������·����
    Animate* walkLeftAnimate; // ������·��������
    Animate* walkRightAnimate; // ������·��������
    Animate* walkUpAnimate; // ������·��������
    Animate* walkDownAnimate; // ������·��������

    // �����¼�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void usetools(const std::string& filename);
};


#endif // __CHARACTER_WITH_TOOLS_H__