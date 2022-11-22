/*
 * RPNG.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#pragma once
#ifndef PRNG_H_
#define PRNG_H_

namespace PokeLib {
class DLL_EXPORT PRNG {
 public:
  uint32_t seed;
  void prevSeed();
  void nextSeed();
  uint16_t prev();
  uint16_t current() const;
  uint16_t next();
};
}  // namespace PokeLib
#endif /* PRNG_H_ */
