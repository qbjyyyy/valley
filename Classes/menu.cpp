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
    //设置开始背景
    auto spriteback = Sprite::create("picture/menu.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(0, 0));
    this->addChild(spriteback);
    
   
    
    //设置你的名字
    std::string labelText1 = "Your name :";
    int fontSize = 40;
    TextHAlignment hAlignment = TextHAlignment::CENTER;
    TextVAlignment vAlignment = TextVAlignment::CENTER;
    Vec2 labelPosition = Vec2(1050, 900);
    std::string fontName = "fonts/Marker Felt.ttf";
    auto label1 = Label::createWithTTF(labelText1, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label1->setPosition(labelPosition);
    this->addChild(label1);
    //输入框
    auto frame1 = Sprite::create("picture/frame.png");
    frame1->setPosition(Vec2(1340, 900));
    this->addChild(frame1);
    //输入你的名字
    auto text1 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text1->setPosition(Vec2(1260, 900));
    this->addChild(text1);
    text1->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //设置你的农场的名字
    std::string labelText2 = "Your farm's name :";
    Vec2 labe2Position = Vec2(1100, 800);
    auto label2 = Label::createWithTTF(labelText2, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label2->setPosition(labe2Position);
    this->addChild(label2);
    //输入框
    auto frame2 = Sprite::create("picture/frame2.png");
    frame2->setPosition(Vec2(1420, 800));
    this->addChild(frame2);
    //输入你的农场的名字
    auto text2 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text2->setPosition(Vec2(1400, 800));
    this->addChild(text2);
    text2->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //设置最喜欢的食物
    std::string labelText3 = "Your favourite food :";
    Vec2 labe3Position = Vec2(1110, 700);
    auto label3 = Label::createWithTTF(labelText3, fontName, fontSize, Size::ZERO, hAlignment, vAlignment);
    label3->setPosition(labe3Position);
    this->addChild(label3);
    //输入框
    auto frame3 = Sprite::create("picture/frame2.png");
    frame3->setPosition(Vec2(1430, 700));
    this->addChild(frame3);
    //输入你最喜欢的食物的名字
    auto text3 = cocos2d::ui::TextField::create("Input ", "fonts/Marker Felt.ttf", 40);
    text3->setPosition(Vec2(1400, 700));
    this->addChild(text3);
    text3->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eventType) {});

    //地图单选框
   RadioButtonGroup* radioButtonmapGroup = RadioButtonGroup::create();
   this->addChild(radioButtonmapGroup);
   for (size_t i = 1,j=1; i <= 7; i=i+2,j++) {
       std::string normalImage = StringUtils::format("picture/ch%d.png", i);
       std::string selectedImage = StringUtils::format("picture/ch%d.png", i+1);
       // 创建 RadioButton，并设置正常和选中状态的图片
       RadioButton* radioButtonmap = RadioButton::create(normalImage, selectedImage);
       radioButtonmap->setTag(j);
       radioButtonmap->setPosition(Vec2(1740, 790-160*(j-1)-5*j));
        radioButtonmapGroup->addRadioButton(radioButtonmap);
        this->addChild(radioButtonmap);
   }
   radioButtonmapGroup->setSelectedButton(0);

  
  
   // 创建一个层来放置背景图片
   auto backgroundLayer = Layer::create();
   auto backgroundSprite = Sprite::create("picture/Character Backgrounds.png");
   backgroundSprite->setPosition(Vec2(700,700)); // 左上方位置
   backgroundSprite->setScale(2);
   backgroundLayer->addChild(backgroundSprite);

   // 将背景层添加到场景中
   this->addChild(backgroundLayer, 1); // 确保层在其他元素之上

   // 创建选择按钮
   leftButton = MenuItemImage::create(
       "picture/male.png", // 左侧按钮图片
       "picture/male.png", // 左侧按钮按下时的图片
       CC_CALLBACK_1(menu::onLeftButtonClicked, this) // 点击事件回调
   );

   rightButton = MenuItemImage::create(
       "picture/female.png", // 右侧按钮图片
       "picture/female.png", // 右侧按钮按下时的图片
       CC_CALLBACK_1(menu::onRightButtonClicked, this) // 点击事件回调
   );

   // 设置按钮位置
   leftButton->setPosition(Vec2(620, 430));
   rightButton->setPosition(Vec2(800, 430));

   // 缩小按钮
  
   leftButton->setScale(0.4);
   rightButton->setScale(0.4);

   // 创建菜单并添加按钮
   auto menu = Menu::create(leftButton, rightButton, NULL);
   menu->setPosition(Vec2::ZERO); // 将菜单位置设置为零
   this->addChild(menu,3);

  
   




   //猫猫还是狗狗
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

   //将两个 RadioButtonGroup 的选择结果作为选择下一个场景的依据
   // 为地图单选框组添加事件监听器
   radioButtonmapGroup->addEventListener(CC_CALLBACK_2(menu::onMapRadioButtonSelected, this));
   

   //“ok”按钮
   auto ok = Button::create("picture/ok.png", "picture/ok2.png");
   ok->setPosition(Vec2(1500, 120));
   this->addChild(ok);
   ok->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
       switch (type)
       {
           case Widget::TouchEventType::BEGAN:
               // 按钮被按下
               break;
           case Widget::TouchEventType::ENDED:
               // 按钮被释放
               // 执行点击后的操作
               break;
           default:
               break;
       }
       });

   //背景音乐调节
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
               
               //内容
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

               //按钮
               bottom = Button::create("picture/bottom.png", "picture/bottom2.png");
               bottom->setPosition(Vec2(950, 600));
               this->addChild(bottom);
               bottom->addTouchEventListener(CC_CALLBACK_2(menu::onButtonPressed, this));

               //滑块
               part= Slider::create();
               part->loadBarTexture("picture/part.png");
               part->loadSlidBallTextures("picture/part_one.png", "picture/part_one2.png", ""); // 滑块按钮纹理
               part->loadProgressBarTexture("picture/part2.png"); // 进度条纹理
               part->setMaxPercent(100); // 设置最大值
               part->setPercent(50); // 设置初始值
               part->setPosition(Vec2(1000, 750)); // 设置位置
               part->addEventListener(CC_CALLBACK_2(menu::onSliderValueChanged, this)); // 添加事件监听器
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
            // 当输入框获得焦点时调用
            break;
        case TextField::EventType::DETACH_WITH_IME:
            // 当输入框失去焦点时调用
            break;
        case TextField::EventType::INSERT_TEXT:
            // 当文本被插入时调用
            break;
        case TextField::EventType::DELETE_BACKWARD:
            // 当文本被删除时调用
            break;
        default:
            break;
    }
}


void menu::onMapRadioButtonSelected(RadioButton* radioButton, int index) {
    if (radioButton) {
        selectedMapIndex = index; // 保存当前选中的地图索引
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
        // 这里可以添加您希望在滑块值改变时执行的代码
    }
}



void menu::onLeftButtonClicked(Ref* sender) {
    // 移除之前的层图片（如果存在）
    this->removeChildByTag(6); // 使用标签 2 来标识层图片

    // 在背景上放置第一个层图片
    auto layerSprite1 = Sprite::create("picture/boy1.png"); // 替换为您的层图片
    layerSprite1->setPosition(Vec2(700, 730));

    // 设置缩放比例，调整大小
    float scaleFactor = 0.2f; // 根据需要调整缩放比例
    layerSprite1->setScale(scaleFactor);

    this->addChild(layerSprite1, 2, 6); // 确保层在背景上方，并使用标签 2

    // 切换按钮图片
    leftButton->setNormalImage(Sprite::create("picture/chmale.png")); // 切换为选中状态的图片
    rightButton->setNormalImage(Sprite::create("picture/female.png")); // 切换为未选中状态的图片

    // 单独缩小 chmale
    float chmaleScaleFactor = 0.3f; // 根据需要调整缩放比例
    leftButton->setScale(chmaleScaleFactor); // 设置 chmale 的缩放比例
}


void menu::onRightButtonClicked(Ref* sender) {
    // 移除之前的层图片（如果存在）
    this->removeChildByTag(6); // 使用标签 2 来标识层图片

    // 在背景上放置第二个层图片
    auto layerSprite2 = Sprite::create("picture/girl1.png"); // 替换为您的层图片
    layerSprite2->setPosition(Vec2(690,720));

    // 设置缩放比例，调整大小
    float scaleFactor = 0.2f; // 根据需要调整缩放比例
    layerSprite2->setScale(scaleFactor);

    this->addChild(layerSprite2, 2, 6); // 确保层在背景上方，并使用标签 2

    // 切换按钮图片
    rightButton->setNormalImage(Sprite::create("picture/chfemale.png")); // 切换为选中状态的图片
    leftButton->setNormalImage(Sprite::create("picture/male.png")); // 切换为未选中状态的图片

    // 单独缩小 chfemale
    float chfemaleScaleFactor = 0.35f; // 根据需要调整缩放比例
    rightButton->setScale(chfemaleScaleFactor); // 设置 chfemale 的缩放比例
}