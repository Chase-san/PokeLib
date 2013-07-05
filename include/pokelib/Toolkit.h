/*
 * Toolkit.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#pragma once
#ifndef TOOLKIT_H_
#define TOOLKIT_H_

#include <vector>

namespace PokeLib {

//this is a prototype
class PRNG;

union bIV {
public:
    inline void set(int _hp, int _atk, int _def, int _spd, int _satk, int _sdef) {
        hp = _hp;
        atk = _atk;
        def = _def;
        spd = _spd;
        satk = _satk;
        sdef = _sdef;
    }
    uint32_t block;
#pragma pack(push, 1)
    struct {
        unsigned int hp   : 5;
        unsigned int atk  : 5;
        unsigned int def  : 5;
        unsigned int spd  : 5;
        unsigned int satk : 5;
        unsigned int sdef : 5;
        unsigned int EXTRA : 2;
    };
#pragma pack(pop)
};

class DLL_EXPORT Toolkit {
private:
    static uint8_t* _shuffle(uint8_t*, bool);
    static uint8_t* _crypt(uint8_t*, bool);
public:
    static uint16_t crc16(uint8_t*, uint32_t);
    static uint16_t checksum(uint16_t*, uint32_t);
    static uint8_t* shuffle(uint8_t*);
    static uint8_t* unshuffle(uint8_t*);
    static uint8_t* crypt(uint8_t*);
    static bIV calcIVsfromSeed(uint32_t seed);
    static bIV calcIVsfromSeed(PRNG &prng);
    static std::vector<bIV> calcIVsfromPID(uint32_t pid);
    static std::vector<uint32_t> calcPIDsfromIVs(bIV &ivs);
    //static uint32_t calcPIDfromIVs(bIV &ivs);
    //static uint32_t calcPIDfromIVs(uint8_t hp,uint8_t atk,uint8_t def,uint8_t speed,uint8_t satk,uint8_t sdef);
};

}

#endif /* TOOLKIT_H_ */
