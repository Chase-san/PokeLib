/*
 * Box.cpp
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#include "internal.h"

namespace PokeLib {

Box::Box() {
    data = (uint8_t*)malloc(136*30);
}

Box::~Box() {
    free(data);
}


Pokemon Box::getPokemon(uint8_t slot) const {
    if(slot < 1 || slot > 30) return *((Pokemon*)NULL);
    uint8_t *ptr = &data[136*(slot-1)];
    Pokemon out(ptr,136);
    out.decrypt();
    out.updateBattleStats();
    return out;
}

widetext Box::getName() const {
    return name;
}

void Box::setName(const widetext &text) {
    name.clear();
    name = text;
}

void Box::setPokemon(uint8_t slot, const Pokemon &pkm) {
    if(slot < 1 || slot > 30) return;
    if(&pkm == NULL) { //erase the slot
        erasePokemon(slot);
        return;
    }
    uint8_t *ptr = &data[136*(slot-1)];
    Pokemon p(pkm);
    p.encrypt();
    memcpy(ptr, p.pkm->raw, 136);
    /* The other option.. I determined decryption to be more computationally
    expensive then just making a temporary copy. 236 bytes is not much. */
    /*
    pkm.encrypt();
    memcpy(ptr, pkm.pkm->raw, 236);
    pkm.decrypt();
    */
}

void Box::erasePokemon(uint8_t slot) {
    if(slot < 1 || slot > 30) return;
    uint8_t *ptr = &data[136*(slot-1)];
    memset(ptr, 0, 136);
    //do not need to shuffle all zeros
    Toolkit::crypt(ptr);
}

uint8_t Box::count() const {
    uint8_t out = 0;
    for(uint8_t i=1; i<=30; ++i) {
        Pokemon tmp = getPokemon(i);
        if(tmp.pkm->pkm.species != 0) {
            ++out;
        }
    }
    return out;
}

}
