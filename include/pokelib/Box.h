/*
 * Box.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 *
 *  Description: This header file will handle the loading and saving of pokemon
 *  into their boxes. This includes calling the encrypting and shuffling.
 *
 *  As well as provide a unified input/output format the boxes. Having all the pokemon in the box
 *  unshuffled and decrypted when output into this byte structure.
 *
 */

#pragma once
#ifndef BOX_H_
#define BOX_H_

namespace PokeLib {
class Box {
	widetext name;
	uint8_t wallpaper;
public:
	Box();
	virtual ~Box();
	uint8_t *data;

	widetext getName() const;
	void setName(const widetext &text);

	uint8_t getWallpaper() const { return wallpaper; }
	void setWallpaper(uint8_t numb) { wallpaper = numb; }

	Pokemon getPokemon(uint8_t slot) const;
	void setPokemon(uint8_t slot, const Pokemon &pkm);
	void erasePokemon(uint8_t slot);

	uint8_t count() const;
};

}

#endif /* BOX_H_ */
