#ifndef _MENU_H_
#define _MENU_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "valleybegin.h"
#include "CCTextFieldTTF.h"
#include "outside.h"

using namespace cocos2d;
using namespace ui;

class menu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createmenuScene();
    void textFieldEvent(Ref* sender, TextField::EventType type);
    virtual bool init();
    //void onMapRadioButtonSelected(Ref* sender, RadioButton* radioButton);
    void onMapRadioButtonSelected(RadioButton* radioButton, int index);
    void onGenderRadioButtonSelected(Ref* sender,RadioButton* radioButton);
    void onButtonPressed(Ref* pSender, Widget::TouchEventType type);
    void onSliderValueChanged(Ref* sender, Slider::EventType type);
   
    // 按钮点击回调函数
    void onLeftButtonClicked(Ref* sender);
    void onRightButtonClicked(Ref* sender);

    // 角色创建按钮的回调
    void onCreateCharacter(Ref* sender);



    CREATE_FUNC(menu);
private:
    RadioButtonGroup* radioButtonGroup;
    RadioButtonGroup* radioButtongenderGroup;
    int selectedMapIndex = -1; // 初始化为无效值
    int selectedGenderIndex = -1; // 初始化为无效值
    bool _isLayerVisible;
    ImageView* _backImage;
    Label* music1=nullptr;
    Label* music2 = nullptr;
    Button* bottom=nullptr;
    Slider* part;

    MenuItemImage* leftButton;    // 左侧按钮
    MenuItemImage* rightButton;   // 右侧按钮


   

};
#endif // !_HELLOWORLD_SCENE_H_