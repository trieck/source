/*
 * INVERTER.H
 * 
 * Inverted list of term locations in memory
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __INVERTER_H__
#define __INVERTER_H__

/* inverter structure */
struct Inverter {
	uint32_t count;		/* number of terms */
	uint32_t size;		/* size of internal hash table */
	uint32_t maxpool;	/* maximum ammount of pool memory allowed */
	char **record;		/* array of pointers to document lists */
	char *pool;		/* memory allocation pool */
	char *ppool;		/* pointer to next available byte */
};

typedef struct Inverter Inverter_t;

Inverter_t *inverter_create(void);
void inverter_insert(Inverter_t * v, const char *term, uint32_t docid);
void inverter_free(Inverter_t * v);
int inverter_isfull(Inverter_t * v);
int inverter_write(Inverter_t * v, FILE * fp);

#endif				/* __INVERTER_H__ */
