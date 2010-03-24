/*
 * Pokedex.h
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 *
 *  Description: This handles the editing of pokedex data, and all things there in.
 */

#pragma once
#ifndef POKEDEX_H_
#define POKEDEX_H_

namespace PokeLib {
	class Pokedex {
	public:
		Pokedex(Save *sav);
		virtual ~Pokedex();

		void saveInto(Save *sav);

		bool hasSeen(int num) { return false; }
		bool hasCaught(int num) { return false; }
		bool hasGender(int num) { return false; }
	};
}

#endif /* POKEDEX_H_ */
