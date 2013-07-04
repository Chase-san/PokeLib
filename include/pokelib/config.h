/*
 * Trainer.h
 *
 *  Created on: Jul 3, 2013
 *      Author: Nicholas Corgan
 *
 *  Description: This file contains the macro for enabling DLL export with MSVC while ignoring it
 *  with GCC.
 */
 
#ifndef __POKELIB_CONFIG_H
#define __POKELIB_CONFIG_H
 
#ifdef _MSC_VER
    #define DLL_EXPORT __declspec(dllexport)
    #pragma warning(disable: 4251) // class 'A<T>' needs to have dll-interface to be used by clients of class 'B'
#else
    #define DLL_EXPORT __attribute__((visibility("default")))
#endif
 
#endif /* _POKELIB_CONFIG_H */