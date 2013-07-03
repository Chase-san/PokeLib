/*
 * Pokemon.h
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 *
 *  Description: This handles the editing of pokemon, and all their stats.
 *
 *  Should allow input and output of raw PKM structure.
 */

#pragma once
#ifndef POKEMON_H_
#define POKEMON_H_

namespace PokeLib {

#pragma pack(push, 1)
typedef struct {
	//Byte 1
	unsigned int sinnoh_champ	: 1;
	unsigned int ability		: 1;
	unsigned int great_ability	: 1;
	unsigned int double_ability	: 1;
	unsigned int multi_ability	: 1;
	unsigned int pair_ability	: 1;
	unsigned int world_ability	: 1;
	unsigned int alert	: 1;
	//Byte 2
	unsigned int shock	: 1;
	unsigned int downcast	: 1;
	unsigned int careless	: 1;
	unsigned int relax	: 1;
	unsigned int snooze	: 1;
	unsigned int smile	: 1;
	unsigned int gorgeous	: 1;
	unsigned int royal	: 1;
	//Byte 3
	unsigned int gorgeous_royal	: 1;
	unsigned int footprint	: 1;
	unsigned int record	: 1;
	unsigned int history	: 1;
	unsigned int legend	: 1;
	unsigned int red	: 1;
	unsigned int green	: 1;
	unsigned int blue	: 1;
	//Byte 4
	unsigned int festival	: 1;
	unsigned int carnival	: 1;
	unsigned int classic	: 1;
	unsigned int premier	: 1;
	unsigned int UNKNOWN	: 4;
} pRibbonSinnohA;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	//Byte1
	unsigned int cool_normal	: 1;
	unsigned int cool_super	: 1;
	unsigned int cool_hyper	: 1;
	unsigned int cool_master	: 1;
	unsigned int beauty_normal	: 1;
	unsigned int beauty_super	: 1;
	unsigned int beauty_hyper	: 1;
	unsigned int beauty_master	: 1;
	//Byte2
	unsigned int cute_normal	: 1;
	unsigned int cute_super	: 1;
	unsigned int cute_hyper	: 1;
	unsigned int cute_master	: 1;
	unsigned int smart_normal	: 1;
	unsigned int smart_super	: 1;
	unsigned int smart_hyper	: 1;
	unsigned int smart_master	: 1;
	//Byte3+4
	unsigned int tough_normal	: 1;
	unsigned int tough_super	: 1;
	unsigned int tough_hyper	: 1;
	unsigned int tough_master	: 1;
	unsigned int UNKNOWN	: 12;
} pRibbonSinnohB;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	//Byte1
	unsigned int cool_normal	: 1;
	unsigned int cool_super	: 1;
	unsigned int cool_hyper	: 1;
	unsigned int cool_master	: 1;
	unsigned int beauty_normal	: 1;
	unsigned int beauty_super	: 1;
	unsigned int beauty_hyper	: 1;
	unsigned int beauty_master	: 1;
	//Byte2
	unsigned int cute_normal	: 1;
	unsigned int cute_super	: 1;
	unsigned int cute_hyper	: 1;
	unsigned int cute_master	: 1;
	unsigned int smart_normal	: 1;
	unsigned int smart_super	: 1;
	unsigned int smart_hyper	: 1;
	unsigned int smart_master	: 1;
	//Byte3
	unsigned int tough_normal	: 1;
	unsigned int tough_super	: 1;
	unsigned int tough_hyper	: 1;
	unsigned int tough_master	: 1;
	unsigned int champion	: 1;
	unsigned int winning	: 1;
	unsigned int victory	: 1;
	unsigned int artist	: 1;
	//Byte4
	unsigned int effort	: 1;
	unsigned int marine	: 1;
	unsigned int land	: 1;
	unsigned int sky	: 1;
	unsigned int country	: 1;
	unsigned int national	: 1;
	unsigned int earth	: 1;
	unsigned int world	: 1;
} pRibbonHoenn;
#pragma pack(pop)

#pragma pack(push, 1)
//Be careful if you choose to edit this, its packed!
struct pPKM {
	uint32_t pid;
	uint8_t unknown_x04;
	uint8_t unknown_x05;
	uint16_t checksum;

	//BlockA
	uint16_t species;
	uint16_t held_item;
	uint16_t ot_id;
	uint16_t ot_sid;
	uint32_t exp;
	uint8_t  friendship;
	uint8_t  ability;
	uint8_t  markings;
	uint8_t  country; //16
	uint8_t  ev_hp;
	uint8_t  ev_atk;
	uint8_t  ev_def;
	uint8_t  ev_spd;
	uint8_t  ev_satk;
	uint8_t  ev_sdef;
	uint8_t  contest_cool;
	uint8_t  contest_beauty;
	uint8_t  contest_cute;
	uint8_t  contest_smart;
	uint8_t  contest_tough;
	uint8_t  contest_sheen;
	pRibbonSinnohA ribbonSinnohA;

	//BlockB
	uint16_t move[4]; //8
	uint8_t  movePP[4]; //4
	uint8_t  movePPUP[4]; //4
	unsigned int iv_hp   : 5;
	unsigned int iv_atk  : 5;
	unsigned int iv_def  : 5;
	unsigned int iv_spd  : 5;
	unsigned int iv_satk : 5;
	unsigned int iv_sdef : 5;
	bool isEgg : 1;
	bool isNicknamed : 1;
	pRibbonHoenn ribbonHoenn;
	bool isFatefulEncounter : 1;
	bool isFemale : 1;
	bool isGenderless : 1;
	unsigned int form : 5; //25
	uint8_t shining_leaf; //00XAAAAA, X is crown bit, A are individual leaf bits
	uint8_t unknown_x42; //27
	uint8_t unknown_x43;	//28
	uint16_t eggLoc_Plat; //30
	uint16_t metLoc_Plat; //32 //46, 47

	//BlockC
	uint16_t nickname[11]; //2*11 = 22
	uint16_t hometown; //24
	pRibbonSinnohB ribbonSinnohB;
	uint8_t unknown_x64;
	uint8_t unknown_x65;
	uint8_t unknown_x66;
	uint8_t unknown_x67;

	//BlockD
	 //8*2 = 16, sad your name is shorter then any of your pokemons
	uint16_t ot_name[8];
	uint8_t  eggDate[3];
	uint8_t  metDate[3];
	uint16_t eggLoc_DP;
	uint16_t metLoc_DP;
	uint8_t  pokerus;
	uint8_t  pokeball;
	int metLevel : 7;
	bool ot_female : 1;
	uint8_t encounterType;
	uint8_t pokeball_HGSS;
	uint8_t unknown_x87;

	//Party Data
	//uint8_t partyData[100];
	//x88
	int eff_sleep : 3;
	int eff_poison : 1;
	int eff_burn : 1;
	int eff_frozen : 1;
	int eff_paralyze : 1;
	int eff_toxic : 1;
	uint8_t unknown_x89; //2, Max (Flags?) 0xF0
	uint8_t unknown_x8A; //3
	uint8_t unknown_x8B; //4
	uint8_t battle_level; //5
	uint8_t battle_capsule;//6
	uint16_t battle_hp;    //8
	uint16_t battle_max_hp;//10
	uint16_t battle_atk;   //12
	uint16_t battle_def;   //14
	uint16_t battle_spd;   //16
	uint16_t battle_satk;  //18
	uint16_t battle_sdef;  //20
	uint8_t battle_unknown_x9C_xD3[56]; //76
	uint8_t battle_seal_coord[24]; //100
};
#pragma pack(pop)

#pragma pack(push, 1)
struct pBlock {
	uint32_t pid;
	char unknown[2];
	uint16_t checksum;
	uint8_t block[4][32];
	uint8_t partyData[100];
};
#pragma pack(pop)

union PKM {
	uint8_t	raw[236];
	pPKM	pkm;	//0x88 + 100
	pBlock	block;	//0x88 + 100
};

enum Gender {
	MALE=0,FEMALE=1,GENDERLESS=3
};

class Pokemon {
public:
	Pokemon();
	Pokemon(uint8_t* data, uint8_t length);
	Pokemon(const Pokemon &p);
	virtual ~Pokemon();
	PKM *pkm;

	inline pPKM* getStructure() { return &pkm->pkm; }

	void set(const Pokemon &p);

	widetext getNickname() const;
	widetext getTrainerName() const;
	void updateBattleStats();
	void setNickname(const widetext &name);
	void setTrainerName(const widetext &name);
	void setNickname(const char *name, size_t length);
	void setTrainerName(const char *name, size_t length);
	//Please double check these three methods!
	uint8_t getLevel() const;
	uint32_t getExpToNextLevel() const;
	void setLevel(uint8_t level);
	//End check of methods
	uint8_t getGenderValue() const;
	uint8_t getNatureValue() const;
	Gender getPersonalityGender() const;
	uint8_t getHiddenPowerType() const;
	uint8_t getHiddenPowerAttack() const;
	bool isShiny() const;
	//Species specific
	//Set unown form support, use a char 'A' etc to specify. Support '!' and '?' aswell.
	void setUnownForm(char f);
	//Some basic utility functions! These are called automatically by Box and Party classes.
	//These deshuffle+decrypt, and shuffle+encrypt respectively
	void decrypt();
	void encrypt();
};

}

#endif /* POKEMON_H_ */
