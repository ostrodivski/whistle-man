#include <Management/Queue.h>

/* add an element at the top of the queue */

template <typename T>

void push(Queue<T> **queue, T my_data)
{
	if((*queue) == NULL) 		// !! don't forget to initialize your queue to NULL if you don't want to receive a SEGFAULT
	{
		*queue = new(Queue<T>) ;
		(*queue) -> data = my_data ;
		(*queue) -> next_queue = NULL ;
		(*queue) -> first_queue = *queue ;
	} else {
		Queue<T> *new_queue = new(Queue<T>) ;
		new_queue -> data = my_data ;
		new_queue -> next_queue = NULL ;
		new_queue -> first_queue = (*queue) -> first_queue ; 		// pass the address of the first block to the new block
		(*queue) -> next_queue = new_queue ;			// replace the reference of the current block to the next bloc by the new bloc
		*queue = new_queue ;			// the new block become the current block
	}
}




/* remove the first element of the queue */

template<typename T>
T pop(Queue<T> **queue)
{
	T poped_data = (*queue) -> first_queue -> data ;			// save the content of the first block
	if((*queue) -> first_queue -> next_queue != NULL)			// if there is a block following the current block
	{
		Queue<T> *tmp_queue = (*queue) -> first_queue -> next_queue ;
		delete((*queue) -> first_queue) ;
		(*queue) -> first_queue = tmp_queue ;			// replace the reference of the current block to the former first block by the new first block
									// note : the reference of the non current block to the first block stay inchanged, but actually it's not a problem because we don't need this attribute anymore
	} else {			// if the current block is the last
		*queue = NULL ;
	}
	return(poped_data) ;
}




/* delete the queue */

template<typename T>
void del(Queue<T> **queue)
{
	if((*queue) != NULL)			// if the queue exists already =/
	{
		while((*queue) -> first_queue -> next_queue != NULL)			// while we found a bloc following the current block
		{
			Queue<T> *tmp_queue = (*queue) -> first_queue -> next_queue ;
			delete((*queue) -> first_queue) ;
			(*queue) -> first_queue = tmp_queue ;			// replace the reference of the current block to the former first block by the new first block
		}
		delete(*queue) ;
	}
}
