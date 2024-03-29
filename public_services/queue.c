#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

queue_t
queue_create(int16_t size)
{
    queue_t qp = malloc(sizeof(struct QUEUE));
    if (qp == NULL)
        return NULL;

    size = (size > QUEUE_MAX_SIZE)? QUEUE_MAX_SIZE : size;
    qp->data = malloc((size+1) * sizeof(elem_t));
    if (qp->data == NULL)
        return NULL;

    qp->front = qp->rear = 0;
    qp->size = size+1;

    return qp;
}

int16_t
queue_is_empty(queue_t q)
{
    return (q->front == q->rear);
}

int16_t
queue_is_full(queue_t q)
{
    return ((q->rear+1) % q->size == q->front);
}

queue_state_t
queue_en(queue_t q, elem_t d)
{
    if (queue_is_full(q))
        return QUEUE_FULL;
    q->data[q->rear] = d;
    q->rear = (q->rear+1) % q->size;

    return QUEUE_OK;
}

queue_state_t
queue_de(queue_t q, elem_t *d)
{
    if (queue_is_empty(q))
        return QUEUE_EMPTY;

    *d = q->data[q->front];
    q->front = (q->front+1) % q->size;

    return QUEUE_OK;
}

int16_t
queue_length(queue_t q)
{
    return ((q->rear + q->size - q->front) % q->size);
}

//void
//queue_print(queue_t q)
//{
//	int16_t i;
//	for (i = 0; i < queue_length(q); i++)
//        printf("%d\t", q->data[(q->front+i) % q->size]);
//    printf("\n");
//}

void
queue_clear(queue_t q)
{
    q->front = q->rear = 0;
}

void
queue_free(queue_t *qp)
{
    free((*qp)->data);
    free(*qp);
}
