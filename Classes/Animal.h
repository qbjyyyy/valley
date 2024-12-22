#ifndef _ANIMAL_H_
#define _ANIMAL_H_


#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

class Animal : public Sprite {
protected:
    Vec2 targetPosition; // Ŀ���
    Rect Bounds; // �߽�
    Animation * animalmoveAnimation;
    Animate *animalmoveAnimate;
    float speed;//������ٶ�

public:
    Animal() ;
    virtual ~Animal();
    static Animal* create(const std::string& filename);
    virtual bool init(const std::string& filename)=0;
    void generateNewTarget();
    void update(float delta);
};

//����
class Sheep :public Animal 
{
public:
    static Sheep* create(const std::string& filename);
    Sheep();
    ~Sheep();
    bool init(const std::string& filename)override;
};

//ţ
class Cow :public Animal {
public:
    static Cow* create(const std::string& filename);
    Cow() {};
    ~Cow() {};
    bool init(const std::string& filename)override;
};

//����
class Parrot :public Animal {
public:
    static Parrot* create(const std::string& filename);
    Parrot();
    ~Parrot() {};
    bool init(const std::string& filename)override;
};

#endif // !_ANIMAL_H_