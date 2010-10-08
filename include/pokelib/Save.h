/*
 * Save.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 *
 *  Description: This file handles the higher level save management, such as
 *  the creation, destruction of Box, Trainer and Pokedex data. It handles
 *  both blocks, but only edits one of the saves within a save file at a time.
 *
 *  It however handles the full 512 KiB file.
 *
 *  Functions should be created for the loading and saving of boxes, trainer data,
 *  and pokedex data. All loading functions create a new object and COPY the data
 *  from the save data to the given structure which is to handle the decoding and
 *  recoding for editing the data and for re-integration into the save.
 *
 *  Currently it can support raw 512 KiB or raw 256 KiB save types, however with
 *  use of an automated converted, more types could be supported.
 */

#ifndef ___SAVE_H_
#define ___SAVE_H_

namespace PokeLib {

//Black and White are not yet fully supported

enum SaveType {
	DP=0, PLAT=1, HGSS=2, BW=3
};
enum SaveFormat {
	RAW256KiB=256, RAW512KiB=512
};
enum SavePosition {
	SaveMain, SaveSub
};

class Box;
class Party;
class Trainer;
class Pokedex;

class Save {
	//these are internal for safety reasons
	SaveType type;
	SaveFormat format;
	SavePosition pos;

	uint8_t* FooterA;
	uint8_t* FooterB;
public:
	Save(uint32_t size);
	virtual ~Save();

	uint8_t* data;
	uint8_t* BlockA;
	uint8_t* BlockB;

	//Basic functions
	bool parseRawSave();
	uint16_t calcBlockAChecksum() const;
	uint16_t calcBlockBChecksum() const;
	void repairBlockAChecksum();
	void repairBlockBChecksum();

	//Informative functions
	inline SaveType getSaveType() const { return type; }
	inline SaveFormat getSaveFormat() const { return format; }
	inline SavePosition getSavePosition() const { return pos; }
	void setSavePosition(SavePosition p);

	//Box functions
	Box *getBox(uint8_t n) const;
	void setBox(uint8_t n, Box *b);

	//Party functions
	Party *getParty() const;
	void setParty(Party *p);

	//Trainer
	Trainer *getTrainer() const;
	void setTrainer(Trainer *p);
	
	//Signature
	//http://www.projectpokemon.org/wiki/Trainer_Card_Signature
	//0x600 bytes long, 1 bpp, 192x64
	//8x8 blocks
	uint8_t * getSignatureRaw() const;
	void setSignatureRaw(uint8_t * raw);

	//Pokedex
	Pokedex *getPokedex() const;
	void setPokedex(Pokedex *p);
};

}

#endif /* ___SAVE_H_ */
