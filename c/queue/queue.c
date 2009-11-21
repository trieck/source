/*
 * QUEUE.C : Generalized FIFO queue of pointers
 *
 * Copyright(c) 2002, Thomas A. Rieck, All Rights Reserved
 *
 */

#include <stdlib.h>
#include "queue.h"

/*
 * allocate a queue
 *
 */
struct queue* qalloc() {
	struct queue *q = (struct queue*)malloc(sizeof(struct queue));
	q->head = 0;
	return q;
}

/*
 * put an item on the queue
 *
 */
void qput(struct queue *q, void *pv)
{
	struct node *N, *prev;
	N = (struct node*)malloc(sizeof(struct node));
	N->data = pv;

	if (q->head) {
		prev = q->head->prev;
		prev->next = q->head->prev = N;

		N->prev = prev;
		N->next = q->head;
		if (q->head->next == q->head) q->head->next = N;
	} else {
		q->head = N->prev = N->next = N;
	}
}

/*
 * get an item off the queue
 *
 */
void *qget(struct queue *q)
{
	struct node *head, *next, *prev;
	void *pv;

	if (q->head == 0)
		return 0;

	pv = q->head->data;

	head = q->head;
	prev = q->head->prev;
	next = q->head->next;

	if (head == prev && prev == next) {
		q->head = 0;
	} else {
		q->head = prev->next = next;
		q->head->prev = prev;
	}

	free(head);

	return pv;
}

/*
 * free a queue
 *
 */
void qfree(struct queue *q)
{
	struct node *head, *current, *next;

	head = current = q->head;

	while (current) {
		next = current->next;
		free(current);
		current = next;

		if (current == head)
			break;
	}

	free(q);
}
