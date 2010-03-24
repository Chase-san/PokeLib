/*
 * PokeText.h
 *
 *  Created on: Dec 3, 2009
 *      Author: Chase
 */

#pragma once
#ifndef POKETEXT_H_
#define POKETEXT_H_

namespace PokeLib {

typedef std::basic_string<uint16_t> poketext;
typedef std::basic_string<wchar_t> widetext;

/**
 * Warning: Multibyte conversion!
 */
class PokeText {
public:
	//these convert to and from poketext
	static widetext convertFrom(const poketext &text);
	static poketext convertTo(const widetext &text);
	//this converts it from native Pokemon format to our poketext
	static poketext toPoketext(const uint16_t* arr, size_t length);
	//these convert it from native c strings to widetext
	static widetext toWidetext(const wchar_t* wc, size_t length);
	static widetext toWidetext(const char* mb, size_t length);
};

}

#endif /* POKETEXT_H_ */
