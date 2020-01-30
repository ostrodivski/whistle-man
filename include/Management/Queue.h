#ifndef QUEUE_H
#define QUEUE_H

/* "first in, first out" */

/* template definition for more flexibility =) */

template<typename T>
struct Queue
{
	T data ;
	struct Queue<T> *next_queue ;			// pointer to the next bloc
	struct Queue<T> *first_queue ;			// pointer to the first bloc
} ;

template<typename T> void push(Queue<T> **queue, T my_data) ;			// add an element at the top of the queue
template<typename T> T pop(Queue<T> **queue) ;			// remove the first element of the queue
template<typename T> void del(Queue<T> **queue) ;				// delete the queue

#include <Management/Queue.tpp>
#endif
