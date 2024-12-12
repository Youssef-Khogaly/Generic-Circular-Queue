# Generic Circular Queue


A versatile, template-based circular queue implemented using a dynamic array. This data structure is capable of storing elements of any data type and supports the following operations:

- Enqueue: Adds an element to the rear of the queue.
- Dequeue: Removes and returns the element from the front of the queue. 
- Qdestroy: Deallocates all memory associated with the queue.
## Basic usage

- Copy data to and from the queue

```c
#include <stdio.h>
#include "CircularQueue.h"

#define MAX_NUMBER_OF_ELEMENTS      (10U)
typedef struct {
    int x;
    float z;
    double y;
    char chars[20];
}passByCopyStruct;
int main()
{
    QueueStatus_t ret_status = Q_NOTOK;
    passByCopyStruct value = {.x = 5 , .y = 20 , .z = 50};
    /*create a queue of 10 elements used to send a copy of the struct*/
    Queue_t* myQueue = Qeueu_inis(sizeof(passByCopyStruct) , MAX_NUMBER_OF_ELEMENTS , &ret_status);
    if(Q_OK == ret_status)
    {
        /*
            Send the entire structure to the queue.
            it will make a copy of the struct "Value"
        */
        ret_status = Enqueue(myQueue , (void*)&value);
    }
    /*receive a message from the queue  , after calling Dequeue function Rx Struct will have a copy from queue message*/
    passByCopyStruct RxStruct;
    ret_status = Dequeue(myQueue , (void*)&RxStruct);
}
```


- Pass memory addresses of data to and from the queue

```c

/*Pass by pointer*/

#include <stdio.h>
#include "CircularQueue.h"

#define MAX_NUMBER_OF_ELEMENTS (10U)
typedef struct
{
    int x;
    float z;
    double y;
    char chars[20];
} passByPointerStruct;
int main()
{
    QueueStatus_t ret_status = Q_NOTOK;
    passByPointerStruct value = {.x = 5, .y = 20, .z = 50};

    /*create a queue of 10 elements each element is a pointer to the struct*/
    Queue_t *myQueue = Qeueu_inis(sizeof(passByPointerStruct *), MAX_NUMBER_OF_ELEMENTS, &ret_status);
    if (Q_OK == ret_status)
    {
        /*
            Send the address of value to the queue
        */
        passByPointerStruct *Pointer_TxStruct = &value;
        ret_status = Enqueue(myQueue, (void *)&Pointer_TxStruct);
    }
    /*Receive a message from the created queue to hold pointers*/
    passByPointerStruct *Pointer_RxStruct;
    ret_status = Dequeue(myQueue, (void *)&Pointer_RxStruct);
}


```
