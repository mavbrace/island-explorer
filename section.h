#ifndef SECTION_H
#define SECTION_H

#include "item.h"
#include "exactitem.h"

#include <string>
#include <map>
#include <vector>
#include <QString>


/*  SECTIONS of ISLANDS: center=0, n=1, e=2, s=3, s=4 */
typedef std::map<int, std::string> mappedSectionNames;
typedef std::vector<item*>::iterator itemVecIt;
typedef std::vector<QString>::iterator nameVecIt;

class Section {

private:
   int section_type;
   int test;
   std::vector<item*> items;
   int itemCount;
   int islandID;

public:   
   Section(int s_type, int whichIsland);
   int getSectionType();
   std::string getSectionName();
   void generateSection(int);
   QString getAllItemsAsDesc();
   QString getIndividualItemName(int);
   int getItemCount();
   std::vector<item*> setItemVectorFromNames();
   //-----------------//
   static const mappedSectionNames SECTION_NAMES;
};

#endif // SECTION_H
