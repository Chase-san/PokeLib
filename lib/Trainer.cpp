/*
 * Trainer.cpp
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 */

#include "internal.h"
#include <pokelib/Save.h>
#include <pokelib/Trainer.h>

namespace PokeLib {

uint8_t itemNum[3][8] = {
    {165,50,100,12,40,64,15,30},
    {165,50,100,12,40,64,15,30},
    {165,43,100,12,40,64,24,30},
};
uint16_t itemOffset[3][8] = {
    {0x624,0x8B8,0x980,0xB10,0xB40,0xBE0,0xCE0,0xD1C},
    {0x630,0x8C4,0x98C,0xB1C,0xB4C,0xBEC,0xCEC,0xD28},
    {0x644,0x8D8,0x9A4,0xB34,0xB64,0xC04,0xD04,0xD64},
};

enum {
    offsetName = 0,
    offsetTID, offsetSID, offsetMoney,
    offsetGender, offsetCountry,
    offsetBadges, offsetBadges2,
    offsetAvatar, offsetRival,
};

uint16_t tOffset[][3] = {
    {0x0064, 0x0068, 0x0064}, //TNAME (x8 16 bit)
    {0x0074, 0x0078, 0x0074}, //TID
    {0x0076, 0x007A, 0x0076}, //SID
    {0x0078, 0x007C, 0x0078}, //MONEY
    {0x007C, 0x0080, 0x007C}, //GENDER
    {0x007D, 0x0081, 0x007D}, //COUNTRY
    {0x007E, 0x0082, 0x007E}, //BADGES (HGSS Johto)
    {0x007E, 0x0082, 0x0083}, //BADGES 2 (HGSS Kanto, others mirror)
    {0x007F, 0x0083, 0x007F}, //Multiplayer Avatar
    {0x25A8, 0x27E8, 0x22D4}, //Rival Name (x8 16 bit)
};

/*
 	Trainer::Trainer(Save *s) {
		save = s;
		u8 type = s->getSaveType();
		data.name = (u16*)&s->BlockA[tOffset[offsetName][type]];
		data.rival = (u16*)&s->BlockA[tOffset[offsetRival][type]];
		data.tid = (u16*)&s->BlockA[tOffset[offsetTID][type]];
		data.sid = (u16*)&s->BlockA[tOffset[offsetSID][type]];
		data.money = (u32*)&s->BlockA[tOffset[offsetMoney][type]];
		data.gender = (u8*)&s->BlockA[tOffset[offsetGender][type]];
		data.country = (u8*)&s->BlockA[tOffset[offsetCountry][type]];
		data.badges = (u8*)&s->BlockA[tOffset[offsetBadges][type]];
		data.badges2 = (u8*)&s->BlockA[tOffset[offsetBadges2][type]];
		data.avatar = (u8*)&s->BlockA[tOffset[offsetAvatar][type]];
	}
 */

Trainer::Trainer(const Save *sav) {
    //BagItem**items;
    type = sav->getSaveType();
    items = new BagItem*[8];
    for(int i = 0; i < 8; ++i) {
        items[i] = new BagItem[itemNum[type][i]];
        memcpy(items[i],&sav->BlockA[itemOffset[type][i]],itemNum[type][i]);
//		for(int j = 0; j < itemNum[type][i]; ++j) {
//			items[i][j] = 0; //Get item from save
//		}
    }

    trainer = PokeText::toPoketext((const uint16_t*)&sav->BlockA[tOffset[offsetName][type]],8);
    rival = PokeText::toPoketext((const uint16_t*)&sav->BlockA[tOffset[offsetRival][type]],8);
    isFemale = (sav->BlockA[tOffset[offsetGender][type]] == 0 ? false : true);

    badgeMain = *((Badge*)&sav->BlockA[tOffset[offsetBadges][type]]);
    badgeAlt = *((Badge*)&sav->BlockA[tOffset[offsetBadges2][type]]);
}

Trainer::~Trainer() {
    for(int i = 0; i < 8; ++i) {
        delete items[i];
    }
    delete items;
}

void Trainer::saveInto(Save *sav) {
    uint8_t ntype = sav->getSaveType();
    //Set Items
    for(int i = 0; i < 8; ++i) {
        memcpy(&sav->BlockA[itemOffset[ntype][i]],items[i],min(itemNum[type][i],itemNum[ntype][i]));
//		for(int j = 0; j < itemNum[type][i]; ++j) {
//			items[i][j] = 0; //Get item from save
//		}
    }
    for(int i=0; i<8; ++i) {
        ((uint16_t*)&sav->BlockA[tOffset[offsetName][type]])[i] = trainer[i];
        ((uint16_t*)&sav->BlockA[tOffset[offsetRival][type]])[i] = rival[i];
    }
    sav->BlockA[tOffset[offsetGender][type]] = isFemale ? 1 : 0;

    sav->BlockA[tOffset[offsetBadges2][type]] = *((uint8_t*)&badgeAlt);
    sav->BlockA[tOffset[offsetBadges][type]] = *((uint8_t*)&badgeMain);
}


//Actual Trainer stuff
widetext Trainer::getName() const {
    return PokeText::convertFrom(trainer);
}
void Trainer::setName(const widetext text) {
    if(text.length() <= 8) {
        trainer = PokeText::convertTo(text);
    }
}
void Trainer::setName(const poketext text) {
    if(text.length() <= 8) {
        trainer = text;
    }
}

widetext Trainer::getRivalName() const {
    return PokeText::convertFrom(rival);
}
void Trainer::setRivalName(const widetext text) {
    if(text.length() <= 8) {
        rival = PokeText::convertTo(text);
    }
}
void Trainer::setRivalName(const poketext text) {
    if(text.length() <= 8) {
        rival = text;
    }
}

bool Trainer::getFemale() const {
    return isFemale;
}
void Trainer::setFemale(bool female) {
    isFemale = female;
}

//Item Stuff
uint8_t Trainer::getPocketSize(ItemPocket pocket) const {
    uint8_t max = itemNum[type][pocket];
    for(int i=0; i<max; ++i) {
        if(!items[pocket][i].item) return i;
    }
    return max;
}
uint8_t Trainer::getPocketMaxSize(ItemPocket pocket) const {
    return itemNum[type][pocket];
}
BagItem Trainer::getItem(ItemPocket pocket,uint8_t slot) const {
    return items[pocket][slot];
}
void Trainer::setItem(ItemPocket pocket,uint8_t slot,BagItem item) {
    items[pocket][slot] = item;
}
void Trainer::eraseItem(ItemPocket pocket,uint8_t slot) {
    BagItem tmp;
    tmp.count = 0;
    tmp.item = 0;
    items[pocket][slot] = tmp;
}

inline int sortcompare(const void * a, const void * b) {
    return ((BagItem*)a)->item - ((BagItem*)b)->item;
}

void Trainer::sortPocket(ItemPocket pocket) {
    qsort(items[pocket], getPocketSize(pocket), sizeof(BagItem), sortcompare);
}

}
