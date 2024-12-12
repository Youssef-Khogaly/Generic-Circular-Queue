#ifndef _CIRCULARQUEUE_H
#define _CIRCULARQUEUE_H

#include "Types.h"
#define DEBUGG 1

typedef enum
{
    Q_NOTOK,
    Q_OK,
    Q_NULL,
    Q_EMPTY,
    Q_FULL,
    Q_negative
} QueueStatus_t;

typedef struct Queue_t Queue_t;

/**
 * @brief inisalize the Qeueue
 *
 * @param max_size  max size of the queue
 * @param return_val    rked well
 * @return Queue_t* return pointer to the qeueu
 */
Queue_t *Qeueu_inis(uint32_t element_Size, uint32_t max_size, QueueStatus_t *return_val);
/**
 * @brief enqueue element to the queue
 *
 * @param queue_ptr  pointer to the queue
 * @param element element to be enqueue
 * @return QueueStatus_t  return Q_OK if funciton success
 */
QueueStatus_t Enqueue(Queue_t *queue_ptr, const void *element);
/**
 * @brief Dequeue element to the queue
 *
 * @param queue_ptr  pointer to the queue
 * @param pvBuffer void pointer to receive message from the queue
 * @return QueueStatus_t  return Q_OK if funciton success
 */
QueueStatus_t Dequeue(Queue_t *q_ptr, void *pvBuffer);

/*
 * @brief enqueue element to the queue
 *
 * @param queue_ptr  pointer to the queue
 * @param element element to be enqueue
 * @return QueueStatus_t  return 1 if funciton success
 */
QueueStatus_t Qdestroy(Queue_t **ptr);

#endif