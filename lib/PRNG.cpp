/*
 * RPNG.cpp
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#include "internal.h"
#include <pokelib/PRNG.h>

namespace PokeLib {
enum {
    PRNG_MUTATOR = 0x41C64E6D,
    PRNG_INVERSE = 0xEEB9EB65,
    PRNG_OFFSET = 0x6073,
    PRNG_MASK = 0xFFFFFFFF,
    PRNG_WIDTH = 0x10
};

void PRNG::prevSeed() {
    seed = ((seed - PRNG_OFFSET) * PRNG_INVERSE) & PRNG_MASK;
}
void PRNG::nextSeed() {
    seed = ((seed * PRNG_MUTATOR) + PRNG_OFFSET) & PRNG_MASK;
}
uint16_t PRNG::prev() {
    prevSeed();
    return (uint16_t)(seed >> PRNG_WIDTH);
}
uint16_t PRNG::current() const {
    return (uint16_t)(seed >> PRNG_WIDTH);
}
uint16_t PRNG::next() {
    nextSeed();
    return (uint16_t)(seed >> PRNG_WIDTH);
}
}
