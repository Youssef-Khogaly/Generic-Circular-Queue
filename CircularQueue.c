#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularQueue.h"

typedef struct Queue_t
{
    void **queue_obj;
    sint32_t element_count;
    sint32_t front;
    sint32_t rear;
    uint32_t max_size;
    uint32_t elementSize; // each element size on queue in bytes
} Queue_t;

/*Helper functions*/
static QueueStatus_t Qeueu_empty(Queue_t *Q_ptr);
static QueueStatus_t Qeueu_full(Queue_t *Q_ptr);

/**************************************************** */

Queue_t *Qeueu_inis(uint32_t element_Size, uint32_t max_size, QueueStatus_t *return_val)
{

    if (max_size <= 0)
    {
        *return_val = Q_negative;
        return NULL;
    }
    if (NULL == return_val)
    {
        *return_val = Q_NULL;
        return NULL;
    }
    else
    {
        Queue_t *ptr = (Queue_t *)malloc(1U * sizeof(Queue_t));
        if (!ptr)
        {
            *return_val = Q_NULL;
            return NULL;
        }
        else
        {
            ptr->queue_obj = (void **)calloc(max_size, sizeof(void *));
            if (!ptr->queue_obj)
            {
                *return_val = Q_NULL;
                return NULL;
            }

            else
            {
                ptr->front = -1;
                ptr->rear = -1;
                ptr->element_count = 0;
                ptr->max_size = max_size;
                ptr->elementSize = element_Size;
                *return_val = Q_OK;
                return ptr;
            }
        }
    }
}
QueueStatus_t Enqueue(Queue_t *queue_ptr, const void *element)
{
    QueueStatus_t ret = Q_NOTOK;
    void **pvDestination = NULL;
    if (!queue_ptr || !element)
    {
        ret = Q_NULL;
    }
    else
    {
        if (Q_FULL == (Qeueu_full(queue_ptr)))
        {
            ret = Q_FULL;
        }
        else
        {
            /*Handle front and rear*/
            if (Q_EMPTY == (Qeueu_empty(queue_ptr)))
            {
                (queue_ptr->front) += 1;
                (queue_ptr->rear) += 1;
                (queue_ptr->element_count) += 1;
                pvDestination = &(queue_ptr->queue_obj[queue_ptr->front]);
            }
            /* circular queue condition */
            else if (queue_ptr->rear == (queue_ptr->max_size) - 1)
            {
                queue_ptr->rear = 0;
                (queue_ptr->element_count) += 1;
                pvDestination = &(queue_ptr->queue_obj[queue_ptr->rear]);
            }
            else
            {
                (queue_ptr->rear) += 1;
                (queue_ptr->element_count) += 1;
                pvDestination = &(queue_ptr->queue_obj[queue_ptr->rear]);
            }
            /*********/

            /*Copy data to queue*/
            if (*pvDestination == NULL)
            {
                *pvDestination = (void *)malloc(queue_ptr->elementSize);
                printf("1\n");
            }
            if (NULL != *pvDestination)
            {
                memcpy_s(*pvDestination, queue_ptr->elementSize, element, queue_ptr->elementSize);
                ret = Q_OK;
                printf("2\n");
            }
        }
    }
    return ret;
}

QueueStatus_t Dequeue(Queue_t *q_ptr, void *pvBuffer)
{
    QueueStatus_t ret = Q_NOTOK;
    if ((NULL == q_ptr))
    {
        ret = Q_NULL;
        return ret;
    }
    else
    {
        if (Q_EMPTY == (Qeueu_empty(q_ptr)))
        {
            ret = Q_EMPTY;

            return ret;
        }
        else
        {
            memcpy_s(pvBuffer, q_ptr->elementSize, q_ptr->queue_obj[q_ptr->front], q_ptr->elementSize);

            /*  if queue have 1 element  */
            if (q_ptr->element_count == 1)
            {

                q_ptr->front = -1;
                q_ptr->rear = -1;
                --(q_ptr->element_count);
                ret = Q_OK;
                return ret;
            }
            else
            {
                --(q_ptr->element_count);
                (q_ptr->front)++;
                // ciruclar queue condition
                if (q_ptr->front == q_ptr->max_size)
                {
                    q_ptr->front = 0;
                }
                ret = Q_OK;
                return ret;
            }
        }
    }
}

QueueStatus_t Qdestroy(Queue_t **ptr)
{
    QueueStatus_t ret = Q_NOTOK;
    if (NULL == ptr)
    {
        ret = Q_NULL;
        return ret;
    }
    else
    {
        for(int i = 0 ; i < (*ptr)->max_size ; ++i)
        {
            if((*ptr)->queue_obj[i] != NULL)
            {
                free((*ptr)->queue_obj[i]);
                (*ptr)->queue_obj[i] = NULL;
            }   
        }
        free((*ptr)->queue_obj);
        (*ptr)->queue_obj = NULL;
        free(*ptr);
        *ptr = NULL;
        ret = Q_OK;
        return ret;
    }
}

/* Helper functions definitions */
static QueueStatus_t Qeueu_empty(Queue_t *Q_ptr)
{
    QueueStatus_t return_val = Q_NOTOK;
    if (NULL == Q_ptr)
    {
        return_val = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! passing null pointer to Qeueue_empty , ret = %i",
               return_val);
#endif
        return return_val;
    }
    else
    {
        if (Q_ptr->element_count == 0)
        {
            return_val = Q_EMPTY;
            return return_val;
        }
        else
        {
            return_val = Q_OK;
            return return_val;
        }
    }
}
static QueueStatus_t Qeueu_full(Queue_t *Q_ptr)
{
    QueueStatus_t return_val = Q_NOTOK;
    if (NULL == Q_ptr)
    {
        return_val = Q_NULL;
#ifdef DEBUGG
        printf("ERROR!! passing null pointer to Qeueue_empty , ret = %i",
               return_val);
#endif
    }
    else
    {
        if (Q_ptr->element_count == Q_ptr->max_size)
        {
            return_val = Q_FULL;
            return return_val;
        }
        else
        {
            return_val = Q_OK;
            return return_val;
        }
    }
}
