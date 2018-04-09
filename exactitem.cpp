#include "exactitem.h"

// This file contains 2 classes ( so far ), both derived from -item- //
// 1. natureItem
// 2. civilItem

// --------------------------------------------------------------------------- //
// ----------------------------ITEM FROM NATURE------------------------------- //
// --------------------------------------------------------------------------- //

void natureItem::generateItem(){

    QString first_part = "";
    QString second_part = "";
    QString totalWord = "";
    int val1 = 0;
    int val2 = 0;
    int totalVal = 0;

    int r1 = rand() % 4; // different choices of nature arrays. Minus the 'standalone' array.
    if (r1 == 0){
        //stone
        val1 = rand() % (natureDescsStone.size());
        first_part = natureDescsStone[ val1 ];
        val2 = rand() % (natureItemsStone.size());
        second_part = natureItemsStone[ val2 ];
    } else if (r1 == 1){
        //feather or bone
        val1 = rand() % (natureDescsA.size());
        first_part = natureDescsA[ val1 ];
        val2 = rand() % (natureItemsA.size());
        second_part = natureItemsA[ val2 ];
    } else if (r1 == 2){
        // twigs, and other assorted tree stuffs: VERY BURN-ABLE
        burnable = true;
        val1 = rand() % (natureDescsB.size());
        first_part = natureDescsB[ val1 ];
        val2 = rand() % (natureItemsB.size());
        second_part = natureItemsB[ val2 ];
    } else { //TODO...
        val1 = 4;
        first_part = "banana";
        val2 = 4;
        second_part = "peel";
    }
    // 1.chance to replace first-part (aka 'description') with a general nature description:
    int r2 = rand() % 5;
    if (r2 == 0){
        val1 = rand() % (natureDescsGeneral.size());
        first_part = natureDescsGeneral[ val1 ];
    }
    //--JOIN TOGETHER--//
    totalWord = first_part + " " + second_part;
    value = val1 + val2; //~~~
    //-----------------//
    // 2.chance to replace entire name with a standalone nature item.
    int r3 = rand() % 25;
    if (r3 == 0){
        value = rand() % (natureStandAlones.size());
        totalWord = natureStandAlones[ totalVal ];
    }
    // 3.chance to replace entire name with MISC
    int r4 = rand() % 25;
    if (r4 == 0){
        totalWord = makeMiscName(); //note: updates 'value' as well!!!
    }

    name = totalWord;

}

// --------------------------------------------------------------------------- //
// -------------------------ITEM FROM CIVILIZATION---------------------------- //
// --------------------------------------------------------------------------- //


//generate NAME, find VALUE of NAME
void civilItem::generateItem(){
    QString first_part = "";
    QString second_part = "";
    QString totalWord = "";
    int val1 = 0;
    int val2 = 0;

    int r1 = rand() % 4;
    if (r1 == 0){
        val1 = rand() % (knickknackDescs.size());
        first_part = knickknackDescs[ val1 ];
        val2 = rand() % (knickknacks.size());
        second_part = knickknacks[ val2 ];
    } else if (r1 == 1){
        val1 = rand() % (clothDescs.size());
        first_part = clothDescs[ val1 ];
        val2 = rand() % (clothItems.size());
        second_part = clothItems[ val2 ];
    } else if (r1 == 2){
        val1 = rand() % (richDescs.size());
        first_part = richDescs[ val1 ];
        val2 = rand() % (knickknacks.size());
        second_part = knickknacks[ val2 ];
    } else {
        val1 = rand() % (richDescs.size());
        first_part = richDescs[ val1 ];
        val2 = rand() % (richItems.size());
        second_part = richItems[ val2 ];
    }

    totalWord = first_part + " " + second_part;

    value = val1 + val2;
    name =  totalWord;

}


