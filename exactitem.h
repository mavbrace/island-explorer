#ifndef EXACTITEM_H
#define EXACTITEM_H

#include "item.h"

class natureItem : public item { // : public item
public:
    natureItem(int zoneFoundIn, int islandFoundOn) : item(zoneFoundIn, islandFoundOn) { }

    virtual void generateItem();

};

class civilItem : public item {
public:
    civilItem(int zoneFoundIn, int islandFoundOn) : item(zoneFoundIn, islandFoundOn) { }

    virtual void generateItem();

};



#endif // EXACTITEM_H
