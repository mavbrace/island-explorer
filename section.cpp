#include "section.h"
#include "areamanager.h"
#include "lookwindow.h"

#include <QDebug>
#include <random>

/* [section] in an [area] */



//CONSTANT
/*  SECTIONS of ISLANDS */
const mappedSectionNames Section::SECTION_NAMES = {{0,"CENTER"},{1,"NORTH"},
                                             {2,"EAST"},{3,"SOUTH"},{4,"WEST"}};

Section::Section(int s_type, int whichIsland) {
    islandID = whichIsland;
    //initialize
    itemCount = 0;
    items.reserve(10);
    //section type (1 of each, AREA_NAMES)
    if (section_type >= areaManager::NUM_SECTIONS){
        //ERROR
        QString msg = QString::number(section_type);
        qDebug() << "Error: not a valid section type: " << msg;
    } else {
        //OKAY
        section_type = s_type;
    }

}

void Section::generateSection(int zone){
    //ZONES: 0. desolate, 1.mountainous/treed, 2.inhabited/abandoned, 3.grassy/hill

    qDebug("Generating Section");
    //items: max is 10. Will usually be no more than 5. TODO: add chance for extras.
    itemCount = rand() % 6; //0 - 5;
    for (int i = 0; i < itemCount; i++){
        int r = 0;
        if (zone == 2){ //if you happen to be on an island with traces of a civilization
            r = rand() % 4; //better chance of getting the civilization item than the nature or food item
        }
        if (r == 0){
            natureItem *tempItemPtr = new natureItem(zone,islandID);
            tempItemPtr->generateItem();
            items.push_back(tempItemPtr);
        } else if (r == 1){
            civilItem *tempItemPtr = new civilItem(zone,islandID);
            tempItemPtr->foodGenerator();
            items.push_back(tempItemPtr);
        } else {
            civilItem *tempItemPtr = new civilItem(zone,islandID);
            tempItemPtr->generateItem();
            items.push_back(tempItemPtr);
        }
    }

}

QString Section::getAllItemsAsDesc(){
    QString intro = "There's "; //TODO: vary this.
    if (itemCount > 0){
        QString final_desc = intro + items[0]->getAName();
        for (int i = 1; i < itemCount-1; i++){
            final_desc = final_desc + ", " + items[i]->getAName();
        }
        if (itemCount == 1){
            return final_desc + ".";
        } else {
            return (final_desc + " and " + items[itemCount-1]->getAName() + ".");
        }
    } else {
        return QString("Nothing of interest.");
    }
}

//by index, the string name.
QString Section::getIndividualItemName(int index){
    if (index < items.size()){
        return items[index]->getName();
    } else {
        return QString("");
        qDebug("Error getting Individual Item Name. Out of bounds.");
    }

}

int Section::getItemCount(){
    return itemCount;
}

int Section::getSectionType(){
    return section_type;
}

std::string Section::getSectionName(){
    mappedSectionNames::const_iterator iter = SECTION_NAMES.find(section_type);
    if (iter == SECTION_NAMES.end()){
        qDebug("Error in getting area name!");
        return "";
    } else {
        return iter->second;
    }
}

//TODO........
//note: std::vectors do not have bounds checking(??). Use itemCount as the upper bounds.
std::vector<item*> Section::setItemVectorFromNames(){
    qDebug("updating...");
    std::vector<item*> itemsTemp;
    //remove the takenItems from the Section Item Vector!!
    for (nameVecIt nameIter = lookWindow::takenItemNames.begin();
                              nameIter != lookWindow::takenItemNames.end(); nameIter++){
        for (itemVecIt iter = items.begin(); iter != items.begin()+itemCount; iter++){
            if ((*iter)->getName() == *nameIter){
                itemsTemp.push_back(*iter); //add the item object to itemTemps
                qDebug() << "Deleting: " + (*iter)->getName();
                items.erase(iter); //memory management (this should take care of it)
                itemCount--;
                break;
            }
        }
    }

    lookWindow::takenItemNames.clear();

    return itemsTemp; //return vector of item objects

}

void Section::freeAllItems(){
    for (itemVecIt iter = items.begin(); iter != items.begin()+itemCount; iter++){
        delete *iter;
    }
}
