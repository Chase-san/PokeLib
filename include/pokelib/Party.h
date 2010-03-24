/*
 * Party.h
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 *
 *  Description: This header file will handle the loading and saving of pokemon
 *  into the party. This includes calling the encrypting and shuffling.
 *
 *  As well as provide a unified input/output format for the party. Having all the pokemon in the party
 *  unshuffled and decrypted when output into this byte structure.
 */

#pragma once
#ifndef PARTY_H_
#define PARTY_H_

namespace PokeLib {

class Party {
public:
	Party();
	virtual ~Party();
	/* Size of the data is 1416 [6*236] bytes. */
	uint8_t *data;

	Pokemon getPokemon(uint8_t slot) const;
	void setPokemon(uint8_t slot, const Pokemon &pkm);
	//Sorts all pokemon to the top of the party
	void erasePokemon(uint8_t slot);
	uint8_t count();
	void sort();
};

}

#endif /* PARTY_H_ */
