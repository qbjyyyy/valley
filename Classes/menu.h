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
   
    // ��ť����ص�����
    void onLeftButtonClicked(Ref* sender);
    void onRightButtonClicked(Ref* sender);

    // ��ɫ������ť�Ļص�
    void onCreateCharacter(Ref* sender);



    CREATE_FUNC(menu);
private:
    RadioButtonGroup* radioButtonGroup;
    RadioButtonGroup* radioButtongenderGroup;
    int selectedMapIndex = -1; // ��ʼ��Ϊ��Чֵ
    int selectedGenderIndex = -1; // ��ʼ��Ϊ��Чֵ
    bool _isLayerVisible;
    ImageView* _backImage;
    Label* music1=nullptr;
    Label* music2 = nullptr;
    Button* bottom=nullptr;
    Slider* part;

    MenuItemImage* leftButton;    // ��ఴť
    MenuItemImage* rightButton;   // �Ҳఴť


   

};
#endif // !_HELLOWORLD_SCENE_H_