#include "valleybegin.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"
#include "CCTextFieldTTF.h"
#include "GameTimeSystem.h"


using namespace cocos2d;
using namespace ui;

USING_NS_CC;

Scene* menu::createmenuScene()
{
    auto scene = Scene::create();
    auto layer = menu::create();
    scene->addChild(layer);
    return scene;
}



bool menu::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //���ÿ�ʼ����
    auto spriteback = Sprite::create("picture/menu.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(0, 0));
    this->addChild(spriteback);
    
   
    
    //�����������
    std::string labelText1 = "Your name :";
    int fontSize = 40;
    TextHAlignment hAlignment = TextHAlignment::CENTER;
    TextVAlignment vAlignment = TextVAlignment::CENTER;
    Vec2 labelPosition = Vec2(1050, 900);
    std::string fontName = "fonts/Marker Felt.ttf";
    auto label1 = Label::createWithTTF(labelText1, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label1->setPosition(labelPosition);
    this->addChild(label1);
    //�����
    auto frame1 = Sprite::create("picture/frame.png");
    frame1->setPosition(Vec2(1340, 900));
    this->addChild(frame1);
    //�����������
    auto text1 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text1->setPosition(Vec2(1260, 900));
    this->addChild(text1);
    text1->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //�������ũ��������
    std::string labelText2 = "Your farm's name :";
    Vec2 labe2Position = Vec2(1100, 800);
    auto label2 = Label::createWithTTF(labelText2, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label2->setPosition(labe2Position);
    this->addChild(label2);
    //�����
    auto frame2 = Sprite::create("picture/frame2.png");
    frame2->setPosition(Vec2(1420, 800));
    this->addChild(frame2);
    //�������ũ��������
    auto text2 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text2->setPosition(Vec2(1400, 800));
    this->addChild(text2);
    text2->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //������ϲ����ʳ��
    std::string labelText3 = "Your favourite food :";
    Vec2 labe3Position = Vec2(1110, 700);
    auto label3 = Label::createWithTTF(labelText3, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label3->setPosition(labe3Position);
    this->addChild(label3);
    //�����
    auto frame3 = Sprite::create("picture/frame2.png");
    frame3->setPosition(Vec2(1430, 700));
    this->addChild(frame3);
    //��������ϲ����ʳ�������
    auto text3 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text3->setPosition(Vec2(1400, 700));
    this->addChild(text3);
    text3->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //��ͼ��ѡ��
   RadioButtonGroup* radioButtonmapGroup = RadioButtonGroup::create();
   this->addChild(radioButtonmapGroup);
   for (size_t i = 1,j=1; i <= 7; i=i+2,j++) {
       std::string normalImage = StringUtils::format("picture/ch%d.png", i);
       std::string selectedImage = StringUtils::format("picture/ch%d.png", i+1);
       // ���� RadioButton��������������ѡ��״̬��ͼƬ
       RadioButton* radioButtonmap = RadioButton::create(normalImage, selectedImage);
       radioButtonmap->setTag(j);
       radioButtonmap->setPosition(Vec2(1740, 790-160*(j-1)-5*j));
        radioButtonmapGroup->addRadioButton(radioButtonmap);
        this->addChild(radioButtonmap);
   }
   radioButtonmapGroup->setSelectedButton(0);

  
  
   // ����һ���������ñ���ͼƬ
   auto backgroundLayer = Layer::create();
   auto backgroundSprite = Sprite::create("picture/Character Backgrounds.png");
   backgroundSprite->setPosition(Vec2(700,700)); // ���Ϸ�λ��
   backgroundSprite->setScale(2);
   backgroundLayer->addChild(backgroundSprite);

   // ����������ӵ�������
   this->addChild(backgroundLayer, 1); // ȷ����������Ԫ��֮��

   // ����ѡ��ť
   leftButton = MenuItemImage::create(
       "picture/male.png", // ��ఴťͼƬ
       "picture/male.png", // ��ఴť����ʱ��ͼƬ
       CC_CALLBACK_1(menu::onLeftButtonClicked, this) // ����¼��ص�
   );

   rightButton = MenuItemImage::create(
       "picture/female.png", // �ҲఴťͼƬ
       "picture/female.png", // �Ҳఴť����ʱ��ͼƬ
       CC_CALLBACK_1(menu::onRightButtonClicked, this) // ����¼��ص�
   );

   // ���ð�ťλ��
   leftButton->setPosition(Vec2(620, 430));
   rightButton->setPosition(Vec2(800, 430));

   // ��С��ť
  
   leftButton->setScale(0.4);
   rightButton->setScale(0.4);

   // �����˵�����Ӱ�ť
   auto menu = Menu::create(leftButton, rightButton, NULL);
   menu->setPosition(Vec2::ZERO); // ���˵�λ������Ϊ��
   this->addChild(menu,3);

  
   




   //èè���ǹ���
   std::string labelTexta = "Choose your lovely animal :";
   Vec2 labelaPosition = Vec2(1165, 600);
   auto labela = Label::createWithTTF(labelTexta, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
   labela->setPosition(labelaPosition);
   this->addChild(labela);

   RadioButtonGroup* radioButtonanimalGroup = RadioButtonGroup::create();
   this->addChild(radioButtonanimalGroup);
   for (size_t i = 1, j = 1; i <= 3; i = i + 2, j++) {
       std::string normalImageanimal = StringUtils::format("picture/animal%d.png", i);
       std::string selectedImageanimal = StringUtils::format("picture/animal%d.png", i + 1);

       RadioButton* radioButtonanimal = RadioButton::create(normalImageanimal, selectedImageanimal);
       radioButtonanimal->setTag(j);
       radioButtonanimal->setPosition(Vec2(1100 + (j - 1) * 130, 500));
       radioButtonanimalGroup->addRadioButton(radioButtonanimal);
       this->addChild(radioButtonanimal);
   }
   radioButtonanimalGroup->setSelectedButton(0);

   //������ RadioButtonGroup ��ѡ������Ϊѡ����һ������������
   // Ϊ��ͼ��ѡ��������¼�������
   radioButtonmapGroup->addEventListener(CC_CALLBACK_2(menu::onMapRadioButtonSelected, this));
   

   //��ok����ť
   auto ok = Button::create("picture/ok.png", "picture/ok2.png");
   ok->setPosition(Vec2(1500, 120));
   this->addChild(ok);
   ok->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {
           case Widget::TouchEventType::BEGAN:
               // ��ť������
               break;
           case Widget::TouchEventType::ENDED:
               // ��ť���ͷ�
               // ִ�е����Ĳ���
               break;
           default:
               break;
       }
       });

   //�������ֵ���
   auto tool = Button::create("picture/tools.png", "picture/tools2.png");
   tool->setPosition(Vec2(1700, 110));
   this->addChild(tool);
   _isLayerVisible = false;
   tool->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
       if (type == Widget::TouchEventType::ENDED) {
           if (!_isLayerVisible&&!music1&&!music2&&!bottom&&!part) {
               _backImage = ImageView::create("picture/back.png");
               _backImage->setPosition(Vec2(1010, 500));
               _backImage->setScale(0.9);
               this->addChild(_backImage);
               
               //����
               int musicSize = 40;
               TextHAlignment mhAlignment = TextHAlignment::CENTER;
               TextVAlignment mvAlignment = TextVAlignment::CENTER;
               std::string musicName = "fonts/Marker Felt.ttf";
               std::string musictext1 = "Music Volume :";
               Vec2 musicPosition1 = Vec2(710, 750);
               music1 = Label::createWithTTF(musictext1, musicName, musicSize, Size::ZERO, mhAlignment, mvAlignment);
               music1->setPosition(musicPosition1);
               this->addChild(music1);
               music1->setTag(8);

               std::string musictext2 = "Background Music :";
               Vec2 musicPosition2 = Vec2(750, 600);
               music2 = Label::createWithTTF(musictext2, musicName, musicSize, Size::ZERO, mhAlignment, mvAlignment); 
               music2->setPosition(musicPosition2);
               this->addChild(music2);
               music2->setTag(7);

               //��ť
               bottom = Button::create("picture/bottom.png", "picture/bottom2.png");
               bottom->setPosition(Vec2(950, 600));
               this->addChild(bottom);
               bottom->addTouchEventListener(CC_CALLBACK_2(menu::onButtonPressed, this));

               //����
               part= Slider::create();
               part->loadBarTexture("picture/part.png");
               part->loadSlidBallTextures("picture/part_one.png", "picture/part_one2.png", ""); // ���鰴ť����
               part->loadProgressBarTexture("picture/part2.png"); // ����������
               part->setMaxPercent(100); // �������ֵ
               part->setPercent(50); // ���ó�ʼֵ
               part->setPosition(Vec2(1000, 750)); // ����λ��
               part->addEventListener(CC_CALLBACK_2(menu::onSliderValueChanged, this)); // ����¼�������
               this->addChild(part);

               _isLayerVisible = true;

           }
           else {
               if (_backImage) {
                   this->removeChild(_backImage);
                   _backImage = nullptr; 
               }
               if (music1) {
                   this->removeChildByTag(8);
                   music1 = nullptr;
               }
               if (music2) {
                   this->removeChildByTag(7);
                   music2 = nullptr;
               }
               if (bottom) {
                   this->removeChild(bottom);
                   bottom = nullptr;
               }

                if (part) {
                   this->removeChild(part);
                   part = nullptr;
               }
               _isLayerVisible = false;
             

           }
       }
       });
    return true;
}

void menu::textFieldEvent(Ref* sender, TextField::EventType type)
{
    switch (type)
    {
        case TextField::EventType::ATTACH_WITH_IME:
            // ��������ý���ʱ����
            break;
        case TextField::EventType::DETACH_WITH_IME:
            // �������ʧȥ����ʱ����
            break;
        case TextField::EventType::INSERT_TEXT:
            // ���ı�������ʱ����
            break;
        case TextField::EventType::DELETE_BACKWARD:
            // ���ı���ɾ��ʱ����
            break;
        default:
            break;
    }
}


void menu::onMapRadioButtonSelected(RadioButton* radioButton, int index) {
    if (radioButton) {
        selectedMapIndex = index; // ���浱ǰѡ�еĵ�ͼ����
        log("Selected Map Index: %d", selectedMapIndex);
        auto newScene = outside::createSceneWithMapIndex(selectedMapIndex);
        Director::getInstance()->replaceScene(newScene);
    }
}


void menu::onButtonPressed(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            bottom->loadTexturePressed("picture/bottom2.png");
            break;

        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED:
            bottom->loadTextureNormal("picture/bottom2.png");
            break;
        default:
            break;
    }
}

void menu::onSliderValueChanged(Ref* sender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        log("Slider value changed: %d", percent);
        // ������������ϣ���ڻ���ֵ�ı�ʱִ�еĴ���
    }
}



void menu::onLeftButtonClicked(Ref* sender) {
    // �Ƴ�֮ǰ�Ĳ�ͼƬ��������ڣ�
    this->removeChildByTag(6); // ʹ�ñ�ǩ 2 ����ʶ��ͼƬ

    // �ڱ����Ϸ��õ�һ����ͼƬ
    auto layerSprite1 = Sprite::create("picture/boy1.png"); // �滻Ϊ���Ĳ�ͼƬ
    layerSprite1->setPosition(Vec2(700, 730));

    // �������ű�����������С
    float scaleFactor = 0.2f; // ������Ҫ�������ű���
    layerSprite1->setScale(scaleFactor);

    this->addChild(layerSprite1, 2, 6); // ȷ�����ڱ����Ϸ�����ʹ�ñ�ǩ 2

    // �л���ťͼƬ
    leftButton->setNormalImage(Sprite::create("picture/chmale.png")); // �л�Ϊѡ��״̬��ͼƬ
    rightButton->setNormalImage(Sprite::create("picture/female.png")); // �л�Ϊδѡ��״̬��ͼƬ

    // ������С chmale
    float chmaleScaleFactor = 0.3f; // ������Ҫ�������ű���
    leftButton->setScale(chmaleScaleFactor); // ���� chmale �����ű���
}


void menu::onRightButtonClicked(Ref* sender) {
    // �Ƴ�֮ǰ�Ĳ�ͼƬ��������ڣ�
    this->removeChildByTag(6); // ʹ�ñ�ǩ 2 ����ʶ��ͼƬ

    // �ڱ����Ϸ��õڶ�����ͼƬ
    auto layerSprite2 = Sprite::create("picture/girl1.png"); // �滻Ϊ���Ĳ�ͼƬ
    layerSprite2->setPosition(Vec2(690,720));

    // �������ű�����������С
    float scaleFactor = 0.2f; // ������Ҫ�������ű���
    layerSprite2->setScale(scaleFactor);

    this->addChild(layerSprite2, 2, 6); // ȷ�����ڱ����Ϸ�����ʹ�ñ�ǩ 2

    // �л���ťͼƬ
    rightButton->setNormalImage(Sprite::create("picture/chfemale.png")); // �л�Ϊѡ��״̬��ͼƬ
    leftButton->setNormalImage(Sprite::create("picture/male.png")); // �л�Ϊδѡ��״̬��ͼƬ

    // ������С chfemale
    float chfemaleScaleFactor = 0.35f; // ������Ҫ�������ű���
    rightButton->setScale(chfemaleScaleFactor); // ���� chfemale �����ű���
}