/*
 * Party.cpp
 *
 *  Created on: Dec 4, 2009
 *      Author: Chase
 */

#include "internal.h"

namespace PokeLib {

Party::Party() {
    data = (uint8_t*)malloc(6*236);
}

Party::~Party() {
    free(data);
}

Pokemon Party::getPokemon(uint8_t slot) const {
    if(slot < 1 || slot > 6) return *((Pokemon*)NULL);
    uint8_t *ptr = &data[236*(slot-1)];
    Pokemon out(ptr,236);
    out.decrypt();
    return out;
}

void Party::setPokemon(uint8_t slot, const Pokemon &pkm) {
    if(slot < 1 || slot > 6) return;
    if(&pkm == NULL) { //erase the slot
        erasePokemon(slot);
        return;
    }
    uint8_t *ptr = &data[236*(slot-1)];
    Pokemon p(pkm);
    p.encrypt();
    memcpy(ptr, p.pkm->raw, 236);
    /* The other option.. I determined decryption to be more computationally
    expensive then just making a temporary copy. 236 bytes is not much. */
    /*
    pkm.encrypt();
    memcpy(ptr, pkm.pkm->raw, 236);
    pkm.decrypt();
    */
}

void Party::erasePokemon(uint8_t slot) {
    if(slot < 1 || slot > 6) return;
    uint8_t *ptr = &data[236*(slot-1)];
    memset(ptr, 0, 236);
    //do not need to shuffle all zeros
    Toolkit::crypt(ptr);
}

inline int sortcompare(const void * a, const void * b) {
    return ((uint8_t*)a)[4] - ((uint8_t*)b)[4];
}

void Party::sort() {
    //TODO: THIS IS A HACKY HACKY HACKY HACKY HACKY HACK!!!
    for(uint8_t i=1; i<6; ++i) {
        Pokemon tmp = getPokemon(i);
        if(tmp.pkm->pkm.species == 0) {
            data[236*(i-1)+4] = 0xFF;
        } else {
            data[236*(i-1)+4] = i;
        }
    }

    //By assigning values to the filled slots into the margin space in the
    //pkm file between the PID and the checksum, I do not have to decrypt
    //them again, and I can just use this built in quick sorting function.
    qsort(data, 6, 236, sortcompare);

    //Now go and reset all those numbers to zero, and were done! No fuss. :)
    for(uint8_t i=1; i<6; ++i) {
        data[236*(i-1)+4] = 0;
    }
}

uint8_t Party::count() {
    uint8_t out = 0;
    for(uint8_t i=1; i<=6; ++i) {
        Pokemon tmp = getPokemon(i);
        if(tmp.pkm->pkm.species != 0) {
            ++out;
        }
    }
    return out;
}

}
