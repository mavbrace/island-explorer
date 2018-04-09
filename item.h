#ifndef ITEM_H
#define ITEM_H

#include <array>
#include <QString>

//--ABSTRACT CLASS--//
class item {

public:
    virtual void generateItem() = 0;  // !!!-- the pure virtual function ---!!! //

    item(int, int);
    QString getName();
    QString getAName();
    bool isEdible();
    bool isBurnable();
    QString makeMiscName();
    QString addA(QString);

    void foodGenerator();

    static const std::array<QString, 4> natureItemsStone;
    static const std::array<QString, 10> natureDescsStone;

    static const std::array<QString, 2> natureItemsA;
    static const std::array<QString, 9> natureDescsA;

    static const std::array<QString, 8> natureItemsB;
    static const std::array<QString, 11> natureDescsB;

    static const std::array<QString, 10> natureDescsGeneral;

    static const std::array<QString,7> natureStandAlones;

    static const std::array<QString,11> knickknacks;
    static const std::array<QString,5> knickknackDescs;

    static const std::array<QString,6> richItems;
    static const std::array<QString,9> richDescs;

    static const std::array<QString,8> clothItems;
    static const std::array<QString,10> clothDescs;

    static const std::array<QString,7> personalItems;
    static const std::array<QString,4> techItems;

    static const std::array<QString,8> giftItemsFood;
    static const std::array<QString,7> giftDescsFoodA;
    static const std::array<QString,9> giftDescsFoodB;

    static const std::array<QString,8> giftItemsCloth;

    static const std::array<QString,24> miscAnimals;
    static const std::array<QString,5> miscColours;
    static const std::array<QString,14> miscSeconds;


protected:
    QString name;
    int origin; //which zone did it originate from
    int originIsland; //which island did it originate from (just a unique id)
    int value;
    bool edible;
    bool burnable;
};

#endif // ITEM_H
