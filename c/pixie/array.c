/*
 * ARRAY.C
 *
 * Dynamic array
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <string.h>
#include <stdlib.h>
#include "pixie.h"
#include "array.h"
#include "xmalloc.h"

#define NALLOC 10

#ifdef max
#undef max
#endif							/* max */

#ifdef min
#undef min
#endif							/* min */

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

static void range_check(Array * array, unsigned n);

/* allocate an array */
Array *array_alloc(unsigned size)
{
	Array *array = (Array *) xmalloc(sizeof(Array));
	array->alloced = max(NALLOC, size);
	array->v = (Symbol **) xmalloc(sizeof(Symbol *) * array->alloced);
	array->size = 0;
	return array;
}

/* copy an array */
Array *array_copy(Array * src)
{
	unsigned i;
	Array *dest = array_alloc(src->size);
	for (i = 0; i < src->size; i++) {
		dest->v[i] = symcopy(src->v[i]);
	}
	dest->size = src->size;
	return dest;
}

/* free an array */
void array_free(Array * array)
{
	unsigned i;
	if (array) {
		for (i = 0; i < array->size; i++) {
			symfree(array->v[i]);
		}
		xfree(array->v);
		xfree(array);
	}
}

/* push element onto back of array */
void array_push(Array * array, Symbol * sym)
{
	range_check(array, array->size + 1);
	array->v[array->size++] = symcopy(sym);
}

/* copy elements from source array onto back of dest array */
void array_vpush(Array * dest, Array * src)
{
	unsigned i;
	for (i = 0; i < src->size; i++) {
		array_push(dest, src->v[i]);
	}
}

/* pop element from back of array */
Symbol *array_pop(Array * array)
{
	Symbol *sym;

	if (array->size == 0) {
		error("unable to pop empty array.");
		return 0;
	}

	array->size--;

	sym = symcopy(array->v[array->size]);

	symfree(array->v[array->size]);

	return sym;
}

/* get element at index */
Symbol *array_elementat(Array * array, unsigned index)
{
	if (index >= array->size) {
		error("array index out of range.");
		return 0;
	}

	return array->v[index];
}

void array_setelementat(Array * array, unsigned index, Symbol * fld)
{
	if (index >= array->size) {
		error("array index out of range.");
	}

	symfree(array->v[index]);
	array->v[index] = symcopy(fld);
}

/* reverse elements in array */
void array_reverse(Array * array)
{
	unsigned i, j;
	Symbol *t;

	if (array->size == 0)
		return;					/* nothing to do */

	for (i = 0, j = array->size - 1; i != j; i++, j--) {
		t = array->v[i];
		array->v[i] = array->v[j];
		array->v[j] = t;
	}
}

/* copy elements from source array onto front of destination array */
void array_vunshift(Array * dest, Array * src)
{
	int i;
	for (i = src->size - 1; i >= 0; i--) {
		array_unshift(dest, src->v[i]);
	}
}

/* remove element from front of array */
Symbol *array_shift(Array * array)
{
	unsigned i;
	Symbol *sym;

	if (array->size == 0) {
		error("unable to shift empty array.");
		return 0;
	}

	sym = symcopy(array->v[0]);
	symfree(array->v[0]);

	for (i = 1; i < array->size; i++) {
		array->v[i - 1] = array->v[i];
	}

	array->size--;

	return sym;
}

/* front insertion */
void array_unshift(Array * array, Symbol * sym)
{
	int i;

	range_check(array, array->size + 1);

	for (i = array->size; i > 0; i--) {
		array->v[i] = array->v[i - 1];
	}

	array->v[0] = symcopy(sym);

	array->size++;
}

/* ensure capacity */
void range_check(Array * array, unsigned n)
{
	while (array->alloced < n) {
		array->v = (Symbol **) xrealloc(array->v,
										(array->alloced * 2) *
										sizeof(Symbol *));
		array->alloced = array->alloced * 2;
	}
}
