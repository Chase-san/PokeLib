/*
 * Trainer.h
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 *
 *  Description: This file handles the editing of trainer data. This may be a bit complex
 *  since trainer data is split by the party data. As such no specific output file is needed.
 *
 *  This class also handles the item data. Since it fits it pretty nicely.
 *
 *  Just try the best to get it to be able to be put back into save in one piece.
 */

#ifndef __TRAINER_H_
#define __TRAINER_H_

namespace PokeLib {

class Save;

enum ItemPocket {
	ItemGeneral = 0,
	ItemKey = 1,
	ItemTM = 2,
	ItemMail = 3,
	ItemMedicine = 4,
	ItemBerry = 5,
	ItemBall = 6,
	ItemBattle = 7,
};

//4 byte structure
#pragma pack(push, 1)
struct BagItem {
	uint16_t item;
	uint16_t count;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Badge {
	unsigned int badge_1 : 1;
	unsigned int badge_2 : 1;
	unsigned int badge_3 : 1;
	unsigned int badge_4 : 1;
	unsigned int badge_5 : 1;
	unsigned int badge_6 : 1;
	unsigned int badge_7 : 1;
	unsigned int badge_8 : 1;
};
#pragma pack(pop)

class Trainer {
	poketext trainer;
	poketext rival;
	bool isFemale;
	BagItem**items;
	uint8_t type;
public:
	Trainer(const Save *sav);
	virtual ~Trainer();

	void saveInto(Save *sav);

	Badge badgeMain;
	Badge badgeAlt;

	//gets the badges
	Badge getBadges() const { return badgeMain; }
	//gets the alternate badges, if no alternate, gets the normal badges
	Badge getAltBadges() const { return badgeAlt; }

	//sets the badges
	void setBadges(Badge b) { badgeMain = b; }
	//sets the alternate badges, if no alternate, sets the normal badges
	void setAltBadges(Badge b) { badgeAlt = b; }

	widetext getName() const;
	void setName(const widetext text);
	void setName(const poketext text);

	widetext getRivalName() const;
	void setRivalName(const widetext text);
	void setRivalName(const poketext text);

	bool getFemale() const;
	void setFemale(bool female);

	uint8_t getPocketSize(ItemPocket pocket) const;
	uint8_t getPocketMaxSize(ItemPocket pocket) const;
	BagItem getItem(ItemPocket pocket,uint8_t slot) const;
	void setItem(ItemPocket pocket,uint8_t slot,BagItem item);
	void eraseItem(ItemPocket pocket,uint8_t slot);
	void sortPocket(ItemPocket pocket);
};

}

#endif /* __TRAINER_H_ */
