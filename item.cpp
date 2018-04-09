#include "item.h"
#include <random>
#include <QDebug>

//---------------------------//
//--stone
const std::array<QString,4> item::natureItemsStone = {"pebble","rock","stone","shell"};
const std::array<QString,10> item::natureDescsStone = {"chipped","angular","heavy","spotted","cloud-coloured","pitted",
                                                     "rust-stained","shimmery black","perfectly spherical","glittery, silver"};
//--feather or bones
const std::array<QString,2> item::natureItemsA = {"feather","bone"};
const std::array<QString,9> item::natureDescsA = {"old grey","yellowing","thin","fine",
                                                "long, thin","delicate","fish","bird","hawk"};
//--forest floor: very burn-able
const std::array<QString,8> item::natureItemsB = {"leaf","twig","branch","stick","acorn","piece of bark",
                                                 "mushroom","flower"};
const std::array<QString,11> item::natureDescsB = {"old","bent","mottled","rotting","dry","bumpy-textured","split",
                                                 "half-eaten","hairy","perfectly symmetrical","brightly-spotted"};
//-general-//
const std::array<QString,10> item::natureDescsGeneral {"dull","dull grey","fragment of a","tiny","flat",
                                                      "smooth","brittle","pure white","exceptional-looking","lucky"};
//---standalones---//
const std::array<QString,7> item::natureStandAlones ={"puddle of sap","pile of droppings","bit of charcoal","bird's nest",
                                                     "piece of wasp's nest","tuft of fur","lump of bright amber"};
//---------------------------//
//---------------------------//
const std::array<QString,11> item::knickknacks = {"fragment","marble","button","pin","coin","spoon","comb","knife",
                                                 "mirror","whistle","timepiece"};
const std::array<QString,5> item::knickknackDescs = {"dull","glass","dull copper","shiny copper","carved wooden"};

const std::array<QString,6> item::richItems = {"ring","necklace","earring","bracelet","pocket watch","monocle"};
const std::array<QString,9> item::richDescs = {"ancient gold","tarnished silver","golden","silver","gold","sapphire",
                                               "glittering crystal","old, diamond-encrusted","diamond-encrusted"};
const std::array<QString,8> item::clothItems = {"rag","sock","slipper","shirt","flag","blanket","tablecloth","curtain"};
const std::array<QString,10> item::clothDescs = {"stained","moth-eaten","tattered old","tattered","worn","threadbare",
                                                 "musty old","sad old","faded old","well-worn"};

const std::array<QString,7> item::personalItems = {"shoe","sandle","pair of glasses","pair of shoes","bowl","doll",
                                                   "locket with a faded portrait inside"};
const std::array<QString,4> item::techItems = {"bicycle","telescope","machine","engine"};

const std::array<QString,8> item::giftItemsFood = {"soup","tea","bun","sandwich","sauce","pie","butter","steak"};
const std::array<QString,7> item::giftDescsFoodA = {"fish","bird","onion","spicy","plum","ginger","dried"};
const std::array<QString,9> item::giftDescsFoodB = {"bowl of","cup of","warm","ice-cold","fresh","fermented","coffee with",
                                                    "creamed","stew made with"};
const std::array<QString,8> item::giftItemsCloth = {"cloak","cape","shirt","hat","scarf","pair of pants","jacket",
                                                     "vest"};

//---------------------------//
//---------------------------//
//---MISC- can be used anywhere ----//
const std::array<QString,24> item::miscAnimals = {"beetle","ladybug","chicken","sparrow","wasp","fish","snake",
                                                      "wolf","beaver","otter","whale","crow","shark",
                                                       "fox","seal","walrus","mouse",
                                                       "bird","lion","raven","heron","hare","moth","hawk"};
const std::array<QString,5> item::miscColours = {"red","crimson","blue","silver","orange"};
const std::array<QString,14> item::miscSeconds = {"weed","tooth","leaf","sand","berries","dust","teeth","bone",
                                           "'s tooth","'s tail"," fur","foot","'s tongue"," eye"};
//------------end of MISC------------//


item::item(int zoneFoundIn, int islandFoundOn) {
    //the zone the item was found in (0 1 2 or 3) (ie desolate, mountainous/treed, inhabited/abandoned, grassy/hill)
    //note: islandfoundOn == symbol ID (ie the unique id of the island)
    origin = zoneFoundIn;
    originIsland = islandFoundOn;
    //intialize value
    value = 0;
    //initialize edibility
    edible = false;
    //intialize name
    name = "Placeholder";
    //intialize burnable
    burnable = false;

}

bool item::isEdible(){
    return edible;
}

bool item::isBurnable(){
    return burnable;
}

QString item::getName(){
    return name;
}

QString item::getAName(){
    return addA(name);
}


void item::foodGenerator(){
    int r1 = rand() % giftDescsFoodB.size();
    QString first_part = giftDescsFoodB[r1];
    //---//
    int r2 = rand() % giftDescsFoodA.size();
    QString second_part = giftDescsFoodA[r2];
    //---//
    int r3 = rand() % giftItemsFood.size();
    QString third_part = giftItemsFood[r3];

    QString totalWord = first_part + " " + second_part + " " +  third_part;

    value = r1 + r2 + r3;
    name = totalWord;
    edible = true;
}


//note: changes 'value' within
QString item::makeMiscName(){
    QString first_part = "";
    QString second_part = "";
    int val1 = 0;
    int rr = rand() % ( (miscAnimals.size()) + (miscColours.size()) );
    if (rr < miscAnimals.size()){
        first_part = miscAnimals[rr];
        val1 = rr;
    } else {
        first_part = miscColours[rr-miscAnimals.size()];
        val1 = rr-miscAnimals.size();
    }
    int rr2 = rand() % (miscSeconds.size());
    second_part = miscSeconds[rr2];
    value = val1 + rr2;

    return first_part + second_part; //no space.
}

QString item::addA(QString str){
    //add an 'a' or an 'an' to the beginning of the word
    if (str.at(0) == 'a' || str.at(0) == 'e' || str.at(0) == 'o' || str.at(0) == 'i' || str.at(0) == 'u'){
        str = "an " + str;
    } else {
        str = "a " + str;
    }
    return str;
}


