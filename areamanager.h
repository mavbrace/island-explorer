#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <array>
#include <QWidget>
#include <QString>

#include "section.h"
#include "area.h"
#include "item.h"

/* each island [area] has 5 [sections] */

class areaManager {

public:
    static const int NUM_ISLANDS;
    static const int NUM_SECTIONS;
    static const std::array<QString, 4> islandDescs1;
    static const std::array<QString, 8> islandDescs2;
    static const std::array<QString, 4> launchDescs;
    static const std::array<QString, 4> journeyDescs;
    static const std::array<QString, 4> islandDescsIntros;
    /* ---------------- */
    areaManager(int);
    void generateIsland();
    void arriveAtIsland(area*);
    void arriveAtSection(int, area*);
    void _addItemsToLookWindow();
    std::vector<item*> updateItemRecord();
    /*----getters and setters-----*/
    QString getIslandFullDesc();
    QString getJourneyFullDesc();
    int getSymbolID();
    QString getFullDesc();
    int getCurrentSection();

private:
    std::vector<Section*> sections; //ARRAY of [5]. Should == NUM_SECTIONS above. (gotta be a vector)
    int currentSection;
    int pos;
    int symbolID; //island's id (= the island's symbol)
    int zone;
    QString islandDesc;
    QString journeyDesc;

};

#endif // AREAMANAGER_H
