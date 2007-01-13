/*
 * ARRAY.H
 *
 * Dynamic array
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

Array *array_alloc(unsigned size);
Array *array_copy(Array * array);
void array_free(Array * array);
void array_push(Array * array, Symbol * fld);
void array_vpush(Array * dest, Array * src);
Symbol *array_elementat(Array * array, unsigned index);
void array_setelementat(Array * array, unsigned index, Symbol * fld);
void array_reverse(Array * array);
Symbol *array_shift(Array * array);
Symbol *array_pop(Array * array);
void array_unshift(Array * array, Symbol * fld);
void array_vunshift(Array * dest, Array * src);

#endif							/* __ARRAY_H__ */
