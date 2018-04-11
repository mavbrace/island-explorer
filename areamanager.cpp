#include "areamanager.h"
#include <QDebug>
#include <array>
#include <random>

#include "lookwindow.h"

/*  SECTIONS of ISLANDS: center=0, n=1, e=2, s=3, w=4 */
/* ZONE -> ISLAND/AREA -> SECTION */

//CONSTANT
const int areaManager::NUM_ISLANDS = 10; //don't think this is being used anymore
const int areaManager::NUM_SECTIONS = 5;

const std::array<QString,4> areaManager::launchDescs = {"It takes a few tries, but your engine coughs to life.",
                                                       "After fiddling with the controls and giving the engine a helpful kick, your boat starts to move.",
                                                       "You begin your journey. The engine grumbles a little, but seems to be behaving.",
                                                       "You set off merrily into the waves, leaving the shore behind."};
const std::array<QString,4> areaManager::journeyDescs = {"Soon after the island behind you disappears beneath the horizon, another appears in front of you.",
                                                        "Your journey is long, and the ocean rough. At last you sight land in the distance.",
                                                        "The sea is flat and calm. The sky blue. You watch the ripples your boat leaves behind as it glides along. At last you reach your destination.",
                                                        "A heavy fog sets in. By the time it begins to clear your destination is within sight."};

const std::array<QString,4> areaManager::islandDescsIntros = {"The island you've arrived at seems","You pull up to the island. It seems",
                                                              "You putter up to the island. It appears","You approach the shore of the island. It appears"};
const std::array<QString,4> areaManager::islandDescs1 = {"desolate","to be heavily forested","to once have been inhabited","gently rounded"}; //desolate, mountainous/treed, inhabited/abandoned, grassy/hill
//islandDescs2 is the second part of islandDescs1. There are 2 descs2 for each desc1.
const std::array<QString,8> areaManager::islandDescs2 = {" and guarded by high cliffs"," and lonely"," and mountainous"," and full of life",", but not anymore",", and may still be"," and grassy"," and scattered with trees"};

areaManager::areaManager(int sID) {
    symbolID = sID;
    // initialize the 'position' (integer... *9 bits)
    pos = 0;
    islandDesc = "";
    journeyDesc = "";
    // initialize 5 new sections (per area).
    sections.reserve(NUM_SECTIONS);
    for (int i = 0; i < NUM_SECTIONS; i++){
        sections.push_back(new Section(i,sID)); //note: island ID == symbol ID. Just a unique id relating to the island's symbol.
    }
    generateIsland();

}

// ---GENERATE A -NEW- ISLAND --- //
void areaManager::generateIsland() {
    // #1. Find the zone the island is in. There are 4 zones: desolate, mountainous/treed, inhabited/abandoned, grassy/hill
    int q = 496/4; //q = one quarter  ( [ |q |2q |3q ]4q )
    if (symbolID < q){ //first quarter
        zone = 0;
    } else if (symbolID >= q && symbolID < 2*q){ //second quarter
        zone = 1;
    } else if (symbolID >= 2*q && symbolID < 3*q){ //third quarter
        zone = 2;
    } else { //fourth quarter
        zone = 3;
    }

    // #2. Generate the launch+journey Description.
    int valA = rand() % (launchDescs.size());
    int valB = rand() % (journeyDescs.size());
    journeyDesc = launchDescs[valA] + "\n" + journeyDescs[valB];

    // #3. Generate the Island Description.
    int val1 = rand() % (islandDescsIntros.size());
    islandDesc = islandDescsIntros[val1];
    int n = rand() % 2; // 0 or 1.
    islandDesc = islandDesc + " " + islandDescs1[zone] + islandDescs2[(zone*2) + n] + ".";

    // #4. Generate Each Section
    for (int i = 0; i < NUM_SECTIONS; i++){
        sections[i]->generateSection(zone);
    }
}


// ---HANDLES ARRIVING AT AN ISLAND --- //
void areaManager::arriveAtIsland(area* porthole){
    //land on a random (outside) section...
    int sec = (rand() % 4) + 1; //(1 -> 4. Note: can't land on 0 (the middle)
    arriveAtSection(sec, porthole);
}


void areaManager::arriveAtSection(int whichSection, area* porthole){

    porthole->setOutsideImage(zone,whichSection);

    currentSection = whichSection;
    lookWindow::descOfItems = getFullDesc();

    // Add NEW SECTION items..
    _addItemsToLookWindow();

    //display an 'x' over the section you're on.
    porthole->setSectionMarker(currentSection);
}



std::vector<item*> areaManager::updateItemRecord(){
    // Update the items from the gathered lookwindow information. Eg. some items may have been
    //added to the user's inventory (therefore should delete from the island section, since it's gone).
    Section * s = sections[currentSection];
    std::vector<item*> itemObjects = s->setItemVectorFromNames();

    return itemObjects;
}


void areaManager::_addItemsToLookWindow(){
    Section * s = sections[currentSection];
    lookWindow::itemNames.clear(); //clear.
    for (int i = 0; i < s->getItemCount(); i++){
        lookWindow::itemNames.push_back(s->getIndividualItemName(i));
    }
}

void areaManager::freeAllSections(){
    for (sectionVecIt it = sections.begin(); it != sections.end(); it++){
        //for each section, first free all items inside it
        (*it)->freeAllItems();
        //free the sections vector
        delete *it;
    }
}

// ------- GETTERS AND SETTERS -------- //

int areaManager::getCurrentSection(){
    return currentSection;
}

int areaManager::getSymbolID(){
    return symbolID;
}

QString areaManager::getJourneyFullDesc(){
    return journeyDesc;
}

QString areaManager::getIslandFullDesc(){
    return islandDesc;
}

QString areaManager::getFullDesc(){
    Section * s = sections[currentSection];
    return s->getAllItemsAsDesc();
}

