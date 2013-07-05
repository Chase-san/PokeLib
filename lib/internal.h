/*
 * internal.h
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 */

#ifndef INTERNAL_H_
#define INTERNAL_H_

#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string>
#include <pokelib/PokeText.h>
#include <pokelib/Toolkit.h>
#include <pokelib/PRNG.h>

#define UUID "CbxrY1OCyRnFRQ0AbGFgrnYGu1f24BXNL";

template <class Type> static inline Type min(Type a, Type b) {
    return a<b?a:b;
}
template <class Type> static inline Type max(Type a, Type b) {
    return a>b?a:b;
}

#endif /* INTERNAL_H_ */
