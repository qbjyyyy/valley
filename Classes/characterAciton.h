#pragma once

#ifndef __CHARACTER_WITH_TOOLS_H__
#define __CHARACTER_WITH_TOOLS_H__
#include "cocos2d.h"

USING_NS_CC;

extern std::map<Vec2, bool> cropPositions;  // ���ڼ�¼ÿ��λ���Ƿ��Ѿ�������
#define gridWidth  150.0f  // ������
#define gridHeight  120.0f // ����߶�

class CharacterWithTools : public Sprite {
public:
    // ���ﾫ��
    static CharacterWithTools* create(const std::string& filename);
    

    CharacterWithTools();
    ~CharacterWithTools();

    // ��ʼ������
    virtual bool init(const std::string& filename);

    void move();

    void update(float delta) override;

    bool checkCrop(Vec2 position);

    void plantcrop(Vec2 position);
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