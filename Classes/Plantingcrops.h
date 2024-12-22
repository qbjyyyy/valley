#ifndef __CROP_H__
#define __CROP_H__

#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"
#include "characterAciton.h"


USING_NS_CC;

enum class State {
    seed,
    growing,
    matured,
    harvested,
    dead
};
class Crop :public Sprite {
protected:
    State state;
    double pregrowthTime;
    double growthTime;
    double matureTime;
    bool watered;
    // �����¼�����
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
public:
    virtual bool init(const std::string& filename);
    static Crop* create(const std::string& filename);
    Crop();
    ~Crop();
    void update(float delta);

    // ��ȡ�����״̬
    State getState() const;

    // �ջ�����
    void harvest();
};

#endif // __CROP_H__