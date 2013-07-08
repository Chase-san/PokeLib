/*
 * pokelib.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#pragma once
#ifndef _____POKE_LIB_H_____
#define _____POKE_LIB_H_____

// Configuration
#if defined(_MSC_VER)
#define DLL_EXPORT __declspec(dllexport)
// class 'A<T>' needs to have dll-interface to be used by clients of class 'B'
#pragma warning(disable: 4251)
#elif defined(__GCC__)
// GCC visibility
#define DLL_EXPORT __attribute__((visibility("default")))
#else
// Use an empty macro for everything we don't know about
#define DLL_EXPORT
#endif

#include <stdint.h>
#include <string>
#include <pokelib/PRNG.h>
#include <pokelib/PokeText.h>
#include <pokelib/Toolkit.h>
#include <pokelib/Pokemon.h>
#include <pokelib/Party.h>
#include <pokelib/Box.h>
#include <pokelib/Save.h>
#include <pokelib/Trainer.h>
#include <pokelib/Pokedex.h>

#endif //_____POKE_LIB_H_____
