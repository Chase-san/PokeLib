/*
 * Save.cpp
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#include "internal.h"

namespace PokeLib {

uint32_t footerID[][2] = {
    {0xC0EC, 0x1E2CC},  // DP
    {0xCF18, 0x1F0FC},  // PLAT
    {0xF618, 0x21A00},  // HGSS
};

uint32_t blockID[][2] = {
    {0x0, 0xC100},  // DP
    {0x0, 0xCF2C},  // PLAT
    {0x0, 0xF700},  // HGSS
};

uint32_t footerSize[] = {
    0x14,  // DP
    0x14,  // PLAT
    0x10,  // HGSS
};

uint32_t blockSize[][2] = {
    {0xC100, 0x121E0},  // DP
    {0xCF2C, 0x121E4},  // PLAT
    {0xF628, 0x12310},  // HGSS
};

uint32_t partyStart[] = {
    0x98,  // DP
    0xA0,  // PLAT
    0x98,  // HGSS
};

uint32_t sigStart[] = {
    0x5904,   // DP
    0x5BA8,   // PLAT
    0x4538,   // HGSS
    0x1C100,  // BW
};

uint32_t sigSize[] = {
    0x600,
    0x600,
    0x600,
    0x600,
};

#pragma pack(push, 1)
struct FooterHGSS {
  uint32_t saveNum;
  uint32_t blockSize;
  uint32_t unknown0;
  uint16_t unknown1;
  uint16_t checksum;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FooterDPPt {
  uint32_t saveStorage;
  uint32_t saveGeneral;
  uint32_t blockSize;
  uint32_t unknown0;
  uint16_t unknown1;
  uint16_t checksum;
};
#pragma pack(pop)

union Footer {
  FooterHGSS HGSS;
  FooterDPPt DPPT;
};

uint32_t getBoxOffset(int box, SaveType t) {
  if (box < 1 || box > 18)
    return 0;
  if (t == HGSS)
    return (30 * (box - 1) * 0x88 + (box - 1) * 16);
  return (30 * (box - 1) * 0x88) + 4;
}

Save::Save(uint32_t size) {
  if (size == 0x40000 || size == 0x80000) {
    type = DP;
    format = RAW512KiB;
    if (size == 0x40000)
      format = RAW256KiB;
    data = (uint8_t *)malloc(size);
  }
}

Save::~Save() {
  free(data);
}

void Save::setSavePosition(SavePosition p) {
  if (getSaveFormat() == RAW256KiB)
    return;
  // BlockA (small block)
  bool sub = false;
  if (p == SaveSub)
    sub = true;
  Footer *tmp0 = (Footer *)&data[footerID[type][0]];
  Footer *tmp1 = (Footer *)&data[footerID[type][0] + 0x40000];
  BlockA = &data[blockID[type][0] + 0x40000];
  FooterA = (uint8_t *)tmp1;
  if (type < HGSS) {
    // we already have 1 assigned, so check for the other...
    if (tmp0->DPPT.saveGeneral > tmp1->DPPT.saveGeneral) {
      if (!sub) {
        FooterA = (uint8_t *)tmp0;
        BlockA = &data[blockID[type][0]];
      }
    } else if (sub) {
      FooterA = (uint8_t *)tmp0;
      BlockA = &data[blockID[type][0]];
    }
  } else {
    if (tmp0->HGSS.saveNum > tmp1->HGSS.saveNum) {
      if (!sub) {
        FooterA = (uint8_t *)tmp0;
        BlockA = &data[blockID[type][0]];
      }
    } else if (sub) {
      FooterA = (uint8_t *)tmp0;
      BlockA = &data[blockID[type][0]];
    }
  }

  // BlockB (large block)
  tmp0 = (Footer *)&data[footerID[type][1]];
  tmp1 = (Footer *)&data[footerID[type][1] + 0x40000];
  BlockB = &data[blockID[type][1] + 0x40000];
  FooterB = (uint8_t *)tmp1;
  if (type < HGSS) {
    // if(tmp1->DPPT.saveStorage > tmp0->DPPT.saveStorage) {
    // we already did the sub thing for the main block, this is just
    // getting the save block that block (sub or not), refers to
    if (((Footer *)FooterA)->DPPT.saveStorage == tmp0->DPPT.saveStorage) {
      FooterB = (uint8_t *)tmp0;
      BlockB = &data[blockID[type][1]];
    }
  } else {
    if (tmp0->HGSS.saveNum > tmp1->HGSS.saveNum) {
      if (!sub) {
        FooterB = (uint8_t *)tmp0;
        BlockB = &data[blockID[type][1]];
      }
    } else if (sub) {
      FooterB = (uint8_t *)tmp0;
      BlockB = &data[blockID[type][1]];
    }
  }
}

bool Save::parseRawSave() {
  // just testing these work because chances of having a
  // 32 bit integer at one of these locations in the file
  // randomly equal one of these numbers is astronomical
  if (*((uint32_t *)&data[0xC0F4]) == blockSize[DP][0]) {  // DP
    type = DP;
  } else if (*((uint32_t *)&data[0xCF20]) == blockSize[PLAT][0]) {  // Plat
    type = PLAT;
  } else if (*((uint32_t *)(&data[0xF61C])) == blockSize[HGSS][0]) {  // HGSS
    type = HGSS;
  } else {
    return false;
  }

  if (getSaveFormat() == RAW256KiB) {
    BlockA = &data[blockID[type][0]];
    FooterA = &data[footerID[type][0]];
    // set it to the same thing
    BlockB = &data[blockID[type][0]];
    FooterB = &data[footerID[type][0]];
    return true;
  }

  // This sets the main and secondary saves for RAW512KiB
  setSavePosition(SaveMain);

  return true;
}

uint16_t Save::calcBlockAChecksum() const {
  return Toolkit::crc16(BlockA, blockSize[type][0] - footerSize[type]);
}

uint16_t Save::calcBlockBChecksum() const {
  return Toolkit::crc16(BlockB, blockSize[type][1] - footerSize[type]);
}

void Save::repairBlockAChecksum() {
  if (type != HGSS) {
    ((Footer *)FooterA)->DPPT.checksum = calcBlockAChecksum();
  } else {
    ((Footer *)FooterA)->HGSS.checksum = calcBlockAChecksum();
  }
}

void Save::repairBlockBChecksum() {
  if (type != HGSS) {
    ((Footer *)FooterB)->DPPT.checksum = calcBlockBChecksum();
  } else {
    ((Footer *)FooterB)->HGSS.checksum = calcBlockBChecksum();
  }
}

// Box functions
Box *Save::getBox(uint8_t n) const {
  if (n < 1 || n > 18)
    return NULL;
  Box *b = new Box();
  int offset = getBoxOffset(n, getSaveType());
  uint8_t *ptr = &BlockB[offset];
  memcpy(b->data, ptr, 136 * 30);

  // DPPt and HGSS are both 40 bytes long.
  offset = getBoxOffset(18, getSaveType()) + 30 * 0x88 + 40 * (n - 1);
  if (getSaveType() == HGSS)
    offset += 16 + 8;
  // Each box name is 22 bytes long (11 uint16 characters)
  b->setName(PokeText::convertFrom(
      PokeText::toPoketext((uint16_t *)&BlockB[offset], 11)));

  return b;
}

void Save::setBox(uint8_t n, Box *b) {
  int offset = getBoxOffset(n, getSaveType());
  uint8_t *ptr = &BlockB[offset];
  memcpy(ptr, b->data, 136 * 30);

  // DPPt and HGSS are both 40 bytes long.
  offset = getBoxOffset(18, getSaveType()) + 30 * 0x88 + 40 * (n - 1);
  if (getSaveType() == HGSS)
    offset += 16 + 8;
  // set it correctly now
  poketext tmp = PokeText::convertTo(b->getName());
  uint16_t *name = (uint16_t *)&BlockB[offset];
  for (uint16_t i = 0; i < tmp.length() && i < 11; ++i) {
    name[i] = tmp[i];
  }
}

Party *Save::getParty() const {
  Party *p = new Party();
  uint8_t *ptr = &BlockA[partyStart[getSaveType()]];
  memcpy(p->data, ptr, 0xEC * 6);
  return p;
}

void Save::setParty(Party *p) {
  uint8_t *ptr = &BlockA[partyStart[getSaveType()]];
  p->sort();
  memcpy(ptr, p->data, 0xEC * 6);
  //*((uint32_t*)&BlockA[partyStart[getSaveType()]-4]) = p->count();
  *((uint32_t *)ptr - 4) = p->count();
}

Trainer *Save::getTrainer() const {
  return new Trainer(this);
}
void Save::setTrainer(Trainer *p) {
  p->saveInto(this);
}

uint8_t *Save::getSignatureRaw() const {
  int type = getSaveType();
  uint8_t *block = new uint8_t[sigSize[type]];
  uint8_t *ptr = &BlockA[sigStart[type]];
  memcpy(block, ptr, sigSize[type]);
  return block;
}

void Save::setSignatureRaw(uint8_t *raw) {
  uint8_t *block = new uint8_t[sigSize[type]];
  uint8_t *ptr = &BlockA[sigStart[type]];
  memcpy(ptr, block, sigSize[type]);
}

}  // namespace PokeLib
