/*
 * QUEUE.H : Generalized FIFO queue of pointers
 *
 * Copyright(c) 2002, Thomas A. Rieck, All Rights Reserved
 *
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

/*
 * node structure
 *
 */
struct node {
    void *data;
    struct node *prev, *next;
};

/*
 * queue structure
 *
 */
struct queue {
    struct node *head;
};

/*
 * queue interface
 *
 */
extern struct queue* qalloc();
extern void qfree(struct queue *q);
extern void qput(struct queue *q, void *pv);
extern void* qget(struct queue *q);
extern int qempty(struct queue *q);

#endif /* __QUEUE_H__ */